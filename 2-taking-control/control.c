#include <stdio.h>
#include <string.h>

void overflow(void){
  char buff[80];
  printf("Command: ");
  gets(buff);

  if( !strcmp(buff, "dir") || !strcmp(buff, "ls") ) {
    system("ls -al");
  } else if(!strncmp(buff, "cd ", 3)) {
    chdir(buff + 3);
    printf("Directory changed to %s\n", getcwd(buff));
  } else if(!strcmp(buff, "help")) {
    printf("\tdir - lists the current directory\n"
    "\tcd [folder] - switches the current directory\n"
    "\thelp - shows this help\n");
  } else if (!strcmp(buff, "end")) {
    printf("Good bye!\n");
    exit(0);
  } else {
    printf("Unknown command\n");
  }
}

int main(void) {

 printf("Press Ctrl+C or type end to quit\n");

 for(;;) {
  overflow();
 }

 return 0;
}
