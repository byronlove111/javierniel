#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Caractères qui définissent comment lire et afficher la carte
typedef struct s_map_chars
{
    int  line_count;
    char empty;
    char obstacle;
    char full;
} t_map_chars;

// La grille elle-même : un tableau 2D de caractères
typedef struct s_grid
{
    char **rows;
    int  width;
    int  height;
} t_grid;

// Position et taille du plus grand carré trouvé
typedef struct s_square
{
    int size;
    int top_row;
    int left_col;
} t_square;

int execute_bsq(FILE *file);
int run_bsq_on_file(char *filename);

#endif
