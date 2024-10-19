#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 100
#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

// 用户结构体
typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User users[MAX_USERS];
int userCount = 0;

// 从文件加载用户数据
void loadUsers(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No user data found. Starting fresh.\n");
        return;
    }

    while (fscanf(file, "%s %s", users[userCount].username, users[userCount].password) != EOF) {
        userCount++;
    }

    fclose(file);
}

// 将用户数据保存到文件
void saveUsers(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for saving users.\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(file);
}

// 添加新用户
void addUser(const char *username, const char *password) {
    // 检查用户名是否已存在
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Error: Username already exists.\n");
            return;
        }
    }

    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;

    printf("User added successfully!\n");
    saveUsers("users.txt");
}

// 验证用户登录
int loginUser(const char *username, const char *password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1;  // 登录成功
        }
    }
    return 0;  // 登录失败
}

int main() {
    int choice;
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    // 加载用户数据
    loadUsers("users.txt");

    while (1) {
        printf("\nUser Management System\n");
        printf("1. Add User\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                addUser(username, password);
                break;
            case 2:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                if (loginUser(username, password)) {
                    printf("Login successful!\n");
                } else {
                    printf("Invalid username or password.\n");
                }
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

