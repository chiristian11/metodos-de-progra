#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//funcion para agregar los logs a cada accion del programa
void logs(char *accion){
	time_t tiempoActual;
	struct tm *infotiempo;
	time(&tiempoActual);
	infotiempo = localtime(&tiempoActual);
	
	char filename[1000];
	snprintf(filename,sizeof (filename),"%04d%02d%02d_%02d%02d.txt",infotiempo->tm_year + 1900,infotiempo->tm_mon + 1,infotiempo->tm_mday,infotiempo->tm_hour,infotiempo->tm_min);
	FILE *file = fopen(filename,"a");
	fprintf(file,"[%04d-%02d-%02d %02d:%02d] %s\n",infotiempo->tm_year + 1900,infotiempo->tm_mon + 1,infotiempo->tm_mday,infotiempo->tm_hour,infotiempo->tm_min,accion);
	fclose(file);
}
//funcion para reemplazar cada parte del interfaz

void actualizar_matriz(int **mapa, int **minimap, int fila, int columna){
	FILE *archivo = fopen("interfaz.txt","a");
	int aux = columna - 3;
	fila = fila - 3;
	for(int i = 0;i < 7; i++){
		columna = aux;
		for(int j=0; j < 7; j++){
			columna = aux;
			if(fila < 0 || fila > 49 || columna < 0 || columna > 49){
				minimap[i][j] = -3;
			}
			else{
				fprintf(archivo,"%d",minimap[i][j]);
			}if (j < columna - 1){
			fprintf(archivo, ".png,");
			}
			columna = columna + 1;
		}
		fila = fila + 1;
		fprintf(archivo, "\n");
	}


	fclose(archivo);
	return;
}
//

// Definiciones de estructuras
typedef struct {
	int salud;
	int salud_maxima;
	int movimientos;
	int arma1;
	int arma2;
	int municion;
	// Otras propiedades del personaje
} personaje;

typedef struct {
	int balas;
	int agravio;
	int balas_maxima;  //el cargador se va a 0 si se elige disparar 1 vez
} arma;

typedef struct {
	int agravio;
	int cura;
	int cantidad;
	int movilidad;
} objeto;

// Funciones
void ya(int i){
	// funcion que indica que el programa paso por aqui
	printf("Llegue %d\n",i);
	return;
}

void salto(int n){
	// crea n saltos de lineas
	for(int i = 0; i < n + 1; i++){
		printf("\n");
	}
	return;
}

void liberar_memoria_n(int **matriz,int fila){
	// libera la memoria de una matriz de numeros
	for(int i = 0; i < fila; i++){
		free(matriz[i]);
	}
	free(matriz);
	return;
}

void liberar_memoria_c(char **matriz,int fila){
	// libera la memoria de una matriz de caracteres
	for(int i = 0; i < fila; i++){
		free(matriz[i]);
	}
	free(matriz);
	return;
}

int** mapa_num(int fila,int columna){
	// crea una matriz de numeros con todos los valores reiniciados
	int **mapa;
	mapa = (int **)malloc(fila*sizeof(int *));
	for(int i=0;i < fila;i++){
		int *dfila;
		dfila = (int*)malloc(columna *sizeof(int));
		for(int j = 0;j < columna;j++){
			dfila[j] = 0;
		}
		mapa[i] = dfila;
	}
	return mapa;
}

void mostrar(int *arreglo,int cantidad){
	//muestra los elementos de un arreglo numeros
	for(int i=0;i < cantidad;i++){
		printf("%d ",arreglo[i]);
	}
	return;
}

void mostrar_sub_num(int **arreglo, int cantidad){
	//muestra los sub-elementos de un arreglo de arreglos de numeros
	for(int i=0;i < cantidad;i++){
		mostrar(arreglo[i], cantidad);
	}
	return;
}

void mostrar_forma_tabla_n(int **arreglo,int fila,int columna){
	// muestra numeros de una matriz en forma de matriz
	int *r_fila;
	for(int i=1; i<fila + 1; i++){
		r_fila = arreglo[i-1];
		for(int j=0; j < columna; j++){
			printf("%d ",r_fila[j]);
		}
		printf("\n\n");
	}
	return;
}

char** mapabase(int fila,int columna){
	// crea una matriz de caracteres con todos los valores reiniciados
	char **mapa;
	mapa = (char **)malloc(fila*sizeof(char *));
	for(int i=0;i < fila;i++){
		char *fila;
		fila = (char*)malloc(columna *sizeof(char));
		for(int j = 0;j < columna;j++){
			fila[j] = 0;
		}
		mapa[i] = fila;
	}
	return mapa;
}

