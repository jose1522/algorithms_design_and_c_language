#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char username[20];
    char password[20];
} User;

User* users = NULL;
int registeredUsers = 0;

int registerUser() {
    char username[20], password[20];
    printf("Enter username: ");
    scanf("%s", username);

    // Check if the username has already been registered
    for (int i = 0; i < registeredUsers; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("This username is already registered! Please choose a different username.\n");
            return 0; // Return early if the username is already registered
        }
    }

    users = (User*) realloc(users, (registeredUsers + 1) * sizeof(User));
    if (users == NULL) {
        printf("Memory allocation failed!\n");
        return 0;
    }

    // If the username is unique, store it along with the password
    strcpy(users[registeredUsers].username, username);
    printf("Enter password: ");
    scanf("%s", users[registeredUsers].password);

    registeredUsers++;

    printf("User registered successfully!\n");
    return 1;
}

int authenticateUser() {
    char username[20], password[20];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < registeredUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Authentication successful!\n");
            printf("Username: %s\n", users[i].username);
            printf("Password: %s\n", users[i].password);
            return 1;
        }
    }
    printf("Authentication failed!\n");
    return 0;
}

int main() {
    int choice;
    do {
        printf("1. Register\n");
        if (registeredUsers > 0) { // Only show the authenticate option if there are registered users
            printf("2. Authenticate\n");
        }
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (registeredUsers > 0) { // Only allow the authenticate option if there are registered users
                    authenticateUser();
                } else {
                    printf("No users registered. Cannot authenticate.\n");
                }
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 3);
    free(users); // Free allocated memory when done
    return 0;
}
