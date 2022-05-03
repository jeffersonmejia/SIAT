//LIBRERIAS A UTILIZAR
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
//*****************************************************************************************************************************************************************
//ESTRUCTURA DE DATOS: PROVINCIA
struct provincia{
	int id;
	char pName[14];
	char pRegion[14];
	char pClima[14];
	char pPais[14];
};
//ESTRUCTURA DE DATOS: SITIO TURISTICO
struct sitio{
	int id;
	char sName[32];
	char sCost[10];
	char sComida[10];
	char sHotel[10];
	char sPiscina[10];
	char sPlaya[10];
	char sRios[10];
	char sVolcanes[10];
};
//NOMBRE DEL EMPLEADO AL INGRESAR
char employee[32];
//FUNCIÓN: LIMPIAR LA PANTALLA
void limpia(void){
	int f, c;
	
	for (f=4; f<=22; f++)
	for (c=22; c<=78; c++){
    	gotoxy(c,f);cprintf(" ");
	}
}
//ITEM 1: PRESENTACION
void showUs(void){
	textcolor(WHITE);
	gotoxy(22,6);  cprintf(" ....................PROYECTO FINAL....................\n");
	gotoxy(22,7);  cprintf(" ---------- Universidad T%ccnica de Manab%c UTM ---------\n\n", 130, 161);
	gotoxy(22,9);  cprintf("           Facultad: Ciencias inform%cticas          \n", 160);
	gotoxy(22,10);  cprintf("          Carrera: Sistemas de informaci%cn          \n", 162);
	gotoxy(22,11);  cprintf("                   Estudiantes:          \n");
	gotoxy(22,12);  cprintf("          -> Jefferson Pa%cl Mej%ca Ch%cvez          \n", 163, 161, 160);
	gotoxy(22,13); cprintf("          -> Williams Johao Castillo Mina          \n");
	gotoxy(22,14); cprintf("        Asignatura: Fundamentos de programaci%cn          \n", 162);
	gotoxy(22,15); cprintf("              Docente: Ing. Gabriel Demera          \n");
	gotoxy(22,16); cprintf("                   Paralelo: A          \n");
	gotoxy(22,17); cprintf("          Peri%cdo lectivo: Oct. 2021 - Feb. 2022          \n", 162);
	gotoxy(22,18); cprintf(" -------------------------------------------------------\n");
	gotoxy(22,19); cprintf("     Presione cualquier tecla para regresar al men%c ", 163); 
	getch();
	limpia();
	textcolor(YELLOW);
}
//FUNCIÓN: INGRESO NUEVOS DATOS
void provinceIn(void){
	
	textcolor(WHITE);	
	FILE *p;
	char r;
	provincia nueva;

	if((p=fopen("prov.txt", "a+b"))==NULL){
		printf("    Algo ha ocurrido... no hemos podido abrir el archivo");
		return;
	}

	limpia();

	//PEDIDO DE DATOS
	gotoxy(24, 7); cprintf("Ingrese ID de provincia: "); 
	scanf("%d", &nueva.id);
	
	fflush(stdin);
	
	gotoxy(24, 8);  cprintf("Ingrese la provincia   : "); gets(nueva.pName);
	gotoxy(24, 9);  cprintf("Ingrese la regi%cn      : ", 162); gets(nueva.pRegion);
	gotoxy(24, 10); cprintf("Ingrese el clima       : "); gets(nueva.pClima);
	gotoxy(24, 11); cprintf("Ingrese el pa%cs        : ", 161); gets(nueva.pPais);
	gotoxy(24, 13);
	
	printf("Desea guardar los cambios si(s)/no(n): ");
	r=getch();
	
	if (r=='s'|| r=='S')
		fwrite(&nueva, sizeof(provincia), 1, p);
		fclose(p);
	limpia();
	textcolor(YELLOW);
}
//FUNCIÓN: MOSTRAR PROVINCIAS
void provinceShow(){ 
	textcolor(WHITE);
	provincia nueva;
	FILE *p;
	
	if ((p = fopen("prov.txt", "r+b"))== NULL){ 
		printf("\tNo se puede abrir el archivo.\n");
		textcolor(YELLOW);
		return;    
	}
  	 
	limpia();
  	
	while(!feof(p)){
		if (fread(&nueva, sizeof(provincia), 1, p)){
	    	gotoxy(24, 5 );cprintf("Provincia ID  : %d\n", nueva.id);
			gotoxy(24, 6 );cprintf("Provincia     : %s\n", nueva.pName);
	    	gotoxy(24, 7 );cprintf("Regi%cn        : %s\n", 162, nueva.pRegion);
	    	gotoxy(24, 8 );cprintf("Clima         : %s\n", nueva.pClima);
	    	gotoxy(24, 9 );cprintf("Pa%cs          : %s\n", 161, nueva.pPais);
	    	gotoxy(24, 11 );cprintf("Presione 'enter' para mostrar m%cs...", 160);
	    	getch();
			limpia();
		}
	}
	fclose(p);
	limpia();
	textcolor(YELLOW);
}
//*********************************************************************
//FUNCIÓN: Ingreso de atractivos turísticos

