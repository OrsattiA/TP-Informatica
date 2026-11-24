#include <stdio.h>
#include <string.h>

//--------------------FUNCIONES ENUNCIADO 1--------------------

void buscarCancion(char codigo[400][6], char titulo[400][21], char artista[400][21], int duracion[400], char codigoCancionBuscado[6])
{
    int i = 0;

    while (i < 400 && strcmp(codigo[i], codigoCancionBuscado) != 0) //Buscas el indice que se corresponda, si exsite, con el codigoCancionBuscado.
    {
        i++;
    }

    if(i<400)
    {
        printf("---------------------------------------------------------------------------------------------------\n");
        printf("El codigo de cancion buscado (%s) tiene asociado las siguientes caracteristicas: \n", codigoCancionBuscado);
        printf("Titulo: %s\n", titulo[i]);
        printf("Artista: %s\n", artista[i]);
        printf("Duracion: %d segundos\n", duracion[i]);
        printf("---------------------------------------------------------------------------------------------------\n");
    }
    else
    {
        printf("---------------------------------------------------------------------------------------------------\n");
        printf("El codigo ingresado (%s) no tiene asociada ninguna cancion en el catalogo.\n", codigoCancionBuscado);
        printf("---------------------------------------------------------------------------------------------------\n");
    }
}

void mostrarPorcentajeAbandonadas(float porcentajeReproduccionesAbandonadas)
{
    /*
    Propósito: Muestra por pantalla el porcentaje calculado previamente en cargarReproduccionesValidas
    */

    if(porcentajeReproduccionesAbandonadas < 0)
    {
        printf("---------------------------------------------------------------------------------------------------\n");
        printf("El archivo no posee reproducciones.\n");
        printf("---------------------------------------------------------------------------------------------------");
    }
    else
    {
        printf("---------------------------------------------------------------------------------------------------\n");
        printf("El porcentaje de reproducciones abandonadas es: %f %%.\n", porcentajeReproduccionesAbandonadas);
        printf("---------------------------------------------------------------------------------------------------");
    }
}


//--------------------FUNCIONES ENUNCIADO 2 y 3--------------------

void cargarCanciones(char codigoCancion[400][6], char titulo[400][21], char artista[400][21], int duracion[400])
{
    /*
    Proposito: Lee el archivo canciones.txt, y devuelve, por referencia, los arreglos con los respectivos datos cargados.
    */
    FILE *canciones;
    canciones = fopen("canciones.txt", "r"); //abrimos canciones.txt y obtenemos la información útil
    int i = 0;
    char genero;

    while(!feof(canciones))
    {
        fscanf(canciones, "%s %s %s %c %d", codigoCancion[i], titulo[i], artista[i], &genero, &duracion[i]);
        i++;
    }

    fclose(canciones); //cerramos canciones.txt
}

