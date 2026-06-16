#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "inc.h"

#define INT_SIZE B_Size*T_Size
#define FLOAT_SIZE B_Size*T_Size*C_Size

int data[INT_SIZE];
float float_data_0[FLOAT_SIZE];
float float_data_1[FLOAT_SIZE];
float float_data_2[FLOAT_SIZE];
float float_data_3[FLOAT_SIZE];

void generate_data() {
    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Generate random integers [0, 9]
    for (int i = 0; i < INT_SIZE; i++) {
        data[i] = rand() % 10;
    }

    // Generate random floats [0.0, 1.0)
    for (int i = 0; i < FLOAT_SIZE; i++) {
        float_data_0[i] = (float)rand() / RAND_MAX;
        float_data_1[i] = (float)rand() / RAND_MAX;
        float_data_2[i] = (float)rand() / RAND_MAX;
        float_data_3[i] = (float)rand() / RAND_MAX;
    }
}

void write_float_array_to_file(const char *filename, const char *arrname, const char *writemode, float *array, int size) {
    FILE *fp = fopen(filename, writemode);
    if (fp == NULL) {
        perror("Failed to open float file");
        return;
    }
    fprintf(fp, "float %s[] = {",arrname);
    for (int i = 0; i < size-1; i++) {
        fprintf(fp, "%f, ", array[i]);
    }
    fprintf(fp, "%f ", array[size-1]);
    fprintf(fp, "};\n");
    fclose(fp);
}

void write_int_array_to_file(const char *filename, const char *arrname, const char *writemode, int *array, int size) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Failed to open float file");
        return;
    }
    fprintf(fp, "int %s[] = {",arrname);
    for (int i = 0; i < size-1; i++) {
        fprintf(fp, "%d, ", array[i]);
    }
    fprintf(fp, "%d ", array[size-1]);
    fprintf(fp, "};\n");    
    fclose(fp);
}

int main() {
    generate_data();

    write_int_array_to_file  ("data.h", "inp"  , "w", data        , INT_SIZE  );
    write_float_array_to_file("data.h", "data1", "a", float_data_0, FLOAT_SIZE);
    // write_float_array_to_file("data.h", "data2", "a", float_data_1, FLOAT_SIZE);
    // write_float_array_to_file("data.h", "data3", "a", float_data_2, FLOAT_SIZE);
    // write_float_array_to_file("data.h", "data4", "a", float_data_3, FLOAT_SIZE);

    return 0;
}