#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "shell.h"

/**
 * main - Entery poin
 *
 * Return: Always 0.
 */
int main(void)
{
	char usrIn[1024];
	char *params[20];
	char *en[] = {NULL};
	/*char *ar[] ={"ls",NULL};*/
	while (1)
	{
		printf("# ");
		read_command(usrIn);
		parseInput(usrIn, params);
		if (fork() == 0)
		{
			if (execve(params[0], params, en) == -1)
			{
				perror(params[0]);
			}
		}
		else
		{
			wait(NULL);
		}
		if (strcmp(params[0], "exit\0") == 0)
			exit(1);

	}

	return (0);
}
/**
 *read_command - reads input line from stdin
 *@uin: array of chars from user input
 */
void read_command(char *uin)
{
	char *buff;
	size_t bufsize = 1024;
	int count = 0;

	buff = malloc(bufsize * sizeof(char));
	if (buff == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}
	count = getline(&buff, &bufsize, stdin);
	if (count == 1)
		return;
	strcpy(uin, buff);
	free(buff);
}
/**
 *parseInput - parses user input into array of words
 *@inpt: single line char array from user input
 *@params: array of words
 */
void parseInput(char *inpt, char *params[])
{
	char *wrd;
	char *inpt2;
	int j = 0;

	inpt2 = strdup(inpt);
	wrd = strtok(inpt2, " \n");
	while (wrd != NULL)
	{
		params[j++] = strdup(wrd);
		wrd = strtok(NULL, " \n");
	}
	params[j] = NULL;
}
