#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char** argv)
{
	uint8_t* memory;
	int i;
	memory = malloc(sizeof(uint8_t) * argc);
	if(!memory)
	{
		perror("malloc");
		return EXIT_FAILURE;
	}
	
	printf("I'm a proc\n");
	for(i = 0; i < argc; ++i) {
		memory[i] = i + 1;
		printf("%X\n",memory[i]);
 	}
	while( 1 ) {}

	free(memory);
	return EXIT_SUCCESS;
}
