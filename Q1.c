#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h>

void PrintQ1(char* buf)
{
write(0,buf,strlen(buf));
}

int main()
{
PrintQ1("$ ./enseash\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash %\n");
return 0;
}



