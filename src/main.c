#include <stdio.h>
#include <locale.h>
#include "../include/tasks.h"

#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"


// Dimensions de la fenêtre
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void run_task_manager();

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");  // Gestion des accents
    printf("Bienvenue dans l'application principale !\n");

    // Ajouter des tâches avant de lancer l'application
    addTask("Première tâche", "Description de test", TODO);
    addTask("Deuxième tâche", "Encore une description", IN_PROGRESS);
    addTask("Troisième tâche", "Description finale", DONE);

    // Ici on va faire l'Appel du gestionnaire de tâches
    run_task_manager();

    return 0;
}


