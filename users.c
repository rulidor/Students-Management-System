#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "users.h"


// returns: 1 if ok; 0 if bad username or pass; 2 if error opening users.txt file
int check_credentials(char *username, char *pass){
    FILE *filePointer;
    char curr_username[20];
    char curr_pass[20];
    filePointer = fopen(USERS_PATH, "r");
    if ( filePointer == NULL )
    {
        return 2;
    }
    while(fscanf(filePointer, "%s\t%s", curr_username, curr_pass) != EOF){
        if (strcmp(username, curr_username) == 0 && strcmp(pass, curr_pass) == 0){
            return 1;
        }
    }
    fclose(filePointer);
    return 0;
}

// returns: 1 if ok; 0 username already exists; 2 if error opening users.txt file
int register_user(char *username, char *pass){
    FILE *filePointer;
    char curr_username[20];
    char curr_pass[20];
    filePointer = fopen(USERS_PATH, "r+");
    if ( filePointer == NULL )
    {
        return 2;
    }
    while(fscanf(filePointer, "%s\t%s", curr_username, curr_pass) != EOF){
        if (strcmp(username, curr_username) == 0){
            return 0;
        }
    }
    fseek(filePointer, 0, SEEK_END);
    fprintf(filePointer, "\n%s\t%s", username, pass);
    fclose(filePointer);
    return 1;
}