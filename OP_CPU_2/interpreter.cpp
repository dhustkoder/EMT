// Copyright (C) 2016 Rafael Moura
// Demonstration of an 8 bit opcode interpreter and carry, borrow, sign flag
// for 16 bit math

// done for -std=c++98

#include <stdio.h>  // puts printf
#include <stdlib.h> // EXIT_... macros
#include <stddef.h> // size_t
#include <stdint.h> // _t types
#include <inttypes.h> // SCNd16
#include <fstream>
#include <vector>




template<class T>
void print_bits(const T);


int main(int argc, char** argv)
{

	if(argc < 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return EXIT_SUCCESS;
	}

	std::ifstream rom(argv[1], std::ios::binary);

	if(!rom.good())
	{
		perror("failed to open \'ROM\'");
		return EXIT_FAILURE;
	}

	rom.seekg(0, rom.end);
	const size_t rom_size = static_cast<size_t>(rom.tellg());
	rom.seekg(0, rom.beg);

	printf("%s size: %lu\n", argv[1], rom_size);
	puts("start reading bytes");

	std::vector<uint8_t> bytes;
	bytes.reserve(rom_size);
	
	for(size_t i = 0; i < rom_size; ++i)
		bytes.push_back(rom.get());


	puts("showing bytes read:");
	puts("HEX    |    DEC");
	for(size_t i = 0; i < bytes.size(); ++i)
		printf("$%02X         %3d\n", bytes[i], bytes[i]);



	// FLAGS: CF ( CARRY FLAG and borrow )  SF ( SIGN FLAG )
	// Registers: A B C X
	// 01: store next byte in A
	// 02: store next byte in B
	// 04: store next byte in C
	// 08: add B to A
	// 10: add C to A
	// 20: sub B from A
	// 40: sub C from A
	// 80: store A to X
	// 82: clear SF
	// 84: clear CF
	// 90: zero registers



	uint8_t CF = 0, SF = 0;
	uint8_t A=0, B=0, C=0; // <= 255
	uint16_t X=0; // > 255
	
	bytes.push_back(0x00); // push back a null op for offset secutiry;
	for(size_t i = 0; i < bytes.size(); ++i)
	{
		switch(bytes[i])
		{
			case 0x00: continue;
			case 0x01: A = bytes[++i]; continue;
			case 0x02: B = bytes[++i]; continue;
			case 0x04: C = bytes[++i]; continue;


			case 0x08: // add B to A with carry
			{
				uint16_t res = A + B;
				CF = ( 0xff00 & res ) ? 0x80 : 0;
				A = res & 0xff;
				continue;
			}

			case 0x10: 
				A += C; 
				continue;

			case 0x20: // sub B from A with carry
				SF = ( A < B ) ? 1 : 0;
				CF = ( A < B ) ? 0x0 : 0x80;
				A -= B;
				continue;

			case 0x40: 
				A -= C;
				continue;

			case 0x80:
				if(SF) X = 0xff00  | A ;
				else X = (CF << 1) | A;
				continue;

			case 0x82: 
				SF=0; 
				continue; 

			case 0x84: 
				CF=0; 
				continue;

			case 0x90: 
				A=0, B=0, C=0, X=0, SF=0, CF=0;
				continue;

			default: 
				printf("unknown opcode $%X\n", bytes[i]);
				continue;
		}
	}

	puts("\n\tRESULTS:");
	printf("A = %3u | B = %3u | C = %3u | X = %" SCNd16 "", A, B, C, X);

	printf("\nA = "); print_bits(A);
	printf("\nB = "); print_bits(B); 
	printf("\nC = "); print_bits(C);
	printf("\nX = "); print_bits(X);
	putchar('\n');
	
	return EXIT_SUCCESS;
}






template<class T>
void print_bits(const T val)
{

	static const size_t t_lengh = sizeof(T) * 8;
	// bits lengh of T. if T==uint8_t , t_leng = 8
	// if T==uint16_t , t_leng = 16 ...

	static const T mask =  0x01 << (t_lengh - 1);
	// create a mask with the T's MSB set. if T == uint8_t, mask = 0x80, 
	// else if T == uint16_t, mask = 0x8000 ...

	// prints 4 bits and a space
	size_t j = 0;
	do 
	{
		for(int bit = 0; bit < 4; ++j, ++bit)
			printf("%c", (val << j)&mask ? '1' : '0');
	
		putchar(' ');
	} while( j < t_lengh );

}
