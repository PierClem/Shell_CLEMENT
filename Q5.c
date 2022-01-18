#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h>

char buffer[128]; //Déclaration d'un tableau servant à stocker une chaîne de caractère 
size_t nBytes= sizeof(buffer); //taille du tableau
ssize_t nBytesRead; //Valeur de retour du tableau
int pID,status; //pID est l'identifiant du processus tandis que status donne l'état du traitement du processus 
char signalRetour[64]; //Variable contenant le prompt de retour du signal
char codeRetour[64]; //Variable contenant le prompt de retour du signal
struct timespec Start, End;//Variables permettant de définir le début et la fin du comptage  
long elapsed; //Variable permettant d'obtenir le temps déroulé  
void Print(char* buf)
{
    write(STDOUT_FILENO,buf,strlen(buf)); //On créé une fonction Print pour remplacer les write qui contient les arguments du tableau
}

int main()
{
	Print("$ ./enseash\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n");
	while(1)
	{
	Print("enseash % ");
	nBytesRead=read(STDIN_FILENO,buffer,nBytes); //On stocke la valeur de retour du buffer dans nBytesRead 
	buffer[nBytesRead-1]=0; //Ajout d'un caractère de fin de chaîne
	clock_gettime(CLOCK_REALTIME,&Start); //On lance le comptage du temps 
	if(!strcmp(buffer,"exit") || !nBytesRead) //On compare simplement des chaînes de caractères grâce à strcmp
		{
            Print("Bye Bye...\n"); 
            exit(EXIT_SUCCESS);
        }
	pID=fork(); //Identification d'un processus grâce a la fork 
	if(pID>0) 
	{
		wait(&status);
	if(WIFEXITED(status))
		{
		clock_gettime(CLOCK_REALTIME,&End); //Recuperation du temps passé grâce a clock_gettime
                elapsed = (End.tv_nsec - Start.tv_nsec)/1000000; //division par 10000000 pour avoir ce temps en ns
			sprintf(codeRetour,"enseash [exit : %d | %ld ms] :: ",WEXITSTATUS(status),elapsed); //Permet de donner la valeur du fils ainsi que le temps passé en ns
            Print(codeRetour);
        }
    if(WIFSIGNALED(status))
        {
	    clock_gettime(CLOCK_REALTIME,&End);
            elapsed = (End.tv_nsec - Start.tv_nsec)/1000000; //division par 10000000 pour avoir ce temps en ns
            printf(signalRetour,"enseash [sign : %d | %ld ns] :: ",WTERMSIG(status),elapsed); //Permet de renvoyer le signal qui a kill le fils ainsi que le temps passé en ns
            Print(signalRetour);
        }                   
	}
	else
	{
		execlp(buffer,buffer,(char*)NULL); //execlp permet comme précisé dans le cours d'exécuter une commande 
		exit(-1);
	}
	clock_gettime(CLOCK_REALTIME,&End);
        elapsed = (End.tv_nsec - Start.tv_nsec)/1000000;
	}
	return 0;
}
