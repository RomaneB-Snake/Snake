#ifndef GETOPT_LONG_H
#define GETOPT_LONG_H

#include <stdio.h>

//nom de l'exécutable
extern const char* program_name;
//stocke nom fichier entrée en option
extern const char* input_filename;
//Affiche à l'utilisateur les options disponibles
void print_usage(FILE* stream, int exit_code);
// Traitement les arguments mis en ligne de commande
void print_help(int argc, char* argv[]);

#endif
