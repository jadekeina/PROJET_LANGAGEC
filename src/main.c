#include <stdio.h>
#include "../cmake_modules/SDL2/SDL.h"
#include "../include/tasks.h"
#include "../include/SDL_ttf.h"

// Dimensions de la fenêtre
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void run_task_manager();

int main(int argc, char *argv[]) {
    printf("Bienvenue dans l'application principale !\n");

    // Ici on va faire l'Appel du gestionnaire de tâches
    run_task_manager();

    return 0;
}
