#include <stdio.h>

#include "alumno.h"

int main()
{
    Alumno *lista = NULL;
    int opcion;

    do
    {
        printf("\n--- MENU DE GESTION DE ALUMNOS ---\n");
        printf("1. Agregar un nuevo alumno\n");
        printf("2. Mostrar todos los alumnos\n");
        printf("3. Buscar Alumno\n");
        printf("4. Eliminar Alumno\n");
        printf("5. Guardar en Archivo\n");
        printf("0. Salir\n");
        printf("-----------------------------------\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
            agregarAlumno(&lista);
            break;
        case 2:
            mostrarAlumnos(lista);
            break;
        case 3:
            printf("\nOpcion 3 buscar un alumno...\n");
            break;
        case 4:
            printf("\nOpcion 4 eliminar un alumno...\n");
            break;
        case 5:
            printf("\nOpcion 5 guardar un alumno...\n");
            break;
        case 0:
            break;
        default:
            printf("\nError: Opci�n '%d' no es v�lida. Intente de nuevo.\n", opcion);
            break;
        }
    } while (opcion != 0);

    liberarLista(&lista);

    // system("pause");
    return 0;
}
