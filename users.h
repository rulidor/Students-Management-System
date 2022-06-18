#ifndef USERS_HEADER_FILE
#define USERS_HEADER_FILE

#define USERS_PATH "./data/users.txt"

int check_credentials(char *username, char *pass);
int register_user(char *username, char *pass);

struct user {
  char username[20];
  char pass[20];

};

#endif