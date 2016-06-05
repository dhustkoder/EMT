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


void print_bits(const uint8_t);

int main()
{
	std::ifstream rom("ROM", std::ios::binary);

	if(!rom.good())
	{
		puts("failed to open \'ROM\'");
		return EXIT_FAILURE;
	}

	rom.seekg(0, rom.end);
	const size_t rom_size = static_cast<size_t>(rom.tellg());
	rom.seekg(0, rom.beg);

	printf("ROM size: %lu\n", rom_size);
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
	// 88: print results
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

			case 0x82: SF=0; continue; 
			case 0x84: CF=0; continue;


			case 0x90: A=0, B=0, C=0, X=0;

			default: 
				printf("unknown opcode $%X\n", bytes[i]);
				continue;
		}
	}

	puts("\n\tRESULTS:");
	printf("A = %3u | B = %3u | C = %3u | X = %" SCNd16 "\n" , A, B, C, X);

	printf("A = "); print_bits(A);
	printf("\nB = "); print_bits(B); 
	printf("\nC = "); print_bits(C);
	
	// 16 bits X 
	printf("\nX = "); 
	print_bits( (X & 0xff00) >> 8 );
	putchar(' ');
	print_bits(X & 0xff);
	putchar('\n');


	return EXIT_SUCCESS;
}











void print_bits(const uint8_t byte)
{
	size_t j;

	for(j = 8; j > 4; --j)
		printf("%c", ((byte >> (j-1)) & 0x01) ? '1' : '0');
	
	putchar(' ');
		
	for(; j > 0; --j)
		printf("%c", ((byte >> (j-1)) & 0x01) ? '1' : '0');

}
