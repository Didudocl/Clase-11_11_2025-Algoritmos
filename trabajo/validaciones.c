#include <stdio.h>
#include <string.h>

#include "validaciones.h"

void leerString(char *buffer, int tam) {
    fgets(buffer, tam, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}
