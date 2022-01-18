#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h>

char buffer[512];
size_t nBytes;
ssize_t nBytesRead;
int pID,status;

void Print(char* buf)
{
    write(STDOUT_FILENO,buf,strlen(buf));
}

int main()
{
	nBytes = sizeof(buffer);
	Print("$ ./enseash\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n");
	while(1)
	{
	Print("enseash % ");
	nBytesRead=read(STDIN_FILENO,buffer,nBytes);
	buffer[nBytesRead-1]=0;
	pID=fork();
	
	if(pID)
	{
	if(!strcmp(buffer,"exit") || !nBytesRead)
        {
            Print("Bye Bye...\n");
            exit(EXIT_SUCCESS);

        }
		wait(&status);
	}
	else
	{
		execlp(buffer,buffer,(char*)NULL);
		exit(EXIT_FAILURE);
	}
	}
	return 0;
}

