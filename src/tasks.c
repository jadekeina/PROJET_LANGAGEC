#define SDL_MAIN_HANDLED
#include "../include/tasks.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
#define MAX_INPUT_LENGTH 256

char task_title_input[MAX_INPUT_LENGTH] = "";  // Correction du point-virgule manquant
char task_description_input[MAX_INPUT_LENGTH] = "";  // Correction du point-virgule manquant

// Ici on a le tableau de task et du compteur
Task tasks[MAX_TASKS];
int task_count = 0;

bool is_title_input_active = false;  // Pour savoir si le champ du titre est actif
bool is_description_input_active = false;  // Pour savoir si le champ de description est actif

void create_task(Task* task, const char* title, const char* description) {
    if (task != NULL) {
        static int task_id = 0;
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

void handle_text_input(SDL_Event *event) {
    if (event->type == SDL_TEXTINPUT) {
        // Saisie pour le titre ou la description
        if (is_title_input_active) {
            strncat(task_title_input, event->text.text, sizeof(task_title_input) - strlen(task_title_input) - 1);
        } else if (is_description_input_active) {
            strncat(task_description_input, event->text.text, sizeof(task_description_input) - strlen(task_description_input) - 1);

        }
    }
}

void renderTasks(SDL_Renderer *renderer, TTF_Font *font) {
    int x = 50, y = 50, width = 200, height = 50;

    for (int i = 0; i < task_count; i++) {
        // Choisir la couleur en fonction du statut
        if (tasks[i].status == TODO) {
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Orange
        } else if (tasks[i].status == IN_PROGRESS) {
            SDL_SetRenderDrawColor(renderer, 70, 130, 180, 255); // Bleu
        } else if (tasks[i].status == DONE) {
            SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255); // Vert
        }

        SDL_Rect taskRect = {x, y + i * (height + 10), width, height};
        SDL_RenderFillRect(renderer, &taskRect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir
        SDL_RenderDrawRect(renderer, &taskRect);

        SDL_Color textColor = {0, 0, 0}; // Texte en noir
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, tasks[i].title, textColor);
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_Rect textRect = {x + 10, y + i * (height + 10) + 10, textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

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

void run_task_manager() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *window = SDL_CreateWindow("Gestion des Tâches", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *font = TTF_OpenFont("path_to_font/arial.ttf", 24);
    if (!font) {
        printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_TEXTINPUT) {
                handle_text_input(&event);  // Gérer l'entrée du texte
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        renderTasks(renderer, font);  // Affichage des tâches
        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
}
