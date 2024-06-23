#define _POSIX_C_SOURCE 200809L
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include <unistd.h>  // Pour getline
#include <sys/types.h>  // Pour getline

// Allocation mémoire pour la grille avec nbl pour lignes et nbc pour nb colonnes
Grid* allocate_grid(int nbl, int nbc) {
    //Allocation de mémoire pour la structure Grid
    Grid* grid = malloc(sizeof(Grid));
    //Vérification si l'allocation a échoué
    if (!grid) {
        fprintf(stderr, "Allocation mémoire impossible pour le structure de la grille\n");
        //Message d'erreur affiché et arrêt de la compilation
        exit(EXIT_FAILURE);
    }
    //Initialisation du nombre de colonnes et de lignes
    grid->nbl = nbl;
    grid->nbc = nbc;
    //Allocation mémoire pour la grille
    grid->grid = malloc(nbl * sizeof(char*));
    //Si allocation a échoué alors message d'erreur et arrêt de la compilation
    if (!grid->grid) {
        free(grid);
        fprintf(stderr, "Allocation mémoire impossible for grid rows\n");
        exit(EXIT_FAILURE);
    }
    //Boucle permet allocation pour chaque lignes
    for (int i = 0; i < nbl; i++) {
        //Allocation mémoire pour chaque colonnes
        grid->grid[i] = malloc(nbc * sizeof(char));
        //Vérification si l'allocation a bien fonctionné
        if (!grid->grid[i]) {
            for (int j = 0; j < i; j++) {
                free(grid->grid[j]);
            }
            //Libération de la mémoire allouée pour les lignes et les colonnes
            free(grid->grid);
            free(grid);
            fprintf(stderr, "Allocation mémoire impossible for grid rows %d.\n", i);
            exit(EXIT_FAILURE);
        }
    }
    //retourne pointeur vers la grille allouée
    return grid;
}

// Libère mémoire de la grille
void free_grid(Grid *grid) {
    //Boucle permet de libérer mémoire
    for (int i = 0; i < grid->nbl; i++) {
        free(grid->grid[i]);
    }
    free(grid->grid);
    free(grid);
}

// Compte nb de fruits dans la grille
int compte_fruits(const Grid *grid) {
    int count = 0;
    //Boucle sur chaque ligne de la grille
    for (int i = 0; i < grid->nbl; i++) {
        //Boucle sur chaque colonne de la grille
        for (int j = 0; j < grid->nbc; j++) {
            if (grid->grid[i][j] == FRUIT) {
                count++;
            }
        }
    }
    return count;
}

//Compte nb lignes dans la grille
int count_nb_lines(FILE *file) {
    int lines = 0;
    char ch;
    //Boucle pour permet de lire chaque caractères du fichier
    while ((ch = fgetc(file)) != EOF) {
        //Vérifie si caractère est pour aller à la ligne
        if (ch == '\n') {
            //Incrémente le nombre de ligne
            lines++;
        }
    }
    //Retourne le nombre de ligne dans le fichier
    return lines;
}

// Charge grille à partir du fichier
int charge_grid_fichier(Grid *grid, const char* filename) {
    //Ouverture du fichier en lecture
    FILE* file = fopen(filename, "r");
    //Si ouverture fichier a échoué alors un message d'erreur s'affcihe
    if (!file) {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s pour lire la grille\n", filename);
        return -1;
    }

    int nbl = count_nb_lines(file);
    //Met le pointeur de fichier au début
    rewind(file);

    size_t size_buf = 0;
    char *buf = NULL;
    //Lecture de la première ligne du fichier
    ssize_t nbc = getline(&buf, &size_buf, file);
    //Si lecture a échoué alors message d'erreur et retourne une erreur
    if (nbc == -1) {
        fprintf(stderr, "Impossible de lire le fichier\n");
        fclose(file);
        return -1;
    }
    nbc--; 
    
    //réalloue la mémoire pour le nombre de ligne et de colonnes
    grid->grid = realloc(grid->grid, nbl * sizeof(char*));
    grid->grid[0] = realloc(grid->grid[0], nbc * sizeof(char));
    //Copie la ligne dans la grille
    strncpy(grid->grid[0], buf, nbc);
    
    //Boucles pour les lignes suivantes
    for (int i = 1; i < nbl; i++) {
        grid->grid[i] = malloc(nbc * sizeof(char));
        //Lecture de la ligne suivante
        getline(&buf, &size_buf, file);
        strncpy(grid->grid[i], buf, nbc);
    }

    //Libère la mémoire tampon
    free(buf);
    //Ferme fichier
    fclose(file);

    //initialise le nombre de ligne et de colonnes
    grid->nbl = nbl;
    grid->nbc = nbc;

    return 0;
}

