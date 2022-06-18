#ifndef GRADES_HEADER_FILE
#define GRADES_HEADER_FILE

#define GRADES_PATH "./data/grades/"

int add_grade(char *username, char* course_name, double grade);
struct grades* get_all_grades(char *username);

struct gradeInCourse {
  char course_name[20];
  double grade;

};

struct grades {
  struct gradeInCourse grades[100];
  int len; //count of grades
};





#endif