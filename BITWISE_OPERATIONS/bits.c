/* Copyright (C) 2016 Rafael Moura (Dhust)
 *
 * Demonstration of how to play with bits 
 * with AND, OR, XOR
 * done for -std=c89 
 */


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>



/* reads a binary file named ROM, and shows its 
 * sequencial bytes OR XOR AND results
 */



void print_bytes(const uint8_t* bytes, const size_t size);
void print_bits(uint8_t byte);


int main()
{
	FILE* rom;
	uint8_t* bytes;
	size_t rom_size;
	size_t i;

	uint8_t result[3] = { 0, 0, 0};


	rom = fopen("ROM", "rb");
	if(!rom)
	{
		perror("Could not open \'ROM\'");
		return EXIT_FAILURE;
	}
	
	fseek(rom, 0, SEEK_END);
	rom_size = (size_t) ftell(rom);
	fseek(rom, 0, SEEK_SET);

	printf("ROM size: %lu\n", rom_size);

	bytes = malloc(sizeof(uint8_t) * rom_size);
	
	if(!bytes)
	{
		perror("Failed to allocate memory");
		goto exit_failure;
	}

	if( fread(bytes, rom_size, sizeof(uint8_t), rom) < rom_size )
	{
		if(ferror(rom)) 
		{
			perror("error while reading ROM");	
			goto exit_failure;
		}
	}
		

	print_bytes(bytes, rom_size);

	for(i=0; i < rom_size-1; ++i)
	{
		result[0] = bytes[i] | bytes[i+1];
		result[1] = bytes[i] ^ bytes[i+1];
		result[2] = bytes[i] & bytes[i+1];
		printf("BYTES %lu and %lu\n", i, i+1);
		printf("ORed:  ");  print_bits(result[0]);
		printf("\nXORed: "); print_bits(result[1]);
		printf("\nANDed: "); print_bits(result[2]);
		putchar('\n');
	}


	fclose(rom);
	free(bytes);
	return EXIT_SUCCESS;

exit_failure:
	fclose(rom);
	free(bytes);
	return EXIT_FAILURE;
}






void print_bytes(const uint8_t* bytes, const size_t size)
{
	size_t i;

	printf("showing bytes read:\nHEX    DEC    BIN");
	for(i = 0; i < size; ++i)
	{
		printf("\n$%02X    %3d    ", bytes[i], bytes[i]);
		print_bits(bytes[i]);
		
	}
	puts("\n--------------------------");
}






void print_bits(uint8_t byte)
{
	size_t j;

	for(j = 8; j > 4; --j)
		printf("%c", ((byte >> (j-1)) & 0x01) ? '1' : '0');
	
	putchar(' ');
		
	for(; j > 0; --j)
		printf("%c", ((byte >> (j-1)) & 0x01) ? '1' : '0');


}
