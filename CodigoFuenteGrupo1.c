#include <stdio.h>
#include <string.h>

//----------FUNCIONES ENUNCIADO 1----------

void pedirCodigoCancion(int *codigoCancionBuscado) //se pide el parámetro con el * por 2 razones: 1, solo las subrutinas pueden interactuar con el usuario. Y 2, C asi lo requiere.
{
    /*
    Propósito: Pide la direccion de memoria en donde esta el codigo de la cancion buscado, y escribe en ella lo que el usuario le dice. 
    */
    printf("Ingrese el codigo de la cancion que quiere buscar: ");
    scanf("%d", codigoCancionBuscado);
}

void validacionOpcionElegida(int *opcionElegida)
{
    /*
    Propósito: Bloquea el avance del programa principal hasta que opcionElegida es una de las 3 opciones válidas.
    */
    while(*opcionElegida != 1 && *opcionElegida != 2 && *opcionElegida != 3) //repetir mientras
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
    printf("3. Salir\n");
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

void buscarCancion(FILE *canciones, int codigoCancionBuscado)
{
    /*
    Propósito: Busca el codigo de la cancion: Si existe, imprime el titulo, el artista y el genero; si no, indica que ese codigo no tiene asociado ninguna cancion.
    */

    if(canciones == NULL) 
    {//si el archivo no está abierto:
        canciones = fopen("canciones_cn.txt", "r"); //lo abre
    }

    fseek(canciones, 0, SEEK_SET); //Si ya lo está: Que vuelva a la primer linea.
    //Hacer estos 2 pasos es util, porque si el usuario solo quiere calcular el porcentaje u otras opciones, no hace falta que el sistema
    //cargue en memoria todo el archivo canciones, con sus 400 lineas.

    int codigoCancion, duracion;
    char titulo[21], artista[21], genero; // "cadena de hasta 20 caracteres" afirma el enunciado
    int seEncontroCancion = 0; //bandera

    while(!feof(canciones)) // ¿&& seEncontroCancion != 1? así sale del repetir mientras una vez que encontró la cancion buscada
    {
        fscanf(canciones ," %d %s %s %c %d", &codigoCancion, titulo, artista, &genero, &duracion);
        if(codigoCancion == codigoCancionBuscado)
        {
            printf("---------------------------------------------------------------------------------------------------\n");
            printf("El codigo de cancion buscado (%d) tiene asociado las siguientes caracteristicas: \n", codigoCancionBuscado);
            printf("Titulo: %s\n", titulo);
            printf("Artista: %s\n", artista);
            printf("Genero: %c\n", genero);
            printf("---------------------------------------------------------------------------------------------------");
            seEncontroCancion = 1;
        }
    }

    //Se podría separar la parte de la búsqueda de la de mostrar. (Haciendo algo como char tituloEncontrado[21] y que cuando lo encuentre guarde su titulo)
    if(seEncontroCancion == 0) //si no se encontró:  
    {
        printf("---------------------------------------------------------------------------------------------------\n");
        printf("El codigo ingresado (%d) no tiene asociada ninguna cancion en el catálogo.\n", codigoCancionBuscado);
        printf("---------------------------------------------------------------------------------------------------");
    }
}

void mostrarPorcentajeReproduccionesAbandonadas(float porcentajeRepAbandonadas)
{
    /*
    Proposito: Imprime en pantalla, si hay, el porcentaje de reproducciones abandonadas, y si no, lo informa.
    */

    if(porcentajeRepAbandonadas == -1)
    {
        printf("---------------------------------------------------------------------------------------------------\n");
        printf("El archivo no posee reproducciones almacenadas en el.\n");
        printf("---------------------------------------------------------------------------------------------------");
    }
    else
    {
        printf("---------------------------------------------------------------------------------------------------\n");
        printf("El porcentaje de reproducciones abandonadas es de: %% %f\n", porcentajeRepAbandonadas);
        printf("---------------------------------------------------------------------------------------------------");
    }
}

float calcularPorcentajeAbandonadas(FILE *reproducciones)
{
    /*
    Propósito: Recorre reproducciones_cn.txt, contabiliza la cantidad de reproducciones y de reproducciones abandonadas, y devuelve el porcentaje.
    */

    reproducciones = fopen("reproducciones_cn.txt", "r"); //abrimos el archivo
    int codigoCancion;
    char pais[3];
    int dia, mes, segundosEscuchados;
    char dispositivo;

    int cancionesTotales = 0, reproduccionesAbandonadas = 0;

    while(!feof(reproducciones))
    {
        fscanf(reproducciones, " %d %s %d %d %d %c", &codigoCancion, pais, &dia, &mes, &segundosEscuchados, &dispositivo);
        if(segundosEscuchados < 30) //Las reproducciones consideradas abandonadas son aquellas que duran menos de 30 segundos.
        {
            reproduccionesAbandonadas++;
        }
        cancionesTotales++;
    }

    cancionesTotales--; //Esto es porque cuenta a la última linea como una canción (cuando es solo un \0) entonces la decrementamos en 1.

    fclose(reproducciones); //En un futuro, lo optimo sería abrir el archivo reproducciones.txt 1 sola vez y leerlo entero para completar todos los enunciados.

    if(cancionesTotales == 0)
    {
        return -1; //indica que no tiene canciones
    }
    else
    {
        return (reproduccionesAbandonadas * 1.0 / cancionesTotales * 1.0) * 100; //devuelve el porcentaje
    }
}

void MENU(char codigoCancion[400][6], char titulo[400][21], char artista[400][21], char genero[400], int duracion[400], int reproduccionesValidas[400])
{
    int opcionElegida;

    mostrarOpciones(); //Primero mostramos las opciones
    pedirOpcion(&opcionElegida); //Despues pedimos y validamos. 
    
    while(opcionElegida != 3) //Repetir mientras <> 3 (el usuario no quiera salir)
    { 
        switch(opcionElegida) //Segun sea
        {
            case 1: 
            {
                
                int codigoCancionBuscado;
                pedirCodigoCancion(&codigoCancionBuscado); //La subrutina pedirCodigoCancion interactua con el usuario, y guarda eso en codigoCancionBuscado.
                //buscarCancion(canciones, codigoCancionBuscado); ADAPTAR AL NUEVO FORMATO
                break;
                
            }
            case 2:
            {
                //float porcentajeRepAbandonadas = calcularPorcentajeAbandonadas(reproducciones); ADAPTAR AL NUEVO FORMATO
                //mostrarPorcentajeReproduccionesAbandonadas(porcentajeRepAbandonadas); ADAPTAR AL NUEVO FORMATO
                break;
            }
            case 3:
            {
                break;
            }
        }

        mostrarOpciones(); //Escribir
        pedirOpcion(&opcionElegida); //Leer (garantizamos que se pueda salir del bucle).
    }
}

//----------FUNCIONES ENUNCIADO 2----------

void cargarCanciones(char codigoCancion[400][6], char titulo[400][21], char artista[400][21], char genero[400], int duracion[400])
{
    /*
    Proposito: Lee el archivo canciones.txt, y devuelve, por referencia, los arreglos con los respectivos datos cargados.
    */
    FILE *canciones;
    canciones = fopen("canciones.txt", "r"); //abrimos canciones.txt y obtenemos la información útil
    int i = 0;

    while(!feof(canciones))
    {
        fscanf(canciones, "%s %s %s %c %d", codigoCancion[i], titulo[i], artista[i], &genero[i], &duracion[i]);
        i++;
    }

    fclose(canciones); //cerramos canciones.txt
}

void cargarReproduccionesValidas(char codigoCancion[400][6], int reproduccionesValidas[400])
{
    /*
    Proposito: Lee el archivo reproducciones.txt, y devuelve, por referencia, el arreglo reproduccionesValidas con los respectivos datos cargados.
    */
    FILE *reproducciones;
    reproducciones = fopen("reproducciones.txt", "r");
    char codigoCancionReproduccion[6]; //5 caracteres mas \0
    char codigoPaisReproduccion[3];
    int diaReproduccion;
    int mesReproduccion;
    int segundosEscuchados;
    char dispositivoReproduccion;

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
        }
    }

    fclose(reproducciones);
}