void cargarReproduccionesValidas(char codigoCancion[400][6], int reproduccionesValidas[400],int cantidadReproduccionesvalidapais[120], char listapaises[120][3], float *porcentajeReproduccionesAbandonadas)
{
    /*
    Proposito: Lee el archivo reproducciones.txt, y devuelve, por referencia, el arreglo reproduccionesValidas con los respectivos datos cargados
    asi como tambien cuenta la cantidad de reproducciones, las reproducciones abandonadas, y devuelve el porcentaje de las mismas sobre el total.
    */

    FILE *reproducciones;
    reproducciones = fopen("reproducciones.txt", "r");
    char codigoCancionReproduccion[6]; //5 caracteres mas \0
    char codigoPaisReproduccion[3];
    int diaReproduccion;
    int mesReproduccion;
    int segundosEscuchados;
    char dispositivoReproduccion;

    int cantidadReproduccionesAbandonadas = 0;
    int cantidadReproducciones = -1;
    //Se resta 1 porque se cuenta a la ultima linea (que esta vacia) como una reproduccion más.
    //Ademas, si no hay reproducciones es un valor bandera que nos indica justamente eso.

    while(!feof(reproducciones))
    {
        fscanf(reproducciones, "%s %s %d %d %d %c", codigoCancionReproduccion, codigoPaisReproduccion, &diaReproduccion, &mesReproduccion, &segundosEscuchados, &dispositivoReproduccion);

        if(segundosEscuchados >= 30) //Si es una reproduccion válida
        {
            int i = 0;
            while(strcmp(codigoCancionReproduccion, codigoCancion[i]) != 0)
            {
                i++; //Buscas la cancion a la que pertenece la reproduccion, mediante ver en qué indice está en códigoCancion

            }
            reproduccionesValidas[i]++; //Sumas una reproduccion válida
            //buscar pais
            int cont=0;
            while (cont<120 && (strcmp(codigoPaisReproduccion, listapaises[cont]) !=0)){
                cont=cont+1;
            }
            cantidadReproduccionesvalidapais[cont]=cantidadReproduccionesvalidapais[cont]+1;
            }
        else
        {
            cantidadReproduccionesAbandonadas++;
        }
        cantidadReproducciones++;
    }
    cantidadReproducciones--; //Se resta 1 porque se cuenta a la ultima linea (que esta vacia) como una reproduccion más.
    *porcentajeReproduccionesAbandonadas = (cantidadReproduccionesAbandonadas * 1.0 / cantidadReproducciones * 1.0) * 100;

    fclose(reproducciones);
}

void diezCancionesMasReproducidas(char codigodecaciones[400][6], int reproduccionesvalidas[400], char topdiez[10][6]){
    int aux;
    char aux2[6];

    for(int i = 0; i < 399;i++)
    {
        for(int j=0;j<399-i;j++)
        {
            if(reproduccionesvalidas[j]<reproduccionesvalidas[j+1]){
                //ordeno reproducciones validas
                aux=reproduccionesvalidas[j];
                reproduccionesvalidas[j]=reproduccionesvalidas[j+1];
                reproduccionesvalidas[j+1]=aux;
                //ordeno el arreglo de los codigosdecaciones
                strcpy(aux2, codigodecaciones[j]);
                strcpy(codigodecaciones[j], codigodecaciones[j+1]);
                strcpy(codigodecaciones[j+1], aux2);
            }
        }
    }

    for(int l=0;l<10;l++)
    {
        strcpy(topdiez[l],codigodecaciones[l]); //Obtenes los 10 codigos que pertenecientes a las canciones con más reproducciones
    }
}

