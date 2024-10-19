#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define TITLE_LENGTH 100
#define DESCRIPTION_LENGTH 256

typedef struct {
    char title[TITLE_LENGTH];
    char description[DESCRIPTION_LENGTH];
    int completed; // 0 - δ��ɣ�1 - �����
} Task;

void load_tasks(Task tasks[], int *task_count) {
    FILE *file = fopen("tasks.txt", "r");
    if (file) {
        while (fscanf(file, "%[^|]|%[^|]|%d\n", tasks[*task_count].title, tasks[*task_count].description, &tasks[*task_count].completed) == 3) {
            (*task_count)++;
        }
        fclose(file);
    }
}

void save_tasks(Task tasks[], int task_count) {
    FILE *file = fopen("tasks.txt", "w");
    for (int i = 0; i < task_count; i++) {
        fprintf(file, "%s|%s|%d\n", tasks[i].title, tasks[i].description, tasks[i].completed);
    }
    fclose(file);
}

void display_tasks(Task tasks[], int task_count) {
    printf("�����б�:\n");
    for (int i = 0; i < task_count; i++) {
        printf("%d. [%s] %s - %s\n", i + 1, tasks[i].completed ? "?" : "?", tasks[i].title, tasks[i].description);
    }
}

int main() {
    Task tasks[MAX_TASKS];
    int task_count = 0;
    int choice;

    load_tasks(tasks, &task_count);

    while (1) {
        printf("\n�������ϵͳ\n");
        printf("1. �������\n");
        printf("2. �鿴��������\n");
        printf("3. �������Ϊ���\n");
        printf("4. ɾ������\n");
        printf("5. �˳�\n");
        printf("���������ѡ��: ");
        scanf("%d", &choice);
        getchar(); // ���ջ��з�

        switch (choice) {
            case 1:
                if (task_count < MAX_TASKS) {
                    printf("�������������: ");
                    fgets(tasks[task_count].title, TITLE_LENGTH, stdin);
                    tasks[task_count].title[strcspn(tasks[task_count].title, "\n")] = 0; // ȥ�����з�
                    printf("��������������: ");
                    fgets(tasks[task_count].description, DESCRIPTION_LENGTH, stdin);
                    tasks[task_count].description[strcspn(tasks[task_count].description, "\n")] = 0; // ȥ�����з�
                    tasks[task_count].completed = 0;
                    task_count++;
                    save_tasks(tasks, task_count); // ���浽�ļ�
                } else {
                    printf("�����������޷���Ӹ�������\n");
                }
                break;

            case 2:
                display_tasks(tasks, task_count);
                break;

            case 3:
                if (task_count > 0) {
                    printf("������Ҫ���Ϊ��ɵ�������: ");
                    int complete_index;
                    scanf("%d", &complete_index);
                    if (complete_index > 0 && complete_index <= task_count) {
                        tasks[complete_index - 1].completed = 1;
                        save_tasks(tasks, task_count); // ���浽�ļ�
                        printf("�����ѱ��Ϊ��ɡ�\n");
                    } else {
                        printf("��Ч�ı�š�\n");
                    }
                } else {
                    printf("û������ɱ�ǡ�\n");
                }
                break;

            case 4:
                if (task_count > 0) {
                    printf("������Ҫɾ����������: ");
                    int delete_index;
                    scanf("%d", &delete_index);
                    if (delete_index > 0 && delete_index <= task_count) {
                        for (int i = delete_index - 1; i < task_count - 1; i++) {
                            tasks[i] = tasks[i + 1];
                        }
                        task_count--;
                        save_tasks(tasks, task_count); // ���浽�ļ�
                        printf("������ɾ����\n");
                    } else {
                        printf("��Ч�ı�š�\n");
                    }
                } else {
                    printf("û�������ɾ����\n");
                }
                break;

            case 5:
                return 0;

            default:
                printf("��Ч��ѡ�������ԡ�\n");
        }
    }

    return 0;
}