void CARGA(char codigoCancion[400][6], char titulo[400][21], char artista[400][21], char genero[400], int duracion[400], int reproduccionesValidas[400])
{
    /*
    Propósito: Lee los archivos 1 vez y recopila, a través de arreglos apareados, todos los datos necesarios para la resolución del problema.
    */

    cargarCanciones(codigoCancion, titulo, artista, genero, duracion); 
    //Cargas, a traves de una subrutina auxiliar, cada uno de los codigos, titulos, artista, genero y duracion de todas las canciones

    for(int i = 0; i < 400; i++)
    {
        reproduccionesValidas[i] = 0;
        //Inicializamos en 0 todo el arreglo que contiene las reproducciones validas, porque puede ser que haya canciones que no tengan reproducciones válidas.
    }

    cargarReproduccionesValidas(codigoCancion, reproduccionesValidas);
    //Cargas, a traves de una subrutina auxiliar, las reproducciones validas de cada cancion en el indice respectivo.
}

int main(){
    /*
        
    CONSIDERACIONES:
        TRATAR DE ABREVIAR LO MENOS POSIBLE
        NOMBRAR FUNCIONES/SUBRUTINAS CON LOS NOMBRES MÁS EXACTOS POSIBLES (NO IMPORTA LONGITUD)

    */
    char codigoCancion[400][6]; //5 letras mas \0
    char titulo[400][21];
    char artista[400][21];
    char genero[400];
    int duracion[400];
    int reproduccionesValidas[400]; //Reproducciones válidas correspondientes a las 400 canciones

    CARGA(codigoCancion, titulo, artista, genero, duracion, reproduccionesValidas);
    //CODIGO PARA PROBAR QUE FUNCIONA
    /*
    for(int j = 0; j < 400; j++)
    {
        printf("Codigo: %s\n", codigoCancion[j]);
        printf("Titulo: %s\n", titulo[j]);
        printf("Artista: %s\n", artista[j]);
        printf("Genero: %c\n", genero[j]);
        printf("Duracion: %d\n", duracion[j]);
        printf("Cantidad Rep. Validas: %d\n\n", reproduccionesValidas[j]);
    }
    
    printf("\nCodigo: %s\n", codigoCancion[219]);
    printf("Cantidad Rep. Validas: %d\n\n", reproduccionesValidas[219]);
    printf("Codigo: %s\n", codigoCancion[14]);
    printf("Cantidad Rep. Validas: %d\n\n", reproduccionesValidas[14]);
    */

    MENU(codigoCancion, titulo, artista, genero, duracion, reproduccionesValidas);

    return 0;
}
