#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include "grades.h"

// returns 1 if success; else - returns 0
int add_grade(char *username, char* course_name, double grade){
    FILE *filePointer;
    char path[200];
    strcpy(path, GRADES_PATH);
    strcat(path, username);
    strcat(path, "_grades.txt");

    filePointer = fopen(path, "a");
    if ( filePointer == NULL )
    {
        return 0;
    }
    char grade_str[30];
    snprintf(grade_str, 50, "%f", grade);
    char grade_record[50] = "";
    strcat(grade_record, course_name);
    strcat(grade_record, "\t");
    strcat(grade_record, grade_str);

    fprintf(filePointer, "%s\n", grade_record);
    fclose(filePointer);
    return 1;
}

// returns 1 if successfull; else returns 0
int delete_grades_data(char *username){
    FILE *filePointer;
    char path[200];
    strcpy(path, GRADES_PATH);
    strcat(path, username);
    strcat(path, "_grades.txt");

    filePointer = fopen(path, "w");
    if ( filePointer == NULL )
    {
        return 0;
    }
    fclose(filePointer);
    return 1;
}

struct grades* get_all_grades(char *username){
    struct grades* student_grades = (struct grades*)malloc(sizeof(struct grades));
    (*student_grades).len = 0;
    FILE *filePointer;
    char path[200];
    strcpy(path, GRADES_PATH);
    strcat(path, username);
    strcat(path, "_grades.txt");
    filePointer = fopen(path, "r");
    if ( filePointer == NULL )
    {
        return NULL;
    }
    char course_name[20];
    double grade;
    int count = 0;
    while(fscanf(filePointer, "%s\t%lf", course_name, &grade) != EOF){
        strcpy((*student_grades).grades[count].course_name, course_name);
        (*student_grades).grades[count].grade = grade;
        count += 1;
        (*student_grades).len += 1;
    }

    fclose(filePointer);
    return student_grades;
}