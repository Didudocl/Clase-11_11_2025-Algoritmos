// Hola a todos!
// Adios
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nombre[100];
} Carrera;

typedef struct
{
    int id;
    char nombre[100];
} Region;

typedef struct Estudiante
{
    char nombre[50];
    char apellido[50];
    int edad;
    int idCarrera;
    int idRegion;
    struct Estudiante *sgte;
} Estudiante;

#define MAX_CARRERAS 20
#define MAX_REGIONES 20

Carrera g_carreras[MAX_CARRERAS];
int g_numCarreras = 0;
Region g_regiones[MAX_REGIONES];
int g_numRegiones = 0;

// --- Prototipos ---
void cargarCarreras();
void cargarRegiones();
const char *getNombreCarrera(int id);
const char *getNombreRegion(int id);
void cargarEstudiantesDesdeArchivo(Estudiante **inicio, const char *nombreArchivo);
void mostrarEstudiantes(Estudiante *inicio);
void buscarEstudiantePorNombre(Estudiante *inicio, const char *nombreBuscado, const char *apellidoBuscado);
void liberarLista(Estudiante **inicio);

int main()
{
    Estudiante *listaEstudiantes = NULL;

    cargarCarreras();
    cargarRegiones();

    printf("\nCargadas %d carreras y %d regiones.\n\n", g_numCarreras, g_numRegiones);

    cargarEstudiantesDesdeArchivo(&listaEstudiantes, "estudiantes.txt");

    mostrarEstudiantes(listaEstudiantes);

    printf("Buscando a 'Diego Salazar'...\n");
    buscarEstudiantePorNombre(listaEstudiantes, "Diego", "Salazar");

    printf("Liberando memoria de la lista enlazada...\n");
    liberarLista(&listaEstudiantes);
    system("pause");
    return 0;
}

void cargarCarreras()
{
    FILE *f = fopen("carreras.txt", "r");
    if (f == NULL)
    {
        printf("Error al abrir carreras.txt\n");
        return;
    }
    g_numCarreras = 0;

    while (!feof(f))
    {
        int camposLeidos = fscanf(f, "%d %[^\n]\n",
                                  &g_carreras[g_numCarreras].id,
                                  g_carreras[g_numCarreras].nombre);

        if (camposLeidos == 2 && g_numCarreras < MAX_CARRERAS)
        {
            g_numCarreras++;
        }
        else
        {
            if (feof(f))
            {
                break;
            }
        }
    }
    fclose(f);
}

void cargarRegiones()
{
    FILE *f = fopen("regiones.txt", "r");
    if (f == NULL)
    {
        printf("Error al abrir regiones.txt\n");
        return;
    }
    g_numRegiones = 0;

    while (!feof(f))
    {
        int camposLeidos = fscanf(f, "%d %[^\n]\n",
                                  &g_regiones[g_numRegiones].id,
                                  g_regiones[g_numRegiones].nombre);

        if (camposLeidos == 2 && g_numRegiones < MAX_REGIONES)
        {
            g_numRegiones++;
        }
        else
        {
            if (feof(f))
            {
                break;
            }
        }
    }
    fclose(f);
}

const char *getNombreCarrera(int id)
{
    int i;
    for (i = 0; i < g_numCarreras; i++)
    {
        if (g_carreras[i].id == id)
        {
            return g_carreras[i].nombre;
        }
    }
    return "Desconocida";
}

const char *getNombreRegion(int id)
{
    int i;
    for (i = 0; i < g_numRegiones; i++)
    {
        if (g_regiones[i].id == id)
        {
            return g_regiones[i].nombre;
        }
    }
    return "Desconocida";
}

void cargarEstudiantesDesdeArchivo(Estudiante **inicio, const char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        printf("Error: No se pudo abrir el archivo '%s'.\n", nombreArchivo);
        return;
    }

    if (*inicio != NULL)
    {
        liberarLista(inicio);
    }

    int contador = 0;

    while (!feof(archivo))
    {

        Estudiante *nuevo = (Estudiante *)malloc(sizeof(Estudiante));
        if (nuevo == NULL)
        {
            printf("Error fatal: No se pudo asignar memoria.\n");
            fclose(archivo);
            return;
        }

        // Lectura con fscanf para 5 campos
        int camposLeidos = fscanf(archivo, "%s %s %d %d %d",
                                  nuevo->nombre,
                                  nuevo->apellido,
                                  &nuevo->edad,
                                  &nuevo->idCarrera,
                                  &nuevo->idRegion);

        if (camposLeidos == 5)
        {
            nuevo->sgte = NULL;
            if (*inicio == NULL)
            {
                *inicio = nuevo;
            }
            else
            {
                Estudiante *aux = *inicio;
                while (aux->sgte != NULL)
                {
                    aux = aux->sgte;
                }
                aux->sgte = nuevo;
            }
            contador++;
        }
        else
        {
            free(nuevo);
            if (feof(archivo))
            {
                break;
            }
        }
    }

    fclose(archivo);
    printf("Se cargaron %d estudiantes desde '%s'.\n", contador, nombreArchivo);
}

void liberarLista(Estudiante **inicio)
{
    if (*inicio == NULL)
        return;

    Estudiante *aux;
    int contador = 0;
    while (*inicio != NULL)
    {
        aux = *inicio;
        *inicio = (*inicio)->sgte;
        free(aux);
        contador++;
    }
    printf("%d nodos de estudiantes liberados.\n", contador);
}

void mostrarEstudiantes(Estudiante *inicio)
{
    if (inicio == NULL)
    {
        printf("\nNo hay estudiantes registrados.\n");
        return;
    }

    printf("\n--- LISTA DE ESTUDIANTES (DESNORMALIZADA) ---\n");
    Estudiante *aux = inicio;
    while (aux != NULL)
    {

        const char *nombreCarrera = getNombreCarrera(aux->idCarrera);
        const char *nombreRegion = getNombreRegion(aux->idRegion);

        printf("Nombre: %s %s\n", aux->nombre, aux->apellido);
        printf("  Edad:    %d\n", aux->edad);
        printf("  Carrera: %s\n", nombreCarrera);
        printf("  Region:  %s\n", nombreRegion);
        printf("---------------------------------------\n");
        aux = aux->sgte;
    }
}

void buscarEstudiantePorNombre(Estudiante *inicio, const char *nombreBuscado, const char *apellidoBuscado)
{
    if (inicio == NULL)
    {
        printf("No hay estudiantes en la lista para buscar.\n");
        return;
    }

    Estudiante *aux = inicio;
    int encontrado = 0;
    while (aux != NULL)
    {
        if (strcmp(aux->nombre, nombreBuscado) == 0 && strcmp(aux->apellido, apellidoBuscado) == 0)
        {

            const char *nombreCarrera = getNombreCarrera(aux->idCarrera);
            const char *nombreRegion = getNombreRegion(aux->idRegion);

            printf("--- Estudiante Encontrado ---\n");
            printf("Nombre: %s %s\n", aux->nombre, aux->apellido);
            printf("  Edad:    %d\n", aux->edad);
            printf("  Carrera: %s\n", nombreCarrera);
            printf("  Region:  %s\n", nombreRegion);
            printf("-----------------------------\n");

            encontrado = 1;
            break;
        }
        aux = aux->sgte;
    }

    if (!encontrado)
    {
        printf("No se encontro al estudiante '%s %s'.\n", nombreBuscado, apellidoBuscado);
    }
}

