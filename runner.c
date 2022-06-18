#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "grades.h"


void login_menu();
void register_menu();
void logged_in_menu(char *username);
int comp (const void * elem1, const void * elem2);


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
        printf("3. Calc GPA\n");
        printf("4. Delete grades data\n");
        printf("5. Get top 3 courses with highest grade\n");
        printf("6. Log out\n");
        scanf("%d", &choice);
        struct grades* student_grades = NULL;
        struct gradeInCourse *gradeInCourse;
        int len=0;
        int res=0;
        switch (choice) {
            case 1:
                fflush(stdin);
                printf("Enter course name: ");
                scanf("%[^\n]%*c", course_name);
                double grade;
                printf("grade: ");
                scanf("%lf", &grade);
                res = add_grade(username, course_name, grade);
                if (res == 1){
                    printf("Added successfully.\n\n");
                } else {
                    printf("Error occured.\n\n");
                }
                break;
            case 2:
                printf("Student grades:\n");
                student_grades = get_all_grades(username);
                if (student_grades == NULL){
                    printf("No data available.\n\n");
                    break;
                }
                len = student_grades->len;
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
                student_grades = get_all_grades(username);
                if (student_grades == NULL){
                    printf("No data available.\n\n");
                    break;
                }
                len = student_grades->len;
                int sum_grades = 0;
                for(int i=0; i<len; i++){
                    gradeInCourse = &(student_grades->grades[i]);
                    char course[20];
                    strcpy(course, gradeInCourse->course_name);
                    double grade = gradeInCourse->grade;
                    sum_grades += grade;
                }
                printf("\n**********\nGPA: %f\n**********\n\n", (double) sum_grades/len);
                break;
            case 4:
                res = delete_grades_data(username);
                if (res == 1){
                    printf("Data deleted successfully.\n\n");
                } else {
                    printf("Error while deleting data.\n\n");
                }
                break;
            case 5:
                student_grades = get_all_grades(username);
                if (student_grades == NULL){
                    printf("No data available.\n\n");
                    break;
                }
                len = student_grades->len;
                struct gradeInCourse grades_tmp[100];
                memcpy(&grades_tmp, &(student_grades->grades), sizeof(struct gradeInCourse) * len);
                qsort (grades_tmp, sizeof(grades_tmp)/sizeof(*grades_tmp), sizeof(*grades_tmp), comp);
                printf("\n**********\nTOP 3 courses with highest grade:\n");
                for(int i=0; i<3; i++){
                    printf("course: %s, grade: %f\n", grades_tmp[i].course_name, grades_tmp[i].grade);
                }
                printf("**********\n\n");
                break;
            case 6:
                printf("Logged out.\n\n");
                return;
            default:
                printf("Please enter a choice in the range 1-6.\n\n");
        }
    }
}

// comparing 2 grades
int comp (const void * elem1, const void * elem2) 
{
    double grade_f = ((struct gradeInCourse*)elem1)->grade;
    double grade_s = ((struct gradeInCourse*)elem2)->grade;
    if (grade_f < grade_s) return  1;
    if (grade_f > grade_s) return -1;
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
