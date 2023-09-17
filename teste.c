#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool found;

void exibir_vetor(int *v, int len){
	for (int i = 0; i < len; i++){
		if (i == 0) printf("[");
		if (i == len - 1) printf("%d]", v[i]);
		else printf("%d, ", v[i]);
	}
}

bool worked(int *thumbdrive_a, int *thumbdrive_b, int size_GB, int n_files_a, int n_files_b) //, int size_files)
{   /*
     * Verify if the size of the files in A did not exceed the capacity of A (in GB)
     * Verify if the size of the files in B did not exceed the capacity of B (in GB)
     *      tamanho_atual_A = thumbdrive_a[0] + thumbdrive_a[1] + ... + thumbdrive_a[n_a] < s_a
     *      tamanho_atual_B = thumbdrive_b[0] + thumbdrive_b[1] + ... + thumbdrive_b[n_b] < s_b
    */
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

void backup(int *thumbdrive_a, int *thumbdrive_b, int sizeGB, int *files, int n_files, int count_a, int count_b, int count_files)
{   /*
     * thumbdrive_a and thumbdrive_b are arrays in which the files will be stored.
     * sizeGB is the max size that each thumbdrive can store in GB.
     * n_files is the lenght of the thumbdrive arrays and also the number of files that
     * have to be stored in the thumbdrives.
    */
    if (found) return;

    if (count_files == n_files) {
        if (worked(thumbdrive_a, thumbdrive_b, sizeGB, count_a, count_b)){
            printf("thumbdrive_a: "); exibir_vetor(thumbdrive_a, count_a); printf("\n");
            printf("thumbdrive_b: "); exibir_vetor(thumbdrive_b, count_b); printf("\n");
            found = true;
            printf("\n"); return;
        } else {
            return;
        }
    }

    thumbdrive_a[count_a] = files[count_files];
    backup(thumbdrive_a, thumbdrive_b, sizeGB, files, n_files, count_a + 1, count_b, count_files + 1);

    thumbdrive_b[count_b] = files[count_files];
    backup(thumbdrive_a, thumbdrive_b, sizeGB, files, n_files, count_a, count_b + 1, count_files + 1);
}

int main()
{
    int q[] = {64, 4, 128, 6};
    /*
        This array provides info about the thumb drives and about
        the number of files for each test. q[0] is the combined size
        of thumbdrive A and B in the first test.
    */

    int len_q    = sizeof(q)/sizeof(q[0]);
    int n_tests = len_q / 2;

    int a[] = {13, 7, 30, 10,
               44, 36, 18, 8, 9, 23};
    /*
        This array provides info about the size of each file for
        each test. Since the first test 
    */

    for (int test = 0; test <= n_tests; test = test + 2)
    {
        int size_thumbdrive = q[test] / 2;
        int len_thumbdrive_array =  q[test + 1];
        // int size_files = get_size(a, len_thumbdrive_array)
        int *thumbdrive_a = (int*) malloc(len_thumbdrive_array * sizeof(int));
        int *thumbdrive_b = (int*) malloc(len_thumbdrive_array * sizeof(int));
        backup(thumbdrive_a, thumbdrive_b, size_thumbdrive, a, len_thumbdrive_array, 0, 0, 0);
        free(thumbdrive_a);
        free(thumbdrive_b);
        break;
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