void mostrar_c(char* arreglo,int cantidad){
	//muestra los elementos de un arreglo caracteres
	for(int i=0;i < cantidad;i++){
		printf("%c ",arreglo[i]);
	}
	return;
}

void mostrar_sub_cha(char **arreglo, int fila, int columna){
	//muestra los sub-elementos de un arreglo de arreglos de caracteres
	for(int j=0;j < fila;j++){
		mostrar_c(arreglo[j], columna);
	}
	return;
}

void mostrar_forma_tabla_c(char **arreglo,int fila,int columna){
	// muestra caracteres de una matriz en forma de matriz
	char *r_fila;
	for(int i=1; i<fila + 1; i++){
		r_fila = arreglo[i-1];
		for(int j=0; j < columna; j++){
			printf("%c ",r_fila[j]);
		}
		printf("\n\n");
	}
	return;
}

void dificultad_medio(char **mapa,int tipo,char letra,char letra2){
	int n;
	n = rand() % 4 + 1;
	switch(tipo){
		case 1:
		switch(n){
			case 1:
			mapa[1][14] = letra;
			mapa[43][43] = letra2;
			break;
			case 2:
			mapa[19][3] = letra;
			mapa[21][41] = letra2;
			break;
			case 3:
			mapa[1][45] = letra;
			mapa[30][12] = letra2;
			break;
			default:
			mapa[8][29] = letra;
			mapa[38][25] = letra2;
		}
		break;
		case 2:
		switch(n){
			case 1:
			mapa[42][19] = letra;
			mapa[2][40] = letra2;
			break;
			case 2:
			mapa[18][6] = letra;
			mapa[36][33] = letra2;
			break;
			case 3:
			mapa[18][41] = letra;
			mapa[32][9] = letra2;
			break;
			default:
			mapa[2][11] = letra;
			mapa[46][46] = letra2;
		}
		break;
		default:
		switch(n){
			case 1:
			mapa[47][37] = letra;
			mapa[2][2] = letra2;
			break;
			case 2:
			mapa[16][7] = letra;
			mapa[26][45] = letra2;
			break;
			case 3:
			mapa[1][39] = letra;
			mapa[36][21] = letra2;
			break;
			default:
			mapa[3][28] = letra;
			mapa[46][13] = letra2;
		}
		break;
	}
	return;
}

void dificultad_dificil(char **mapa,int tipo,char letra,char letra2,char letra3){
	int n;
	n = rand() % 3 + 1;
	switch(tipo){
		case 1:
		switch(n){
			case 1:
			mapa[1][45] = letra;
			mapa[30][12] = letra2;
			mapa[30][27] = letra3;
			break;
			case 2:
			mapa[1][14] = letra;
			mapa[21][41] = letra2;
			mapa[38][25] = letra3;
			break;
			default:
			mapa[8][29] = letra;
			mapa[30][12] = letra2;
			mapa[43][43] = letra3;
		}
		break;
		case 2:
		switch(n){
			case 1:
			mapa[2][24] = letra;
			mapa[32][9] = letra2;
			mapa[46][46] = letra3;
			break;
			case 2:
			mapa[2][11] = letra;
			mapa[18][41] = letra2;
			mapa[42][19] = letra3;
			break;
			default:
			mapa[18][6] = letra;
			mapa[36][33] = letra2;
			mapa[2][40] = letra3;
		}
		break;
		default:
		switch(n){
			case 1:
			mapa[19][13] = letra;
			mapa[26][45] = letra2;
			mapa[36][21] = letra3;
			break;
			case 2:
			mapa[2][2] = letra;
			mapa[1][39] = letra2;
			mapa[46][13] = letra3;
			break;
			default:
			mapa[16][7] = letra;
			mapa[47][37] = letra2;
			mapa[3][28] = letra3;
		}
		break;
	}
	return;
}

