#ifndef SNAKE_H
#define SNAKE_H

struct Grid;  // Forward declaration

//Déplacement du serpent
typedef enum { TOP, BOTTOM, LEFT, RIGHT } Direction;

//structure de la position du serpent
typedef struct Position {
    int x;
    int y;
    struct Position* next;
} Position;

//structure du serpent
typedef struct {
    Position* segments_list;
    Direction dir;
    int size;
} Snake;

//structure pour les coordonnées du serpent
typedef struct {
    int x;
    int y;
} Coord;

//initialisation du serpent
Snake* new_snake();

//Ajouter un segment au serpent
void add_segment(Snake* snake, int x, int y);

//Libération allocation mémoire dynamique du serpent
void free_snake(Snake* snake);

// Place du serpent dans la grille
void place_snake(struct Grid *grid, Snake *snake);

#endif

