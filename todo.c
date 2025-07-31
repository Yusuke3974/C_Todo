#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_LEN 256
#define FILENAME "data/tasks.txt"

char tasks[MAX_TASKS][MAX_LEN];
int task_count = 0;

void load_tasks()
{
    FILE *file = fopen(FILENAME, "r");
    if (!file)
        return;

    while (fgets(tasks[task_count], MAX_LEN, file))
    {
        tasks[task_count][strcspn(tasks[task_count], "\n")] = '\0'; // remove newline
        task_count++;
    }
    fclose(file);
}

void save_tasks()
{
    FILE *file = fopen(FILENAME, "w");
    for (int i = 0; i < task_count; i++)
    {
        fprintf(file, "%s\n", tasks[i]);
    }
    fclose(file);
}

void list_tasks()
{
    for (int i = 0; i < task_count; i++)
    {
        printf("%d. %s\n", i + 1, tasks[i]);
    }
}

void add_task(const char *task)
{
    if (task_count < MAX_TASKS)
    {
        strncpy(tasks[task_count], task, MAX_LEN);
        task_count++;
        save_tasks();
    }
}

void remove_task(int index)
{
    if (index < 1 || index > task_count)
        return;
    for (int i = index - 1; i < task_count - 1; i++)
    {
        strcpy(tasks[i], tasks[i + 1]);
    }
    task_count--;
    save_tasks();
}

int main()
{
    char command[MAX_LEN];
    load_tasks();

    printf("簡易ToDoリスト\nadd <task> / list / remove <index> / exit\n");
    while (1)
    {
        printf("> ");
        fgets(command, MAX_LEN, stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strncmp(command, "add ", 4) == 0)
        {
            add_task(command + 4);
        }
        else if (strcmp(command, "list") == 0)
        {
            list_tasks();
        }
        else if (strncmp(command, "remove ", 7) == 0)
        {
            int index = atoi(command + 7);
            remove_task(index);
        }
        else if (strcmp(command, "exit") == 0)
        {
            break;
        }
        else
        {
            printf("コマンドが無効です。\n");
        }
    }
    return 0;
}
