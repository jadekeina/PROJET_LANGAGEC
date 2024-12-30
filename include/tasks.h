//
// Created by jadek on 27/12/2024.
//
// tasks.h
#ifndef PROJETS_TASKS_H_H
#define PROJETS_TASKS_H_H

#define MAX_TASKS 100

typedef enum {
    TODO,        // Tâche à faire
    IN_PROGRESS, // Tâche en cours
    DONE         // Tâche terminée
} TaskStatus;

typedef struct {
    int id;               // Identifiant unique de la tâche
    char title[100];      // Titre de la tâche
    char description[200]; // Description de la tâche
    TaskStatus status;    // Statut de la tâche
    char assignee[50];    // Utilisateur auquel la tâche est attribuée
} Task;

void create_task(Task* task, const char* title, const char* description);
void modify_task(Task* task, const char* new_title, const char* new_description);
void assign_task(Task* task, const char* assignee);
void set_task_status(Task* task, TaskStatus status);
void display_task(const Task* task);

#endif // TASKS_H