void attractiveIn(void){ 
	
	FILE *p;
	char r;
	int f,i,pid,x;
	sitio nuevo;
	
	//para recuperar el listado de provincias y ponerlo en un vector
	provincia aux, listado[100];
	
	if ((p = fopen("prov.txt", "a+b"))== NULL){
		printf("No se puede abrir el archivo.\n");
		return;
	}
	//proceso de llenar los provincias en un vector
	rewind(p); i=0;
	while(!feof(p) && i < 100){ 
		if(fread(&aux, sizeof(provincia), 1, p)){
			listado[i]=aux;
			i++;
		}
	}
  
	fclose(p); textcolor(WHITE); limpia();
	//proceso de mostrar la lista de provincias
	do{
    	limpia();f=5;
    	for(x=0;x<i;x++){
		gotoxy(24,f);
		cprintf("<%4d> - %s, %s",listado[x].id,listado[x].pName,listado[x].pPais);
		f++;
		if(f==21){
		f=5;
	    gotoxy(24,21);
	    cprintf("Presione una tecla para ver el resto de provincias");
	    getch();limpia();
		}
    }
    
    fflush(stdin);gotoxy(24,22); cprintf("Ingrese el ID: "); scanf("%d",&pid);
    
	//proceso de localizacion 
f=-1;
    for(x=0; x<i && f==-1 ;x++){
       if(pid==listado[x].id)f=x;
    }
    //en caso de no existir
    if(f==-1){ gotoxy(22,22);
	       cprintf("ID no encontrado");
	       getch();}
  }while(f==-1);

	if ((p = fopen("at.txt", "a+b"))== NULL){
		printf("No se puede abrir el archivo.\n");
	return;
    } 
	  limpia();
	  gotoxy(24,5 ); cprintf("ID       : %d",listado[f].id);
	  nuevo.id=listado[f].id; 
	  gotoxy(24,6 ); cprintf("Provincia: %s",listado[f].pName);
	  gotoxy(24,7 ); cprintf("Regi%cn   : %s", 162, listado[f].pRegion);
	  gotoxy(24,8 ); cprintf("Clima    : %s",listado[f].pClima);
	  gotoxy(24,9 ); cprintf("Pa%cs     : %s", 161,listado[f].pPais);
	  fflush(stdin);//
	  gotoxy(24,11 );cprintf("Ingrese el atractivo    : "); gets(nuevo.sName);
	  gotoxy(24,12); cprintf("Ingrese el costo        : $");  gets(nuevo.sCost);
	  gotoxy(24,13); cprintf("Ingrese comida(si/no)   : ");  gets(nuevo.sComida);
	  gotoxy(24,14); cprintf("Ingrese hotel(si/no)    : ");  gets(nuevo.sHotel);
	  gotoxy(24,15); cprintf("Ingrese piscina(si/no)  : ");  gets(nuevo.sPiscina);
	  gotoxy(24,16); cprintf("Ingrese playa(si/no)    : ");  gets(nuevo.sPlaya);
	  gotoxy(24,17); cprintf("Ingrese rios(si/no)     : ");  gets(nuevo.sRios);
	  gotoxy(24,18); cprintf("Ingrese volcanes(si/no) : ");  gets(nuevo.sVolcanes);
	  gotoxy(24,20);
	  printf("Desea guardarlo Si(s)/No(n):");  r=getch();
	  if (r=='s'|| r=='S') fwrite(&nuevo, sizeof(sitio), 1, p);
	  fclose(p);
 	  textcolor(YELLOW);
	  limpia();
}