void obtenerTop10Canciones(char codigoCancion[400][6], int reproduccionesValidas[400], int top10Canciones[10])
{
    /*
    Proposito: Ordena de mayor a menor una copia de los arreglos apareados, y devuelve una lista con los indices de las 10 canciones con mas reproducciones
    */

    char codigoTopDiezCanciones[10][6];
    char codigoCancionesCopia[400][6];
    int reproduccionesValidasCopia[400];

    for(int i = 0; i < 400; i++)
    {
        strcpy(codigoCancionesCopia[i], codigoCancion[i]); //Copiamos codigoCancion para pasarlo por valor y no por referencia.
    }
    for(int i = 0; i < 400; i++)
    {
        reproduccionesValidasCopia[i] = reproduccionesValidas[i]; //Copiamos reproduccionesValidas para pasarlo por valor y no por referencia.
    }

    diezCancionesMasReproducidas(codigoCancionesCopia, reproduccionesValidasCopia, codigoTopDiezCanciones);

    int j;
    for(int i = 0; i < 10; i++)
    {
        j = 0;
        while(strcmp(codigoCancion[j], codigoTopDiezCanciones[i]) != 0)
        {
            j++;
        }
        top10Canciones[i] = j; //Le asignás el indice que contiene a ese codigo, que es uno de las 10 canciones con más reproducciones.
    }

}
void cargapaisesyregalias (char listapaises[120][3],float regalia[120],char nombrepaises[120][16]){
    FILE *paises;
    int i=0;
    paises=fopen("paises.txt","r");
    while(i < 120 && fscanf(paises, "%2s %19s %f", listapaises[i], nombrepaises[i], &regalia[i]) == 3){
        i=i+1;
    }
    fclose(paises);
}
void CARGA(char listapaises[120][3],float regalia[120], char codigoCancion[400][6], char titulo[400][21], char artista[400][21], int duracion[400], int reproduccionesValidas[400], int top10Canciones[10], int cantidadReproduccionesvalidapais[120],float regaliascalulada[120], char nombrepaises[120][16], float *porcentajeReproduccionesAbandonadas)
{
    /*
    Propósito: Lee los archivos 1 vez y recopila, a través de arreglos apareados, todos los datos necesarios para la resolución del problema.
    */

    cargarCanciones(codigoCancion, titulo, artista, duracion);
    //Cargas, a traves de una subrutina auxiliar, cada uno de los codigos, titulos, artista, genero y duracion de todas las canciones

    //Cargamos los paises
    cargapaisesyregalias(listapaises, regalia, nombrepaises);

    for(int i = 0; i < 400; i++)
    {
        reproduccionesValidas[i] = 0;
        //Inicializamos en 0 todo el arreglo que contiene las reproducciones validas, porque puede ser que haya canciones que no tengan reproducciones válidas.
    }
     for(int i = 0; i < 120; i++)
    {
        cantidadReproduccionesvalidapais[i] = 0;
        //Inicializamos en 0 todo el arreglo que contiene las cantidad de reproducciones validad en un pais.
    }
    cargarReproduccionesValidas(codigoCancion, reproduccionesValidas, cantidadReproduccionesvalidapais, listapaises, porcentajeReproduccionesAbandonadas);
    //Cargas, a traves de una subrutina auxiliar, las reproducciones validas de cada cancion en el indice respectivo.
    obtenerTop10Canciones(codigoCancion, reproduccionesValidas, top10Canciones);
     for(int i = 0; i < 120; i++)
    {
        regaliascalulada[i] = 0;
    }
    for(int i = 0; i < 120; i++){
        regaliascalulada[i]=regalia[i]*cantidadReproduccionesvalidapais[i];
    }
}

//--------------------FUNCION MENU Y AUXILIARES--------------------

void pedirCodigoCancion(char codigoCancionBuscado[6])
{
    /*
    Propósito: Pide la direccion de memoria en donde esta el codigo de la cancion buscado, y escribe en ella lo que el usuario le dice.
    */
    printf("Ingrese el codigo de la cancion que quiere buscar: ");
    scanf("%s", codigoCancionBuscado);
}

void validacionOpcionElegida(int *opcionElegida)
{
    /*
    Propósito: Bloquea el avance del programa principal hasta que opcionElegida es una de las 3 opciones válidas.
    */

    while(*opcionElegida < 1 || *opcionElegida > 5) //repetir mientras
        {
            printf("La opcion ingresada es incorrecta, reintente: ");
            scanf("%d", opcionElegida);
        }
}

void mostrarOpciones()
{
    /*
    Proposito: Imprime en pantalla todas las opciones.
    */
    printf("\nMenu de opciones:\n");
    printf("1. Consultar la duracion de una cancion.\n");
    printf("2. Calcular el porcentaje de reproducciones abandonadas.\n");
    printf("3. Mostrar 10 canciones con más reproducciones.\n");
    printf("4. Mostrar el pais con mas regalias.\n");
    printf("5. Salir.\n");
}

void pedirOpcion(int *opcionElegida)
{
    /*
    Propósito: Pide la opcion en el menú y no termina hasta que sea una opción válida (gracias a validacionOpcionElegida).
    */
    printf("\nIngrese la opcion deseada: ");
    scanf("%d", opcionElegida);
    validacionOpcionElegida(opcionElegida); //La validación dentro de una subrutina, como dijo Javi.
}

