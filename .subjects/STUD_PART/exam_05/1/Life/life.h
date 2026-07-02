#ifndef LIFE_H
#define LIFE_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// Contient tout ce qui est nécessaire pour une session du Jeu de la Vie.
// Le plateau est un tableau 1D : board[row * width + col]
// Valeurs : 0 = cellule morte, 1 = cellule vivante
typedef struct s_game
{
    int    width;
    int    height;
    int    iterations;
    int    cursor_row;    // ligne actuelle du curseur (contrôlé par w/s)
    int    cursor_col;    // colonne actuelle du curseur (contrôlée par a/d)
    int    draw_enabled;  // 1 si le mode dessin est actif, 0 sinon
    char  *board;         // plateau courant
    char  *next_board;    // plateau de la prochaine génération (double buffer)
} t_game;

int  init_game(t_game *game, char *argv[]);
void fill_board(t_game *game);
void play(t_game *game);
void print_board(t_game *game);
void free_board(t_game *game);

#endif
