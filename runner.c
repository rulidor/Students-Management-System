#include <stdio.h>
#include <stdlib.h>
#include "users.h"


void login_menu();
void register_menu();


int main(){
    while(1){
        int choice = -1;
        printf("Welcome to Students Management System!\n\n");
        while(1){
            printf("Please choose an option:\n");
            printf("1. Login\n");
            printf("2. Register\n");
            printf("3. Exit\n");
            scanf("%d", &choice);
            if (choice == 1){
                login_menu();
            } else if (choice == 2){
                register_menu();
            } else if (choice == 3){
                printf("Exiting\n");
                exit(0);
            } else { 
                printf("Wrong input.\n\n");
                break;
            }
        }
    }

    return 0;
}

void login_menu(){
    char username[20];
    char pass[20];
    printf("username: ");
    scanf("%s", username);
    printf("password: ");
    scanf("%s", pass);
    printf("Chekcing credentials...\n");
    int res = check_credentials(username, pass);
    if (res == 1){
        printf("Logged in successfully.\n\n");
    } else if (res == 0){
        printf("Bad username or password.\n\n");
    } else {
        printf("Error while authenticating user.\nExiting.\n");
        exit(1);
    }
}

void register_menu(){
    char username[20];
    char pass[20];
    printf("choose username: ");
    scanf("%s", username);
    printf("choose password: ");
    scanf("%s", pass);
    int res = register_user(username, pass);
    if (res == 1){
        printf("Registered successfully.\n\n");
    } else if (res == 0){
        printf("Username already exists.\n\n");
    } else {
        printf("Error while registering user.\nExiting.\n");
        exit(1);
    }
}
