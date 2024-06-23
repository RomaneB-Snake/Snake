#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "grid.h"
#include "snake.h"
#include "getopt_long.h"

// Difficulté 6, vitesse serpent
#define DIFFICULTY 6

int main(int argc, char* argv[]) {
    // Traitement des arguments mis en ligne de commande
    print_help(argc, argv);

    // Création d'une grille de jeu
    Grid* grid = NULL;
    //Variable permet de compter les fruits
    int nb_fruit = 0;
    //nombre boucle serpent
    int nb_boucle = 0;

    //Au départ aucune touche au clavier
    MLV_Keyboard_button touche = MLV_KEYBOARD_NONE;
    //Création fenêtre de jeu
    MLV_create_window("SNAKE", "3R-IN1B", 640, 480);
    //Taux de rafraîchissement changé à 24 images par secondes 
    MLV_change_frame_rate(24);
    
    //Détermine si le fichier à charger est en paramètre ou le fichier par défaut
    const char* filename = input_filename ? input_filename : "levels/default";
    //Allocation mémoire pour la grille
    grid = allocate_grid(22, 36); // Taille exemple, à adapter selon le contenu du fichier
    
    //Chargement grille à partir du fichier
    if (charge_grid_fichier(grid, filename) != 0) {
        //Message d'erreur si le fichier ne peut pas charger
        fprintf(stderr, "Impossible de charger la grille depuis le fichier default: %s\n", filename);
        if (strcmp(filename, "levels/default") != 0) {
            fprintf(stderr, "Chargement de la grille du fichier default à partir du dossier levels\n");
            if (charge_grid_fichier(grid, "levels/default") != 0) {
                fprintf(stderr, "Impossible de charger la grille à partir du fichier default: levels/default\n");
                //Libération mémoire de la grille
                free_grid(grid);
                //Fermeture fenêtre
                MLV_free_window();
                return 1;
            }
        } else {
            //Libération mémoire de la grille
            free_grid(grid);
            //Fermeture de la fenêtre
            MLV_free_window();
            return 1;
        }
    }
    //compte nombre de fruits dans la grille
    nb_fruit = compte_fruits(grid);

    // Création et initialisation du serpent
    Snake* snake = new_snake();
    //Des segments sont ajoutés au serpent
    add_segment(snake, 1, 3);
    add_segment(snake, 1, 2);
    add_segment(snake, 1, 1);
    add_segment(snake, 1, 0);
    //La direction du serpent par défaut est vers la droite
    snake->dir = RIGHT;
    //Placement du serpent dans la grille
    place_snake(grid, snake);

    // Boucle principale
    while ((MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL) == MLV_NONE) || touche != MLV_KEYBOARD_ESCAPE) {
        //Fond de la fenêtre marron par défaut
        MLV_clear_window(MLV_COLOR_BROWN);
        nb_boucle = (nb_boucle + 1) % DIFFICULTY;
        if (nb_boucle == 0) {
            //Déplacement du serpent et gestion des collisions
            Element result = move_snake(grid, snake);
            if (result == WALL || result == SNAKE) {
                //Affiche message de fin de jeu
                MLV_draw_text(0, 0, "Partie perdue!", MLV_COLOR_RED);
                MLV_actualise_window();
                sleep(2);
                break;
            } else if (result == FRUIT) {
                //nombre de fruits décrémenter
                nb_fruit--;
                if (nb_fruit == 0) {
                    //Affiche message que le serpent a mangé tous les fruit, la partie est gagnée
                    MLV_draw_text(0, 0, "Bravo vous avez mangé tous les fruits de la grille !", MLV_COLOR_GREEN);
                    MLV_actualise_window();
                    sleep(2);
                    break;
                }
            }
        }
        
        //La grille est dessinée
        draw_grid(grid);
        MLV_actualise_window();

        // Gestion des directions du serpent selon la touche pressée
        switch (touche) {
            case MLV_KEYBOARD_DOWN:
                //Exemple: déplacement vers le bas
                if (snake->dir != TOP) snake->dir = BOTTOM;
                break;
            case MLV_KEYBOARD_UP:
                if (snake->dir != BOTTOM) snake->dir = TOP;
                break;
            case MLV_KEYBOARD_LEFT:
                if (snake->dir != RIGHT) snake->dir = LEFT;
                break;
            case MLV_KEYBOARD_RIGHT:
                if (snake->dir != LEFT) snake->dir = RIGHT;
                break;
            default:
                break;
        }

        // Touche réinitialiser pour prochain tour/boucle
        touche = MLV_KEYBOARD_NONE;
        MLV_delay_according_to_frame_rate();
    }
    
    //Libération de la mémoire dynamique du serpent
    free_snake(snake);
    //Libération de la mémoire dynamique de la grille
    free_grid(grid);
    //Fermeture de la fenêtre
    MLV_free_window();
    //Fin programme
    return 0;
}