void dificultad(char **mapa,int tipo,int enemigov,int enemigol){
	//implementa el lugar de jugadores en el mapa
	char letra;
	char letra2;
	char letra3;
	int m;
	if(enemigov == 0){
		letra = 'E';
		letra2 = 'L';
		m = rand() % 2 + 1;
		if(m == 1){
			letra = 'L';
			letra2 = 'E';
		}
		dificultad_medio(mapa, tipo, letra, letra2);
	}
	else if(enemigol == 0){
		letra = 'E';
		letra2 = 'V';
		m = rand() % 2 + 1;
		if(m == 1){
			letra = 'V';
			letra2 = 'E';
		}
		dificultad_medio(mapa, tipo, letra, letra2);
	}
	else{
		int n;
		int m;
		n = rand() % 3 + 1;
		m = rand() % 2 + 1;
		switch(n){
			case 1:
			letra = 'L';
			switch(m){
				case 1:
				letra2 = 'E';
				letra3 = 'V';
				break;
				default:
				letra2 = 'V';
				letra3 = 'E';
				break;
			}
			break;
			case 2:
			letra = 'V';
			switch(m){
				case 1:
				letra2 = 'E';
				letra3 = 'L';
				break;
				default:
				letra2 = 'L';
				letra3 = 'E';
				break;
			}
			break;
			default:
			letra = 'E';
			switch(m){
				case 1:
				letra2 = 'L';
				letra3 = 'V';
				break;
				default:
				letra2 = 'V';
				letra3 = 'L';
			}
		}
		dificultad_dificil(mapa, tipo,letra,letra2,letra3);
	}
	return;
}

void leermapa(FILE* fmapa, char** mapa, int fila,int columna){
	// lee los elementos de una matriz de caracteres que esten en un archivo
	for (int i = 0; i < fila; i++){
		for (int j = 0; j < columna; j++){
			fscanf(fmapa," %c",&mapa[i][j]);
		}
	}
	return;
}

char** lector(int i,int *fila,int *columna,int dificil){
	// lee el mapa especificado por el numero, actualmente solo es mapa1
	FILE* fmapa;
	switch (i){
		case 1:
		fmapa = fopen("mapa1", "r");
		break;
		case 2:
		fmapa = fopen("mapa2","r");
		break;
		default:
		fmapa = fopen("mapa3","r");
		break;
	}
	fscanf(fmapa,"%d",fila);
	fscanf(fmapa,"%d",columna);

	int tamaño = *fila * *columna;

	char **mapa;
	mapa = mapabase(*fila,*columna);
	leermapa(fmapa, mapa, *fila, *columna);

	int n;
	switch(dificil){
		case 1:
		n = rand() % 2 + 1;
		if(n == 1)
			dificultad(mapa,i,0,5);
		else
			dificultad(mapa,i,5,0);
		break;
		default:
		dificultad(mapa, i, 5, 5);
	}

	fclose(fmapa);
	return mapa;
}

void localizar(int** mapa,int* fila,int* columna,int caracter){
	//localiza en el mapa un caracter, y guarda su posicion en fila y columna
	int conseguido = 0;
	int lugar = 0;
	for (int i = 0;i < *fila && conseguido == 0;i++){
		for (int j = 0;j < *columna && conseguido == 0;j++){
			if (mapa[i][j] == caracter)
				conseguido = 1;
			else
				lugar ++;
		}
	}
	*fila = lugar / *columna;
	*columna = lugar - (*fila) * (*columna);
	return;
}

//recordar cambiar estos valores
int** transformada(char** mapa,int fila,int columna){
	int **mapa_int;
	char pared_c = '*';
	int remplazo_c = -3;
	char pared_a = '/';
	int remplazo_a = -2;
	char comida_b = '+';
	int remplazo_b = -1;
	char aliado = 'E';
	int remplazo_s = 1;
	char enemigo_l = 'L';
	int remplazo_l = 6;
	char enemigo_v = 'V';
	int remplazo_v = 11;
	int remplazo_n = 0;
	mapa_int = mapa_num(fila,columna);
	for (int i=0;i < fila;i++){
		for (int j=0;j < columna;j++){
			if (mapa[i][j] == pared_c)
				mapa_int[i][j] = remplazo_c;
			else if (mapa[i][j] == pared_a)
				mapa_int[i][j] = remplazo_a;
			else if (mapa[i][j] == comida_b)
				mapa_int[i][j] = remplazo_b;
			else if (mapa[i][j] == aliado)
				mapa_int[i][j] = remplazo_s;
			else if (mapa[i][j] == enemigo_l)
				mapa_int[i][j] = remplazo_l;
			else if (mapa[i][j] == enemigo_v)
				mapa_int[i][j] = remplazo_v;
			else
				mapa_int[i][j] = remplazo_n;
		}
	}
	return mapa_int;
}