void attractiveShow(void){
	
	textcolor(WHITE);
	FILE *p;
	char r;
	int f,i,pid,x;
	sitio nuevo;
	
	provincia aux, listado[100];
	if ((p = fopen("prov.txt", "a+b"))== NULL){
		printf("No se puede abrir el archivo.\n");
		return;
    }
	//proceso de llenar los provincias en un vector
	rewind(p); i=0;
	while(!feof(p) && i < 100){
		if(fread(&aux, sizeof(provincia), 1, p)){
			listado[i]=aux;
			i++;
		}
	}
	fclose(p); 
	limpia();
	//proceso de mostrar la lista de provincias
	do{
		limpia();f=5;
    	for(x=0;x<i;x++){
			gotoxy(24,f);
			cprintf("<%4d> - %s, %s",listado[x].id,listado[x].pName,listado[x].pPais);
			f++;
			
			if(f==21){
			f=3;
			gotoxy(24,21);
			cprintf("Presione una tecla para ver el resto de provincias");
			getch();
			limpia();
			}
		}
	
		fflush(stdin);gotoxy(24,22); cprintf("Ingrese el ID: "); scanf("%d",&pid);
    	//proceso de localizacion de provincia
    	f=-1;
    	for(x=0; x<i && f==-1 ;x++){
    		if(pid==listado[x].id)f=x;
    	}
    
		//en caso de no existir
    	if(f==-1){ gotoxy(24,22);
	    	cprintf("ID no encontrado");
			getch();}
  		}
	while(f==-1);

	if ((p = fopen("at.txt", "a+b"))== NULL){
		printf("No se puede abrir el archivo.\n");
		return;
	}
  	x=1;
  	
	while(!feof(p)){
   		if (fread(&nuevo, sizeof(sitio), 1, p) && listado[f].id==nuevo.id) {
		limpia();
		gotoxy(24,5 ); cprintf("Provincia ID  : %d",listado[f].id);
		gotoxy(24,6 ); cprintf("Provincia     : %s",listado[f].pName);
		gotoxy(24,7 ); cprintf("Regi%cn        : %s", 162 ,listado[f].pRegion);
		gotoxy(24,8 ); cprintf("Pa%cs          : %s", 161 ,listado[f].pPais);
		gotoxy(24,9 ); cprintf("Clima         : %s",listado[f].pClima);
		gotoxy(24,11 ); cprintf("<<< N%cmero de provincia: %d >>>", 163, x++);
		gotoxy(24,12 ); cprintf("Atractivo   : %s",nuevo.sName);
		gotoxy(24,13); cprintf("Costo       : $%s",nuevo.sCost);
		gotoxy(24,14); cprintf("Comida      : %s",nuevo.sComida);
		gotoxy(24,15); cprintf("Hotel       : %s",nuevo.sHotel);
		gotoxy(24,16); cprintf("Piscina     : %s",nuevo.sPiscina);
		gotoxy(24,17); cprintf("Playa       : %s",nuevo.sPlaya);
		gotoxy(24,18); cprintf("Rios        : %s",nuevo.sRios);
		gotoxy(24,19); cprintf("Volcanes    : %s",nuevo.sVolcanes);										
		gotoxy(24,21);cprintf("Presione 'enter' para continuar...");
		getch();
		}
	}
		fclose(p);
		limpia();
		textcolor(YELLOW);
}


