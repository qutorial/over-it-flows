#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    "\tend - leave the program\n"
    "\thelp - shows this help\n");
  } else if (!strcmp(buff, "\x65\x67\x67")) {
	const unsigned char array[61] =
	{
    0x67, 0x6f, 0x6f, 0x67,
    0x6c, 0x65, 0x20, 0x74,
    0x72, 0x61, 0x6e, 0x73,
    0x6c, 0x61, 0x74, 0x65,
    0x3a, 0x20, 0x56, 0x79,
    0x20, 0x73, 0x6d, 0x6f,
    0x74, 0x72, 0x65, 0x6c,
    0x69, 0x20, 0x76, 0x20,
    0x73, 0x61, 0x6d, 0x69,
    0x79, 0x20, 0x6b, 0x6f,
    0x6e, 0x65, 0x74, 0x73,
    0x20, 0x66, 0x61, 0x79,
    0x6c, 0x61, 0x20, 0x72,
    0x65, 0x61, 0x64, 0x6d,
    0x65, 0x3f, 0x0d, 0x0a, 0x00
	};

	printf(array);
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
  sleep(1);
 }

 return 0;
}
