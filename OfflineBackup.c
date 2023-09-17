#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool found;

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

void exibir_vetor(int *v, int len)
{
	for (int i = 0; i < len; i++)  {
		if (i == 0) printf("[");
		if (i == len - 1) printf("%d]", v[i]);
		else printf("%d, ", v[i]); }
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
        printf("thumbdrive_a: "); exibir_vetor(thumbdrive_a, count_a); printf("\n");
        printf("thumbdrive_b: "); exibir_vetor(thumbdrive_b, count_b); printf("\n");
        if (worked(thumbdrive_a, thumbdrive_b, sizeGB, count_a, count_b)){
            printf("\n WORKED \n");
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
    //                  Dealing with files starts here
    FILE *file = fopen("entrada.txt", "r");
    if (!file) { printf("Erro ao abrir arquivo"); return 1; }

    int n_lines = count_lines(file) + 1;
    int n_tests; fscanf(file, "%d", &n_tests);
    int len_info = n_tests * 2;
    int *info = (int*) malloc(len_info * sizeof(int));
    // This array provides info about the thumb drives and about the number of files for each test.
    int len_file_sizes = n_lines - n_tests - 1;
    int *file_sizes = (int*) malloc(len_info * sizeof(int));
    // This array provides info about the size of each file for each test.
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
    //                  Dealing with files ends here

    printf("Info array: "); exibir_vetor(info, len_info); printf("\n");
    printf("File sizes: "); exibir_vetor(file_sizes, len_file_sizes); printf("\n");

    int counter_file_sizes = 0;
    for (int test = 0; test <= n_tests; test = test + 2)
    {
        printf("\n\n==== TESTE 0%d ====\n", test / 2 + 1);
        found = false;
        int size_thumbdrive = info[test] / 2;
        int len_thumbdrive_array =  info[test + 1];
        int *thumbdrive_a = (int*) malloc(len_thumbdrive_array * sizeof(int));
        int *thumbdrive_b = (int*) malloc(len_thumbdrive_array * sizeof(int));
        printf("size_thumbdrive : %d\n", size_thumbdrive);
        printf("len_thumbdrive_array : %d\n", len_thumbdrive_array);
        printf("counter_file_sizes: %d\n", counter_file_sizes);
        printf("files: "); exibir_vetor(file_sizes, len_file_sizes);
        backup(thumbdrive_a, thumbdrive_b, size_thumbdrive, file_sizes, len_thumbdrive_array, 0, 0, counter_file_sizes);
        counter_file_sizes = counter_file_sizes + len_thumbdrive_array;
        free(thumbdrive_a);
        free(thumbdrive_b);
        if (!found) printf("Impossible");
    }
    return 0;
}