void colocar_personajes(int **mapa,int fila_max,int columna_max){
	int fila_aux = fila_max;
	int columna_aux = columna_max;
	localizar(mapa,&fila_aux,&columna_aux,1);
	if(fila_aux != fila_max && columna_aux != 0){
		mapa[fila_aux - 1][columna_aux + 1] = 2;
		mapa[fila_aux + 1][columna_aux + 1] = 3;
		mapa[fila_aux + 1][columna_aux - 1] = 4;
		mapa[fila_aux - 1][columna_aux - 1] = 5;
	}
	fila_aux = fila_max;
	columna_aux = columna_max;
	localizar(mapa,&fila_aux,&columna_aux,6);
	if(fila_aux != fila_max && columna_aux != 0){
		mapa[fila_aux - 1][columna_aux + 1] = 7;
		mapa[fila_aux + 1][columna_aux + 1] = 8;
		mapa[fila_aux + 1][columna_aux - 1] = 9;
		mapa[fila_aux - 1][columna_aux - 1] = 10;
	}
	fila_aux = fila_max;
	columna_aux = columna_max;
	localizar(mapa,&fila_aux,&columna_aux,11);
	if(fila_aux != fila_max && columna_aux != 0){
		mapa[fila_aux - 1][columna_aux + 1] = 12;
		mapa[fila_aux + 1][columna_aux + 1] = 13;
		mapa[fila_aux + 1][columna_aux - 1] = 14;
		mapa[fila_aux - 1][columna_aux - 1] = 15;
	}
	return;
}

personaje sniper = {1000,1000,4,3,1,3};
personaje ranger = {1500,1500,5,4,6,3};
personaje grenadier = {1200,1200,4,2,1,3};
personaje specialist = {1000,1000,4,3,1,3};
personaje cannibal = {1200,1200,4,2,1,3};
personaje volatilee = {950,950,4,5,6,3};

arma francotirador={2,400,2};
arma pistola = {6,100,6};
arma fusil = {4,200,4};
arma escopeta = {3,600,3};
arma ametralladora = {4,300,4};
arma espada ={5000,300,5000};

