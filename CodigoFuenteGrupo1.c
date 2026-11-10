#include <stdio.h>
#include <string.h>

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

void desplegarMenu(FILE *canciones, FILE *reproducciones)
{
    int opcionElegida;

    mostrarOpciones(); //Primero mostramos las opciones
    pedirOpcion(&opcionElegida); //Despues pedimos y validamos. 
    //Lo hacemos de la misma forma que lo venimos haciendo en informática. Primero pedimos, despues entramos al bucle, y finalmente volvemos a pedir.
    
    while(opcionElegida != 3) //Repetir mientras
    { 
        switch(opcionElegida) //Segun sea
        {
            case 1: 
            {
                int codigoCancionBuscado;
                pedirCodigoCancion(&codigoCancionBuscado); //La subrutina pedirCodigoCancion interactua con el usuario, y guarda eso en codigoCancionBuscado.
                buscarCancion(canciones, codigoCancionBuscado);
                break;
            }
            case 2:
            {
                float porcentajeRepAbandonadas = calcularPorcentajeAbandonadas(reproducciones);
                mostrarPorcentajeReproduccionesAbandonadas(porcentajeRepAbandonadas);
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

int main(){
    /*
    Cambios:
        -Borré seaValida()
        -Corregí las boludeces que pedía C para que nos ande el código a todos bien.
        -Hice que pedirCodigoCancion sea una subrutina que interactue con el usuario, y no una función.
        -Hice la validación de la opción elegida como una subrutina propia.
        -Adapté al pedir opciones al estándar de informática.
        -Hice que la muestra de las opciones y el pedido de las opciones sean sus propias subrutinas.
        -Hice el ejercicio 2.
    */

    FILE *canciones = NULL;
    FILE *reproducciones = NULL;
    desplegarMenu(canciones, reproducciones);

    if(canciones != NULL) //Si el archivo nunca se abrio, no debe de ser cerrado.
    {
        fclose(canciones);
    }

    return 0;
}
