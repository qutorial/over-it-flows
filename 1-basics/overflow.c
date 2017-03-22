#include <stdio.h>
#include <string.h>

int main(void) {

 char buff[80];
 int pass=0;

 printf("Password please: ");
 gets(buff);
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
