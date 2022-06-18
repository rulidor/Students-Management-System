#ifndef HEADER_FILE
#define HEADER_FILE

#define USERS_PATH "./data/users.txt"

int check_credentials(char username[20], char pass[20]);
int register_user(char username[20], char pass[20]);

struct user {
  char username[20];
  char pass[20];

};

#endif