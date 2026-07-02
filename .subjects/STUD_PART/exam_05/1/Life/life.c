#include "life.h"

// ─── Initialisation ───────────────────────────────────────────────────────────

// calloc initialise tout à 0, donc le plateau démarre avec toutes les cellules mortes —
// pas besoin de boucle d'initialisation.
int init_game(t_game *game, char *argv[])
{
    int total_cells;

    game->width        = atoi(argv[1]);
    game->height       = atoi(argv[2]);
    game->iterations   = atoi(argv[3]);
    game->cursor_row   = 0;
    game->cursor_col   = 0;
    game->draw_enabled = 0;

    total_cells = game->width * game->height;

    game->board      = calloc(total_cells, 1);
    game->next_board = calloc(total_cells, 1);

    if (game->board == NULL || game->next_board == NULL)
        return -1;
    return 0;
}

// ─── Remplissage du plateau depuis stdin ──────────────────────────────────────

// Lit les commandes de stdin un caractère à la fois :
//   w / s  →  déplace le curseur en haut / bas
//   a / d  →  déplace le curseur à gauche / droite
//   x      →  active ou désactive le mode dessin
// Quand le mode dessin est actif, chaque déplacement colorie la cellule
// sous le curseur comme vivante (valeur 1).
void fill_board(t_game *game)
{
    char  input;
    int   cell_index;

    while (read(STDIN_FILENO, &input, 1) > 0)
    {
        if (input == 'x')
        {
            if (game->draw_enabled == 0)
                game->draw_enabled = 1;
            else
                game->draw_enabled = 0;
        }
        else if (input == 'w' && game->cursor_row > 0)
            game->cursor_row--;
        else if (input == 's' && game->cursor_row < game->height - 1)
            game->cursor_row++;
        else if (input == 'a' && game->cursor_col > 0)
            game->cursor_col--;
        else if (input == 'd' && game->cursor_col < game->width - 1)
            game->cursor_col++;

        if (game->draw_enabled == 1)
        {
            cell_index = game->cursor_row * game->width + game->cursor_col;
            game->board[cell_index] = 1;
        }
    }
}

// ─── Règles du Jeu de la Vie ──────────────────────────────────────────────────

// Compte le nombre de voisins vivants autour de la cellule (row, col).
// Le voisinage est constitué des 8 cellules entourant la cellule (voisinage de Moore).
static int count_alive_neighbors(t_game *game, int row, int col)
{
    int alive_count;
    int row_delta;
    int col_delta;
    int neighbor_row;
    int neighbor_col;
    int neighbor_index;

    alive_count = 0;
    row_delta   = -1;
    while (row_delta <= 1)
    {
        col_delta = -1;
        while (col_delta <= 1)
        {
            // On ignore la cellule elle-même
            if (row_delta == 0 && col_delta == 0)
            {
                col_delta++;
                continue;
            }

            neighbor_row = row + row_delta;
            neighbor_col = col + col_delta;

            if (neighbor_row >= 0 && neighbor_row < game->height
                && neighbor_col >= 0 && neighbor_col < game->width)
            {
                neighbor_index = neighbor_row * game->width + neighbor_col;
                if (game->board[neighbor_index] == 1)
                    alive_count++;
            }
            col_delta++;
        }
        row_delta++;
    }
    return alive_count;
}

// Fait avancer le plateau d'une génération selon les règles :
//   - Une cellule vivante avec 2 ou 3 voisins survit.
//   - Une cellule morte avec exactement 3 voisins devient vivante.
//   - Toutes les autres cellules meurent (ou restent mortes).
//
// Le résultat est écrit dans next_board, puis les deux pointeurs sont échangés.
// Cela évite toute allocation mémoire pendant la boucle principale.
void play(t_game *game)
{
    int  row;
    int  col;
    int  cell_index;
    int  neighbor_count;
    char *tmp;

    row = 0;
    while (row < game->height)
    {
        col = 0;
        while (col < game->width)
        {
            cell_index     = row * game->width + col;
            neighbor_count = count_alive_neighbors(game, row, col);

            if (game->board[cell_index] == 1)
            {
                if (neighbor_count == 2 || neighbor_count == 3)
                    game->next_board[cell_index] = 1;
                else
                    game->next_board[cell_index] = 0;
            }
            else
            {
                if (neighbor_count == 3)
                    game->next_board[cell_index] = 1;
                else
                    game->next_board[cell_index] = 0;
            }
            col++;
        }
        row++;
    }

    // Échange des deux buffers : next_board devient le plateau courant,
    // et l'ancien board devient disponible pour la prochaine génération.
    tmp              = game->board;
    game->board      = game->next_board;
    game->next_board = tmp;
}

// ─── Affichage ────────────────────────────────────────────────────────────────

// Convertit les valeurs internes (0/1) en caractères affichables (' '/'O').
void print_board(t_game *game)
{
    int row;
    int col;
    int cell_index;

    row = 0;
    while (row < game->height)
    {
        col = 0;
        while (col < game->width)
        {
            cell_index = row * game->width + col;
            if (game->board[cell_index] == 1)
                putchar('O');
            else
                putchar(' ');
            col++;
        }
        putchar('\n');
        row++;
    }
}

// ─── Gestion de la mémoire ────────────────────────────────────────────────────

// Les deux buffers sont alloués ensemble et libérés ensemble.
void free_board(t_game *game)
{
    free(game->board);
    free(game->next_board);
    game->board      = NULL;
    game->next_board = NULL;
}

// ─── Point d'entrée ───────────────────────────────────────────────────────────

int main(int argc, char *argv[])
{
    t_game game;
    int    generation;

    if (argc != 4)
        return 1;

    if (init_game(&game, argv) == -1)
        return 1;

    fill_board(&game);

    generation = 0;
    while (generation < game.iterations)
    {
        play(&game);
        generation++;
    }

    print_board(&game);
    free_board(&game);
    return 0;
}
