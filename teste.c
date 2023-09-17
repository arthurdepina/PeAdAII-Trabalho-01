#include <stdio.h>
#include <stdlib.h>

int backup(int *thubmdrive_a, int *thumbdrive_b, int size, int *files, int n_files, int count)
{
    /*
     * thumbdrive_a and thumbdrive_b are arrays in which the files will be stored.
     * size is the max size that each thumbdrive can store.
     * n_files is the lenght of the thumbdrive arrays and also the number of files that
     * have to be stored in the thumbdrives.
    */
    return 0;
}

int main()
{
    int q[] = {64, 4, 128, 6};
    /*
        This array provides info about the thumb drives and
        about the number of files for each test.
        q[0] and q[2] are the sizes for thumbdrive_a and thumbdrive_b combined
    */

    int len_q    = sizeof(q)/sizeof(q[0]);
    int n_tests = len_q / 2;

    int a[] = {13, 7, 30, 10,           // file sizes
               44, 36, 18, 8, 9, 23};   // file sizes

    for (int test = 0; test <= n_tests; test = test + 2)
    {
        int size_thumbdrive = q[test] / 2;
        int len_thumbdrive_array =  q[test + 1];
        int *thumbdrive_a = (int*) malloc(len_thumbdrive_array * sizeof(int));
        int *thumbdrive_b = (int*) malloc(len_thumbdrive_array * sizeof(int));
        // backup(thumbdrive_a, thumbdrive_b, size_thumbdrive, a, len_thumbdrive_array, 0);
        free(thumbdrive_a);
        free(thumbdrive_b);
    }
    return 0;
}

int store_a()
    /*
        printf("TESTE %d\n", test);
        printf("CAPACIDADE (GB) DOS PENDRIVES: %d\n", size_thumbdrive);
        printf("CAPACIDADE (EM PASTAS) DOS PENDRIVES: %d\n", len_thumbdrive_array);
    */
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
