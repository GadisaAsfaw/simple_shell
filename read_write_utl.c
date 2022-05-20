#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "shell.h"

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
