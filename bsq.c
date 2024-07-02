#include <stdio.h>
#include <stdlib.h>

// Função para encontrar o menor entre três números
int min(int a, int b, int c) {
    int m = a;
    if (m > b) m = b;
    if (m > c) m = c;
    return m;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <map_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    int rows;
    char empty, obstacle, full;
    fscanf(file, "%d%c%c%c\n", &rows, &empty, &obstacle, &full);

    // Determinar o número de colunas
    fseek(file, 0, SEEK_SET);
    while (fgetc(file) != '\n');
    int cols = 0;
    while (fgetc(file) != '\n') cols++;
    fseek(file, 0, SEEK_SET);

    fscanf(file, "%d%c%c%c\n", &rows, &empty, &obstacle, &full);

    // Lendo o mapa
    char **map = malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        map[i] = malloc((cols + 1) * sizeof(char)); // +1 for the null terminator
        fgets(map[i], cols + 1, file);
        fgetc(file); // Para consumir o '\n'
    }
    fclose(file);

    // Criação da matriz auxiliar
    int **dp = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        dp[i] = malloc(cols * sizeof(int));
    }

    int max_size = 0, max_row = 0, max_col = 0;

    // Preenchimento da matriz auxiliar
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == empty) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1; // Primeira linha ou primeira coluna
                } else {
                    dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1;
                }

                if (dp[i][j] > max_size) {
                    max_size = dp[i][j];
                    max_row = i;
                    max_col = j;
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    // Marca o maior quadrado no mapa original
    for (int i = max_row; i > max_row - max_size; i--) {
        for (int j = max_col; j > max_col - max_size; j--) {
            map[i][j] = full;
        }
    }

    // Imprime o mapa resultante
    for (int i = 0; i < rows; i++) {
        printf("%s\n", map[i]);
        free(map[i]);
    }

    free(map);
    for (int i = 0; i < rows; i++) {
        free(dp[i]);
    }
    free(dp);

    return 0;
}

