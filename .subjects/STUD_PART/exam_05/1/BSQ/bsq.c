#include "bsq.h"

// ─── Fonctions mémoire ────────────────────────────────────────────────────────

static void free_rows(char **rows)
{
    int i;

    if (rows == NULL)
        return;
    i = 0;
    while (rows[i] != NULL)
    {
        free(rows[i]);
        i++;
    }
    free(rows);
}

// Copie nb_chars caractères depuis la position start dans src vers une nouvelle chaîne.
static char *extract_substring(char *src, int start, int nb_chars)
{
    char *result;
    int  i;
    int  j;

    result = (char *)malloc(nb_chars + 1);
    if (result == NULL)
        return NULL;
    i = 0;
    j = 0;
    while (src[i])
    {
        if (i >= start && j < nb_chars)
        {
            result[j] = src[i];
            j++;
        }
        i++;
    }
    result[j] = '\0';
    return result;
}

// ─── Lecture de l'en-tête ────────────────────────────────────────────────────

// Lit la première ligne du fichier : "N vide obstacle plein"
// Retourne 0 en cas de succès, -1 si l'en-tête est invalide.
static int parse_header(FILE *file, t_map_chars *chars)
{
    int fields_read;

    fields_read = fscanf(file, "%d %c %c %c",
        &chars->line_count,
        &chars->empty,
        &chars->obstacle,
        &chars->full);

    if (fields_read != 4)
        return -1;
    if (chars->line_count <= 0)
        return -1;
    if (chars->empty    == chars->obstacle)
        return -1;
    if (chars->empty    == chars->full)
        return -1;
    if (chars->obstacle == chars->full)
        return -1;
    if (chars->empty    < 32 || chars->empty    > 126)
        return -1;
    if (chars->obstacle < 32 || chars->obstacle > 126)
        return -1;
    if (chars->full     < 32 || chars->full     > 126)
        return -1;
    return 0;
}

// ─── Validation de la carte ───────────────────────────────────────────────────

// Vérifie que chaque cellule de la grille est soit empty_char soit obstacle_char.
static int validate_grid_chars(char **rows, char empty_char, char obstacle_char)
{
    int row;
    int col;

    row = 0;
    while (rows[row] != NULL)
    {
        col = 0;
        while (rows[row][col] != '\0')
        {
            if (rows[row][col] != empty_char && rows[row][col] != obstacle_char)
                return -1;
            col++;
        }
        row++;
    }
    return 0;
}

// ─── Chargement de la carte ───────────────────────────────────────────────────

// Libère le buffer de lecture et les lignes déjà allouées, puis retourne -1.
// Centralise le nettoyage pour éviter la répétition à chaque point d'erreur.
static int load_error(char *line, char **rows)
{
    if (line)
        free(line);
    if (rows)
        free_rows(rows);
    return -1;
}

// Lit toutes les lignes du fichier et remplit la grille.
// Retourne 0 en cas de succès, -1 si la carte est malformée.
static int load_grid(FILE *file, t_grid *grid, t_map_chars *chars)
{
    char   *line;
    size_t  buffer_size;
    int     bytes_read;
    int     row_index;
    int     row_length;

    grid->height = chars->line_count;
    grid->rows   = (char **)malloc((grid->height + 1) * sizeof(char *));
    if (grid->rows == NULL)
        return -1;
    grid->rows[grid->height] = NULL;

    line        = NULL;
    buffer_size = 0;

    // On saute le reste de la ligne d'en-tête
    if (getline(&line, &buffer_size, file) == -1)
        return load_error(line, grid->rows);

    row_index = 0;
    while (row_index < grid->height)
    {
        bytes_read = (int)getline(&line, &buffer_size, file);
        if (bytes_read == -1)
            return load_error(line, grid->rows);

        // La ligne doit se terminer par '\n' (garanti par l'énoncé)
        if (line[bytes_read - 1] != '\n')
            return load_error(line, grid->rows);

        // On supprime le '\n' : la longueur réelle de la ligne est bytes_read - 1
        row_length = bytes_read - 1;

        // Toutes les lignes doivent avoir la même largeur
        if (row_index == 0)
            grid->width = row_length;
        else if (grid->width != row_length)
            return load_error(line, grid->rows);

        grid->rows[row_index] = extract_substring(line, 0, row_length);
        if (grid->rows[row_index] == NULL)
            return load_error(line, grid->rows);

        row_index++;
    }

    free(line);

    if (validate_grid_chars(grid->rows, chars->empty, chars->obstacle) == -1)
        return load_error(NULL, grid->rows);

    return 0;
}

