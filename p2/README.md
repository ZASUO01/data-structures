# TP2 - Algoritmos de Ordenação
## Objetivo

Este trabalho consiste em analisar o desempenho de diferentes algoritmos de ordenação em
diferentes cenários, descritos a seguir. Esta análise consiste em comparar os algoritmos
considerando três métricas de desempenho: número de comparações de chaves, o número de
cópias de registros realizadas, e o tempo total gasto para ordenação (tempo de processamento e
não o tempo de relógio). As entradas são conjuntos de elementos com chaves aleatoriamente
geradas.

## Descrição

Deve-se comparar o desempenho de diferentes variações do Quicksort para
ordenar um conjunto de N registros armazenados em um vetor. Essas variações devem ainda ser compradas 
com o Heapsort e Mergesort.
Cada registro contém:

 - Um inteiro, que é a chave para ordenação
 - Quinze cadeias de caracteres (strings), cada uma com 200 caracteres
 - 10 números reais

As variações do Quicksort a serem implementadas e avaliadas são:
- Quicksort Recursivo.
- Quicksort Mediana(k): esta variação do Quicksort recursivo escolhe o pivô para partição
como sendo a mediana de k elementos do vetor, aleatoriamente escolhidos.
- Quicksort Seleção(m): esta variação modifica o Quicksort Recursivo para utilizar o
algoritmo de Seleção para ordenar partições com tamanho menor ou igual a m.
- Quicksort Iterativo: esta variação escolhe o pivô como o elemento do meio (como
apresentado em sala de aula), mas não é recursiva, utilizando uma pilha para armazenar
partições a serem processadas posteriormente. 
- Quicksort Empilha Inteligente: esta variação do Quicksort processa primeiro a menor
partição.

## Análise de Complexidade
Segue uma comparação teórica do desempenho desses algorítmos.

| Algoritmo     | Melhor Caso | Caso Médio  | Pior Caso   | Espaço Auxiliar | Estável? |
|--------------|------------|------------|------------|---------------|---------|
| **Heap Sort**  | O(n log n) | O(n log n) | O(n log n) | O(1) | Não |
| **Merge Sort** | O(n log n) | O(n log n) | O(n log n) | O(n) | Sim |
| **Quick Sort** | O(n log n) | O(n log n) | O(n²) | O(log n) | Não |

- Heap Sort
-- Usa uma heap para organizar os elementos.
-- Apresenta complexidade constante O(n log n) em todos os casos.
-- Não necessita de espaço extra.
-- Não é estável e chaves iguais podem ser trocadas de posição.

- Merge Sort
-- Utiliza o paradigma de divisão e consquista.
-- Garante sempre a complexidade O(n log n).
-- Requer O(n) espaço adicional na fusão das sublistas.
-- É estavél.
 
- Quick Sort
-- Escolhe um pivô e particiona o array.
-- No melhor e caso médio apresenta O(n log n) de complexidade.
-- No pior caso da escolha de um pivô ruim, a complexidade piora para O(n²).
-- O espaço adicional gasto na recursão é em media O(log n). A versão iterativa elimina esse gasto.
-- Não é estável.

## Avaliação Experimental

Cada algoritmo deve ser aplicado a entradas aleatórias com diferentes
tamanhos N = 1000, 5000, 10000, 50000, 100000, 500000 e 1000000.
Os valores médios de 5 execuções foram contabilizados.

# Execução

Para executar cada algorítmo deve-se rodar:

```sh
# compilar o programa
make

# executar os casos de teste
make quick_sort
make merge_sort
make heap_sort

```

Exemplo de execução:
```sh
# program [algname] -v version -s seed -k optional -m optional -i input -o output  
./bin/main quicksort -v 1 -s 10 -i input.txt -o output.txt
```

Para analise visual dos dados:
```sh
# gerar graficos
make plot
```
Para limpar o projeto para uma nova execução:
```sh
make clean
make clean_plot
```

