import sys
import io





key_words = [ "MOVE", "LOAD", "ADD", "SUB", "STORE" ]
registers = [ 'A', 'B', 'C', 'D' ]
code_gen = []





def SplitOperands(operands):
	firstOperand = operands[:operands.find(',')]
	secondOperand = operands[len(firstOperand)+1:]
	firstOperand = firstOperand.strip()
	secondOperand = secondOperand.strip()
	return (firstOperand, secondOperand)





def GetValue(string):
	try:
		if string[0] == '#':
			string = string[1:]

		if string[0] == '$':
			return int(string[1:], 16)
		elif string[0:2] == "0x":
			return int(string[2:], 16)
		else:
			return int(string, 10)

	except:
		raise Exception("Failed to get value from: " + str(string))





def move(operands):

	print("MOVE DECODER")

	first, second = SplitOperands(operands)

	if first != 'A': raise Exception("ONLY REGISTER A CAN BE MOVED TO")

	msb = 0xA0

	if second == 'B': lsb = 0x01
	elif second == 'C': lsb = 0x02
	else: raise Exception("UNKNOWN REGISTER \'" + str(second) + "\'")

	print("ADD GENERATED: %X" % (msb << 8 | lsb))

	code_gen.append(msb)
	code_gen.append(lsb)




def load(operands): 

	print("LOAD DECODER")


	first, second = SplitOperands(operands)


	try:
		registers.index(str(first))
	except:
		raise Exception("INVALID REGISTER \'" + str(first) + "\'")


	register = first

	print("WITH OPERANDS: " + str(operands[:len(operands)-1]))
	print("FIRST: " + str(first))
	print("SECOND: " + str(second))
	
	
	if second[0] == '#':
		# is immediate
		if register == 'A': msb = 0xA1
		elif register == 'B': msb = 0xB1
		elif register == 'C': msb = 0xC1		
		elif register == 'D':
			raise Exception("CAN't LOAD IMMEDIATE VALUE INTO D REGISTER")
	else:
		# is addr
		if register == 'A': msb = 0xA2
		elif register == 'B': msb = 0xB2
		elif register == 'C': msb = 0xC2
		elif register == 'D': msb = 0xD2

	lsb = GetValue(second)

	print("LOAD DECODER GENERATED: %X" % (msb << 8 | lsb) )
	
	code_gen.append(msb)
	code_gen.append(lsb)





def add(operands):
	print("ADD DECODER")

	first, second = SplitOperands(operands)

	if first != 'A': raise Exception("ONLY REGISTER A CAN BE ADDED TO")


	msb = 0xA0

	if second == 'B': lsb = 0x02
	elif second == 'C': lsb = 0x03
	else: raise Exception("UNKNOWN REGISTER \'" + str(second) + "\'")

	print("ADD GENERATED: %X" % (msb << 8 | lsb))

	code_gen.append(msb)
	code_gen.append(lsb)





def sub(operands):
	print("SUB DECODER")

	if first != 'A': raise Exception("ONLY REGISTER A CAN BE SUB FROM")


	msb = 0xA0

	if second == 'B': lsb = 0x04
	elif second == 'C': lsb = 0x05
	else: raise Exception("UNKNOWN REGISTER \'" + str(second) + "\'")

	print("SUB GENERATED: %X" % (msb << 8 | lsb))

	code_gen.append(msb)
	code_gen.append(lsb)







def store(operands):
	print("STORE DECODER")


	first, second = SplitOperands(operands)


	try:
		registers.index(str(first))
	except:
		raise Exception("INVALID REGISTER \'" + str(first) + "\'")


	register = first

	print("WITH OPERANDS: %s" % str(operands[:len(operands)-1]))
	print("FIRST: %s" % str(first))
	print("SECOND: %s" % str(second))
	
	
	if second[0] == '#':
		raise Exception("CANT STORE IN A IMMEDIATE VALUE \'" + str(second) + "\'")

	else:
		# is addr
		if register == 'A': msb = 0xA4
		elif register == 'B': msb = 0xB4
		elif register == 'C': msb = 0xC4

	lsb = GetValue(second)

	print("LOAD DECODER GENERATED: %X" % (msb << 8 | lsb) )
	
	code_gen.append(msb)
	code_gen.append(lsb)




key_words_decoders = [ move, load, add, sub, store ]







def Decode(keyword, operands):
	key_words_decoders[key_words.index(keyword)](operands)










def CheckKeyWord(string):
	if string.find(' ') >= 0:
		string = string[0:string.find(' ')]
	elif string.find(';') >= 0:
		string = string[0:string.find(';')]
	elif string.find('\n') >= 0:
		string = string[0:string.find('\n')]

	try:
		key_words.index(string)
	
	except:
		raise Exception("INVALID KEYWORD \'" + str(string) + "\'")
	

	print("KEYWORD FOUND: " + str(string) )
	return string







def IsIdentifierCharacter(char):
	return char != ';' and char != '\n' and char != ' ' and char != '\t'









def Parse(codeLines):

	for line in codeLines:
		uline = line.upper()
		for i in range(0, len(uline)):
			if IsIdentifierCharacter(uline[i]):
				try:
					hasComment = uline.find(';')
					
					if hasComment < 0: hasComment = len(uline)

					uline = uline[0:hasComment]
					keyword = CheckKeyWord(uline[i:])
					operands = uline[len(keyword):]
					Decode(keyword, operands)
					break
				except Exception as err:
					errStr = str(err)
					raise Exception("ERROR IN  LINE " + str(codeLines.index(line)+1) + ": " + errStr)

				




























