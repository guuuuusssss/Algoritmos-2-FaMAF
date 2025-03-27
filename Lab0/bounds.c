#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
    struct bound_data res;
    res.is_upperbound = false;
    res.is_lowerbound = false;
    res.exists = false;

    unsigned int mayores = 0;
    unsigned int menores = 0;

    for (unsigned int i = 0; i < length; i++) {
        if (value > arr[i]) {
            mayores++;
        } else if (value == arr[i]) {
            res.exists = true;
            res.where = i;
            mayores++;
            menores++;
        } else if (value < arr[i]) {
            menores++;
        }
    }

    if (mayores == length) { res.is_upperbound = true; }
    if (menores == length) { res.is_lowerbound = true; }
    
    return res;
}

int main(void) {
    int a[ARRAY_SIZE] = {0, -1, 9, 4};
    int value=9;

    printf("Por favor, ingrese los 4 elementos del arreglo separados por un espacio (solo numeros enteros)\n");
    if (scanf("%d %d %d %d", &a[0], &a[1], &a[2], &a[3]) != 4) {
        printf("Error al leer los elementos del arreglo\n");
        return EXIT_FAILURE;
    }

    printf("Ahora ingrese el valor que desea comparar con los elementos del arreglo\n");
    if (scanf("%d", &value) != 1) {
        printf("Error al leer el valor\n");
        return EXIT_FAILURE;
    }
    
    struct bound_data result = check_bound(value, a, ARRAY_SIZE);
    
    // TODO: REEMPLAZAR LO SIGUIENTE LUEGO POR LA SALIDA QUE PIDE EL ENUNCIADO
    if (result.exists) {
        if (result.is_upperbound) {
            printf("%d %s un maximo del arreglo, ubicado en el indice %d.\n", 
                    value, result.is_upperbound ? "es" : "no es", result.where);
        }
        if (result.is_lowerbound) {
            printf("%d %s un minimo del arreglo, ubicado en el indice %d.\n", 
                    value, result.is_lowerbound ? "es" : "no es", result.where);
        }
    } else {
        printf("%d %s del arreglo.\n", value, 
                result.is_upperbound ? "es una cota superior" : 
                (result.is_lowerbound ? "es una cota inferior" : "no es cota superior ni inferior"));
    }

    return EXIT_SUCCESS;
}