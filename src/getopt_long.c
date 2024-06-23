#include "getopt_long.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>


const char* program_name;
//fichier récupérer avec option -i
const char* output_filename = NULL;
const char* input_filename = NULL;

void print_usage (FILE* stream, int exit_code)
{
  fprintf (stream, "Utilisation : %s options [fichierentrée ...]\n",program_name);
  fprintf (stream,
           " -h --help               Affiche ce message.\n"
           " -i --input <filename>   Spécifie le fichier d'entrée pour la grille.\n"
           " -o --output filename    Redirige la sortie vers un fichier.\n"
           " -v --verbose            Affiche des messages détaillés.\n");
  exit (exit_code);
}



//Traitement des arguments mis en ligne de commande
void print_help (int argc, char* argv[])
{
  int next_option;
  //lettre valide
  const char* const short_options = "hi:o:v";
  /* Tableau décrivant les options longues valides. */
  const struct option long_options[] = {
    { "help",     0, NULL, 'h' },
    { "input",    1, NULL, 'i'},
    { "output",   1, NULL, 'o' },
    { "verbose", 0, NULL, 'v' },
    { NULL,       0, NULL, 0   }   /* Requis à la fin du tableau.  */
};


/* Indique si l'on doit afficher les messages détaillés. */
int verbose = 0;
/* Mémorise le nom du programme, afin de l'intégrer aux messages.
    Le nom est contenu dans argv[0]. */
program_name = argv[0];
do {
   next_option = getopt_long (argc, argv, short_options,
                              long_options, NULL);
   switch (next_option) {
    case 'h':   /* -h or --help */
        print_usage(stdout, 0);
        break; 
    case 'i':
                // Stocke le nom de fichier d'entrée utilisé pour option -i
                input_filename = optarg;  
                break;
    case 'o':   /* -o ou --output */
        output_filename = optarg;
        break;
    case 'v':   /* -v ou --verbose */
        verbose = 1;
        break;
    case '?':   /* L'utilisateur a saisi une option invalide. */
        print_usage(stderr, 1);
        break;  // Ajoutez ce break
    case -1:    /* Fin des options.  */
        break;
    default:    /* Quelque chose d'autre : inattendu.  */
        abort();
  }

}
while (next_option != -1);
  if (verbose) {
    int i;
    for (i = optind; i < argc; ++i)
      printf ("Argument : %s\n", argv[i]);
  }

  
}
