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

	firstOperand, secondOperand = SplitOperands(operands)

	print("WITH OPERANDS: " + str(operands[:len(operands)-1]))
	print("FIRST: " + str(firstOperand))
	print("SECOND: " + str(secondOperand))

	

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
		print("KEYWORD NOT FOUND: " + str(string) )
		return None
	else:
		print("KEYWORD FOUND: " + str(string) )
		return string



def IsIdentifierCharacer(char):
	return char != ' ' and char != '\n' and char != ';' and char != '\t'


def Parse(codeLines):

	for line in codeLines:
		line = line.upper()
		for i in range(0, len(line)):
			if line[i] == ';': break;
			elif IsIdentifierCharacer(line[i]):
				keyword = CheckKeyWord(line[i:])

				if keyword != None:
					operands = line[len(keyword):]
					Decode(keyword, operands)
					break
				else:
					raise Exception("INVALID KEYWORD: " + str() + "\nLINE: " + str(codeLines.index(line)+1))



























