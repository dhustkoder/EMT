import sys
import io





key_words = [ "LOAD", "ADD", "SUB", "STORE" ]
registers = [ 'A', 'B', 'C', 'D' ]
code_gen = []





def SplitOperands(operands):
	firstOperand = operands[:operands.find(',')]
	secondOperand = operands[len(firstOperand)+1:]
	firstOperand = firstOperand.strip()
	secondOperand = secondOperand.strip()
	return (firstOperand, secondOperand)


def load(operands): 
	print("LOAD DECODER")

	first, second = SplitOperands(operands)

	print("WITH OPERANDS: " + str(operands[:len(operands)-1]))
	print("FIRST: " + str(first))
	print("SECOND: " + str(second))
	if second[0] == '#':
		x = first[0]
		
		if x == 'A': return	
			
		elif x == 'B': return
			
		elif x == 'C':	return
			
		elif x == 'D':	return 
			
		else:
			raise Exception("INVALID REGISTER")
		
	

def add(operands):
	print("ADD DECODER")

def sub(operands):
	print("SUB DECODER")

def store(operands):
	print("STORE DECODER")


key_words_decoders = [ load, add, sub, store ]


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
		pass
		raise Exception("INVALID KEYWORD \'" + str(string) + "\'")
	

	print("KEYWORD FOUND: " + str(string) )
	return string



def IsIdentifierCharacter(char):
	return char != ';' and char != '\n' and char != ' ' and char != '\t'


def Parse(codeLines):

	for line in codeLines:
		line = line.upper()
		for i in range(0, len(line)):
			if IsIdentifierCharacter(line[i]):
				try:
					keyword = CheckKeyWord(line[i:])
					operands = line[len(keyword):]
					Decode(keyword, operands)
				except Exception as err:
					pass
					errStr = str(err)
					raise Exception("ERROR IN  LINE " + str(codeLines.index(line)+1) + ": " + errStr)
				break
				




