void provinceUp(void){ 
	textcolor(WHITE);
	provincia nueva, lista[100];
	
	int pid,f,x;
	int linea,i;
	char r;
	
	FILE *p;
	
	if ((p = fopen("prov.txt", "a+b"))== NULL){
		printf("No se puede abrir el archivo.\n");
		return;
    }
	//proceso de llenar el vector para la actulización
	rewind(p); i=0;
	while(!feof(p)){
    	if(fread(&nueva, sizeof(provincia), 1, p)){
			lista[i]=nueva;
			i++;
		}
	}
	fclose(p);
  	//proceso de mostrar la lista de provincias para escoger al que desea actualizar
  	do{
    	limpia();f=5;
    	
		for(x=0;x<i;x++){
			gotoxy(24,f);
			cprintf("<%4d > - %s, %s",lista[x].id,lista[x].pName,lista[x].pPais);
			f++;
			if(f==21){
			f=5;
			gotoxy(24,21);
			cprintf("Presione una tecla para ver el resto de provincias");
			getch();
			limpia();
			}
    	}
    	fflush(stdin);
    	gotoxy(24,22);
		cprintf("Ingrese el ID: "); 
		scanf("%d",&pid);
    	//proceso de localizacion 
    	f=-1;
    	for(x=0; x<i && f==-1 ;x++){
    		if(pid==lista[x].id)f=x;
    	}
    	//en caso de no existir
    	if(f==-1){ gotoxy(24,22);
	       cprintf("ID no encontrado");
	       getch();
		}
	}while(f==-1);
	//Proceso de actualización de datos 
	do {
		limpia();
    	gotoxy(24,5 );cprintf("1. ID                : %d\n",lista[f].id);
    	gotoxy(24,6 );cprintf("2. Provincia         : %s\n",lista[f].pName);
	    gotoxy(24,7 );cprintf("3. Regi%cn            : %s\n", 162, lista[f].pRegion);
	    gotoxy(24,8 );cprintf("4. Clima             : %s\n",lista[f].pClima);
	    gotoxy(24,9 );cprintf("5. Pa%cs              : %s\n", 161, lista[f].pPais);
	    gotoxy(24,11);cprintf("Escriba la l%cnea a actualizar: ", 161);
    	do{
    		linea=getch();
    	}while(linea<49 || linea>57);
    	fflush(stdin);
    	switch(linea-48){
	    	case 1: gotoxy(24,5 );cprintf("                              ");
		    	gotoxy(24,5 );
		    	cprintf("1. Ingrese el ID     : ");scanf("%d",&lista[f].id);
		    	break;
		    case 2: gotoxy(24,6 );cprintf("                                 ");
			    gotoxy(24,6 );
			    cprintf("2. Ingrese provincia : "); gets(lista[f].pName);
			    break;
		    case 3: gotoxy(24,7 );cprintf("                                 ");
			    gotoxy(24,7 );
			    cprintf("3. Ingrese regi%cn    : ", 162); gets(lista[f].pRegion);
			    break;
		    case 4: gotoxy(24,8 );cprintf("                                 ");
			    gotoxy(24, 8 );
			    cprintf("4. Ingrese clima     : "); gets(lista[f].pClima);
			    break;
			case 5: gotoxy(24,9 );cprintf("                                 ");
			    gotoxy(24, 9 );
			    cprintf("5. Ingrese el pa%s     : "); gets(lista[f].pPais);
			    break;    
		}
	    gotoxy(24,13);cprintf("Si desea actualizar otro dato");
	    gotoxy(24,14);cprintf("Presione s(s%c)/n(no): ", 161);
	    r=getch();
	  }while (r!='n' && r!='N');
	// Proceso de guardar los datos actualizados
	// primero abre el archivo para sobrescribir
	if ((p = fopen("prov.txt", "wb"))== NULL){
		printf("No se puede abrir el archivo.\n");
		return;
	}
	
	//segundo guarda uno a uno los registros actualizados del vector
	for(x=0;x<i;x++){
		fwrite(&lista[x], sizeof(provincia), 1, p);
	}
	textcolor(LIGHTCYAN);
	gotoxy(24,15);cprintf("Datos Actualizados");
	gotoxy(24,16);cprintf("Presione una tecla para continuar... ");
	getch();limpia();
	fclose(p);
	textcolor(YELLOW);
}
//EDITAR
void attractiveUp(void){
	
	provincia nueva, lista[100];
	sitio aux, listaV[100];
	
	int pid,f,x,hayCambios=0;
	int linea,i,j;
	char r;
	
	FILE *p;
	
	if ((p = fopen("prov.txt", "a+b"))== NULL){
		printf("No se puede abrir el archivo.\n");
		return;
    }
	
	//proceso de llenar el vector de provincias
	rewind(p); i=0;
	while(!feof(p)){
    	if(fread(&nueva, sizeof(provincia), 1, p)){
			lista[i]=nueva;
			i++;
		}
  	}
  	fclose(p);
  	textcolor(WHITE);
  	//proceso de mostrar la lista de provicinas para escoger al que desea buscar ID
  	do{
    	limpia();f=5;
    	for(x=0;x<i;x++){
			gotoxy(24,f);
			cprintf("<%4d> - %s %s",lista[x].id,lista[x].pName,lista[x].pPais);
			f++;
			
			if(f==21){
			    f=3;
		    	gotoxy(24,21);
		    	cprintf("Presione 'enter' para ver el resto de provincias");
		    	getch();limpia();
			}
    	}
    	fflush(stdin);
    	gotoxy(24,22); cprintf("Ingrese el ID: "); scanf("%d",&pid);
    	//proceso de localizacion 
    	f=-1;
    	for(x=0; x<i && f==-1 ;x++){
       		if(pid==lista[x].id)f=x;
    	}
    	//en caso de no existir
    	if(f==-1){ 
			gotoxy(24,22);
	    	cprintf("ID no encontrado");
			getch();
		}
	}while(f==-1);
   
  //proceso de mostrar la lista de atractivos
  	if ((p = fopen("at.txt", "a+b"))== NULL){
		printf("No se puede abrir el archivo.\n");
		return;
    }
	//proceso de llenar el vector de atractivos
	rewind(p); j=0;
	while(!feof(p)){
    	if(fread(&aux, sizeof(sitio), 1, p)){
			listaV[j]=aux;
			j++;
		}
 	}
	fclose(p);
	//proceso de mostrar la lista de provincias para escoger al que desea actualizar
  
	limpia();
	for(x=0;x<j;x++){
		if(lista[f].id==listaV[x].id){
        //Proceso de actualización de datos 
        limpia();
        gotoxy(24,5 );cprintf("1. ID                  : %d\n",listaV[x].id);
        gotoxy(24,6 );cprintf("2. Atractivo           : %s\n",listaV[x].sName);
        gotoxy(24,7 );cprintf("3. Costo               : %s\n",listaV[x].sCost);
        gotoxy(24,7 );cprintf("4. Comida              : %s\n",listaV[x].sCost);
        gotoxy(24,7 );cprintf("5. Hotel               : %s\n",listaV[x].sCost);
        gotoxy(24,7 );cprintf("6. Piscina             : %s\n",listaV[x].sCost);
        gotoxy(24,7 );cprintf("7. Playa               : %s\n",listaV[x].sCost);
        gotoxy(24,7 );cprintf("8. Rios                : %s\n",listaV[x].sCost);
        gotoxy(24,7 );cprintf("9. Volcanes            : %s\n",listaV[x].sCost);
        gotoxy(24,12);cprintf("Si desea actualizar el registro");
	    gotoxy(24,13);cprintf("Presione s(s%c)/n(no): ", 161);
        do{
        	r=getch();
        }while(r!='n' && r!='N' && r!='s' && r!='S');
        
		if(r=='s' || r=='S'){
        	hayCambios=1;
        	do{
            	gotoxy(24,14);cprintf("Escriba la l%cnea a actualizar", 161);
            	do{
                	linea=getch();
             	}while(linea<49 || linea>55);
            	fflush(stdin);
             	switch(linea-48){
	                case 1: gotoxy(24,5 );cprintf("                              ");
		                gotoxy(24,5 );
		                cprintf("1. Ingrese el ID       : ");scanf("%d",&listaV[x].id);
		                break;
	                case 2: gotoxy(24,6 );cprintf("                                    ");
		                gotoxy(24,6 );
		                cprintf("2. Ingrese el atractivo: "); gets(listaV[x].sName);
		                break;
	                case 3: gotoxy(24,7 );cprintf("                                     ");
		                gotoxy(24,7 );
		                cprintf("3. Ingrese el costo    : "); gets(listaV[x].sCost);
		                break;
                    
                    case 4: gotoxy(24,8 );cprintf("                                     ");
		                gotoxy(24,8 );
		                cprintf("3. Ingrese el comida    : "); gets(listaV[x].sComida);
		                break;
                
                    case 5: gotoxy(24,9 );cprintf("                                     ");
		                gotoxy(24,9 );
		                cprintf("3. Ingrese el hotel    : "); gets(listaV[x].sHotel);
		                break;
                    case 6: gotoxy(24,10 );cprintf("                                     ");
		                gotoxy(24,10 );
		                cprintf("3. Ingrese el piscina  : "); gets(listaV[x].sPiscina);
		                break;
                    case 7: gotoxy(24,11 );cprintf("                                     ");
		                gotoxy(24,11 );
		                cprintf("3. Ingrese el playa    : "); gets(listaV[x].sPlaya);
		                break;
                    case 8: gotoxy(24,12 );cprintf("                                     ");
		                gotoxy(24,12 );
		                cprintf("3. Ingrese el rios     : "); gets(listaV[x].sRios);
		                break;
                    
                    case 9: gotoxy(24,13 );cprintf("                                     ");
		                gotoxy(24,13 );
		                cprintf("3. Ingrese el volcanes : "); gets(listaV[x].sVolcanes);
		                break;
                    }
                    	gotoxy(24,15);cprintf("Si desea continuar actualizando");
	    				gotoxy(24,16);cprintf("presione s(s%c)/n(no): ", 161);
                do{
                  r=getch();
                }while(r!='n' && r!='N' && r!='s' && r!='S');
            }while (r!='n' && r!='N');
         }
      }
  }
	if(hayCambios){
    	// primero abre el archivo para sobrescribir
        if((p = fopen("at.txt", "wb"))== NULL){
		printf("No se puede abrir el archivo.\n");
            return;
        }
        //segundo guarda uno a uno los registros actualizados del vector
        for(x=0;x<j;x++){
			fwrite(&listaV[x], sizeof(sitio), 1, p);
        }
        textcolor(LIGHTCYAN);
		gotoxy(24,15);cprintf("Datos Actualizados");
		gotoxy(24,16);cprintf("Presione una tecla para continuar... ");
		getch();
		fclose(p);
	}
	textcolor(YELLOW);
	limpia();
}


