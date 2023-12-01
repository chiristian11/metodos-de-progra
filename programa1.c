#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definiciones de estructuras
typedef struct {
    int salud;
    int salud_maxima;
    int movimientos;
    char arma[20];
    int municion;
    // Otras propiedades del personaje
} Personaje;

typedef struct {
    int x;
    int y;
} Posicion;

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
    int m;
    n = rand() % 4 + 1;
    switch(tipo){
      case 1:
      m = rand() % 2 + 1;
      if(m == 1){
          letra = 'L';
          letra2 = 'E';
      }
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
      break;
      default:
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
      break;
      default:
      break;
      }
    return;
}

void dificultad(char **mapa,int tipo,int enemigov,int enemigol){
    //implementa el lugar de jugadores en el mapa
    char letra;
    char letra2;
    char letra3;
    if(enemigov == 0){
        letra = 'E';
        letra2 = 'L';
        dificultad_medio(mapa, tipo, letra, letra2);
        }
    else if(enemigol == 0){
        letra = 'E';
        letra2 = 'V';
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
    int remplazo_c = 1;
    char pared_a = '/';
    int remplazo_a = 2;
    char comida_b = '+';
    int remplazo_b = 3;
    char aliado = 'E';
    int remplazo_s = 9;
    char enemigo_l = 'L';
    int remplazo_l = 8;
    char enemigo_v = 'V';
    int remplazo_v = 7;
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

void ubicar(int **mapa,int **minimap,int fila,int columna){
    int aux = columna - 3;
    fila = fila - 3;
    for(int i = 0;i < 7;i++){
        columna = aux;
        for(int j = 0;j < 7;j++){
            if(fila < 0 || fila > 49 || columna < 0 || columna > 49){
                minimap[i][j] = 1; // Alerta, cambiar a numero de pared c
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
    if(*columna < columna_max - 1){
        signo = mapa[*fila][*columna + 1];
        }
    *energia = *energia - 1;
    if (signo == 0){
        mapa[*fila][*columna + 1] = mapa[*fila][*columna];
        mapa[*fila][*columna] = 0;
        *columna = *columna + 1;
    }
    else if(signo == 3 && mapa[*fila][*columna + 2] == 0 && *energia >= 1){
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
    if(*fila < fila_max - 1){
        signo = mapa[*fila + 1][*columna];
        }
    *energia = *energia - 1;
    if (signo == 0){
        mapa[*fila + 1][*columna] = mapa[*fila][*columna];
        mapa[*fila][*columna] = 0;
        *fila = *fila + 1;
    }
    else if(signo == 3 && mapa[*fila + 2][*columna] == 0 && *energia >= 1){
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
    if(*columna > 0){
        signo = mapa[*fila][*columna - 1];
        }
    *energia = *energia - 1;
    if (signo == 0){
        mapa[*fila][*columna - 1] = mapa[*fila][*columna];
        mapa[*fila][*columna] = 0;
        *columna = *columna - 1;
    }
    else if(signo == 3 &&mapa[*fila][*columna - 2] == 0 && *energia >= 1){
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
    if(*fila > 0){
        signo = mapa[*fila - 1][*columna];
        }
    *energia = *energia - 1;
    if (signo == 0){
        mapa[*fila - 1][*columna] = mapa[*fila][*columna];
        mapa[*fila][*columna] = 0;
        *fila = *fila - 1;
    }
    else if(signo == 3 && mapa[*fila - 2][*columna] == 0 && *energia >= 1){
        if(*columna > 1){
            mapa[*fila - 2][*columna] = mapa[*fila][*columna];
            mapa[*fila][*columna] = 0;
            *fila = *fila - 2;
            *energia = *energia - 1;
            }
    }
    return;
}

// Recordar que en los movimientos, es necesario cambiar el valor de las paredes bajas/obstaculo
int movimiento(int **mapa,int **minimap,int *fila,int fila_max,int *columna,int columna_max,int energia){
    // Mueve el objeto en la zelda elegida hacia donde el jugador quiera dependiendo de las condiciones
    if(energia == 0)
        return 0;
    char mov;
    scanf("%c",&mov);
    switch (mov){
      case 'w':
          mover_arriba(mapa,fila,columna,&energia);
          ubicar(mapa,minimap,*fila,*columna);
          break;
      case 'a':
          mover_izquierda(mapa,fila,columna,&energia);
          ubicar(mapa,minimap,*fila,*columna);
          break;
      case 's':
          mover_abajo(mapa,fila,columna,fila_max,&energia);
          ubicar(mapa,minimap,*fila,*columna);
          break;
      case 'd':
          mover_derecha(mapa,fila,columna,columna_max,&energia);
          ubicar(mapa,minimap,*fila,*columna);
          break;
      case 'q':
          energia = energia - 1;
          ubicar(mapa,minimap,*fila,*columna);
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

void moverPersonaje(Personaje *personaje, Posicion *posicion, int direccion) {
    // Implementa el movimiento del personaje
}

void disparar(Personaje *atacante, Personaje *objetivo) {
    // Implementa la lógica de disparo
}

void recargar(Personaje *personaje) {
    // Implementa la recarga de munición
}

void usarObjeto(Personaje *personaje, char *objeto) {
    // Implementa el uso de objetos
}

// Función principal
int main() {
    Personaje jugador;
    Personaje enemigo;
    Posicion posicionJugador;
    Posicion posicionEnemigo;

    // Inicializa las propiedades de los personajes y posiciones
    // Aqui empieza lo que realize
    srand(time(NULL));
    char **mapabase;
    int numero_alea = 1;
    int fila;
    int columna;
    int dificultad;
    printf("Eliga cuantos equipos enemigos quieres en el mapa: ");
    scanf("%d",&dificultad);
    if(dificultad > 1){
        printf("\nHabran 2 equipos enemigos... destruyelos");
        mapabase = lector(numero_alea,&fila,&columna,2);
    }
    else{
        printf("\nHabra 1 equipo enemigo... destruyelo");
        mapabase = lector(numero_alea,&fila,&columna,1);
    }
    

    salto(1);

    int **mapa;
    mapa = transformada(mapabase, fila, columna);

    salto(5);

    int fila_local = fila;
    int columna_local = columna;
    localizar(mapa, &fila_local, &columna_local, 9);// 9 es el personaje a mover

    int **minimap;
    minimap = mapa_num(7, 7);
    ubicar(mapa,minimap,fila_local,columna_local);
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
    liberar_memoria_c(mapabase, fila);
    liberar_memoria_n(mapa, columna);
    liberar_memoria_n(minimap, 7);
    return 0;
}
