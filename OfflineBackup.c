#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool found; /*variável global para indicar se foi encontrada
              maneira adequada de se preencher os pendrives*/

int count_lines(FILE *file)
{
    /*        Conta as linhas do arquivo.
     * Aloca um char ch, quando esse char igual ao
     * final do arquivo, a contagem é finalizada. */
    int count = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') count++;  
    }
    rewind(file);
    return count;
}

void exibir_preenchimento(int *pendrive_a, int *pendrive_b, int len_a, int len_b, int capacity)
{
    /*      Exibe como os pendrives foram preenchidos
     * Faz um loop pelos arquivos de cada pendrive e os exibe. */
    printf("%d GB\n", capacity * 2);
    printf("Pendrive A (%d GB)\n", capacity);
    for (int i = 0; i < len_a; i++) {
        printf("%d GB\n", pendrive_a[i]);
    }
    printf("Pendrive B (%d GB)\n", capacity);
    for (int i = 0; i < len_b; i++) {
        printf("%d GB\n", pendrive_b[i]);
    }
}

bool worked(int *thumbdrive_a, int *thumbdrive_b, int size_GB, int n_files_a, int n_files_b) //, int size_files)
{   /*                  Verifica se a distribuição de arquivos atuais funcionou.
     * Soma o tamanho em GB dos arquivos de cada pendrive e verifica de tamanhos não excedeu a
     * capacidade de armazenamento do pendrive. Se não excedeu, retorna true, se excedeu, retorna false. */
    int current_size_a = 0, current_size_b = 0;

    for (int file = 0; file < n_files_a; file++) {
        current_size_a = current_size_a + thumbdrive_a[file];
    }
    for (int file = 0; file < n_files_b; file++) {
        current_size_b = current_size_b + thumbdrive_b[file];
    }

    if (current_size_a <= size_GB && current_size_b <= size_GB) return true;
    else return false;
}

void backup(int *thumbdrive_a, int *thumbdrive_b, int sizeGB, int *files, int n_files, int count_a, int count_b, int count_files, int counter)
{
    /* Parâmetros: *thumbdrive_a e *thumbdrive_b: ponteiros para os vetores do pendrive_a e pendrive_b
     *             sizeGB: capacidade em GB de cada pendrive
     *             *files: ponteiro para o vetor com o tamanho dos arquivos
     *             n_files: número de arquivos analisados em cada teste
     *             count_a e count_b: contadores para *thumbdrive_a e *thumbdrive_b
     *             count_files: contador para *files. indica em qual index de *files os arquivos do teste atual começam
     *             counter: contador de quantos arquivos foram adicionados aos pendrives*/
    if (found) return; // Se já foi encontrada uma solução, retorna para sair da função.

    if (counter == n_files) {                                                               // se o número de arquivos adicionados aos pendrive for
        if (worked(thumbdrive_a, thumbdrive_b, sizeGB, count_a, count_b)){                  // igual ao número de arquivos desse teste, verifica se
            exibir_preenchimento(thumbdrive_a, thumbdrive_b, count_a, count_b, sizeGB);     //     o preenchimento foi adequado, e se foi adequado,
            found = true;                                                                   //       found assume o valor true e saímos da recursão
            return;
        } else {
            return;
        }
    }

    thumbdrive_a[count_a] = files[count_files];
    backup(thumbdrive_a, thumbdrive_b, sizeGB, files, n_files, count_a + 1, count_b, count_files + 1, counter+1);

    thumbdrive_b[count_b] = files[count_files];
    backup(thumbdrive_a, thumbdrive_b, sizeGB, files, n_files, count_a, count_b + 1, count_files + 1, counter+1);
}

int main()
{   
    FILE *file = fopen("entrada.txt", "r");                                                 // abrindo arquivo
    if (!file) { printf("Erro ao abrir arquivo"); return 1; }                               // se houver problema encerra o programa

    int n_lines = count_lines(file) + 1;                                                    // conta linhas do arquivo
    int n_tests; fscanf(file, "%d", &n_tests);                                              // pega número de testes
    int len_info = n_tests * 2;                                                             
    int *info = (int*) malloc(len_info * sizeof(int));                                      
    // info: irá receber a capacidade de armazenamento dos pendrives e a quantidade de arquivos de cada teste
    int len_file_sizes = n_lines - n_tests - 1;                                             
    int *file_sizes = (int*) malloc(len_info * sizeof(int));                               
    // file_sizes: irá receber o tamanho em GB de cada arquivo a ser utilizado nos testes
    int count_info = 0, count_file_sizes = 0;                                               // contadores para info e file_sizes
    char line[1024];                                                                        // buffer para linhas do arquivo
    int a, b;                                                                               // variáveis para armazenar temporariamente
                                                                                            //                   o tamanho dos arquivos
    while (fgets(line, sizeof(line), file)) {
        /* fgets() lê até sizeof(line) - 1 ou até um \n ou EOF. se
         * a linha for lida corretamente, retorna um ponteiro para
         * line. caso contrário retorna NULL encerrando o loop  */
        int matched = sscanf(line, "%d %d", &a, &b); // tenta ler dois caracteres na linha e assinalar. se conseguir, assinala e retorna 2.
        if (matched == 2) {                          // se foram assinalados valores em a e b
            info[count_info++] = a;                  // 'a' é a capacidade dos pendrives em GB e 'b' é a quantidade de arquivos de um teste
            info[count_info++] = b;                  // esses valores são armazenados no vetor info.
        } else if (matched == 1) {                   // se apenas um valor foi assinalado, esse valor é o tamanho de um arquivo
            file_sizes[count_file_sizes++] = a;      // esse valor é armazenado em file_sizes.
        }
    }
    /*                                       A parte de leitura de arquivos já foi realizada,
     *                                        Agora temos os valores armazenados em arrays.                                                  */

    int counter_file_sizes = 0;
    for (int test = 0; test < n_tests; test++)
    {
        printf("\n");
        found = false;
        int size_thumbdrive = info[test * 2] / 2;                    // in GB
        int len_thumbdrive_array =  info[test * 2 + 1];         // in # of files
        int *thumbdrive_a = (int*) malloc(len_thumbdrive_array * sizeof(int));
        int *thumbdrive_b = (int*) malloc(len_thumbdrive_array * sizeof(int));
        backup(thumbdrive_a, thumbdrive_b, size_thumbdrive, file_sizes, len_thumbdrive_array, 0, 0, counter_file_sizes, 0);
        counter_file_sizes = counter_file_sizes + len_thumbdrive_array;
        free(thumbdrive_a);
        free(thumbdrive_b);
        if (!found) printf("Impossível gravar todos os arquivos nos pendrives.\n");
    }
    printf("\n");
    return 0;
}
