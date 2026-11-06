#include <stdio.h>
#include <string.h>

int seaValida(int opcionElegida)
{
    if(opcionElegida != 1 && opcionElegida != 2 && opcionElegida != 3)
    {
        return 1;
    }
    return 0;
}

int pedirCodigoCancion() //una funcion interactuando con un usuario ¿correcto o incorrecto?
{
    int codigoBuscado;
    printf("Ingrese el codigo de la cancion que quiere buscar: ");
    scanf("%d", &codigoBuscado);
    return codigoBuscado;
}

void buscarCancion(FILE *canciones, int codigoCancionBuscado)
{
    if(canciones == NULL) 
    {//si el archivo no está abierto:
        canciones = fopen("canciones_cn.txt", "r"); //lo abre
    }

    fseek(canciones, 0, SEEK_SET); //Si ya lo está: Que vuelva a la primer linea.

    //Hacer estos 2 pasos es util, porque si el usuario solo quiere calcular el porcentaje u otras opciones, no hace falta que el sistema
    //cargue en memoria todo el archivo canciones, con sus 400 lineas.

    int codigoCancion, duracion;
    char titulo[50], artista[50], genero[50];
    int seEncontroCancion = 0;

    while(!feof(canciones))
    {
        fscanf(canciones ," %d %s %s %s %d", &codigoCancion, titulo, artista, genero, &duracion);
        if(codigoCancion == codigoCancionBuscado)
        {
            printf("\nEl codigo de cancion buscado (%d) tiene asociado las siguientes caracteristicas: \n", codigoCancionBuscado);
            printf("Titulo: %s\n", titulo);
            printf("Artista: %s\n", artista);
            printf("Genero: %s\n", genero);
            seEncontroCancion = 1;
        }
    }
    if(seEncontroCancion == 0)
    {
        printf("El codigo ingresado (%d) no tiene asociada ninguna cancion en el catálogo.\n", codigoCancionBuscado);
    }
    
}

void desplegarMenu(FILE *canciones)
{
    int opcionElegida = -1; //Empieza en un valor que sabemos que no puede tomar

    while(opcionElegida != 3)
    {
        printf("\nMenu de opciones:\n");
        printf("1. Consultar la duracion de una cancion.\n");
        printf("2. Calcular el porcentaje de reproducciones abandonadas.\n");
        printf("3. Salir\n");

        printf("Ingrese la opcion deseada: ");
        scanf("%d", &opcionElegida);
        while(seaValida(opcionElegida)) //esto se podría hacer con una funcion
        {
            printf("La opcion ingresada es incorrecta, reintente: ");
            scanf("%d", &opcionElegida);
        }

        switch(opcionElegida)
        {
            case 1: //Si el archivo no está abierto, abrirlo, y si lo está, volver al principio y recorrerlo
                int codigoCancionBuscado = pedirCodigoCancion();
                buscarCancion(canciones, codigoCancionBuscado);

            case 2:
                //
        }
    }
    


    





}






int main(){
    //
    //1. Leer archivo
    //2. Obtener todos los datos y escribirlos en un archivo nuestro
    //3. Cerrar el archivo
    //4. Mostrar el menú

    //Anotaciones:
    //  -Leer todo y sacar la mayor cantidad de datos antes de desplegar al menu. Es mejor un tiempo de inicio más alto,y despues más fluida la performance.
    FILE *canciones = NULL;
    FILE *reproducciones;
    desplegarMenu(canciones); //verificar si no tengo que usar &canciones

    if(canciones != NULL) //Si el archivo nunca se abrio, no debe de ser cerrado.
    {
        fclose(canciones);
    }

    return 0;
}