void mostrarTop10Canciones(int top10Canciones[10], char titulo[400][21], char artista[400][21], int reproduccionesValidas[400])
{
    printf("---------------------------------------------------------------------------------------------------\n");
    for(int i = 0; i < 10; i++)
    {
        printf("%d. %s - %s : %d reproducciones.\n", i+1, titulo[top10Canciones[i]], artista[top10Canciones[i]], reproduccionesValidas[top10Canciones[i]]);
    }
    printf("---------------------------------------------------------------------------------------------------");
}

void paismaxregalia(float regaliascalulada[120], char nombrepaises[120][16])
{    
    int max=0;
    for(int i = 0;i<119;i++)
    {
        if(regaliascalulada[i]>regaliascalulada[max])
        {
           max=i;
        }
    }

    for(int i = 0;i<119;i++){
        if(regaliascalulada[i]==regaliascalulada[max])
        {
            printf("---------------------------------------------------------------------------------------------------\n");
            printf("El pais con más regalías es: %s con $%f \n", nombrepaises[i],regaliascalulada[i]);
            printf("---------------------------------------------------------------------------------------------------\n");
        }
    }
}

void MENU(char codigoCancion[400][6], char titulo[400][21], char artista[400][21], int duracion[400], int reproduccionesValidas[400], int top10Canciones[10],float regaliascalulada[120], char nombrepaises[120][16], float porcentajeReproduccionesAbandonadas)
{
    /*
    Proposito: Se encarga de interactuar con el usuario y guiar el curso del programa.
    */
    int opcionElegida;

    mostrarOpciones(); //Primero mostramos las opciones
    pedirOpcion(&opcionElegida); //Despues pedimos y validamos.

    while(opcionElegida != 5) //Repetir mientras <> 5 (el usuario no quiera salir)
    {
        switch(opcionElegida) //Segun sea
        {
            case 1:
            {

                char codigoCancionBuscado[6];
                pedirCodigoCancion(codigoCancionBuscado); //La subrutina pedirCodigoCancion interactua con el usuario, y guarda eso en codigoCancionBuscado.
                buscarCancion(codigoCancion, titulo, artista, duracion, codigoCancionBuscado);
                break;

            }
            case 2:
            {
                mostrarPorcentajeAbandonadas(porcentajeReproduccionesAbandonadas);
                break;
            }
            case 3:
            {
                mostrarTop10Canciones(top10Canciones, titulo, artista, reproduccionesValidas);
                break;
            }
            case 4:
            {
                paismaxregalia(regaliascalulada, nombrepaises);
                break;
            }
            case 5:
            {
                break; //Si la opcion es la 5, sale. Nunca se da este caso, su unico proposito es esclarecer la logica del codigo.
            }
        }

        mostrarOpciones(); //Escribir
        pedirOpcion(&opcionElegida); //Leer (garantizamos que se pueda salir del bucle).
    }
}


int main(){

    char codigoCancion[400][6]; //5 letras mas \0
    char titulo[400][21];
    char artista[400][21];
    char listapaises[120][3];
    char nombrepaises[120][16];
    int duracion[400];
    int reproduccionesValidas[400]; //Reproducciones válidas correspondientes a las 400 canciones
    int cantidadReproduccionesvalidapais[120];
    int top10Canciones[10]; //Un arreglo de enteros, ordenados de mayor a menor, en donde cada uno de sus elementos es el índice de la cancion con mas reproducciones
    float porcentajeReproduccionesAbandonadas;
    float regalia[120];
    float regaliascalulada[120];

    CARGA(listapaises, regalia, codigoCancion, titulo, artista, duracion, reproduccionesValidas, top10Canciones, cantidadReproduccionesvalidapais, regaliascalulada, nombrepaises, &porcentajeReproduccionesAbandonadas);
    
    MENU(codigoCancion, titulo, artista, duracion, reproduccionesValidas, top10Canciones, regaliascalulada, nombrepaises, porcentajeReproduccionesAbandonadas);

    return 0;
}
