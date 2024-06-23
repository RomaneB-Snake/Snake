#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "snake.h"

//Création d'un nouveau serpent
Snake* new_snake() {
    //Allocation de mémoire pour le serpent
    Snake* snake = (Snake*)malloc(sizeof(Snake));
    //Vérification si l'allocation a échoué alors message erreur
    if (snake == NULL) {
        fprintf(stderr, "Impossible d'allouer la mémoire pour le serpent\n");
        exit(EXIT_FAILURE);
    }
    //Initialisation de la liste des segments
    snake->segments_list = NULL;
    snake->size = 0;
    //Initialisation de la direction du serpent à droite
    snake->dir = RIGHT;
    //Retourne pointeur vers nouveau serpent
    return snake;
}
//Ajouter segment au serpent
void add_segment(Snake* snake, int x, int y) {
    //Alloue mémoire pour le nouveau segment
    Position* new_segment = (Position*)malloc(sizeof(Position));
    //Vérification de l'allocation si erreur alors message
    if (new_segment == NULL) {
        fprintf(stderr, "Impossible d'allouer la mémoire pour le nouveau segment\n");
        exit(EXIT_FAILURE);
    }
    //Initialisation de la position x et y du segment
    new_segment->x = x;
    new_segment->y = y;
    new_segment->next = NULL;

    //vérification  si serpent pas encore de segment
    if (snake->segments_list == NULL) {
        snake->segments_list = new_segment;
        //Z'il a segment alors parcours liste
    } else {
        Position* temp = snake->segments_list;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        //ajoute le nouveau segment à la gin de la liste 
        temp->next = new_segment;
    }
    //Incrémentation de la taille du serpent
    snake->size++;
}
//Libération de la mémoire occupé par le serpent
void free_snake(Snake* snake) {
    //Pointeur temporaire pour parcourir la liste
    Position* temp = snake->segments_list;
    //Boucle sur tous les segments du serpent
    while (temp != NULL) {
        //stocke le pointeur vers le segment suivant
        Position* next = temp->next;
        //Libère mémoire du segment
        free(temp);
        //Passe au segment suivant
        temp = next;
    }
    //Libère mémoire serpent 
    free(snake);
}