void provinceDel(void){
	
	provincia nueva, lista[100];
	sitio aux, listaV[100];
	
	int pid,f,x;
	int k,i,j;
	char r;
	FILE *p;
	
	textcolor(WHITE);
	
	if ((p = fopen("prov.txt", "a+b"))== NULL){
		printf("No se puede abrir el archivo.\n");
		return;
    }
	//proceso de llenar el vector para la eliminación
	rewind(p); i=0;
	while(!feof(p)){
    	if(fread(&nueva, sizeof(provincia), 1, p)){
		lista[i]=nueva;
		i++;
		}
	}
	fclose(p);
	//proceso de extraer la lista de atractivos 
	if ((p = fopen("at.txt", "a+b"))== NULL){
		printf("No se puede abrir el archivo.\n");
		return;
    }
  	//proceso de llenar el vector de atractivos
  	rewind(p); j=0;
  	while(!feof(p)){
    	if(fread(&aux, sizeof(sitio), 1, p)){
			listaV[j]=aux;
			j++;
		}
	}
	fclose(p);
	//proceso de mostrar la lista de provincias para escoger al que desea eliminar
	do{
    	limpia();f=5;
    	for(x=0;x<i;x++){
			gotoxy(24,f);
			cprintf("<%4d> - %s, %s",lista[x].id,lista[x].pName,lista[x].pPais);
			f++;
			if(f==21){
		    	f=5;
		    	gotoxy(24,21);
		    	cprintf("Presione una tecla para ver el resto de provincias");
		    	getch();limpia();
			}
    	}
    	fflush(stdin);
    	gotoxy(24,22); cprintf("Ingrese el ID: "); 
		scanf("%d",&pid);
    	//proceso de localizacion 
    	f=-1;
    	for(x=0; x<i && f==-1 ;x++){
       		if(pid==lista[x].id)f=x;
    	}
    	//en caso de no existir
    	if(f==-1){ gotoxy(24,22);
	       cprintf("ID no encontrado");
	       getch();}
	}while(f==-1);
 	 //Proceso de Eliminación 
  	limpia();
	gotoxy(24,5 );cprintf("ID           : %d\n",lista[f].id);
	gotoxy(24,6 );cprintf("Provincia    : %s\n",lista[f].pName);
	gotoxy(24,7 );cprintf("Regi%cn       : %s\n", 162, lista[f].pRegion);
	gotoxy(24,8 );cprintf("Clima        : %s\n",lista[f].pClima);
	gotoxy(24,9 );cprintf("Pa%cs          : %s\n",161, lista[f].pClima);
	gotoxy(24,14); printf("Desea Eliminarlo Si(s)/No(n):");
	do{
    	r=getch();
    }while(r!='n' && r!='N' && r!='s' && r!='S');
  	if (r=='s' || r=='S'){
		//eliminación del registro del vector de provincias 
		lista[f].id=-1;
        // primero abre el archivo para sobrescribir
        if ((p = fopen("prov.txt", "wb"))== NULL){
			printf("No se puede abrir el archivo.\n");
	    	return;
        }
        //segundo guarda uno a uno los registros del vector
        for(x=0;x<i;x++){
        	if(lista[x].id!=-1) fwrite(&lista[x], sizeof(provincia), 1, p);
        }
		fclose(p);
        //eliminación de atractivos
		for(x=0;x<j;x++){
        	if(listaV[x].id==pid)
	          listaV[x].id=-1;
		}
		//Proceso de guardar las atractivos
        if ((p = fopen("at.txt", "wb"))== NULL){
			printf("No se puede abrir el archivo.\n");
	    	return;
        }
        //segundo guarda uno a uno los registros del vector de  atractivos
        for(x=0;x<j;x++){
        	if(listaV[x].id!=-1) fwrite(&listaV[x], sizeof(sitio), 1, p);
        }
        fclose(p);
        textcolor(RED);
        gotoxy(24,15);cprintf("Datos eliminados, presione una tecla para continuar... ");
        getch();
		limpia();
        fclose(p);
        textcolor(YELLOW);
     }
}

