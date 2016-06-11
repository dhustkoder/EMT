'''
	Copyright (C) 2016 Rafael Moura
	Demonstration of a simple 8 bit opcode interpreter , with memory managment , and math
'''


import sys
import io

from parser import *


def PrintError(error):
	sys.stderr.write(str(error) + "\n")








def main():

	if len(sys.argv) < 2:
		PrintError("USAGE: " + str(sys.argv[0]) + " <filename>")
		sys.exit(-1)


	try:
		ifile = open(sys.argv[1], "r")
		ifileLines = ifile.readlines()
		ifile.close()

		Parse(ifileLines)

		ofile = open("OUTPUT.BIN", "wb")
		ofile.write(bytes(code_gen))
		ofile.close()

	except Exception as err:
		PrintError(err)
		sys.exit(-1)
	

	# ....
	sys.exit(0)





main()







