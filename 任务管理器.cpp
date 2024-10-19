#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define TITLE_LENGTH 100
#define DESCRIPTION_LENGTH 256

typedef struct {
    char title[TITLE_LENGTH];
    char description[DESCRIPTION_LENGTH];
    int completed; // 0 - 未完成，1 - 已完成
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
    printf("任务列表:\n");
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
        printf("\n任务管理系统\n");
        printf("1. 添加任务\n");
        printf("2. 查看所有任务\n");
        printf("3. 标记任务为完成\n");
        printf("4. 删除任务\n");
        printf("5. 退出\n");
        printf("请输入你的选择: ");
        scanf("%d", &choice);
        getchar(); // 吸收换行符

        switch (choice) {
            case 1:
                if (task_count < MAX_TASKS) {
                    printf("请输入任务标题: ");
                    fgets(tasks[task_count].title, TITLE_LENGTH, stdin);
                    tasks[task_count].title[strcspn(tasks[task_count].title, "\n")] = 0; // 去掉换行符
                    printf("请输入任务描述: ");
                    fgets(tasks[task_count].description, DESCRIPTION_LENGTH, stdin);
                    tasks[task_count].description[strcspn(tasks[task_count].description, "\n")] = 0; // 去掉换行符
                    tasks[task_count].completed = 0;
                    task_count++;
                    save_tasks(tasks, task_count); // 保存到文件
                } else {
                    printf("任务已满，无法添加更多任务。\n");
                }
                break;

            case 2:
                display_tasks(tasks, task_count);
                break;

            case 3:
                if (task_count > 0) {
                    printf("请输入要标记为完成的任务编号: ");
                    int complete_index;
                    scanf("%d", &complete_index);
                    if (complete_index > 0 && complete_index <= task_count) {
                        tasks[complete_index - 1].completed = 1;
                        save_tasks(tasks, task_count); // 保存到文件
                        printf("任务已标记为完成。\n");
                    } else {
                        printf("无效的编号。\n");
                    }
                } else {
                    printf("没有任务可标记。\n");
                }
                break;

            case 4:
                if (task_count > 0) {
                    printf("请输入要删除的任务编号: ");
                    int delete_index;
                    scanf("%d", &delete_index);
                    if (delete_index > 0 && delete_index <= task_count) {
                        for (int i = delete_index - 1; i < task_count - 1; i++) {
                            tasks[i] = tasks[i + 1];
                        }
                        task_count--;
                        save_tasks(tasks, task_count); // 保存到文件
                        printf("任务已删除。\n");
                    } else {
                        printf("无效的编号。\n");
                    }
                } else {
                    printf("没有任务可删除。\n");
                }
                break;

            case 5:
                return 0;

            default:
                printf("无效的选择，请重试。\n");
        }
    }

    return 0;
}

