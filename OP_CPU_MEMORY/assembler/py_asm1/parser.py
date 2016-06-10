# Copyright (C) 2016 Rafael Moura


import sys


'''
MOV R, R
ADD R, R
SUB R, R
LOAD R, #byte/$offset
STORE R, #byte/$offset

'''

binary = [0x00, 0x00]



def GetValue(operands):

	try:
		hexTag1 = operands.find("0x")
		hexTag2 = operands.find("$")

		if hexTag1 >= 0:
			x = int(operands[hexTag1:], 16)
		elif hexTag2 >= 0:
			x = int(operands[hexTag2+1:], 16)

		else:
				x = int(''.join(it for it in operands if it.isdigit()));

	except Exception as e:
		sys.stderr.write("Failed to get immediate value from: " + str(line) + "\n");


	if x > 0xff:
		raise Exception("VALUE GREATER THAN 0xFF")

	return x








def mov(operands):
	if len(str(operands)) < 3:
		raise Exception("Missing destination and source registers")

	dest = operands[0]
	src = operands[2]

	if dest != 'A':
		raise Exception("Only Register A can be destination in MOV")

	binary.append(0xA0)

	if src == 'B':
		binary.append(0x00)
	elif src == 'C':
		binary.apend(0x01)











def load(operands):
	if len(str(operands)) < 3:
		raise Exception("Missing Operands")

	dest = operands[0]
	token = operands[2]

	if token == '#':
		if dest == 'A': opmsb = 0xA1
		elif dest == 'B': opmsb = 0xB1
		elif dest == 'C': opmsb = 0xC1
		binary.append(opmsb)
	else:
		if dest == 'A': opmsb = 0xA2
		elif dest == 'B': opmsb = 0xB2
		elif dest == 'C': opmsb = 0xC2
		elif dest == 'X': opmsb = 0xD2
		binary.append(opmsb)

	nnVal = GetValue(operands)
	binary.append(nnVal)









def add(operands):
	if len(str(operands)) < 3:
		raise Exception("Missing destination and source registers")

	dest = operands[0]
	src = operands[2]

	if dest != 'A':
		raise Exception("Only Register A can be destination in ADD")

	binary.append(0xA0)

	if src == 'B':
		binary.append(0x02)
	elif src == 'C':
		binary.apend(0x03)









def sub(line):
	if len(str(operands)) < 3:
		raise Exception("Missing destination and source registers")

	dest = operands[0]
	src = operands[2]

	if dest != 'A':
		raise Exception("Only Register A can be destination in SUB")

	binary.append(0xA0)

	if src == 'B':
		binary.append(0x04)
	elif src == 'C':
		binary.apend(0x05)








def store(operands):
	if len(str(operands)) < 3:
		raise Exception("Missing Operands")

	src = operands[0]
	
	if src == 'A': opmsb = 0xA4
	elif src == 'B': opmsb = 0xB4
	elif src == 'C': opmsb = 0xC4

	binary.append(opmsb)
	

	nnVal = GetValue(operands)
	binary.append(nnVal)









tokens = ['A', 'B', 'C', 'X', '#', '$', ',', ';'];
mnemonics = [("MOV", mov), ("LOAD", load), ("ADD", add), ("SUB", sub), ("STORE",store)];








def CheckOperands(operands):
	for tok in operands:
		if tok not in tokens:
			if tok.isdigit():
				continue
			elif int(tok, 16):
				continue
			else: 
				raise Exception("Invalid Operand: " + str(tok))



def Decode(fmtline):
	for mnem, fun in mnemonics:
		if mnem == fmtline[:len(mnem)]:
			operands = fmtline[len(mnem):]
			CheckOperands(operands)
			fun(operands)
			return

	raise Exception("Invalid Mnemonic")











def parse(lines):	

	for line in lines:
		# remove spaces for fmtline
		fmtline = line.strip()
		fmtline = fmtline.replace(' ', '')
		fmtline = fmtline.upper()
		# is empty ?
		if not fmtline: continue
		
		# is comment ? 
		if fmtline[0] == ';': continue
		if fmtline[0] == '#': continue
		try:
			Decode(fmtline)
		except Exception as err:
			sys.stderr.write(str(err) + "\nline " + str(lines.index(line)) + ": " + str(line) + "\n");

	return;








