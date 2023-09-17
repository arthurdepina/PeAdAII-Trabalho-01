#include <stdio.h>
#include <stdlib.h>

void backup(int *pendrive_a, int *pendrive_b, int space, int *arquivos, int n_arquivos)
{
    
}

int main()
{
    int q[] = {64, 4, 128, 6};

    int len_q    = sizeof(q)/sizeof(q[0]);
    int n_testes = len_q / 2;

    int a[] = {13, 7, 30, 10,           // tamanho dos arquivos
               44, 36, 18, 8, 9, 23};   // tamanho dos arquivos
    
    int len = q[1];                         // dois pendrives, A e B
    int *pendrive_a = (int*) malloc(len * sizeof(int));
    int *pendrive_b = (int*) malloc(len * sizeof(int));
    int size_p = q[0] / 2;

    backup(pendrive_a, pendrive_b, size_p, a, len);
    //                               32        4

    free(pendrive_a);
    free(pendrive_b);
    return 0;
}








int store_a()
{
    int a[] = {
                2,          // quantidade de testes
                64, 4,      // tamanho total em GB , quantidade de arquivos
                13,         // tamanho arquivo
                7,
                30,
                10,
                128, 6,     // tamanho total em GB , quantidade de arquivos
                44,         // tamanho arquivo
                36,
                18,
                8,
                9,
                23
            };

    /*
        Acho que vou precisar de dois vetores.
        Um para o tamanho dos arquivos (de todos os testes)
        Um para a quantidade de arquivos em cada teste
            O tamanho desse segundo será *duas vezes a quantidade de testes*
            pois para cada teste, são necessárias duas informações: tamanho
            total em GB e quantidade de arquivos
    */
}
