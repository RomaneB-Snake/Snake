#ifndef GRID_H
#define GRID_H

typedef enum { WALL = 'w', EMPTY = ' ', FRUIT = 'f', SNAKE = 's' } Element;

//Structure de la grille
typedef struct Grid {
    char** grid;
    int nbc;
    int nbl;
} Grid;

#include "snake.h"
#include <stdio.h>

// Allocation mémoire pour la grille avec nbl pour lignes et nbc pour nb colonnes
Grid* allocate_grid(int nbl, int nbc);
// Libère mémoire de la grille
void free_grid(Grid *grid);
// Dessin de la grille dans la fenêtre
void draw_grid(const Grid *grid);
// Deplacement du snake dans la grille
Element move_snake(Grid *grid, Snake *snake);
// Charge grille à partir du fichier
int charge_grid_fichier(Grid *grid, const char* filename);
//compte nombre de fruits dans la grille
int compte_fruits(const Grid *grid);
//Compte nb lignes dans la grille
int count_nb_lines(FILE *file);
// Calcul la taille de chaque carré en fonction de la fenêtre et de la taille de la grille
int compute_size(int w, int h, int nbc, int nbl);
void debug(const Grid *grid);

#endif

