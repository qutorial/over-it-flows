#include <stdio.h>
#include <string.h>

int main(void) {

 char buff[8];
 buff[7] = 0;
 int pass=0;

 printf("Password please: ");

 fgets(buff, sizeof(buff) - 1, stdin);

 if(strcmp(buff, "root")){
  printf("Wrong password\n");
 }

 else {
  printf("Right password\n");
  pass = 1;
 }

 if(pass) {
  printf("Access granted\n");
 }

 return 0;
}
