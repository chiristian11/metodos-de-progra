#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//funcion para agregar los logs a cada accion del programa
struct tm tm;
time_t t;

void actualizar_matriz(int **minimap,int* estado, int fila, int columna){
  FILE *archivo = fopen("interfaz.txt","w");
  fprintf(archivo,"1\n");
  fprintf(archivo,"7,7\n");
  int aux = columna - 3;
  fila = fila - 3;
  for(int i = 0;i < 7; i++){
    columna = aux;
    for(int j=0; j < 7; j++){
      columna = aux;
      if(minimap[i][j] <= 0){
        fprintf(archivo,"%d",minimap[i][j]);
      }
      else{
        fprintf(archivo,"%d",estado[(minimap[i][j] - 1) * 13 + 1]);
      }
      if (j < 6){
        fprintf(archivo, ".png,");
      }
      else{
        fprintf(archivo, ".png");
      }
      columna = columna + 1;
    }
    fila = fila + 1;
    if (i < 6){
      fprintf(archivo, "\n");
    }
  }


  fclose(archivo);
  return;
}

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

objeto botiquin = {0,500,2,0};
objeto granada = {500,0,2,0};
objeto monster = {0,0,0,2};
objeto tnt = {5000,0,0,0};
objeto c4 = {700,0,0,0};

int const pared_item = 14;
int const pared_completa = 13;
int const pared_alta = 12;
int const obstaculo = 11;
int const camino = 10;

