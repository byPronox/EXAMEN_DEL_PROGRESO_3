#include <stdio.h>
#include <stdlib.h>
#include <string.h>//Creacion de las 3 librerias necesarias para el codigo

typedef struct {//Creacion del struct para almacenar cada estudiante con susu datos
    int numero;
    char nombre[40];
    char carrera[40];
    float notas[3];
    float promedio;
} Estudiante;

void mayormenorestudiante(Estudiante* students, int numEstudiantes) {//Creacion del void para el promedio mayor de los estudiantes con su respectivo for y if
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

void calculapromedio(Estudiante* students, int numEstudiantes) {//Void para calcular el promedio y se almacena dentro de calculapromedio
    for (int i = 0; i < numEstudiantes; i++) {//Con doble for 
        float sum = 0;
        for (int j = 0; j < 3; j++) {
            sum += students[i].notas[j];
        }
        students[i].promedio = sum / 3.0;
    }
}

void mayormenorestudiante(Estudiante* students, int numEstudiantes);
void calculapromedio(Estudiante* students, int numEstudiantes);

int main() {//Creacion del int main para ejecutar lo anterior
    FILE* inputFile = fopen("alumnos.txt", "r");//Abrimos el archivo dado
    if (inputFile == NULL) {
        printf("No se pudo abrir el archivo de entrada.\n");
        return 1;
    }

    int numEstudiantes = 0;
    Estudiante students[50];

    // Leer los datos de los estudiantes desde el archivo de entrada con while hasta que los lea todos los 5
    while (fscanf(inputFile, "%d;%[^;];%[^;];%f;%f;%f", &students[numEstudiantes].numero, students[numEstudiantes].nombre, students[numEstudiantes].carrera, &students[numEstudiantes].notas[0], &students[numEstudiantes].notas[1], &students[numEstudiantes].notas[2]) == 6) {
        numEstudiantes++;
    }

    fclose(inputFile);

    // Calcular el promedio de cada estudiante con las 3 notas
    calculapromedio(students, numEstudiantes);

    // Ordenar los estudiantes por promedio de mayor a menor promedio con la ayuda del anterior void
    mayormenorestudiante(students, numEstudiantes);

    // Creacion de el archivo de salida ordenado llamado alumnos_ordenados
    FILE* outputFile = fopen("alumnos_ordenados.txt", "w");
    if (outputFile == NULL) {
        printf("No se pudo crear el archivo de salida.\n");
        return 1;
    }

    for (int i = 0; i < numEstudiantes; i++) {//Se imprime cada estudiante con un for hasta llegar a los 5
        fprintf(outputFile, "%d;%s;%s;%.2f;%.2f;%.2f;%.2f\n", students[i].numero, students[i].nombre, students[i].carrera, students[i].notas[0], students[i].notas[1], students[i].notas[2], students[i].promedio);
    }

    fclose(outputFile);

    printf("Se creó el archivo de salida 'alumnos_ordenados.txt'.\n");

    return 0;
}
