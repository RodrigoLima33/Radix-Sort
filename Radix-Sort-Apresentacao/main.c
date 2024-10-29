#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int obterMaior(int vetor[], int tamanho)
{
    int maior = vetor[0];
    for (int i = 1; i < tamanho; i++)
        if (vetor[i] > maior)
            maior = vetor[i];
    return maior;
}

void ordenacaoContagem(int vetor[], int tamanho, int exp)
{
    int *saida = (int *)malloc(tamanho * sizeof(int));
    int contagem[10] = {0};

    for (int i = 0; i < tamanho; i++)
        contagem[(vetor[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        contagem[i] += contagem[i - 1];

    for (int i = tamanho - 1; i >= 0; i--)
    {
        saida[contagem[(vetor[i] / exp) % 10] - 1] = vetor[i];
        contagem[(vetor[i] / exp) % 10]--;
    }

    for (int i = 0; i < tamanho; i++)
        vetor[i] = saida[i];

    free(saida);
}

void radixSortRecursivo(int vetor[], int tamanho, int exp, int valorMaximo)
{
    if (exp > valorMaximo)
        return;
    ordenacaoContagem(vetor, tamanho, exp);
    radixSortRecursivo(vetor, tamanho, exp * 10, valorMaximo);
}

void radixSort(int vetor[], int tamanho)
{
    int maiorValor = obterMaior(vetor, tamanho);
    radixSortRecursivo(vetor, tamanho, 1, maiorValor);
}

double medirTempoOrdenacao(int vetor[], int tamanho)
{
    clock_t inicio = clock();
    radixSort(vetor, tamanho);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

void gerarVetorCrescente(int vetor[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        vetor[i] = i + 1;
    }
}

void gerarVetorDecrescente(int vetor[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        vetor[i] = tamanho - i;
    }
}

void gerarVetorMeioCrescenteDecrescente(int vetor[], int tamanho)
{
    for (int i = 0; i < tamanho / 2; i++)
    {
        vetor[i] = i + 1;
    }
    for (int i = tamanho / 2; i < tamanho; i++)
    {
        vetor[i] = tamanho - (i - tamanho / 2);
    }
}

void gerarVetorMeioDecrescenteCrescente(int vetor[], int tamanho)
{
    for (int i = 0; i < tamanho / 2; i++)
    {
        vetor[i] = tamanho / 2 - i;
    }
    for (int i = tamanho / 2; i < tamanho; i++)
    {
        vetor[i] = i - tamanho / 2 + 1;
    }
}

void gerarVetorAleatorio(int vetor[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        vetor[i] = rand() % tamanho + 1;
    }
}

int main()
{
    int tamanho = 100000;
    int *vetor = (int *)malloc(tamanho * sizeof(int));

    gerarVetorDecrescente(vetor, tamanho);
    printf("Tempo para ordenar vetor decrescente: %f segundos\n", medirTempoOrdenacao(vetor, tamanho));

    gerarVetorCrescente(vetor, tamanho);
    printf("Tempo para ordenar vetor crescente: %f segundos\n", medirTempoOrdenacao(vetor, tamanho));

    gerarVetorMeioCrescenteDecrescente(vetor, tamanho);
    printf("Tempo para ordenar vetor meio crescente, meio decrescente: %f segundos\n", medirTempoOrdenacao(vetor, tamanho));

    gerarVetorMeioDecrescenteCrescente(vetor, tamanho);
    printf("Tempo para ordenar vetor meio decrescente, meio crescente: %f segundos\n", medirTempoOrdenacao(vetor, tamanho));

    gerarVetorAleatorio(vetor, tamanho);
    printf("Tempo para ordenar vetor desordenado: %f segundos\n", medirTempoOrdenacao(vetor, tamanho));

    free(vetor);
    return 0;
}
