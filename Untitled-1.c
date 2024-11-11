#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define tamanho das arrays
#define ARRAY_SIZE_100 100
#define ARRAY_SIZE_1000 1000
#define ARRAY_SIZE_10000 10000
#define ARRAY_SIZE_50000 50000
#define ARRAY_SIZE_100000 100000

// Funções Sort
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);
void bubbleSort(int arr[], int n);
void mergeSort(int arr[], int n);
void quickSort(int arr[], int n);
void heapSort(int arr[], int n);

// Funções auxiliares
void merge(int arr[], int n);
int existe_no_array(int arr[], int tamanho, int num);
void gerar_array(int arr[], int tamanho);
int* copiar_array(int arr[], int n);

// funções de ordenação e seus nomes para seleção dinâmica
typedef void (*sort_func)(int[], int);
sort_func algoritimos[] = {selectionSort, insertionSort, bubbleSort, mergeSort, quickSort, heapSort};
const char *nomes[] = {"Selection Sort", "Insertion Sort", "Bubble Sort", "Merge Sort", "Quick Sort", "Heap Sort"};

// Configuração do tamanho das arrays
const int tamanhos[] = {ARRAY_SIZE_100, ARRAY_SIZE_1000, ARRAY_SIZE_10000, ARRAY_SIZE_50000, ARRAY_SIZE_100000};
const int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
const int num_sorts = sizeof(algoritimos) / sizeof(algoritimos[0]);



// Programa
int main() {
    int *arr, *arr_copia;
    clock_t inicio, fim;
    double tempo_cpu;

    srand(time(NULL)); // Inicializa o gerador de números aleatórios com o tempo atual para garantir valores diferentes a cada execução

    // Primeiro Loop: itera sobre cada tamanho de array definido em "tamanhos"
    for (int s = 0; s < num_tamanhos; s++) {
        int n = tamanhos[s]; // Define "n" como o tamanho atual do array (100, 1000, 10000, etc.)
        arr = (int*)malloc(n * sizeof(int)); // Aloca memória para o array "arr" com "n" elementos
        if (arr == NULL) {
            printf("Erro de alocação de memória!\n");
            return 1;
        }
        
        gerar_array(arr, n); // Preenche "arr" com "n" números aleatórios únicos
        printf("===== Tempo de execução com %d números =====\n", n);

        // Segundo Loop: itera sobre cada algoritmo de ordenação definido em "algoritimos"
        for (int i = 0; i < num_sorts; i++) {
            arr_copia = copiar_array(arr, n);    // Cria uma cópia de "arr" em "arr_copia" para preservar o array original
            inicio = clock();                    // Registra o tempo de início antes de chamar o algoritmo de ordenação
            algoritimos[i](arr_copia, n);        // Chama o algoritmo de ordenação atual ("algoritimos[i]") para ordenar "arr_copia"
            fim = clock();                       // Registra o tempo de fim após a ordenação
            tempo_cpu = ((double)(fim - inicio)) / CLOCKS_PER_SEC; // Calcula o tempo de execução em segundos
            printf("%s: %f segundos\n", nomes[i], tempo_cpu); // Exibe o nome do algoritmo de ordenação e o tempo de execução
            free(arr_copia);                     // Libera a memória alocada para "arr_copia" após cada ordenação
        }

        printf("\n");
        free(arr); // Libera a memória alocada para o array original "arr" após testar todos os algoritmos
    }

    return 0;
}



// Código das funções

// Função de ordenação Selection Sort
void selectionSort(int arr[], int n) {
    int i, j, minIndex, temp;
    for (i = 0; i < n - 1; i++) {
        minIndex = i; // Define o índice do menor elemento como o atual
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) { // Encontra o menor elemento no restante do array
                minIndex = j; // Atualiza o índice do menor elemento
            }
        }
        if (minIndex != i) { // Troca o elemento atual com o menor elemento encontrado
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

// Função de ordenação Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i]; // Seleciona o elemento a ser inserido na posição correta
        int j = i - 1;
        // Move elementos maiores que 'key' para uma posição à frente
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; // Insere 'key' na posição correta
    }
}

// Função de ordenação Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0; // Flag para otimizar o algoritmo se já estiver ordenado
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) { // Verifica se os elementos estão fora de ordem
                // Troca os elementos adjacentes se estiverem na ordem errada
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1; // Marca que houve uma troca
            }
        }
        if (!swapped) break; // Se nenhuma troca ocorreu, o array já está ordenado
    }
}

