#ifndef ALUMNO_H
#define ALUMNO_H

typedef struct Alumno {
    int id;
    char nombre[50];
    char apellido[50];
    int edad;
    struct Alumno *sgte;
} Alumno;

void agregarAlumno(Alumno **inicio);
void mostrarAlumnos(Alumno *inicio);
void liberarLista(Alumno **inicio);

#endif