int* estado_partida(int **mapa,int* estado,int fila_max,int columna_max){
  int personaje;
  int i = 0;
  int* l = (int*)malloc(sizeof(int) * 15);
  while(i <= 5){
    printf("Eliga al %d personaje\n",i);
    printf("1.- Sniper\n");
    printf("2.- Ranger\n");
    printf("3.- Grenadier\n");
    printf("4.- Specialist\n");
    printf("5.- Cannibal\n");
    printf("6.- Volatile\n");
    printf("cualquier otro numero implicara que el personaje estara sin vida\n");
    scanf("%d",&personaje);
    l[i] = personaje;
  }

  int fila_aux = fila_max;
  int columna_aux = columna_max;
  localizar(mapa,&fila_aux,&columna_aux,6);
  if(fila_aux != fila_max && columna_aux != 0){
    int n = rand() % 3 + 1;
    switch(n){
      case 1:
        l[5] = 2;
        l[6] = 4;
        l[7] = 4;
        l[8] = 1;
        l[9] = 5;
      break;
      case 2:
        l[5] = 2;
        l[6] = 4;
        l[7] = 6;
        l[8] = 6;
        l[9] = 1;
      break;
      default:
        l[5] = 3;
        l[6] = 5;
        l[7] = 5;
        l[8] = 1;
        l[9] = 4;
      break;
    }
  }
  else{
    l[5] = 0;
    l[6] = 0;
    l[7] = 0;
    l[8] = 0;
    l[9] = 0;
  }

  fila_aux = fila_max;
  columna_aux = columna_max;
  localizar(mapa,&fila_aux,&columna_aux,11);
  if(fila_aux != fila_max && columna_aux != 0){
    int n = rand() % 3 + 1;
    switch(n){
      case 1:
        l[10] = 5;
        l[11] = 4;
        l[12] = 2;
        l[13] = 1;
        l[14] = 3;
      break;
      case 2:
        l[10] = 6;
        l[11] = 6;
        l[12] = 3;
        l[13] = 3;
        l[14] = 2;
      break;
      default:
        l[10] = 3;
        l[11] = 4;
        l[12] = 2;
        l[13] = 4;
        l[14] = 3;
      break;
    }
  }
  else{
    l[10] = 0;
    l[11] = 0;
    l[12] = 0;
    l[13] = 0;
    l[14] = 0;
  }
  
  int aux;
  estado = (int*)malloc(sizeof(int) * 196);
  estado[0] = 0;
  i = 0;

  for(int j = 0; j < 15;j++){
    aux = i * 13 + 1;
    switch(l[j]){
      case 1:
          estado[aux] = l[j];
          aux ++;
          estado[aux] = sniper.salud;
          aux ++;
          estado[aux] = sniper.salud_maxima;
          aux ++;
          estado[aux] = sniper.movimientos;
          aux ++;
          estado[aux] = sniper.arma1;
          aux ++;
          estado[aux] = francotirador.balas;
          aux ++;
          estado[aux] = francotirador.balas_maxima;
          aux ++;
          estado[aux] = sniper.arma2;
          aux ++;
          estado[aux] = pistola.balas;
          aux ++;
          estado[aux] = pistola.balas_maxima;
          aux ++;
          estado[aux] = 5;
          aux ++;
          estado[aux] = 5;
          aux ++;
          estado[aux] = 3;
        break;
        case 2:
          estado[aux] = l[j];
          aux ++;
          estado[aux] = ranger.salud;
          aux ++;
          estado[aux] = ranger.salud_maxima;
          aux ++;
          estado[aux] = ranger.movimientos;
          aux ++;
          estado[aux] = ranger.arma1;
          aux ++;
          estado[aux] = fusil.balas;
          aux ++;
          estado[aux] = fusil.balas_maxima;
          aux ++;
          estado[aux] = ranger.arma2;
          aux ++;
          estado[aux] = espada.balas;
          aux ++;
          estado[aux] = espada.balas_maxima;
          aux ++;
          estado[aux] = 1;
          aux ++;
          estado[aux] = 3;
          aux ++;
          estado[aux] = 0;
        break;
        case 3:
          estado[aux] = l[j];
          aux ++;
          estado[aux] = grenadier.salud;
          aux ++;
          estado[aux] = grenadier.salud_maxima;
          aux ++;
          estado[aux] = grenadier.movimientos;
          aux ++;
          estado[aux] = grenadier.arma1;
          aux ++;
          estado[aux] = escopeta.balas;
          aux ++;
          estado[aux] = escopeta.balas_maxima;
          aux ++;
          estado[aux] = grenadier.arma2;
          aux ++;
          estado[aux] = pistola.balas;
          aux ++;
          estado[aux] = pistola.balas_maxima;
          aux ++;
          estado[aux] = 1;
          aux ++;
          estado[aux] = 1;
          aux ++;
          estado[aux] = 0;
        break;
        case 4:
          estado[aux] = l[j];
          aux ++;
          estado[aux] = specialist.salud;
          aux ++;
          estado[aux] = specialist.salud_maxima;
          aux ++;
          estado[aux] = specialist.movimientos;
          aux ++;
          estado[aux] = specialist.arma1;
          aux ++;
          estado[aux] = francotirador.balas;
          aux ++;
          estado[aux] = francotirador.balas_maxima;
          aux ++;
          estado[aux] = specialist.arma2;
          aux ++;
          estado[aux] = pistola.balas;
          aux ++;
          estado[aux] = pistola.balas_maxima;
          aux ++;
          estado[aux] = 3;
          aux ++;
          estado[aux] = 3;
          aux ++;
          estado[aux] = 0;
        break;
        case 5:
          estado[aux] = l[j];
          aux ++;
          estado[aux] = cannibal.salud;
          aux ++;
          estado[aux] = cannibal.salud_maxima;
          aux ++;
          estado[aux] = cannibal.movimientos;
          aux ++;
          estado[aux] = cannibal.arma1;
          aux ++;
          estado[aux] = escopeta.balas;
          aux ++;
          estado[aux] = escopeta.balas_maxima;
          aux ++;
          estado[aux] = cannibal.arma2;
          aux ++;
          estado[aux] = pistola.balas;
          aux ++;
          estado[aux] = pistola.balas_maxima;
          aux ++;
          estado[aux] = 1;
          aux ++;
          estado[aux] = 2;
          aux ++;
          estado[aux] = 0;
        break;
        case 6:
          estado[aux] = l[j];
          aux ++;
          estado[aux] = volatilee.salud;
          aux ++;
          estado[aux] = volatilee.salud_maxima;
          aux ++;
          estado[aux] = volatilee.movimientos;
          aux ++;
          estado[aux] = volatilee.arma1;
          aux ++;
          estado[aux] = ametralladora.balas;
          aux ++;
          estado[aux] = ametralladora.balas_maxima;
          aux ++;
          estado[aux] = volatilee.arma2;
          aux ++;
          estado[aux] = espada.balas;
          aux ++;
          estado[aux] = espada.balas_maxima;
          aux ++;
          estado[aux] = 4;
          aux ++;
          estado[aux] = 6;
          aux ++;
          estado[aux] = 0;
        break;
        default:
          estado[aux] = 0;
          aux ++;
          estado[aux] = 0;
          aux ++;
          estado[aux] = 0;
          aux ++;
          estado[aux] = 0;
          aux ++;
          estado[aux] = 0;
          aux ++;
          estado[aux] = 0;
          aux ++;
          estado[aux] = 0;
          aux ++;
          estado[aux] = 0;
          aux ++;
          estado[aux] = 0;
          aux ++;
          estado[aux] = 0;
          aux ++;
          estado[aux] = 0;
          aux ++;
          estado[aux] = 0;
          aux ++;
          estado[aux] = 0;
        break;
        }
      i = i + 1;
      }
  
  return estado;
}

