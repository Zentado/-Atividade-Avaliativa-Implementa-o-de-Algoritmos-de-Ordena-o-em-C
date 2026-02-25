#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// =====================================================
// FUNÇÃO AUXILIAR PARA IMPRIMIR ARRAY
// =====================================================
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// =====================================================
// BUBBLE SORT
// =====================================================
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// =====================================================
// SELECTION SORT
// =====================================================
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min])
                min = j;
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

// =====================================================
// INSERTION SORT
// =====================================================
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// =====================================================
// QUICK SORT (Funções auxiliares)
// =====================================================
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// =====================================================
// MERGE SORT (Funções auxiliares)
// =====================================================
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// =====================================================
// FUNÇÃO PARA COPIAR ARRAYS
// =====================================================
void copyArray(int source[], int dest[], int n) {
    memcpy(dest, source, n * sizeof(int));
}

// =====================================================
// FUNÇÃO PARA MEDIR TEMPO
// =====================================================
double measureTime(void (*sortFunc)(int[], int), int arr[], int n) {
    clock_t start = clock();
    sortFunc(arr, n);
    clock_t end = clock();

    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// =====================================================
// FUNÇÃO PARA GERAR TIPOS DIFERENTES DE ARRAYS
// =====================================================
void generateArray(int arr[], int n, int type) {
    if (type == 1) { // Aleatório
        for (int i = 0; i < n; i++)
            arr[i] = rand() % 10000;
    } 
    else if (type == 2) { // Crescente
        for (int i = 0; i < n; i++)
            arr[i] = i;
    } 
    else if (type == 3) { // Decrescente
        for (int i = 0; i < n; i++)
            arr[i] = n - i;
    }
}

// =====================================================
// MAIN
// =====================================================
int main() {

    int n, opcao, tipo;

    printf("Digite o tamanho do array: ");
    scanf("%d", &n);

    printf("Tipo de array:\n");
    printf("1 - Aleatorio\n2 - Crescente\n3 - Decrescente\nEscolha: ");
    scanf("%d", &tipo);

    int original[n], arr[n];

    srand(time(NULL));
    generateArray(original, n, tipo);

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Bubble Sort\n");
        printf("2 - Selection Sort\n");
        printf("3 - Insertion Sort\n");
        printf("4 - Quick Sort\n");
        printf("5 - Merge Sort\n");
        printf("6 - Executar TODOS\n");
        printf("0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        double tempo;

        switch(opcao) {

            case 1:
                copyArray(original, arr, n);
                tempo = measureTime(bubbleSort, arr, n);
                printArray(arr, n);
                printf("Tempo: %f segundos\n", tempo);
                break;

            case 2:
                copyArray(original, arr, n);
                tempo = measureTime(selectionSort, arr, n);
                printArray(arr, n);
                printf("Tempo: %f segundos\n", tempo);
                break;

            case 3:
                copyArray(original, arr, n);
                tempo = measureTime(insertionSort, arr, n);
                printArray(arr, n);
                printf("Tempo: %f segundos\n", tempo);
                break;

            case 4:
                copyArray(original, arr, n);
                clock_t start = clock();
                quickSort(arr, 0, n - 1);
                clock_t end = clock();
                tempo = ((double)(end - start)) / CLOCKS_PER_SEC;
                printArray(arr, n);
                printf("Tempo: %f segundos\n", tempo);
                break;

            case 5:
                copyArray(original, arr, n);
                start = clock();
                mergeSort(arr, 0, n - 1);
                end = clock();
                tempo = ((double)(end - start)) / CLOCKS_PER_SEC;
                printArray(arr, n);
                printf("Tempo: %f segundos\n", tempo);
                break;

            case 6:
                printf("\nComparacao de desempenho:\n");

                copyArray(original, arr, n);
                printf("Bubble: %f s\n", measureTime(bubbleSort, arr, n));

                copyArray(original, arr, n);
                printf("Selection: %f s\n", measureTime(selectionSort, arr, n));

                copyArray(original, arr, n);
                printf("Insertion: %f s\n", measureTime(insertionSort, arr, n));

                copyArray(original, arr, n);
                start = clock();
                quickSort(arr, 0, n - 1);
                end = clock();
                printf("Quick: %f s\n", ((double)(end - start)) / CLOCKS_PER_SEC);

                copyArray(original, arr, n);
                start = clock();
                mergeSort(arr, 0, n - 1);
                end = clock();
                printf("Merge: %f s\n", ((double)(end - start)) / CLOCKS_PER_SEC);

                break;
        }

    } while(opcao != 0);

    return 0;
}
