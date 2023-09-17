#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_lines(FILE *file)
{
    int count = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') count++;  
    }

    rewind(file);
    return count;
}

int main()
{
    FILE *file = fopen("entrada.txt", "r");
    if (!file) { printf("Erro ao abrir arquivo"); return 1; }

    int n_lines = count_lines(file) + 1;
    int n_tests; fscanf(file, "%d", &n_tests);
    int len_info = n_tests * 2;
    int *info = (int*) malloc(len_info * sizeof(int));
    int len_file_sizes = n_lines - n_tests - 1;
    int *file_sizes = (int*) malloc(len_info * sizeof(int));
    int count_info = 0, count_file_sizes = 0;

    char line[1024];
    int a, b;  // Variables to store the integers

    while (fgets(line, sizeof(line), file)) {
        int matched = sscanf(line, "%d %d", &a, &b);
        if (matched == 2) {
            info[count_info++] = a;
            info[count_info++] = b;
        } else if (matched == 1) {
            file_sizes[count_file_sizes++] = a;
        }
    }

    free(info);
    free(file_sizes);
    fclose(file);
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
