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

void desplegarMenu(FILE *canciones, FILE *reproducciones)
{
    reproducciones = fopen("reproducciones_cn.txt", "r"); // IGNORAR. ES PARA QUE ANDE EL PROGRAMA POR AHORA, HASTA QUE HAGAMOS LA 2.
    fclose(reproducciones); // IGNORAR. ES PARA QUE ANDE EL PROGRAMA POR AHORA, HASTA QUE HAGAMOS LA 2.
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
                //IMPLEMENTAR Caso 2
                break;
            }
            case 3:
            {
                break;
            }
        }
        mostrarOpciones();
        pedirOpcion(&opcionElegida);
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