// Função auxiliar para mesclar duas metades em Merge Sort
void merge(int arr[], int n) {
    int mid = n / 2; // Ponto médio do array para dividir as duas metades
    int i = 0, j = mid, k = 0;
    int temp[n]; // Array temporário para armazenar os elementos mesclados

    // Compara e insere elementos ordenados das duas metades no array temporário
    while (i < mid && j < n) {
        temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    }

    // Copia os elementos restantes da primeira metade, se houver
    while (i < mid) temp[k++] = arr[i++];

    // Copia os elementos restantes da segunda metade, se houver
    while (j < n) temp[k++] = arr[j++];

    // Copia o array temporário de volta para o array original
    for (i = 0; i < n; i++) arr[i] = temp[i];
}

// Função Merge Sort (recursiva)
void mergeSort(int arr[], int n) {
    if (n < 2) return; // Condição de parada para arrays de tamanho 1
    int mid = n / 2;
    mergeSort(arr, mid);         // Ordena recursivamente a primeira metade
    mergeSort(arr + mid, n - mid); // Ordena recursivamente a segunda metade
    merge(arr, n); // Mescla as duas metades ordenadas
}



// Função de ordenação Quick Sort
void quickSort(int arr[], int n) {
    int stack[n]; // Array usado como pilha para armazenar limites do array
    int top = -1;

    stack[++top] = 0; // Insere o índice inicial na pilha
    stack[++top] = n - 1; // Insere o índice final na pilha

    while (top >= 0) {
        int high = stack[top--]; // Remove o índice final da pilha
        int low = stack[top--]; // Remove o índice inicial da pilha

        int pivot = arr[high]; // Define o pivô como o último elemento
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) { // Move elementos menores que o pivô para a esquerda
                int temp = arr[++i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        // Coloca o pivô na posição correta
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        int pi = i + 1; // Índice de partição do pivô

        // Adiciona sub-arrays à pilha para serem ordenados
        if (pi - 1 > low) { // Partição à esquerda do pivô
            stack[++top] = low;
            stack[++top] = pi - 1;
        }
        if (pi + 1 < high) { // Partição à direita do pivô
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }
}

// Função de ordenação Heap Sort
void heapSort(int arr[], int n) {
    // Constrói o heap máximo a partir dos elementos
    for (int i = n / 2 - 1; i >= 0; i--) {
        int root = i;

        // Ajusta o heap a partir do nó raiz
        while (2 * root + 1 < n) {
            int child = 2 * root + 1;
            if (child + 1 < n && arr[child] < arr[child + 1]) {
                child++; // Seleciona o maior filho
            }
            if (arr[root] < arr[child]) { // Troca se o filho for maior que a raiz
                int temp = arr[root];
                arr[root] = arr[child];
                arr[child] = temp;
                root = child; // Continua ajustando a subárvore
            } else break;
        }
    }

    // Extrai elementos do heap um por um e ordena o array
    for (int i = n - 1; i > 0; i--) {
        // Move a raiz (maior elemento) para o final do array não ordenado
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Chama o heapify na raiz para restaurar o heap máximo
        int root = 0;
        while (2 * root + 1 < i) {
            int child = 2 * root + 1;
            if (child + 1 < i && arr[child] < arr[child + 1]) {
                child++; // Seleciona o maior filho
            }
            if (arr[root] < arr[child]) { // Troca se o filho for maior que a raiz
                temp = arr[root];
                arr[root] = arr[child];
                arr[child] = temp;
                root = child; // Continua ajustando a subárvore
            } else break;
        }
    }
}

// Função para verificar se um número já existe no array
int existe_no_array(int arr[], int tamanho, int num) {
    // Percorre o array até o tamanho atual
    for (int i = 0; i < tamanho; i++) {
        if (arr[i] == num) { // Verifica se o número já está presente no array
            return 1;
        }
    }
    return 0;
}

// Função para gerar um array com números aleatórios únicos
void gerar_array(int arr[], int tamanho) {
    int num; 
    for (int i = 0; i < tamanho; i++) {
        do {
            num = rand(); // Gera um número aleatório
        } while (existe_no_array(arr, i, num)); // Continua gerando até que seja único
        arr[i] = num; // Insere o número único no array
    }
}

// Função para criar uma cópia de um array
int* copiar_array(int arr[], int n) {
    int* copia = (int*)malloc(n * sizeof(int));
    if (copia == NULL) { // Verifica se a alocação foi bem-sucedida
        printf("Erro de alocação de memória!\n"); 
        exit(1); // Encerra o programa em caso de erro de memória
    }

    // Copia cada elemento do array original para o array de cópia
    for (int i = 0; i < n; i++) {
        copia[i] = arr[i];
    }

    return copia;
}