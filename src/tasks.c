#include "../include/tasks.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../cmake_modules/SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
 // Inclusion de SDL_ttf pour le texte

// Tableau de tâches et compteur
Task tasks[MAX_TASKS];
int task_count = 0;

void create_task(Task* task, const char* title, const char* description) {
    if (task != NULL) {
        static int task_id = 0; // Identifiant unique auto-incrémenté
        task->id = task_id++;
        strncpy(task->title, title, sizeof(task->title) - 1);
        strncpy(task->description, description, sizeof(task->description) - 1);
        task->status = TODO;
        task->title[sizeof(task->title) - 1] = '\0';
        task->description[sizeof(task->description) - 1] = '\0';
    }
}

void modify_task(Task* task, const char* new_title, const char* new_description) {
    if (task != NULL) {
        strncpy(task->title, new_title, sizeof(task->title) - 1);
        strncpy(task->description, new_description, sizeof(task->description) - 1);
        task->title[sizeof(task->title) - 1] = '\0';
        task->description[sizeof(task->description) - 1] = '\0';
    }
}

void assign_task(Task* task, const char* assignee) {
    if (task != NULL) {
        strncpy(task->assignee, assignee, sizeof(task->assignee) - 1);
        task->assignee[sizeof(task->assignee) - 1] = '\0';
    }
}

void set_task_status(Task* task, TaskStatus status) {
    if (task != NULL) {
        task->status = status;
    }
}

void display_task(const Task* task) {
    if (task != NULL) {
        printf("ID: %d\n", task->id);
        printf("Titre: %s\n", task->title);
        printf("Description: %s\n", task->description);
        printf("Statut: %d\n", task->status);
        printf("Attribué à: %s\n", task->assignee);
    }
}

// Prototypes des fonctions
void renderTasks(SDL_Renderer *renderer, TTF_Font *font);
void addTask(const char *title, const char *description, TaskStatus status);

void run_task_manager() {
    // Initialisation SDL
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();  // Initialisation de SDL_ttf

    SDL_Window *window = SDL_CreateWindow("Gestion des Tâches", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Chargement de la police (assure-toi que le fichier "font.ttf" est bien dans ton projet)
    TTF_Font *font = TTF_OpenFont("path_to_font/arial.ttf", 24); // Remplace par ton chemin de fichier .ttf
    if (!font) {
        printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return;
    }

    // Ajout de quelques tâches test
    addTask("Tâche 1", "Description 1", TODO);
    addTask("Tâche 2", "Description 2", IN_PROGRESS);
    addTask("Tâche 3", "Description 3", DONE);

    bool running = true;
    SDL_Event event;

    while (running) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Nettoyage et rendu des tâches
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Fond blanc
        SDL_RenderClear(renderer);
        renderTasks(renderer, font); // Affichage des tâches
        SDL_RenderPresent(renderer);
    }

    // Nettoyage
    TTF_CloseFont(font);  // Fermer la police
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();  // Fermer SDL_ttf
}

// Fonction pour afficher les tâches avec des rectangles colorés
void renderTasks(SDL_Renderer *renderer, TTF_Font *font) {
    int x = 50, y = 50, width = 200, height = 50;

    for (int i = 0; i < task_count; i++) {
        // Définir la couleur en fonction du statut
        if (tasks[i].status == TODO) {
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Orange
        } else if (tasks[i].status == IN_PROGRESS) {
            SDL_SetRenderDrawColor(renderer, 70, 130, 180, 255); // Bleu
        } else if (tasks[i].status == DONE) {
            SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255); // Vert
        }

        // Dessiner un rectangle pour chaque tâche
        SDL_Rect taskRect = {x, y + i * (height + 10), width, height};
        SDL_RenderFillRect(renderer, &taskRect);

        // Ajouter une bordure
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir
        SDL_RenderDrawRect(renderer, &taskRect);

        // Créer une texture pour le texte de la tâche
        SDL_Color textColor = {0, 0, 0}; // Texte en noir
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, tasks[i].title, textColor);
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        // Afficher le texte dans la fenêtre
        SDL_Rect textRect = {x + 10, y + i * (height + 10) + 10, textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        // Libération de la surface et texture
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

// Ajouter une tâche
void addTask(const char *title, const char *description, TaskStatus status) {
    if (task_count < MAX_TASKS) {
        tasks[task_count].id = task_count + 1;
        strncpy(tasks[task_count].title, title, sizeof(tasks[task_count].title) - 1);
        tasks[task_count].title[sizeof(tasks[task_count].title) - 1] = '\0';

        strncpy(tasks[task_count].description, description, sizeof(tasks[task_count].description) - 1);
        tasks[task_count].description[sizeof(tasks[task_count].description) - 1] = '\0';

        tasks[task_count].status = status;
        strncpy(tasks[task_count].assignee, "Non assigné", sizeof(tasks[task_count].assignee) - 1);
        task_count++;
    } else {
        printf("Nombre maximum de tâches atteint.\n");
    }
}