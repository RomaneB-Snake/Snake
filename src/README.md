#Jeu : Snake

##Description du projet
Ce projet est la création du jeu Snake dans le cadre de cours en langage de programmation C. La bibliothèque MLV a été utilisé pour permettre l’affichage de la fenêtre de jeu et des couleurs pour les objets du projet comme les fruits, les murs ou les cases vides. L’objectif du jeu est donc de contrôle le serpent pour qu’il se déplace dans la fenêtre et qu’il mange tous les fruits. Si le serpent se rentre dans le mur alors la partie est terminée.

##Fonctionnalités 
-Chargement d’une grille à partir d’un fichier indiqué en paramètres
-Création et affichage de la grille
-Affiche des messages d’erreurs ou de victoire
-Gestion des collisions
-Gestion du déplacement du serpent
-Gestion de la taille du serpent
-Gestion du nombre de fruits présent sur la grille
-Chargement d’un fichier default en cas de problème
-Gestion de l’allocation dynamique de la mémorie

##Téléchargement du projet
-Cloner le dépôt :
git clone https://github.com/RomaneB-Snake/Snake.git 

-Accéder aux fichiers du projet ;
cd Snake

-Compiler :
make

##Lancement du jeu

./game -i level1.txt

##Contrôle du serpent

Flèche Haut : Déplace le serpent vers le haut.
Flèche Bas : Déplace le serpent vers le bas.
Flèche Gauche : Déplace le serpent vers la gauche.
Flèche Droite : Déplace le serpent vers la droite.
Échap : Quitte le jeu.

##Fichiers du projet

-game.c
-grid.h et grid.c
-snake.h et snake.c
-getopt_long.h et getopt_long.c
