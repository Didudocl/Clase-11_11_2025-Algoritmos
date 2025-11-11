#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alumno.h"
#include "validaciones.h"

int g_proximoId = 0;

Alumno *crearAlumno()
{
    Alumno *nuevo = (Alumno *)malloc(sizeof(Alumno));
    if (nuevo == NULL)
    {
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    // !
    printf("\n--- Agregando Nuevo Alumno ---\n");

    nuevo->id = g_proximoId;
    g_proximoId++;

    // !
    printf("ID Asignado: %d\n", nuevo->id);

    printf("Ingrese el nombre: ");
    leerString(nuevo->nombre, sizeof(nuevo->nombre));

    printf("Ingrese el apellido: ");
    leerString(nuevo->apellido, sizeof(nuevo->apellido));

    do
    {
        printf("Ingrse la edad: ");
        scanf("%d", &nuevo->edad);
        getchar();
        if (nuevo->edad <= 0 || nuevo->edad > 100)
        {
            printf("Error: La edad debe ser un n�mero v�lido (ej: 1-100).\n");
        }
    } while (nuevo->edad <= 0 || nuevo->edad > 100);

    nuevo->sgte = NULL;
    return nuevo;
}

void agregarAlumno(Alumno **inicio)
{
    Alumno *nuevo = crearAlumno();

    if (*inicio == NULL)
    {
        *inicio = nuevo;
    }
    else
    {
        Alumno *aux = *inicio;
        while (aux->sgte != NULL)
        {
            aux = aux->sgte;
        }
        aux->sgte = nuevo;
    }
    printf("\nAlumno agregado exitosamente.\n");
}

void mostrarAlumnos(Alumno *inicio)
{
    if (inicio == NULL)
    {
        printf("\nNo hay alumnos registrados en la lista.\n");
        return;
    }

    printf("\n--- LISTA DE ALUMNOS ---\n");
    Alumno *aux = inicio;
    while (aux != NULL)
    {
        printf("ID: %d | Nombre: %s, %s | Edad: %d\n",
               aux->id, aux->apellido, aux->nombre, aux->edad);
        aux = aux->sgte;
    }
    printf("------------------------\n");
}

void liberarLista(Alumno **inicio)
{
    if (*inicio == NULL)
    {
        return;
    }

    printf("\n--- Liberando memoria... ---\n");

    Alumno *aux;
    while (*inicio != NULL)
    {
        aux = *inicio;
        *inicio = (*inicio)->sgte;
        free(aux);
    }
    printf("Toda la memoria de la lista ha sido liberada.\n");
}
