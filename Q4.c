#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h>

char buffer[256];
size_t nBytes= sizeof(buffer);
ssize_t nBytesRead;
int pID,status;
char signalRetour[64];
char codeRetour[64];

void Print(char* buf)
{
    write(STDOUT_FILENO,buf,strlen(buf));
}

int main()
{
	Print("$ ./enseash\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n");
	while(1)
	{
	Print("enseash % ");
	nBytesRead=read(STDIN_FILENO,buffer,nBytes);
	buffer[nBytesRead-1]=0;
	if(!strcmp(buffer,"exit") || !nBytesRead)
		{
            Print("Bye Bye...\n");
            exit(EXIT_SUCCESS);
        }
	pID=fork();
	if(pID>0)
	{
		wait(&status);
	if(WIFEXITED(status))
		{
			sprintf(codeRetour,"enseash [exit : %d] :: ",WEXITSTATUS(status));
            Print(codeRetour);
        }
    if(WIFSIGNALED(status))
        {
            printf(signalRetour,"enseash [sign : %d] :: ",WTERMSIG(status)); 
            Print(signalRetour);
        }                   
	}
	else
	{
		execlp(buffer,buffer,(char*)NULL);
		exit(-1);
	}
	
	}
	return 0;
}
