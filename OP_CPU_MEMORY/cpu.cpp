// Copyright (C) 2016 Rafael Moura
// Demonstration of a simple 8 bit opcode interpreter , with memory managment , and math

// done for -std=c++11

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <bitset>



static struct CPU
{
	// FLAGS
	enum { ZF = 0x00, CF = 0x80, SF = 0x40 }; 
	uint16_t opcode;
	uint16_t X; // 16 bits register
	uint8_t A, B, C; // 8 bits registers
	uint8_t F; // flags
	uint8_t mem[32];

} cpu;


void execute_opcode();
void print_cpu();

int main(int argc, char** argv)
{
	// F = CS00 000Z
	// Registers: A B C X
	// 0xA000: move B to A
	// 0xA001: move C to A
	// 0xA002: add B to A, with carry
	// 0xA003: add C to A
	// 0xA004: sub B from A, with borrow
	// 0xA005: sub C from A
	// 0xA1NN: load NN in A
	// 0xB1NN: load NN in B
	// 0xC1NN: load NN in C
	// 0xA2NN: load mem at NN into A
	// 0xB2NN: load mem at NN into B
	// 0xC2NN: load mem at NN into C
	// 0xD2NN: load mem at NN into X msb, and NN+1 in lsb
	// 0xA4NN: store A into mem at NN
	// 0xB4NN: store B into mem at NN
	// 0xC4NN: store C into mem at NN


	if( argc < 2 )
	{
		std::cerr << "USAGE: " << argv[0] << " <filename> \n";
		return EXIT_FAILURE;
	}

	errno = 0;
	std::ifstream rom(argv[1], std::ios::binary);


	if( !rom.good() )
	{
		std::cerr << "FAILED TO OPEN FILE \'" << argv[1] << '\'';

		if(errno)
			std::perror(":");

		std::cerr << std::endl;

		return EXIT_FAILURE;
	}
	
	rom.seekg(0, rom.end);
	const auto rom_size = rom.tellg();
	rom.seekg(0, rom.beg);

	if( rom_size <= 0 )
	{
		std::cerr << "FILE \'" << argv[1] << "\' IS EMPTY!\n";
		return EXIT_FAILURE;
	}


	std::cout << "ROM SIZE: " << rom_size << '\n';
	std::cout << "READING ROM NOW!\n";

	while(rom.good())
	{
		const auto msb = rom.get();
		const auto lsb = rom.get();
		cpu.opcode = msb << 8 | lsb;
		execute_opcode();
	}

	print_cpu();

	return EXIT_SUCCESS;
}










void execute_opcode()
{

#define OPMSB (cpu.opcode&0xff00)
#define OPLSB (cpu.opcode&0x00ff)

#define ZF (CPU::ZF)
#define CF (CPU::CF)
#define SF (CPU::SF)
#define SETF(FLAG) cpu.F |= FLAG
#define UNSETF(FLAG) cpu.F ^= FLAG
#define GETF(FLAG) (cpu.F & FLAG)
#define A (cpu.A)
#define B (cpu.B)
#define C (cpu.C)
#define X (cpu.X)


	const auto unknown_opcode = []() 
	{
		using namespace std;
		const auto oldf = cout.setf(ios::hex, ios::basefield);
		cout.setf(ios::showbase);
		cout << "UNKNOWN OPCODE: " << cpu.opcode << '\n';
		cout.unsetf(ios::showbase);
		cout.setf(oldf);
	};

	switch( OPMSB  )
	{
		case 0x0000: break;
		case 0xA000:
		{
			switch( OPLSB )
			{
				case 0x00: A = B; break;
				case 0x01: A = C; break;
				
				case 0x02:
				{
					uint16_t res = A + B;
					if(GETF(CF)) ++res;

					if(res > 0xff)
						SETF(CF);
					else
						UNSETF(CF);
					
					A = static_cast<uint8_t>(res);
					break;
				}

				case 0x03: A += C; break;


				case 0x04:
				{
					if( GETF(CF) ) --B;

					if( A > B )
						UNSETF(CF);
					else 
						SETF(CF | SF);

					A -= B;
					break;
				}


				case 0x05: A -= C; break;

				default: unknown_opcode(); break;

			}

			break;
		}

		case 0xA100: A = OPLSB; break;
		case 0xB100: B = OPLSB; break;
		case 0xC100: C = OPLSB; break;  
		case 0xA200: A = cpu.mem[OPLSB]; break; 
		case 0xB200: B = cpu.mem[OPLSB]; break; 
		case 0xC200: C = cpu.mem[OPLSB]; break; 
		case 0xD200: X = cpu.mem[OPLSB] << 8 | cpu.mem[OPLSB+1]; break;
		case 0xA400: cpu.mem[OPLSB] = A; break;
		case 0xB400: cpu.mem[OPLSB] = B; break;
		case 0xC400: cpu.mem[OPLSB] = C; break;
		default: unknown_opcode(); break;
	}

#undef OPMSB 
#undef OPLSB 
#undef A 
#undef B
#undef C
#undef X

#undef ZF
#undef CF
#undef SF
#undef SETF
#undef UNSETF
#undef GETF


}


















std::ostream& operator<<(std::ostream& os, uint8_t val)
{
	os << (unsigned) val;
	return os;
}


void print_cpu()
{
	using namespace std;

	bitset<8> bits;

	const auto oldf = cout.setf(ios::hex, ios::basefield);
	cout.setf(ios::showbase);
	
	cout << "CPU REGISTERS:" << endl
	     << "A = " << cpu.A 
             << " | B = " << cpu.B 
             << " | C = " << cpu.C 
             << " | X = " << cpu.X << '\n';


	cout << "CPU MEMORY:\n";
	
	for(size_t i = 0; i < 32; ++i)
	{
		bits = cpu.mem[i];
		cout << setw(4) << left 
                     << i << ':' 
                     << setw(5) << right
                     << cpu.mem[i]
                     << setw(3) << right
                     << " | " << bits
                     << '\n';
	}

	cout.setf(oldf, ios::basefield);
	cout.unsetf(ios::showbase);
}