// ─── Algorithme BSQ ──────────────────────────────────────────────────────────

static int min_of_three(int a, int b, int c)
{
    int minimum;

    minimum = a;
    if (b < minimum)
        minimum = b;
    if (c < minimum)
        minimum = c;
    return minimum;
}

// Approche par programmation dynamique :
// dp[i][j] = taille du plus grand carré dont le coin bas-droit est en (i, j).
// Pour chaque cellule vide : dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
static void find_biggest_square(t_grid *grid, t_square *best, t_map_chars *chars)
{
    int dp[grid->height][grid->width];
    int row;
    int col;

    // Initialisation du tableau dp à zéro
    row = 0;
    while (row < grid->height)
    {
        col = 0;
        while (col < grid->width)
        {
            dp[row][col] = 0;
            col++;
        }
        row++;
    }

    row = 0;
    while (row < grid->height)
    {
        col = 0;
        while (col < grid->width)
        {
            if (grid->rows[row][col] == chars->obstacle)
            {
                dp[row][col] = 0;
            }
            else if (row == 0 || col == 0)
            {
                // Première ligne ou première colonne : la taille maximale du carré est 1
                dp[row][col] = 1;
            }
            else
            {
                int above      = dp[row - 1][col];
                int left       = dp[row][col - 1];
                int upper_left = dp[row - 1][col - 1];
                dp[row][col] = min_of_three(above, left, upper_left) + 1;
            }

            // On mémorise le plus grand carré trouvé jusqu'ici
            if (dp[row][col] > best->size)
            {
                best->size     = dp[row][col];
                best->top_row  = row - dp[row][col] + 1;
                best->left_col = col - dp[row][col] + 1;
            }
            col++;
        }
        row++;
    }
}

// ─── Affichage ────────────────────────────────────────────────────────────────

// Remplit les cellules du meilleur carré avec le caractère 'full' et affiche la grille.
static void print_grid_with_square(t_grid *grid, t_square *best, t_map_chars *chars)
{
    int row;
    int col;

    // On colorie le carré
    row = best->top_row;
    while (row < best->top_row + best->size)
    {
        col = best->left_col;
        while (col < best->left_col + best->size)
        {
            if (row < grid->height && col < grid->width)
                grid->rows[row][col] = chars->full;
            col++;
        }
        row++;
    }

    // On affiche chaque ligne
    row = 0;
    while (row < grid->height)
    {
        fputs(grid->rows[row], stdout);
        fputc('\n', stdout);
        row++;
    }
}

// ─── Points d'entrée publics ──────────────────────────────────────────────────

// Exécute le pipeline BSQ complet sur un fichier déjà ouvert.
int execute_bsq(FILE *file)
{
    t_map_chars chars;
    t_grid      grid;
    t_square    best;

    if (parse_header(file, &chars) == -1)
        return -1;

    if (load_grid(file, &grid, &chars) == -1)
        return -1;

    best.size     = 0;
    best.top_row  = 0;
    best.left_col = 0;
    find_biggest_square(&grid, &best, &chars);
    print_grid_with_square(&grid, &best, &chars);

    free_rows(grid.rows);
    return 0;
}

// Ouvre le fichier donné, exécute BSQ, puis le ferme.
int run_bsq_on_file(char *filename)
{
    FILE *file;
    int   result;

    file = fopen(filename, "r");
    if (file == NULL)
        return -1;
    result = execute_bsq(file);
    fclose(file);
    return result;
}
