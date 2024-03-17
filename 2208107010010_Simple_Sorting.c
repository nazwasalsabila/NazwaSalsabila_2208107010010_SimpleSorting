#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomNumbers(int *array, int size);
void bubbleSort(int *array, int size);
void selectionSort(int *array, int size);
void insertionSort(int *array, int size);
void copyArray(int *source, int *destination, int size);
void performSort(const char *sortName, void (*sortFunction)(int*, int), int *data, int size, FILE *file);

int main() {
    int sizes[] = {100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
    int n = sizeof(sizes) / sizeof(sizes[0]);

    srand(time(NULL)); // Inisialisasi seed RNG dengan waktu saat ini

    printf("Jenis Algoritma, Jumlah Bilangan, Waktu Eksekusi (ms)\n");

    int max_size = sizes[n - 1];
    int *data = (int*)malloc(max_size * sizeof(int));
    generateRandomNumbers(data, max_size);

    FILE *file = fopen("sortingResults.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        free(data);
        return -1;
    }

    for (int i = 0; i < n; i++) {
        int size = sizes[i];
        int *array = (int*)malloc(size * sizeof(int));
        copyArray(data, array, size);

        fprintf(file, "Size: %d\n\n", size);
        fprintf(file, "Original Array:\n");
        for (int j = 0; j < size; j++) {
            fprintf(file, "%d\n", array[j]);
        }

        // Bubble Sort
        performSort("Bubble Sort", bubbleSort, array, size, file);

        // Reset array to original
        copyArray(data, array, size);

        // Selection Sort
        performSort("Selection Sort", selectionSort, array, size, file);

        // Reset array to original
        copyArray(data, array, size);

        // Insertion Sort
        performSort("Insertion Sort", insertionSort, array, size, file);

        free(array);
    }

    fclose(file);
    free(data);
    return 0;
}

void generateRandomNumbers(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand();
    }
}

void bubbleSort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[minIdx]) {
                minIdx = j;
            }
        }
        int temp = array[minIdx];
        array[minIdx] = array[i];
        array[i] = temp;
    }
}

void insertionSort(int *array, int size) {
    for (int i = 1; i < size; i++) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void copyArray(int *source, int *destination, int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}

void performSort(const char *sortName, void (*sortFunction)(int*, int), int *data, int size, FILE *file) {
    clock_t start, end;
    double cpu_time_used;

    fprintf(file, "\n%s:\n", sortName);

    start = clock();
    sortFunction(data, size);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000.0; // Convert to milliseconds
    printf("%s, %d, %f ms\n", sortName, size, cpu_time_used);

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", data[i]);
    }
    fprintf(file, "\n"); // Add space before next sort or size
}
