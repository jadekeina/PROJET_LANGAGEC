//
// Created by jadek on 27/12/2024.
//
// tasks.h
#ifndef PROJETS_TASKS_H_H
#define PROJETS_TASKS_H_H

#define MAX_TASKS 100

typedef enum {
    TODO,
    IN_PROGRESS,
    DONE
} TaskStatus;

typedef struct {
    int id;
    char title[100];
    char description[200];
    TaskStatus status;
    char assignee[50];
} Task;

void create_task(Task* task, const char* title, const char* description);
void modify_task(Task* task, const char* new_title, const char* new_description);
void assign_task(Task* task, const char* assignee);
void set_task_status(Task* task, TaskStatus status);
void display_task(const Task* task);

#endif // TASKS_H
