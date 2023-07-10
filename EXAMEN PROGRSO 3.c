#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numero;
    char nombre[40];
    char carrera[40];
    float notas[3];
    float promedio;
} Estudiante;

void mayormenorestudiante(Estudiante* students, int numEstudiantes) {
    int i, j;
    Estudiante temp;

    for (i = 0; i < numEstudiantes - 1; i++) {
        for (j = 0; j < numEstudiantes - i - 1; j++) {
            if (students[j].promedio < students[j + 1].promedio) {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

void calculapromedio(Estudiante* students, int numEstudiantes) {
    for (int i = 0; i < numEstudiantes; i++) {
        float sum = 0;
        for (int j = 0; j < 3; j++) {
            sum += students[i].notas[j];
        }
        students[i].promedio = sum / 3.0;
    }
}

void mayormenorestudiante(Estudiante* students, int numEstudiantes);
void calculapromedio(Estudiante* students, int numEstudiantes);

int main() {
    FILE* inputFile = fopen("alumnos.txt", "r");
    if (inputFile == NULL) {
        printf("No se pudo abrir el archivo de entrada.\n");
        return 1;
    }

    int numEstudiantes = 0;
    Estudiante students[50];

    // Leer los datos de los estudiantes desde el archivo de entrada
    while (fscanf(inputFile, "%d;%[^;];%[^;];%f;%f;%f", &students[numEstudiantes].numero, students[numEstudiantes].nombre, students[numEstudiantes].carrera, &students[numEstudiantes].notas[0], &students[numEstudiantes].notas[1], &students[numEstudiantes].notas[2]) == 6) {
        numEstudiantes++;
    }

    fclose(inputFile);

    // Calcular el promedio de cada estudiante
    calculapromedio(students, numEstudiantes);

    // Ordenar los estudiantes por promedio de mayor a menor
    mayormenorestudiante(students, numEstudiantes);

    // Crear el archivo de salida ordenado
    FILE* outputFile = fopen("alumnos_ordenados.txt", "w");
    if (outputFile == NULL) {
        printf("No se pudo crear el archivo de salida.\n");
        return 1;
    }

    for (int i = 0; i < numEstudiantes; i++) {
        fprintf(outputFile, "%d;%s;%s;%.2f;%.2f;%.2f;%.2f\n", students[i].numero, students[i].nombre, students[i].carrera, students[i].notas[0], students[i].notas[1], students[i].notas[2], students[i].promedio);
    }

    fclose(outputFile);

    printf("Se creó el archivo de salida 'alumnos_ordenados.txt'.\n");

    return 0;
}
