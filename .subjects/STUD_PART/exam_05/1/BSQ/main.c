#include "bsq.h"

int main(int argc, char *argv[])
{
    int arg_index;
    int result;

    if (argc == 1)
    {
        result = execute_bsq(stdin);
        if (result == -1)
            fprintf(stderr, "map error\n");
    }
    else
    {
        arg_index = 1;
        while (arg_index < argc)
        {
            result = run_bsq_on_file(argv[arg_index]);
            if (result == -1)
                fprintf(stderr, "map error\n");

            // On affiche une ligne vide entre les cartes (mais pas après la dernière)
            if (arg_index < argc - 1)
                fprintf(stdout, "\n");

            arg_index++;
        }
    }
    return 0;
}
