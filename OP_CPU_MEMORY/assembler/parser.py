# Copyright (C) 2016 Rafael Moura


import sys




'''

MOVBA
MOVCA
ADDBA
ADDCA
SUBAB
SUBAC
LOADA byte
LOADB byte
LOADC byte
LOADMA offset
LOADMB offset
LOADMC offset
LOADMD offset
STOREA offset
STOREB offset
STOREC offset

'''





def get_immediate(line):
	try:
	 	x = int(''.join(ele for ele in line if ele.isdigit()));
	except Exception as e:
		sys.stderr.write("Failed to get immediate value from: " + str(line) + "\n");
		
	else:
		return x;

def loada(line):
	return 0xA1 << 8 | get_immediate(line);
def loadb(line):
	return 0xB1 << 8 | get_immediate(line);
def loadc(line):
	return 0xC1 << 8 | get_immediate(line);
def loadma(line):
	return 0xA2 << 8 | get_immediate(line);
def loadmb(line):
	return 0xB2 << 8 | get_immediate(line);
def loadmc(line):
	return 0xC2 << 8 | get_immediate(line);
def loadmd(line):
	return 0xD2 << 8 | get_immediate(line);
def storea(line):
	return 0xA4 << 8 | get_immediate(line);
def storeb(line):
	return 0xB4 << 8 | get_immediate(line);
def storec(line):
	return 0xC4 << 8 | get_immediate(line);





tokens = [("MOVBA", 0xA000), ("MOVCA", 0xA001),  ("ADDBA", 0xA002), 
          ("ADDCA", 0xA003), ("SUBAB", 0xA004),  ("SUBAC", 0xA005), 
          ("LOADA", loada),  ("LOADB", loadb),   ("LOADC", loadc), 
          ("LOADMA",loadma), ("LOADMB", loadmb), ("LOADMC", loadmc),
          ("LOADMD",loadmd), ("STOREA", storea), ("STOREB",storeb), ("STOREC", storec)];




def decode(tokenSecond, line):
	print(hex(tokenSecond(line)));
	return;







def parse(file):
	try:	
		lines = file.readlines();
		for line in lines:
			if not line.strip(): 
				continue;
			found = 0;
			for a,b in tokens:
				x = line.find(a);
				if x >= 0:
					decode(b, line);
					found = 1;
					break;
					
	except Exception as err:
		sys.stderr.write(str(err) + "\n");

	return;








