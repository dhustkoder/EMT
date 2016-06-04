#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>




int main(int argc, const char** argv)
{
	char name[64];
	char* buff;
	ssize_t readsize;
	int fd, i;


	if (argc < 2) 
	{
	    fprintf(stderr, "usage: %s pid address value\n", argv[0]);
	    exit(1); 
	}

	sprintf(name, "/proc/%.10s/mem", argv[1]);

	if ((fd = open(name, O_WRONLY)) < 0) 
	{
	    perror("Can't access pid");
	    return EXIT_FAILURE; 
	}

	buff = malloc(sizeof(char) * 501);

	if(!buff)
	{
		perror("malloc");
		return EXIT_FAILURE;
	}


	readsize = read(fd, buff, 501);

	buff[500] = '\0';

	for(i = 0; i < readsize; ++i)
		printf("%X\n", buff[i]);


	free(buff);
    return 0;
}