int** crear_mapa(int tipo,int *fila_max,int *columna_max,int *estado,int **mapa){
  char **mapabase;

  estado = estado_partida(mapa,estado,*fila_max,*columna_max);
  
  int dificultad;
  printf("Eliga cuantos equipos enemigos quieres en el mapa: ");
  scanf("%d",&dificultad);
  if(dificultad > 1){
    printf("\nHabran 2 equipos enemigos... destruyelos");
    mapabase = lector(tipo,fila_max,columna_max,2);
  }
  else{
    printf("\nHabra 1 equipo enemigo... destruyelo");
    mapabase = lector(tipo,fila_max,columna_max,1);
  }

  mapa = transformada(mapabase,*fila_max,*columna_max);
  colocar_personajes(mapa,*fila_max,*columna_max);
  liberar_memoria_c(mapabase,*fila_max);
  return mapa;
}

void disparar(personaje *atacante, personaje *defensor, arma *arma_elegida) {
	if ((*arma_elegida).balas > 0) {
		(*defensor).salud = (*defensor).salud - (*arma_elegida).agravio;
		(*arma_elegida).balas=(*arma_elegida).balas - (1);
		
		if ((*defensor).salud <=0) {
			printf("El personaje defensor ha muerto.\n");
		}
	} else {
		printf("El arma no tiene balas.\n");
	}
}

void ubicar_mostrar(int **mapa,int **minimap,int fila,int columna){
	int aux = columna - 3;
	fila = fila - 3;
	for(int i = 0;i < 7;i++){
		columna = aux;
		for(int j = 0;j < 7;j++){
			if(fila < 0 || fila > 49 || columna < 0 || columna > 49){
				minimap[i][j] = -3;
			}
			else{
				minimap[i][j] = mapa[fila][columna];
			}
			columna = columna + 1;
		}
		fila = fila + 1;
	}
	mostrar_forma_tabla_n(minimap, 7, 7);
	return;
}

void mover_derecha(int **mapa,int *fila,int *columna,int columna_max,int *energia){
	// Mueve el objeto en la zelda elegida hacia la derecha dependiendo de las condiciones
	int signo = 100;
	*energia = *energia - 1;
	if(*columna < columna_max - 1){
		signo = mapa[*fila][*columna + 1];
	}
	if (signo == 0){
		mapa[*fila][*columna + 1] = mapa[*fila][*columna];
		mapa[*fila][*columna] = 0;
		*columna = *columna + 1;
	}
	else if(signo == -1 && mapa[*fila][*columna + 2] == 0 && *energia >= 1){
		if(*columna < columna_max - 2){
			mapa[*fila][*columna + 2] = mapa[*fila][*columna];
			mapa[*fila][*columna] = 0;
			*columna = *columna + 2;
			*energia = *energia - 1;
		}
	}
	return;
}

void mover_abajo(int **mapa,int *fila,int *columna,int fila_max,int *energia){
	// Mueve el objeto en la zelda elegida hacia abajo dependiendo de las condiciones
	int signo = 100;
	*energia = *energia - 1;
	if(*fila < fila_max - 1){
		signo = mapa[*fila + 1][*columna];
	}
	if (signo == 0){
		mapa[*fila + 1][*columna] = mapa[*fila][*columna];
		mapa[*fila][*columna] = 0;
		*fila = *fila + 1;
	}
	else if(signo == -1 && mapa[*fila + 2][*columna] == 0 && *energia >= 1){
		if (*fila < fila_max - 2){
			mapa[*fila + 2][*columna] = mapa[*fila][*columna];
			mapa[*fila][*columna] = 0;
			*fila = *fila + 2;
			*energia = *energia - 1;
		}
	}
	return;
}

