#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "grades.h"


void login_menu();
void register_menu();
void logged_in_menu(char *username);


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

void logged_in_menu(char *username){
    int choice = -1;
    char course_name[20];
    while(1){
        printf("Please choose an option:\n");
        printf("1. Add grade\n");
        printf("2. Show all grades\n");
        printf("3. Calc GPA.\n");
        printf("4. Delete grades data.\n");
        printf("5. Get top 3 courses with highest grade.\n");
        printf("6. Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                fflush(stdin);
                printf("Enter course name: ");
                scanf("%[^\n]%*c", course_name);
                double grade;
                printf("grade: ");
                scanf("%lf", &grade);
                int res = add_grade(username, course_name, grade);
                if (res == 1){
                    printf("Added successfully.\n\n");
                } else {
                    printf("Error occured.\n\n");
                }
                break;
            case 2:
                printf("Student grades:\n");
                struct grades* student_grades = NULL;
                student_grades = get_all_grades(username);
                if (student_grades == NULL){
                    printf("No data available.\n\n");
                    break;
                }
                struct gradeInCourse *gradeInCourse;
                int len = student_grades->len;
                printf("**********\n");
                for(int i=0; i<len; i++){
                    gradeInCourse = &(student_grades->grades[i]);
                    char course[20];
                    strcpy(course, gradeInCourse->course_name);
                    double grade = gradeInCourse->grade;
                    printf("course: %s, grade: %f\n", course, grade);
                }
                printf("**********\n\n");
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                printf("Exiting.\n");
                exit(0);
                break;
            default:
                printf("Please enter a choice in the range 1-6.\n\n");
        }
    }
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
        logged_in_menu(username);
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