// Dessin de la grille dans la fenêtre
void draw_grid(const Grid *grid) {
    //Largeur de la fenêtre
    int width = MLV_get_window_width();
    //Hauteur de la fenêtre
    int height = MLV_get_window_height();
    //Calcul la taille de chaque carré
    int taille_carre = compute_size(width, height, grid->nbc, grid->nbl);

    //Netttoie et initialise la couleur de la fenêtre  par marron
    MLV_clear_window(MLV_COLOR_BROWN);
    //Boucle sur les lignes et les colonnes de la grille
    for (int i = 0; i < grid->nbl; i++) {
        for (int j = 0; j < grid->nbc; j++) {
            //Couleur de la fenêtre par défaut
            MLV_Color color = MLV_COLOR_WHITE;
            //La couleur du carré en fonction de son contenu
            switch (grid->grid[i][j]) {
                //Contenu: mur
                case WALL: color = MLV_COLOR_BLACK; break;
                //Contenu: fruit
                case FRUIT: color = MLV_COLOR_RED; break;
                //Contenu serpent
                case SNAKE: color = MLV_COLOR_GREEN; break;
                default: break;
            }
            //Dessin du carré
            MLV_draw_filled_rectangle(j * taille_carre, i * taille_carre, taille_carre, taille_carre, color);
        }
    }
    //Actualisation de la fenêtre
    MLV_actualise_window();
}

// Calcul la taille de chaque carré en fonction de la fenêtre et de la taille de la grille
int compute_size(int w, int h, int nbc, int nbl) {
    //Calcul taille max en largeur
    int taille_max_w = w / nbc;
    //Calcul taille max en hauteur
    int taille_max_h = h / nbl;
    //Retourne taille max carré
    return (taille_max_w < taille_max_h) ? taille_max_w : taille_max_h;
}

// Place du serpent dans la grille
void place_snake(Grid *grid, Snake *snake) {
    //Pointeur vers le premier segment du serpent
    Position *current = snake->segments_list;
    while (current != NULL) {
        //Vérifie segment dans les limites de grille
        if (current->x >= 0 && current->x < grid->nbc && current->y >= 0 && current->y < grid->nbl) {
            //Place segment dans la grille
            grid->grid[current->y][current->x] = SNAKE;
        }
        //Passe segment suivant
        current = current->next;
    }
}

// Deplacement du snake dans la grille
Element move_snake(Grid *grid, Snake *snake) {
    //Pointeur vers la tête du serpent
    Position *head = snake->segments_list;
    //Initialisation de la nouvelle tête du serpent
    int new_x = head->x;
    int new_y = head->y;

    // Calcul la tête du serpent en fonction de sa direction
    switch (snake->dir) {
        //Gauche
        case LEFT: new_x = (head->x - 1 + grid->nbc) % grid->nbc; break;
        //Droite
        case RIGHT: new_x = (head->x + 1) % grid->nbc; break;
        //Vers le gaut
        case TOP: new_y = (head->y - 1 + grid->nbl) % grid->nbl; break;
        //Vers le bas
        case BOTTOM: new_y = (head->y + 1) % grid->nbl; break;
    }

    // Regarde si collision avec le mur ou son corps
    if (grid->grid[new_y][new_x] == WALL || grid->grid[new_y][new_x] == SNAKE) {
        return grid->grid[new_y][new_x];
    }

    // Deplacement de la tête du serpent
    Position *new_head = (Position *)malloc(sizeof(Position));
    if (new_head == NULL) {
        fprintf(stderr, "Allocation de mémoire impossible pour la tête du serpent\n");
        exit(EXIT_FAILURE);
    }
    ///Initialisation de la nouvelle tête
    new_head->x = new_x;
    new_head->y = new_y;
    //Nouvelle tête au début de la liste
    new_head->next = snake->segments_list;
    snake->segments_list = new_head;
      
    //Vérification que la nouvelle tête est un fruit
    if (grid->grid[new_y][new_x] == FRUIT) {
        //Ne supprime pas le serpent et place sa tête dans la grille
        grid->grid[new_y][new_x] = SNAKE;
        //Retourne fruit pour dire que le serpent a mangé un fruit
        return FRUIT;
    } else {
        // Suppression de la queue du serpent
        Position *temp = snake->segments_list;
        while (temp->next->next != NULL) {
            temp = temp->next;
        }
        //Enlève la queue de la grille
        grid->grid[temp->next->y][temp->next->x] = EMPTY;
        //Libère mémoire
        free(temp->next);
        //Mise à jour du pointeur sur l'avant l'avant dernier segment
        temp->next = NULL;
        //Place ma tête du serpent dans la grille 
        grid->grid[new_y][new_x] = SNAKE;
        //Déplacement sans manger de fruit
        return EMPTY;
    }
}

