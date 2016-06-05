// Copyright (C) 2016 Rafael Moura
// Demonstration of a simple 8 bit opcode interpreter , with memory managment , and math

// done for -std=c++11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <bitset>



static struct CPU
{
	enum { ZF = 0x00, CF = 0x80, SF = 0x40 };
	uint16_t opcode;
	uint16_t X;
	uint8_t A, B, C;
	uint8_t mem[32];
	uint8_t flags;

} cpu;


void execute_opcode();
void print_cpu();

int main()
{
	// flags = CS00 000Z
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



	print_cpu();
	return EXIT_SUCCESS;
}










void execute_opcode()
{
#define OPMSB (cpu.opcode&0xff00)
#define OPLSB (cpu.opcoe&0x00ff)

#define ZF (CPU::ZF)
#define CF (CPU::CF)
#define SF (CPU::SF)
#define SETF(FLAG) cpu.flags |= FLAG
#define UNSETF(FLAG) cpu.flags ^= FLAG

#define A (cpu.A)
#define B (cpu.B)
#define C (cpu.C)
#define X (cpu.X)


	const auto unknown_opcode = []() 
	{
		using namespace std;
		const auto oldf = cout.setf(ios::hex, ios::basefield);
		cout.setf(ios::showbase);
		cout << "UNKNOWN OPCODE: " << cpu.opcode << endl;
		cout.unsetf(ios::showbase);
		cout.setf(oldf);
	}

	switch( OPMSB  )
	{
		case 0xA000:
		{
			switch( OPLSB )
			{
				case 0x00: A = B; break;
				case 0x01: A = C; break;
				
				case 0x02:
				{
					uint16_t res = A + B;
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
					if( A > B )
						SETF(CF)
					else 
					{
						UNSETF(CF);
						SETF(SF);
					}

					A -= B;
					break;
				}


				case 0x05: A -= C; break;

				default: unknown_opcode(); break;

			}
		}

		case 0xA100: break;
		case 0xB100: break;
		case 0xC100: break;  
		case 0xA200: break; 
		case 0xB200: break; 
		case 0xC200: break; 
		case 0xD200: break; 


	}

#undef OPMSB (cpu.opcode&0xff00)
#undef OPLSB (cpu.opcoe&0x00ff)

#undef A (cpu.A)
#undef B (cpu.B)
#undef C (cpu.C)
#undef X (cpu.X)

#undef ZF (CPU::ZF)
#undef CF (CPU::CF)
#undef SF (CPU::SF)
#undef SETF(FLAG) cpu.flags |= FLAG
#undef UNSETF(FLAG) cpu.flags ^= FLAG



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
	
	cout << "CPU REGISTERS:" << endl;
	cout << "A = " << cpu.A << " | B = " << cpu.B << " | C = " << cpu.C << endl;
	cout << "CPU MEMORY:" << endl;

	for(size_t i = 0; i < 32; ++i)
	{
		bits = cpu.mem[i];
		cout << setw(4) << left 
                     << i << ":" 
                     << setw(5) << right
                     << cpu.mem[i]
                     << setw(3) << right
                     << " | " << bits
                     << endl;
	}

	cout.setf(oldf, ios::basefield);
	cout.unsetf(ios::showbase);
}