void attractiveDel(void){ 
	textcolor(WHITE);
	provincia nueva, lista[100];
	sitio aux, listaV[100];
	
	int pid,f,x,hayEliminacion=0;
	int linea,i,j;
	char r;
  	
	FILE *p;
  
	if ((p = fopen("prov.txt", "a+b"))== NULL){
		printf("No se puede abrir el archivo.\n");
		return;
    }
	//proceso de llenar el vector de provincias
	rewind(p); i=0;
	while(!feof(p)){
    	if(fread(&nueva, sizeof(provincia), 1, p)){
			lista[i]=nueva;
			i++;
		}
	}
	fclose(p);
	//proceso de mostrar la lista de provincias para escoger al que desea buscar ID
	do{
    	limpia();f=5;
    	
		for(x=0;x<i;x++){
			gotoxy(24,f);
			cprintf("<%4d> - %s, %s",lista[x].id,lista[x].pName,lista[x].pPais);
			f++;
			if(f==21){
	    		f=5;
	    		gotoxy(24,21);
	    		cprintf("Presione una tecla para ver el resto de provincias");
	    		getch();
				limpia();
			}
    	}
    	fflush(stdin);
    	gotoxy(24,22); cprintf("Ingrese ID: "); 
		scanf("%d",&pid);
    	//proceso de localizacion 
    	f=-1;
    	for(x=0; x<i && f==-1 ;x++){
    		if(pid==lista[x].id)
				f=x;
    	}
    	//en caso de no existir
    	if(f==-1){ gotoxy(24,22);
	    cprintf("ID no encontrado");
	    getch();}
	}while(f==-1);
   
	//proceso de mostrar la lista de atractivos  seleccionado
	if ((p = fopen("at.txt", "a+b"))== NULL){
		printf("No se puede abrir el archivo.\n");
		return;
    }
	//proceso de llenar el vector de atractivos
	rewind(p); j=0;
	while(!feof(p)){
    	if(fread(&aux, sizeof(sitio), 1, p)){
			listaV[j]=aux;
			j++;
			}
	}
	fclose(p);
	//proceso de mostrar la lista de provincias para escoger al que desea eliminar
	limpia();
	for(x=0;x<j;x++){
		if(lista[f].id==listaV[x].id){
	        //Proceso de eliminación de datos de la provincia médica 
	        limpia();
	        gotoxy(24,5 ); cprintf("ID              : %d\n",listaV[x].id);
	        gotoxy(24,6 ); cprintf("Atractivo       : %s\n",listaV[x].sName);
	        gotoxy(24,7 ); cprintf("Costo           : $%s\n",listaV[x].sCost);
	        gotoxy(24,8 ); cprintf("Comida          : %s\n",listaV[x].sComida);
	        gotoxy(24,9 ); cprintf("Hotel           : %s\n",listaV[x].sHotel);
	        gotoxy(24,10 );cprintf("Piscina         : %s\n",listaV[x].sPiscina);
	        gotoxy(24,11 );cprintf("Playa           : %s\n",listaV[x].sPlaya);
	        gotoxy(24,12 );cprintf("Rios            : %s\n",listaV[x].sRios);
	        gotoxy(24,13 );cprintf("Volcanes        : %s\n",listaV[x].sVolcanes);
	        gotoxy(24,15);cprintf("Si desea eliminar este registro");
	        gotoxy(24, 16);cprintf("Presione si(s) o no(n)", 161);
	        do{
	         r=getch();
	        }while(r!='n' && r!='N' && r!='s' && r!='S');
	        if(r=='s' || r=='S'){
				listaV[x].id=-1;
				hayEliminacion=1;
			}
    	}
  	}
  	if (hayEliminacion){
        // primero abre el archivo para sobrescribir
        if ((p = fopen("at.txt", "wb"))== NULL){
			printf("No se puede abrir el archivo.\n");
            return;
        }
        //segundo guarda uno a uno los registros actualizados del vector
        for(x=0;x<j;x++){ 
			if(listaV[x].id!=-1) fwrite(&listaV[x], sizeof(sitio), 1, p);
        }
		textcolor(RED);           
        gotoxy(24,17);cprintf("Datos Eliminados, presione una tecla para continuar... ");
		getch();
		fclose(p);
	}
	textcolor(YELLOW);
	limpia();
}