int equipo_aliado = 61;
int equipo_l = 81;
int equipo_v = 91;

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
  for(int i=0; i<fila; i++){
    for(int j=0; j < columna; j++){
      printf("%d ",arreglo[i][j]);
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

void leerpartida(FILE* fpartida,int** mapa,int fila,int columna){
  // lee los elementos de una matriz de numeros que esten en un archivo
  for (int i = 0; i < fila; i++){
    for (int j = 0; j < columna; j++){
      fscanf(fpartida," %d",&mapa[i][j]);
    }
  }
  return;
}

void leerestado(FILE* fpartida,int* estado){
  // lee los elementos de una matriz de numeros que esten en un archivo
  for (int i = 0; i < 196; i++){
    fscanf(fpartida," %d",&estado[i]);
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

  char **mapa;
  mapa = mapabase(*fila,*columna);
  leermapa(fmapa, mapa, *fila, *columna);

  int n;
  switch(dificil){
    case 1:
    n = rand() % 2 + 1;
    printf("%d",n);
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

int** transformada(char** mapa,int fila,int columna){
  int **mapa_int;
  char pared_c = '*';
  int remplazo_c = pared_completa;
  char pared_a = '/';
  int remplazo_a = pared_alta;
  char comida_b = '+';
  int remplazo_b = obstaculo;
  char aliado = 'E';
  int remplazo_s = equipo_aliado;
  char enemigo_l = 'L';
  int remplazo_l = equipo_l;
  char enemigo_v = 'V';
  int remplazo_v = equipo_v;
  int remplazo_n = camino;
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

void ubicar(int **mapa,int **minimap,int fila,int columna){
  int aux = columna - 3;
  fila = fila - 3;
  for(int i = 0;i < 7;i++){
    columna = aux;
    for(int j = 0;j < 7;j++){
      if(fila < 0 || fila > 49 || columna < 0 || columna > 49){
        minimap[i][j] = pared_completa; // Alerta, cambiar a numero de pared c
      }
      else{
        minimap[i][j] = mapa[fila][columna];
      }
      columna = columna + 1;
    }
    fila = fila + 1;
  }
  return;
}

void colocar_personajes(int **mapa,int fila_max,int columna_max){
  int fila_aux = fila_max;
  int columna_aux = columna_max;
  localizar(mapa,&fila_aux,&columna_aux,equipo_aliado);
  if(fila_aux != fila_max && columna_aux != 0){
    mapa[fila_aux - 1][columna_aux + 1] = equipo_aliado + 1;
    mapa[fila_aux + 1][columna_aux + 1] = equipo_aliado + 2;
    mapa[fila_aux + 1][columna_aux - 1] = equipo_aliado + 3;
    mapa[fila_aux - 1][columna_aux - 1] = equipo_aliado + 4;
  }
  fila_aux = fila_max;
  columna_aux = columna_max;
  localizar(mapa,&fila_aux,&columna_aux,equipo_l);
  if(fila_aux != fila_max && columna_aux != 0){
    mapa[fila_aux - 1][columna_aux + 1] = equipo_l + 1;
    mapa[fila_aux + 1][columna_aux + 1] = equipo_l + 2;
    mapa[fila_aux + 1][columna_aux - 1] = equipo_l + 3;
    mapa[fila_aux - 1][columna_aux - 1] = equipo_l + 4;
  }
  fila_aux = fila_max;
  columna_aux = columna_max;
  localizar(mapa,&fila_aux,&columna_aux,equipo_v);
  if(fila_aux != fila_max && columna_aux != 0){
    mapa[fila_aux - 1][columna_aux + 1] = equipo_v + 1;
    mapa[fila_aux + 1][columna_aux + 1] = equipo_v + 2;
    mapa[fila_aux + 1][columna_aux - 1] = equipo_v + 3;
    mapa[fila_aux - 1][columna_aux - 1] = equipo_v + 4;
  }
  return;
}

void traducir_rol(int rol){
  switch(rol){
    case 1:
    printf("Sniper\n");
    break;
    case 2:
    printf("Ranger\n");
    break;
    case 3:
    printf("Grenadier\n");
    break;
    case 4:
    printf("Specialist\n");
    break;
    case 5:
    printf("Cannibal\n");
    break;
    case 6:
    printf("Volatile\n");
    break;
  }
  return;
}

void traducir_arma(int arma){
  switch(arma){
    case 1:
    printf("Pistola");
    break;
    case 2:
    printf("Escopeta");
    break;
    case 3:
    printf("Francotirador");
    break;
    case 4:
    printf("Fusil");
    break;
    case 5:
    printf("Ametralladora");
    break;
    case 6:
    printf("Espada");
    break;
  }
  return;
}

void traducir_objeto(int objeto){
  switch(objeto){
    case 1:
    printf("Granada, ");
    break;
    case 2:
    printf("Monster, ");
    break;
    case 3:
    printf("Botiquin, ");
    break;
    case 4:
    printf("TNT, ");
    break;
    case 5:
    printf("Diazepan, ");
    break;
    case 6:
    printf("C4, ");
    break;
  }
  return;
}

void estado_partida(int **mapa,int* estado,int fila_max,int columna_max){
  int personaje;
  int i = 1;
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
    l[i - 1] = personaje;
    i = i + 1;
  }

  int fila_aux = fila_max;
  int columna_aux = columna_max;
  localizar(mapa,&fila_aux,&columna_aux,equipo_l);
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
  localizar(mapa,&fila_aux,&columna_aux,equipo_v);
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
          /*fila_aux = fila_max;
          columna_aux = columna_max;
          localizar(mapa,&fila_aux,&columna_aux, i + 1);
          if(fila_aux == fila_max && columna_aux == 0){
            mapa[fila_aux][columna_aux] = 0;
          }
          verificar que esta mal en esta parte */
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

  free(l);
  return;
}

int** crear_mapa(int tipo,int *fila_max,int *columna_max,int *estado,int **mapa){
  char **mapabase;

  int dificultad;
  printf("Eliga cuantos equipos enemigos quieres en el mapa: ");
  scanf("%d",&dificultad);
  if(dificultad > 1){
    printf("\nHabran 2 equipos enemigos... destruyelos\n\n");
    mapabase = lector(tipo,fila_max,columna_max,2);
  }
  else{
    printf("\nHabra 1 equipo enemigo... destruyelo\n\n");
    mapabase = lector(tipo,fila_max,columna_max,1);
  }
  
  mapa = transformada(mapabase,*fila_max,*columna_max);
  
  estado_partida(mapa,estado,*fila_max,*columna_max);
  
  colocar_personajes(mapa,*fila_max,*columna_max);
  
  liberar_memoria_c(mapabase,*fila_max);
  return mapa;
}

void guardar_partida(int** mapa,int* estado, int fila_max, int columna_max){
  FILE *archivo = fopen("salvado","w");
  fprintf(archivo,"%d %d\n",fila_max,columna_max);
  for(int i = 0; i < fila_max; i++){
    for(int j = 0; j < columna_max; j++){
      fprintf(archivo,"%d ",mapa[i][j]);
    }
    fprintf(archivo,"\n");
  }
  fprintf(archivo,"\n");
  for(int i = 0; i < 196; i++){
    fprintf(archivo,"%d ",estado[i]);
  }
  fclose(archivo);
  return;
}

int** leer_partida(int** mapa,int* estado,int *fila_max,int *columna_max){
  FILE* fmapa;
  fmapa = fopen("salvado", "r");
  
  fscanf(fmapa,"%d",fila_max);
  fscanf(fmapa,"%d",columna_max);

  mapa = mapa_num(*fila_max,*columna_max);
  
  leerpartida(fmapa, mapa, *fila_max, *columna_max);
  leerestado(fmapa, estado);

  fclose(fmapa);
  return mapa;
}

void mover_derecha(int **mapa,int *fila,int *columna,int columna_max,int *energia,FILE *log){
  // Mueve el objeto en la zelda elegida hacia la derecha dependiendo de las condiciones
  int signo = 100;
  *energia = *energia - 1;
  if(*columna < columna_max - 1){
    signo = mapa[*fila][*columna + 1];
  }
  if (signo == camino){
    mapa[*fila][*columna + 1] = mapa[*fila][*columna];
    mapa[*fila][*columna] = camino;
    *columna = *columna + 1;
  }
  else if(signo == obstaculo && mapa[*fila][*columna + 2] == camino && *energia >= 1){
    if(*columna < columna_max - 2){
      mapa[*fila][*columna + 2] = mapa[*fila][*columna];
      mapa[*fila][*columna] = camino;
      *columna = *columna + 2;
      *energia = *energia - 1;
    }
  }
  return;
}

void mover_abajo(int **mapa,int *fila,int *columna,int fila_max,int *energia,FILE *log){
  // Mueve el objeto en la zelda elegida hacia abajo dependiendo de las condiciones
  int signo = 100;
  *energia = *energia - 1;
  if(*fila < fila_max - 1){
    signo = mapa[*fila + 1][*columna];
  }
  if (signo == camino){
    mapa[*fila + 1][*columna] = mapa[*fila][*columna];
    mapa[*fila][*columna] = camino;
    *fila = *fila + 1;
  }
  else if(signo == obstaculo && mapa[*fila + 2][*columna] == camino && *energia >= 1){
    if (*fila < fila_max - 2){
      mapa[*fila + 2][*columna] = mapa[*fila][*columna];
      mapa[*fila][*columna] = camino;
      *fila = *fila + 2;
      *energia = *energia - 1;
    }
  }
  return;
}

void mover_izquierda(int **mapa,int *fila,int *columna,int *energia,FILE *log){
  // Mueve el objeto en la zelda elegida hacia la izquierda dependiendo de las condiciones
  int signo = 100;
  *energia = *energia - 1;
  if(*columna > 0){
    signo = mapa[*fila][*columna - 1];
  }
  if (signo == camino){
    mapa[*fila][*columna - 1] = mapa[*fila][*columna];
    mapa[*fila][*columna] = camino;
    *columna = *columna - 1;
  }
  else if(signo == obstaculo &&mapa[*fila][*columna - 2] == camino && *energia >= 1){
    if (*columna > 1){
      mapa[*fila][*columna - 2] = mapa[*fila][*columna];
      mapa[*fila][*columna] = camino;
      *columna = *columna - 2;
      *energia = *energia - 1;
    }
  }
  return;
}

void mover_arriba(int **mapa,int *fila,int *columna,int *energia,FILE *log){
  // Mueve el objeto en la zelda elegida hacia arriba dependiendo de las condiciones
  int signo = 100;
  *energia = *energia - 1;
  if(*fila > 0){
    signo = mapa[*fila - 1][*columna];
  }
  if (signo == camino){
    mapa[*fila - 1][*columna] = mapa[*fila][*columna];
    mapa[*fila][*columna] = camino;
    *fila = *fila - 1;
  }
  else if(signo == obstaculo && mapa[*fila - 2][*columna] == camino && *energia >= 1){
    if(*columna > 1){
      mapa[*fila - 2][*columna] = mapa[*fila][*columna];
      mapa[*fila][*columna] = camino;
      *fila = *fila - 2;
      *energia = *energia - 1;
    }
  }
  return;
}

int movimiento(int **mapa,int **minimap,int *estado,int *fila,int fila_max,int *columna,int columna_max,int energia,FILE *log){
	if(energia == 0)
		return 0;
  char mov;
  scanf("%c",&mov);
  switch (mov){
    case 'w':
    mover_arriba(mapa,fila,columna,&energia,log);
    ubicar(mapa,minimap,*fila,*columna);
    actualizar_matriz(minimap,estado,fila_max,columna_max);
	t = time(NULL);
	tm = *localtime(&t);
	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(log,"el ususario se movio hacia arriba\n");
    break;
    case 'a':
    mover_izquierda(mapa,fila,columna,&energia,log);
    ubicar(mapa,minimap,*fila,*columna);
    actualizar_matriz(minimap,estado,fila_max,columna_max);
	t = time(NULL);
	tm = *localtime(&t);
	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(log,"el ususario se movio hacia la izquierda\n");
    break;
    case 's':
    mover_abajo(mapa,fila,columna,fila_max,&energia,log);
    ubicar(mapa,minimap,*fila,*columna);
    actualizar_matriz(minimap,estado,fila_max,columna_max);
	t = time(NULL);
	tm = *localtime(&t);
	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(log,"el ususario se movio hacia abajo\n");
    break;
    case 'd':
    mover_derecha(mapa,fila,columna,columna_max,&energia,log);
    ubicar(mapa,minimap,*fila,*columna);
    actualizar_matriz(minimap,estado,fila_max,columna_max);
	t = time(NULL);
	tm = *localtime(&t);
	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(log,"el ususario se movio hacia la derecha\n");
    break;
    case 'q':
    energia = energia - 1;
    ubicar(mapa,minimap,*fila,*columna);
	t = time(NULL);
	tm = *localtime(&t);
	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(log,"el ususario gasto energia sin moverse\n");
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
  return movimiento(mapa,minimap,estado,fila,fila_max,columna,columna_max,energia,log);
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

void disparo_probable(int* estado,int atacante,int defensor,int arma,int largo,FILE *log){
  int aux;
  int agravio;
  int porcentaje = 100;
  int probabilidad;
  int seguridad;
  int tipo_arma = estado[(atacante - 1) * 13 + 2 + 3 * arma];
  switch(tipo_arma){
    case 1:
    agravio = pistola.agravio;
    probabilidad = 8;
    seguridad = 3;
    break;
    case 2:
    agravio = escopeta.agravio;
    probabilidad = 20;
    seguridad = 2;
    break;
    case 3:
    agravio = francotirador.agravio;
    probabilidad = 3;
    seguridad = 5;
    break;
    case 4:
    ya(1);
    agravio = fusil.agravio;
    probabilidad = 6;
    seguridad = 3;
    break;
    case 5:
    agravio = ametralladora.agravio;
    probabilidad = 25;
    seguridad = 3;
    break;
    case 6:
    agravio = espada.agravio;
    probabilidad = 100;
    seguridad = 1;
    porcentaje = 90;
    break;
  }
  aux = porcentaje - (largo - seguridad) * probabilidad;
  int probabilidad_disparo = rand() % 101 + 1;
  printf("%d < %d, %d - (%d - %d) * %d ",probabilidad_disparo,aux,porcentaje,largo,seguridad,probabilidad);
  if (probabilidad_disparo < aux){
    printf("El disparo fue exitoso\n\n");
    if(estado[(atacante - 1) * 13 + 3 + 3 * arma] > 0){
      estado[(defensor - 1) * 13 + 2] -= agravio;
      estado[(atacante - 1) * 13 + 3 + 3 * arma] --;
      if (estado[(defensor - 1) * 13 + 2] <= 0){
        estado[(defensor - 1) * 13 + 2] = 0; //easter egg, soldado zombie
        estado[(defensor - 1) * 13 + 3] = 0;
        estado[(defensor - 1) * 13 + 6] = 0;
        estado[(defensor - 1) * 13 + 7] = 0;
        estado[(defensor - 1) * 13 + 9] = 0;
        estado[(defensor - 1) * 13 + 10] = 0;
        t = time(NULL);
	tm = *localtime(&t);
	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(log,"el jugador %d ha muerto\n",defensor);  
        printf("El personaje defensor ha muerto.\n");
      }
    }
    else{
      printf("El arma no tiene balas.\n");
    }
  }
  else{
    printf("El disparo fallo.\n\n");
  }
  return;
}

void disparando(int** mapa,int fila_max,int columna_max,int* estado,int atacante,int orden,int arma,FILE *log){
  char dirrecion;
  int defensor;
  int acierto = 0;
  printf("por favor ingrese la dirrecion a la que quiere disparar, en la misma forma de moverse\n");
  dirrecion = 'f';
  while(dirrecion != 'a' && dirrecion != 'd' && dirrecion != 'w' && dirrecion != 's'){
    scanf("%c",&dirrecion);
  }
  int fila_local = fila_max;
  int columna_local = columna_max;
  int contar = 0;
  localizar(mapa, &fila_local, &columna_local, atacante);
  switch(dirrecion){
    case 'w':
      while(fila_local > 0 && acierto == 0){
        contar ++;
        if(mapa[fila_local - 1][columna_local] > equipo_aliado - 1){
          defensor = mapa[fila_local - 1][columna_local];
          acierto = 1;
        }
        else{
          fila_local--;
        }
      }
    break;
    case 'a':
      while(columna_local > 0 && acierto == 0){
        contar ++;
        if(mapa[fila_local][columna_local - 1] > equipo_aliado - 1){
          defensor = mapa[fila_local][columna_local - 1];
          acierto = 1;
        }
        else{
          columna_local--;
        }
      }
    break;
    case 's':
      while(fila_local < fila_max - 1 && acierto == 0){
        contar ++;
        if(mapa[fila_local + 1][columna_local] > equipo_aliado - 1){
          defensor = mapa[fila_local + 1][columna_local];
          acierto = 1;
        }
        else{
          fila_local++;
        }
      }
    break;
    case 'd':
      while(columna_local < columna_max - 1 && acierto == 0){
        contar ++;
        if(mapa[fila_local][columna_local + 1] > equipo_aliado - 1){
          defensor = mapa[fila_local][columna_local + 1];
          acierto = 1;
        }
        else{
          columna_local++;
        }
      }
    break;
  }
  if(acierto == 1){
    if(defensor < equipo_aliado + 6){
      defensor = defensor - equipo_aliado + 1;
	t = time(NULL);
	tm = *localtime(&t);
	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(log,"%d %d","el jugador %d disparo a bot %d \n",atacante,defensor);
    }
    else if(defensor < equipo_l + 6){
      defensor = defensor - equipo_l + 6;
	t = time(NULL);
	tm = *localtime(&t);
	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(log,"%d %d","el jugador %d disparo a bot %d del equipo l\n",atacante,defensor);
    }
    else if(defensor < equipo_v + 6){
      defensor = defensor - equipo_v + 11;
	t = time(NULL);
	tm = *localtime(&t);
	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(log,"%d %d","el jugador %d disparo a bot %d del equipo v\n",atacante,defensor);
    }
    disparo_probable(estado,orden,defensor,arma,contar,log);
  }
  else{
    estado[(atacante - 1) * 13 + 3 + 3 * arma] --;
	t = time(NULL);
	tm = *localtime(&t);
	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(log, "el jugador disparo al aire \n");
    printf("El disparo no impacto a ningun personaje.\n");
  }
}

void tomar_item(int** mapa,int fila_max,int columna_max,int* estado,int jugador){
  char dirrecion;
  int defensor;
  int acierto = 0;
  int fila_local = fila_max;
  int columna_local = columna_max;
  int lugar;
  int objeto;
  printf("por favor ingrese la dirrecion del item, en la misma forma de moverse\n");
  dirrecion = 'f';
  while(dirrecion != 'a' && dirrecion != 'd' && dirrecion != 'w' && dirrecion != 's'){
    scanf("%c",&dirrecion);
  }
  
  localizar(mapa, &fila_local, &columna_local, jugador);
  switch(dirrecion){
    case 'w':
      if(mapa[fila_local - 1][columna_local] == pared_item){
        printf("ingrese la posicion del item nuevo a ubicar\n");
        scanf("%d",&lugar);
      }
    break;
    case 'a':
      if(mapa[fila_local][columna_local - 1] == pared_item){
        printf("ingrese la posicion del item nuevo a ubicar\n");
        scanf("%d",&lugar);
      }
    break;
    case 's':
      if(mapa[fila_local + 1][columna_local] == pared_item){
        printf("ingrese la posicion del item nuevo a ubicar\n");
        scanf("%d",&lugar);
      }
    break;
    case 'd':
      if(mapa[fila_local][columna_local + 1] == pared_item){
        printf("ingrese la posicion del item nuevo a ubicar\n");
        scanf("%d",&lugar);
      }
    break;
  }
  objeto = rand() % 6 + 1;
  estado[(jugador - equipo_aliado) * 13 + 10 + lugar] = objeto;
  return;
}

void recargar(int* estado,int jugador, int arma){
  if(arma != 1 && arma != 2){
    arma = 1;
  }
  estado[(jugador - 1) * 13 + 3 + 3 * arma] = estado[(jugador - 1) * 13 + 4 + 3 * arma];
  printf("se ha recargado el arma llamado: ");
  traducir_arma(estado[(jugador - 1) * 13 + 2 + 3 * arma]);
  printf(", y ahora tiene %d balas\n", estado[(jugador - 1) * 13 + 3 + 3 * arma]);
  return;
}

void usarObjeto_botiquin(int* estado,int jugador,int lugarObjeto,FILE *log){
  if (estado[(jugador - 1) * 13 + 10 + lugarObjeto] == 3){
	t = time(NULL);
	tm = *localtime(&t);
	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(log,"%d","el jugador %d hizo uso de un botiquin\n",jugador);
    if (estado[(jugador - 1) * 13 + 2] <= estado[(jugador - 1) * 13 + 3] - 500){
      estado[(jugador - 1) * 13 + 2] = estado[(jugador - 1 ) * 13 + 2] + 500;
    }
    else{
      estado[(jugador - 1) * 13 + 2] = estado[(jugador - 1) * 13 + 3];
    }
    estado[(jugador - 1) * 13 + 10 + lugarObjeto] = 0;
  }
  else{
	t = time(NULL);
	tm = *localtime(&t);
	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(log,"%d","el jugador %d intento usar un botiquin pero no quedaban disponibles\n", jugador);
    printf("No tienes el botiquin en tu inventario en esa posición");
  }
  return;
}

void aparicion_item(int** mapa,int identificador,int* estado){
  int tipo;
  int n;
  if(estado[0] % 10 == 0){
    n = rand() % 3 + 1;
    tipo = identificador * 3 - n + 1;
    switch (tipo){
      case 1:
      mapa[0][11] = pared_item;
      mapa[4][17] = pared_item;
      mapa[4][48] = pared_item;
      mapa[6][49] = pared_item;
      mapa[8][26] = pared_item;
      mapa[11][3] = pared_item;
      mapa[11][36] = pared_item;
      mapa[15][24] = pared_item;
      mapa[15][26] = pared_item;
      mapa[16][25] = pared_item;
      mapa[21][45] = pared_item;
      mapa[23][5] = pared_item;
      mapa[23][30] = pared_item;
      mapa[27][24] = pared_item;
      mapa[28][16] = pared_item;
      mapa[29][18] = pared_item;
      mapa[35][24] = pared_item;
      mapa[38][10] = pared_item;
      mapa[39][8] = pared_item;
      mapa[40][11] = pared_item;
      mapa[41][9] = pared_item;
      mapa[42][25] = pared_item;
      mapa[43][40] = pared_item;
      mapa[43][46] = pared_item;
      break;
      case 2:
      mapa[1][10] = pared_item;
      mapa[2][11] = pared_item;
      mapa[4][48] = pared_item;
      mapa[5][48] = pared_item;
      mapa[10][17] = pared_item;
      mapa[11][36] = pared_item;
      mapa[15][25] = pared_item;
      mapa[16][17] = pared_item;
      mapa[16][24] = pared_item;
      mapa[16][26] = pared_item;
      mapa[21][45] = pared_item;
      mapa[23][5] = pared_item;
      mapa[23][9] = pared_item;
      mapa[23][30] = pared_item;
      mapa[26][30] = pared_item;
      mapa[28][18] = pared_item;
      mapa[38][9] = pared_item;
      mapa[39][11] = pared_item;
      mapa[40][8] = pared_item;
      mapa[41][10] = pared_item;
      mapa[41][24] = pared_item;
      mapa[42][27] = pared_item;
      mapa[43][34] = pared_item;
      mapa[43][40] = pared_item;
      break;
      case 3:
      mapa[0][11] = pared_item;
      mapa[4][17] = pared_item;
      mapa[6][49] = pared_item;
      mapa[8][26] = pared_item;
      mapa[10][17] = pared_item;
      mapa[11][3] = pared_item;
      mapa[11][36] = pared_item;
      mapa[15][24] = pared_item;
      mapa[15][26] = pared_item;
      mapa[16][24] = pared_item;
      mapa[16][26] = pared_item;
      mapa[21][45] = pared_item;
      mapa[23][5] = pared_item;
      mapa[23][30] = pared_item;
      mapa[27][24] = pared_item;
      mapa[28][16] = pared_item;
      mapa[35][24] = pared_item;
      mapa[38][9] = pared_item;
      mapa[38][10] = pared_item;
      mapa[41][9] = pared_item;
      mapa[41][10] = pared_item;
      mapa[42][25] = pared_item;
      mapa[43][34] = pared_item;
      mapa[43][46] = pared_item;
      break;
      case 4:
      mapa[0][16] = pared_item;
      mapa[3][29] = pared_item;
      mapa[4][16] = pared_item;
      mapa[8][29] = pared_item;
      mapa[9][21] = pared_item;
      mapa[15][8] = pared_item;
      mapa[20][31] = pared_item;
      mapa[21][23] = pared_item;
      mapa[24][15] = pared_item;
      mapa[24][31] = pared_item;
      mapa[24][42] = pared_item;
      mapa[24][43] = pared_item;
      mapa[26][15] = pared_item;
      mapa[27][5] = pared_item;
      mapa[27][7] = pared_item;
      mapa[29][14] = pared_item;
      mapa[33][36] = pared_item;
      mapa[44][33] = pared_item;
      mapa[44][35] = pared_item;
      mapa[44][49] = pared_item;
      mapa[46][24] = pared_item;
      mapa[49][2] = pared_item;
      mapa[49][20] = pared_item;
      mapa[49][43] = pared_item;
      break;
      case 5:
      mapa[0][16] = pared_item;
      mapa[1][49] = pared_item;
      mapa[2][16] = pared_item;
      mapa[2][49] = pared_item;
      mapa[8][29] = pared_item;
      mapa[9][21] = pared_item;
      mapa[15][8] = pared_item;
      mapa[21][22] = pared_item;
      mapa[21][31] = pared_item;
      mapa[22][31] = pared_item;
      mapa[23][15] = pared_item;
      mapa[23][31] = pared_item;
      mapa[24][43] = pared_item;
      mapa[27][15] = pared_item;
      mapa[28][14] = pared_item;
      mapa[33][36] = pared_item;
      mapa[44][33] = pared_item;
      mapa[44][35] = pared_item;
      mapa[46][23] = pared_item;
      mapa[48][49] = pared_item;
      mapa[49][1] = pared_item;
      mapa[49][3] = pared_item;
      mapa[49][21] = pared_item;
      mapa[49][48] = pared_item;
      break;
      case 6:
      mapa[1][49] = pared_item;
      mapa[2][16] = pared_item;
      mapa[4][16] = pared_item;
      mapa[8][29] = pared_item;
      mapa[9][21] = pared_item;
      mapa[15][8] = pared_item;
      mapa[20][31] = pared_item;
      mapa[21][22] = pared_item;
      mapa[21][23] = pared_item;
      mapa[21][31] = pared_item;
      mapa[22][31] = pared_item;
      mapa[23][31] = pared_item;
      mapa[24][31] = pared_item;
      mapa[24][42] = pared_item;
      mapa[24][44] = pared_item;
      mapa[25][15] = pared_item;
      mapa[27][6] = pared_item;
      mapa[27][7] = pared_item;
      mapa[33][36] = pared_item;
      mapa[43][49] = pared_item;
      mapa[49][2] = pared_item;
      mapa[49][20] = pared_item;
      mapa[49][21] = pared_item;
      mapa[49][43] = pared_item;
      break;
      case 7:
      mapa[4][43] = pared_item;
      mapa[5][10] = pared_item;
      mapa[6][13] = pared_item;
      mapa[6][15] = pared_item;
      mapa[6][25] = pared_item;
      mapa[10][31] = pared_item;
      mapa[10][36] = pared_item;
      mapa[14][42] = pared_item;
      mapa[16][17] = pared_item;
      mapa[22][10] = pared_item;
      mapa[25][21] = pared_item;
      mapa[25][29] = pared_item;
      mapa[25][32] = pared_item;
      mapa[25][33] = pared_item;
      mapa[28][29] = pared_item;
      mapa[30][29] = pared_item;
      mapa[32][29] = pared_item;
      mapa[33][24] = pared_item;
      mapa[40][9] = pared_item;
      mapa[40][20] = pared_item;
      mapa[42][19] = pared_item;
      mapa[44][19] = pared_item;
      mapa[49][42] = pared_item;
      mapa[49][43] = pared_item;
      break;
      case 8:
      mapa[4][36] = pared_item;
      mapa[5][4] = pared_item;
      mapa[5][17] = pared_item;
      mapa[6][13] = pared_item;
      mapa[6][14] = pared_item;
      mapa[6][25] = pared_item;
      mapa[13][42] = pared_item;
      mapa[15][42] = pared_item;
      mapa[16][17] = pared_item;
      mapa[16][21] = pared_item;
      mapa[18][4] = pared_item;
      mapa[25][30] = pared_item;
      mapa[25][32] = pared_item;
      mapa[27][29] = pared_item;
      mapa[29][10] = pared_item;
      mapa[29][29] = pared_item;
      mapa[31][29] = pared_item;
      mapa[33][24] = pared_item;
      mapa[33][45] = pared_item;
      mapa[40][20] = pared_item;
      mapa[41][33] = pared_item;
      mapa[43][19] = pared_item;
      mapa[49][41] = pared_item;
      mapa[49][42] = pared_item;
      break;
      case 9:
      mapa[4][36] = pared_item;
      mapa[4][43] = pared_item;
      mapa[5][10] = pared_item;
      mapa[5][17] = pared_item;
      mapa[6][13] = pared_item;
      mapa[6][14] = pared_item;
      mapa[6][25] = pared_item;
      mapa[10][36] = pared_item;
      mapa[13][42] = pared_item;
      mapa[15][42] = pared_item;
      mapa[18][4] = pared_item;
      mapa[25][21] = pared_item;
      mapa[25][30] = pared_item;
      mapa[25][31] = pared_item;
      mapa[25][32] = pared_item;
      mapa[27][29] = pared_item;
      mapa[28][29] = pared_item;
      mapa[29][10] = pared_item;
      mapa[31][29] = pared_item;
      mapa[32][29] = pared_item;
      mapa[41][33] = pared_item;
      mapa[43][19] = pared_item;
      mapa[49][41] = pared_item;
      mapa[49][44] = pared_item;
      break;
      }
  }
  return;
}

int condicion_victoria(int* estado){
  int aux1 = 0;
  int aux2 = 0;
  int aux3 = 0;
  for(int i = 0; i < 5; i++){
    aux2 = aux2 + estado[i * 13 + 3];
    aux3 = aux3 + estado[i * 13 + 3];
  }
  for(int i = 5; i < 10; i++){
    aux1 = aux1 + estado[i * 13 + 3];
    aux3 = aux3 + estado[i * 13 + 3];
  }
  for(int i = 10; i < 15; i++){
    aux1 = aux1 + estado[i * 13 + 3];
    aux2 = aux2 + estado[i * 13 + 3];
  }
  if (aux1 == 0 && aux2 == 0 && aux3 == 0){
    return 4;
  }
  else if (aux3 == 0){
    return 3;
  }
  else if (aux2 == 0){
    return 2;
  }
  else if (aux1 == 0){
    return 1;
  }
  else{
    return 0;
  }
}

// Función principal
int main(){
	FILE *log;
	log = fopen("log.txt", "w");
	fprintf(log, "Fecha           Accion realizada\n");
	fprintf(log, "-------------------------------------------------------------------------------------\n");
	t = time(NULL);
	tm = *localtime(&t);
	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(log, "Inicio del programa \n");
  srand(time(NULL));
  personaje jugador;
  personaje enemigo;

  int opcion;
  opcion = 3;
  while(opcion != 2){
    printf("Elige una opción:\n");
    printf("1. Instrucciones\n");
    printf("2. Jugar\n");
    printf("3. Salir\n");
    scanf("%d", &opcion);
    switch(opcion){
      case 1:
        printf("\nInstrucciones:\n");
        printf("El juego consiste en una lucha campal, se podra elegir luchar contra un enemigo o dos\n");
        printf("El campo de batalla son 50 casillas en donde los equipos apareceran en lugares semi-aleatorios\n");
        printf("Al inicio se elegira entre 6 roles, cada uno con estadisticas, armas y objetos distintos\n");
        printf("   El Sniper posee 1000 puntos de vida, se mueve 4 casillas, tiene un Francotirador y una Pistola\n");
        printf("       sus objetos son dos Diazepam y un Botiquín\n");
        printf("   El Ranger posee 1500 puntos de vida, se mueve 5 casillas, tiene un Fusil y una Espada\n");
        printf("       sus objetos son una Granada y un Botiquín\n");
        printf("   El Grenadier posee 1200 puntos de vida, se mueve 4 casillas, tiene un Escopeta y una Pistola\n");
        printf("       sus objetos son dos Granadas\n");
        printf("   El Specialist posee 1000 puntos de vida, se mueve 4 casillas, tiene un Francotirador y una Pistola\n");
        printf("       sus objetos son dos Botiquines\n");
        printf("   El Cannibal posee 1000 puntos de vida, se mueve 4 casillas, tiene un Escopeta y una Pistola\n");
        printf("       sus objetos son una Granada y un Monster\n");
        printf("   El Volatile posee 1000 puntos de vida, se mueve 4 casillas, tiene un Ametralladora y una Espada\n");
        printf("       sus objetos son una TNT y un C4\n\n");
        printf("Las armas tienen distintas estadisticas, como balas y daño que realizan\n");
        printf("   El Fusil tiene un daño de 200, tiene 4 capacidades de disparo previo a recargar\n");
        printf("       por defecto tiene una precision del 100 porciento a 3 cuadros y pierde un 6 porciento por cada cuadro extra\n");
        printf("   El Francotirador tiene un daño de 400, tiene 2 capacidades de disparo previo a recargar\n");
        printf("       por defecto tiene una precision del 100 porciento a 5 cuadros y pierde un 3 porciento por cada cuadro extra\n");
        printf("   La Escopeta tiene un daño de 600, tiene 3 capacidades de disparo previo a recargar\n");
        printf("       por defecto tiene una precision del 100 porciento a 2 cuadros y pierde un 20 porciento por cada cuadro extra\n");
        printf("   La Pistola tiene un daño de 100, tiene 6 capacidades de disparo previo a recargar\n");
        printf("       por defecto tiene una precision del 100 porciento a 3 cuadros y pierde un 8 porciento por cada cuadro extra\n");
        printf("   La Espada tiene un daño de 300, tiene capacidades de uso practicamente infinito previo a recargar\n");
        printf("       por defecto tiene una precision del 100 porciento a 1 cuadros y pierde un 90 porciento por cada cuadro extra\n");
        printf("   La Ametralladora tiene un daño de 300, tiene 4 capacidades de disparo previo a recargar\n");
        printf("       por defecto tiene una precision del 100 porciento a 3 cuadros y pierde un 25 porciento por cada cuadro extra\n\n");
        printf("Se puede tener un maximo de 3 objetos, los cuales se dividen en dos tipos ataque o apoyo\n");
        printf("   La granada tiene un daño de 500 con una precision del 75 porciento a 3 cuadros y pierde un 20 porciento por cada cuadro extra\n");
        printf("   La TNT tiene un daño Maximo con una precision del 100 porciento a 3 cuadros y pierde un 100 porciento por cada cuadro extra\n");
        printf("   El C4 tiene un daño de 700 con una precision del 100 porciento a 3 cuadros y pierde un 20 porciento por cada cuadro extra\n");
        printf("   La Monster aumenta la capacidad de movimiento por 2 casillas extra durante 2 turnos\n");
        printf("   El Botiquín restaura 500 puntos la vida del jugador que lo uso o del que esta adyacente\n");
        printf("       si se es Specialist restaurara 250 puntos mas\n");
        printf("   El Diazepam aumenta la precisión un 20 porciento durante 2 turnos\n");
        printf("\n\n");
        printf("Durante el juego:\n");
        printf("Cuando se elige moverse\n");
        printf("    El jugador podra moverse una casilla con las teclas w-a-s-d (W: Arriba ; A: Izquierda ; S: Abajo ; D: Derecha)\n");
        printf("        Este movimiento se puede hacer en base a la cantidad de energia que tiene cada personaje, gastando 1 por casilla\n");
        printf("        El Usuario podra saltar obstaculos solo si hay un espacio libre (un Pastizal) pero gastara mas energia\n");
        printf("    El jugador podra disparar al personaje (sea Enemigo o Aliado) que estime conveniente dentro del mapa\n");
        printf("    El jugador podra recargar sus armas y esta accion volvera a la cantidad de balas inicial del arma\n");
        printf("    El jugador podra pasar su turno\n");
        printf("    El jugador no podra salir del mapa\n\n");
		fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
		fprintf(log, "el jugador reviso las instrucciones\n");
      break;
      case 2:
	    fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
		fprintf(log, "el jugador inicio el juego shotrol\n");
      break;
      case 3:
	 	t = time(NULL);
		tm = *localtime(&t);
	  	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
		fprintf(log, "fin de simulacion\n");
		fclose(log);
        exit(0);
      break;
    }
  }
  int **mapa;
  int *estado = (int*)malloc(sizeof(int) * 196);
  int numero_alea = 3; // eleccion de mapa
  int fila;
  int columna;
  int decisiones;
  printf("elija entre nueva partida o cargar partida\n");
  printf("1. nueva partida\n");
  printf("2. cargar partida\n");
  scanf("%d",&decisiones);
  if(decisiones == 1){
    mapa = crear_mapa(numero_alea, &fila, &columna, estado, mapa);
  }
  else{
    mapa = leer_partida(mapa, estado, &fila, &columna);
    int aux = mapa[35][4];
    switch (aux){
      case camino:
        numero_alea = 1;
      break;
      case pared_alta:
        numero_alea = 2;
      break;
      case pared_completa:
        numero_alea = 3;
      break;
    }
  }
  salto(2);


  int fila_local = fila;
  int columna_local = columna;
  localizar(mapa, &fila_local, &columna_local, 1);

  int **minimap;
  minimap = mapa_num(7, 7);

  int i = 6;
  int j = 0;
  int victoria = 0;
  // Bucle principal del juego
  while (victoria == 0){
    aparicion_item(mapa, numero_alea, estado);
    // aqui deberian moverse los enemigos V y despues L, esto no se mostrara al jugador
    
    // Mostrar el estado del juego y opciones al jugador
    ya(1);
    i = 1;
    j = 0;
    while(i < 6){
      fila_local = fila; columna_local = columna;
      localizar(mapa, &fila_local, &columna_local, equipo_aliado + i - 1);
      if(fila_local != fila && columna_local != 0){
        guardar_partida(mapa, estado, fila, columna);
        ubicar(mapa,minimap,fila_local,columna_local);
        actualizar_matriz(minimap,estado,fila,columna);
        printf("Jugador %d:\n",i);
        printf("Rol: ");
        traducir_rol(estado[(i - 1) * 13 + 1]);
        printf("Salud: %d\n",estado[(i - 1) * 13 + 2]);
        printf("Movimientos: %d\n",estado[(i - 1) * 13 + 4]);
        printf("Primer arma: ");
        traducir_arma(estado[(i - 1) * 13 + 5]);
        printf(", con %d balas\n", estado[(i - 1) * 13 + 6]);
        printf("Segundo arma: ");
        traducir_arma(estado[(i - 1) * 13 + 8]);
        printf(", con %d balas\n", estado[(i - 1) * 13 + 9]);
        printf("sus objetos son: ");
        traducir_objeto(estado[(i - 1) * 13 + 11]);
        traducir_objeto(estado[(i - 1) * 13 + 12]);
        traducir_objeto(estado[(i - 1) * 13 + 13]);
        int eleccion;
        int cual;
        printf("Selecciona una acción:\n");
        printf("1. Mover\n");
        printf("2. Disparar\n");
        printf("3. Recargar\n");
        printf("4. Usar objeto\n");
        printf("5. Tomar objetos\n");
        printf("6. Saltar\n");
        printf("7. Salir. ");
        printf("Nota: se perdera el progreso no guardado, practicamente todo\n");
        scanf("%d", &eleccion);
        
        switch (eleccion) {
          case 1:
		t = time(NULL);
		tm = *localtime(&t);
		fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
		fprintf(log,"turno del jugador %d \n",i);
            movimiento(mapa,minimap,estado,&fila_local,fila,&columna_local,columna,estado[(i - 1) * 13 + 4],log);
            break;
          case 2:
		t = time(NULL);
		tm = *localtime(&t);
		fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
		fprintf(log,"turno del jugador %d \n",i);
            printf("Elige el arma a disparar:\n");
            printf("1. Primer arma\n");
            printf("2. Segundo arma\n");
            scanf("%d", &cual);
            disparando(mapa, fila, columna, estado, equipo_aliado + i - 1, i, cual,log);
          // Llama a la función para disparar
          break;
          case 3:
		t = time(NULL);
		tm = *localtime(&t);
		fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
		fprintf(log,"turno del jugador %d \n",i);
            printf("Elige el arma a recargar:\n");
            printf("1. Primer arma\n");
            printf("2. Segundo arma\n");
            scanf("%d", &cual);
            recargar(estado, i, cual);
          // Llama a la función para recargar
          break;
          case 4:
		t = time(NULL);
		tm = *localtime(&t);
		fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
		fprintf(log,"turno del jugador %d \n",i);
            printf("Elige el objeto a usar:\n");
            printf("1. Primer objeto\n");
            printf("2. Segundo objeto\n");
            printf("3. Tercer objeto\n");
            scanf("%d", &cual);
            usarObjeto_botiquin(estado, i, cual,log);
          // Llama a la función para usar objeto
          break;
          case 5:
		t = time(NULL);
		tm = *localtime(&t);
		fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
		fprintf(log,"turno del jugador %d \n",i);
            tomar_item(mapa, fila, columna, estado, equipo_aliado + i - 1);
            j --;
          break;
          case 6:
		t = time(NULL);
		tm = *localtime(&t);
		fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
		fprintf(log,"turno del jugador %d \n",i);
		fprintf(log,"jugador %d ha saltado el turno\n",i);
          break;
          case 7:
          // Salir del juego
            exit(0);
          default:
            printf("Opción no válida\n");
          }
        j ++;
        if(j == 2){
          j = 0;
          i ++;
        }
        }
      else{
        i ++;
      }
    }
    estado[0] ++;
    victoria = condicion_victoria(estado);
  }
  switch(victoria){
    case 1:
	t = time(NULL);
	tm = *localtime(&t);
	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(log,"el equipo del jugador ha ganado la partida\n");
	fclose(log);
      printf("El Jugador ha ganado la contienda\n");
      break;
    case 2:
	t = time(NULL);
	tm = *localtime(&t);
	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(log,"el equipo L ha ganado la partida\n");
	fclose(log);
      printf("El Equipo L ha ganado la batalla\n");
      break;
    case 3:
	t = time(NULL);
	tm = *localtime(&t);
	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(log,"El equipo V ha ganado la partida\n");
	fclose(log);
      printf("El Equipo V ha ganado la guerra\n");
      break;
    default:
	t = time(NULL);
	tm = *localtime(&t);
	fprintf(log, "%d.%d.%d_%d:%d   ", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(log,"Los equipos han empatado\n");
	fclose(log);
      printf("El juego ha terminado en empate\n");
  }
  free(estado);
  liberar_memoria_n(mapa, columna);
  liberar_memoria_n(minimap, 7);
  return 0;
}