void mover_izquierda(int **mapa,int *fila,int *columna,int *energia){
	// Mueve el objeto en la zelda elegida hacia la izquierda dependiendo de las condiciones
	int signo = 100;
	*energia = *energia - 1;
	if(*columna > 0){
		signo = mapa[*fila][*columna - 1];
	}
	if (signo == 0){
		mapa[*fila][*columna - 1] = mapa[*fila][*columna];
		mapa[*fila][*columna] = 0;
		*columna = *columna - 1;
	}
	else if(signo == -1 &&mapa[*fila][*columna - 2] == 0 && *energia >= 1){
		if (*columna > 1){
			mapa[*fila][*columna - 2] = mapa[*fila][*columna];
			mapa[*fila][*columna] = 0;
			*columna = *columna - 2;
			*energia = *energia - 1;
		}
	}
	return;
}

void mover_arriba(int **mapa,int *fila,int *columna,int *energia){
	// Mueve el objeto en la zelda elegida hacia arriba dependiendo de las condiciones
	int signo = 100;
	*energia = *energia - 1;
	if(*fila > 0){
		signo = mapa[*fila - 1][*columna];
	}
	if (signo == 0){
		mapa[*fila - 1][*columna] = mapa[*fila][*columna];
		mapa[*fila][*columna] = 0;
		*fila = *fila - 1;
	}
	else if(signo == -1 && mapa[*fila - 2][*columna] == 0 && *energia >= 1){
		if(*columna > 1){
			mapa[*fila - 2][*columna] = mapa[*fila][*columna];
			mapa[*fila][*columna] = 0;
			*fila = *fila - 2;
			*energia = *energia - 1;
		}
	}
	return;
}

int movimiento(int **mapa,int **minimap,int *fila,int fila_max,int *columna,int columna_max,int energia){
	// Mueve el objeto en la zelda elegida hacia donde el jugador quiera dependiendo de las condiciones
	if(energia == 0)
		return 0;
	char mov;
	scanf("%c",&mov);
	switch (mov){
		case 'w':
		mover_arriba(mapa,fila,columna,&energia);
		ubicar_mostrar(mapa,minimap,*fila,*columna);
		break;
		case 'a':
		mover_izquierda(mapa,fila,columna,&energia);
		ubicar_mostrar(mapa,minimap,*fila,*columna);
		break;
		case 's':
		mover_abajo(mapa,fila,columna,fila_max,&energia);
		ubicar_mostrar(mapa,minimap,*fila,*columna);
		break;
		case 'd':
		mover_derecha(mapa,fila,columna,columna_max,&energia);
		ubicar_mostrar(mapa,minimap,*fila,*columna);
		break;
		case 'q':
		energia = energia - 1;
		ubicar_mostrar(mapa,minimap,*fila,*columna);
		break;
		case '\n':
		printf("le falta gastar %d energia",energia);
		printf(" indique su movimiento: ");
		salto(1);
		break;
		default:
		printf("movimiento no valido\n\n");
		break;
	}
	return movimiento(mapa,minimap,fila,fila_max,columna,columna_max,energia);
}

int** append_preciso(int **arreglo,int cantidad,int *n_elemento,int ubicacion){
	// funcion append expresada de forma especifica para listas de listas numericas
	int **salida;
	int total = cantidad + 1;
	salida = (int **)malloc(sizeof(int *)*(total));
	if (ubicacion > cantidad){
		ubicacion = cantidad;
	}
	for(int i=0;i < ubicacion;i++){
		salida[i] = arreglo[i];
	}
	salida[ubicacion] = n_elemento;
	for(int i=ubicacion;i < cantidad;i++){
		salida[i+1] = arreglo[i];
	}
	free(arreglo);
	return salida;
}

int** append_m(int **arreglo,int cantidad,int *n_elemento){
	// funcion append expresada de forma generica para listas de listas numericas
	int **arreglo_nuevo;
	arreglo_nuevo = append_preciso(arreglo,cantidad,n_elemento,cantidad);
	return arreglo_nuevo;
}

int* append_preciso_menor(int *arreglo,int cantidad,int n_elemento,int ubicacion){
	// funcion append expresada de forma especifica para listas de numeros
	int *salida;
	int total = cantidad + 1;
	salida = (int *)malloc(sizeof(int)*(total));
	if (ubicacion > cantidad){
		ubicacion = cantidad;
	}
	for(int i=0;i < ubicacion;i++){
		salida[i] = arreglo[i];
	}
	salida[ubicacion] = n_elemento;
	for(int i=ubicacion;i < cantidad;i++){
		salida[i+1] = arreglo[i];
	}
	free(arreglo);
	return salida;
}