void divscreen(int cs, int fs, int ci, int fi){
	int i;
	
	for (i=cs;i<=ci;i++){
    	gotoxy(i,fs);cprintf("Í");
    	gotoxy(i,fi);cprintf("Í");
	}
	
	for (i=fs;i<=fi;i++){
    	gotoxy(cs,i);cprintf("º");
    	gotoxy(ci,i);cprintf("º");
	}

	gotoxy(cs,fs);cprintf("É");
	gotoxy(ci,fs);cprintf("»");
	gotoxy(cs,fi);cprintf("È");
	gotoxy(ci,fi);cprintf("¼");
}

void start(){
	int tecla,
		fil=4, 
		i, 
		indice=0;
	
	char name[32];
	
	char menu[10][25]={"Presentacion      ",
					"Ing. Provincia    ",
                    "Ing. Atractivo    ",
                    "Mostrar Provincia ",
                    "Mostrar Atractivo ",
                    "Act. Provincia    ",
                    "Act. Atractivo    ",
                    "Eli. Provincia    ",
                    "Eli. Atractivo    ",
                    "Salir             "};
                    
	textbackground(0);
	
	//PROCESO: OBTENER HORA LOCAL
	time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char output[128];
        strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
	
	//PROCESO: MOSTRAR NOMBRE DEL USUARIO/EMPLEADO INGRESADO
	textcolor(WHITE);
	gotoxy(1, 1); cprintf(" Sesi%cn iniciada como: ", 162);
	textcolor(LIGHTGREEN);
	cprintf("Ing. %s ", employee);
	textcolor(YELLOW);
	//PROCESO DE MOSTRAR UBICACION, FECHA Y HORA
	gotoxy(47, 1); strftime(output,128,"%d/%m/%y - %H:%M:%S",tlocal); printf("Portoviejo, %s\n",output);
	
	gotoxy(67, 25); cprintf("    SIAT UTM");
	textcolor(YELLOW);
	
	  for (i=0;i<10;i++){
		gotoxy(2,fil);
		cprintf("%s",menu[i]);
		fil++;
	}
	fil=4;i=1;
   
   	do{
    	do{
		
		_setcursortype(_NOCURSOR);
		textbackground(GREEN);

		divscreen(1,3,20,24);
		divscreen(21,3,80,24);
		
		gotoxy(2,fil);
		cprintf("%s",menu[indice]);
		tecla=getch();
    	}while(tecla!=72 && tecla != 80 && tecla!=13);
    	
		textbackground(BLACK);
    	gotoxy(2,fil);cprintf("%s",menu[indice]);
    	
		switch(tecla){
    		case 80: 
				if (indice==9){
					fil=4;indice=0;
				}else{
					fil++;indice++;
				}
	    		break;
	    		
			case 72: 
				if (indice==0)
					{
						fil=12;indice=8;
					}else{
						fil--;indice--;
					}
					break;
    	
			case 13:
				_setcursortype(_NORMALCURSOR);
				if (indice==0) showUs();
				if (indice==1) provinceIn();
				if (indice==2) attractiveIn();
				if (indice==3) provinceShow();
				if (indice==4) attractiveShow();
				if (indice==5) provinceUp();
				if (indice==6) attractiveUp();
				if (indice==7) provinceDel();
				if (indice==8) attractiveDel();
				if (indice==9) i=0;
		}
   }while(i);
   
}

//MENSAJE DE BIENVENIDA Y PEDIDO DE NOMBRE DE EMPLEADO
void welcome(void){
	
	int f, c, success = 0;
	textcolor(YELLOW);
	
	gotoxy(13,12);
	cprintf(">> Bienvenido/a al sistema de atractivos tur%csticos SIAT <<", 161);
	
	gotoxy(13,13);
	cprintf("   Ingrese su nombre para continuar: ");	
	gets(employee);
			
	gotoxy(13,14);
	cprintf("   Ok, %s, presione cualquier tecla para continuar", employee);
	getch();
	for (f=0; f<=22; f++)
	for (c=0; c<=78; c++){
    	gotoxy(c,f);cprintf(" ");
	}
	start();
}


//FUNCION PRINCIPAL
void main(){
	clrscr();
	welcome();
}
