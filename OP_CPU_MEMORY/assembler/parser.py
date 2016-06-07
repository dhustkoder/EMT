# Copyright (C) 2016 Rafael Moura


import sys




'''

MOVA

ADDBA
ADDCA
SUBAB
SUBAC
LOAD R, byte
LOADM R, offset
STORE R, offset

'''





def get_immediate(line):

	try:

		hexIdx = line.find("0x");
		
		if hexIdx >= 0:
			x = int(line[hexIdx:], 16);
		else:
	 		x = int(''.join(it for it in line if it.isdigit()));

	except Exception as e:
		sys.stderr.write("Failed to get immediate value from: " + str(line) + "\n");


	else:
		return x;




def RaiseMissingRegId(line):
	raise Exception("Missing Register identifier: " + str(line));




def mova(opcode):

	if opcode.find("B") >= 3:
		return 0xA000;
	if opcode.find("C") >= 3:
		return 0xA001;

	RaiseMissingRegId(opcode);






def adda(opcode):

	if opcode.find("B") >= 0:
		return 0xA002;
	if opcode.find("C") >= 0:
		return 0xA003;

	RaiseMissingRegId(opcode);



def suba(opcode):

	if opcode.find("B") >= 0:
		return 0xA004;
	if opcode.find("C") >= 0:
		return 0xA005;

	RaiseMissingRegId(opcode);




def load(opcode):

	line = str(opcode)[3:];

	if line.find("A,") >= 0:
		return 0xA1 << 8 | get_immediate(line);
	if line.find("B") >= 0:
		return 0xB1 << 8 | get_immediate(line);
	if line.find("C") >= 0:
		return 0xC1 << 8 | get_immediate(line);

	RaiseMissingRegId(opcode);




def loadm(opcode):

	line = str(opcode)[4:];

	if line.find("A") >= 0:
		return 0xA2 << 8 | get_immediate(line);
	if line.find("B") >= 0:
		return 0xB2 << 8 | get_immediate(line);
	if line.find("C") >= 0:
		return 0xC2 << 8 | get_immediate(line);
	if line.find("D") >= 0:
		return 0xD2 << 8 | get_immediate(line);


	RaiseMissingRegId(opcode);



def store(opcode):

	line = str(opcode)[5:];

	if line.find("A") >= 0:
		return 0xA4 << 8 | get_immediate(line);
	if line.find("B") >= 0:
		return 0xB4 << 8 | get_immediate(line);
	if line.find("C") >= 0:
		return 0xC4 << 8 | get_immediate(line);


	RaiseMissingRegId(opcode);


tokens = [("MOVA", mova), ("ADDA", adda), ("SUBA", suba), 
          ("LOAD", load), ("LOADM", loadm), ("STORE", store)];




def decode(tokenSecond, line, ofile):
	binary = tokenSecond(line);
	print(hex(binary));
	ofile.write(bin(binary)[2:]);







def parse(lines):	

	try:
		ofile = open("output.bin", "wb");

		for line in lines:

			if not str(line.strip()): 
				continue;

			if line[0] == "#":
				continue;
		

			for a, b in tokens:
				x = line.find(' ');
				if line[:x] == a:
					decode(b, line, ofile);
					break;
	except Exception as err:
		sys.stderr.write(str(err) + "\n");
	
	finally:
		ofile.close();


	return;