int* append_menor(int *arreglo,int cantidad,int n_elemento){
	// funcion append expresada de forma generica para listas de numeros
	int *arreglo_nuevo;
	arreglo_nuevo = append_preciso_menor(arreglo,cantidad,n_elemento,cantidad);
	return arreglo_nuevo;
}

/* por si es necesaria
int* eliminar(int *arreglo,int cantidad,int ubicacion){
	int *salida;
	int total = cantidad + 1;
	salida = (int *)malloc(sizeof(int)*(total));
	if (ubicacion > cantidad){
		ubicacion = cantidad;
	}
	for(int i=0;i < ubicacion;i++){
		salida[i] = arreglo[i];
	}
	for(int i=ubicacion;i < cantidad;i++){
		salida[i] = arreglo[i+1];
	}
	free(arreglo);
	return salida;
}
*/

void recargar(personaje *personaje) {
    // Implementa la recarga de munición
}

void usarObjeto(personaje *personaje, char *objeto) {
if (*objeto).cantidad > 1{
	if (*personaje).salud < (*personaje).saludmaxima - 500{
		return (*personaje).salud + 500;
	else{
		return (*personaje).salud == (*personaje.saludmaxima);
	}else{
		printf("No tienes objetos en tu inventario");
	}
}
}
	
    // Implementa el uso de objetos
}

// Función principal
int main() {
	personaje jugador;
	personaje enemigo;

	// por cambiar char armas --> int armas
	//personajes

	personaje sniper = {1000,1000,4,3,1,3};

	personaje ranger = {1500,1500,5,4,6,3};

	personaje grenadier = {1200,1200,4,2,1,3};

	personaje specialist = {1000,1000,4,3,1,3};

	personaje cannibal = {1200,1200,4,2,1,3};

	personaje volatilee = {950,950,4,5,6,3};

	//armas, forma = {cant balas, daño}
	arma francotirador={2,400};
	arma pistola = {6,100};
	arma fusil = {4,200};
	arma escopeta = {3,600};
	arma ametralladora = {4,300};
	arma espada ={5000,300};

	// cambiar el parametro cantidad
	//objetos, forma = {daño, vida, cantidad, velocidad por cuadro}
	objeto botiquin = {0,500,2,0};
	objeto granada = {500,0,2,0};
	objeto monster = {0,0,0,2};
	objeto tnt = {5000,0,0,0};
	objeto c4 = {700,0,0,0};

	// Inicializa las propiedades de los personajes y posiciones
	// Aqui empieza lo que realize
	srand(time(NULL));
	int **mapa;
	int numero_alea = 1; // eleccion de mapa
	int fila;
	int columna;

	mapa = crear_mapa(numero_alea, &fila, &columna, mapa);

	int fila_local = fila;
	int columna_local = columna;
	localizar(mapa, &fila_local, &columna_local, 1); // el entero es el personaje a mover

	int **minimap;
	minimap = mapa_num(7, 7);
	ubicar_mostrar(mapa,minimap,fila_local,columna_local);
	movimiento(mapa,minimap, &fila_local, fila, &columna_local, columna, 200); //el ultimo valor es la cantidad de movimientos que se pueden hacer
	// aqui termina lo que realize
    
	// Bucle principal del juego
	while (1) {
		// Mostrar el estado del juego y opciones al jugador
		printf("Jugador:\n");
		// Muestra las estadísticas del jugador (vida, munición, etc.)

		printf("Enemigo:\n");
		// Muestra las estadísticas del enemigo

		int eleccion;
		printf("Selecciona una acción:\n");
		printf("1. Mover\n");
		printf("2. Disparar\n");
		printf("3. Recargar\n");
		printf("4. Usar objeto\n");
		printf("5. Salir\n");

		scanf("%d", &eleccion);

		switch (eleccion) {
			case 1:
			// Llama a la función para mover al jugador
			break;
			case 2:
			// Llama a la función para disparar
			break;
			case 3:
			// Llama a la función para recargar
			break;
			case 4:
			// Llama a la función para usar objeto
			break;
			case 5:
			// Salir del juego
			exit(0);
			default:
			printf("Opción no válida\n");
		}
		// Actualizar el estado del juego (turno del enemigo, verificar victoria/derrota, etc.)
	}
	liberar_memoria_n(mapa, columna);
	liberar_memoria_n(minimap, 7);
	return 0;
}
