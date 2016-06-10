import sys
import io

from parser import *


def PrintError(error):
	sys.stderr.write(str(error) + "\n")








def main():

	if len(sys.argv) < 2:
		PrintError("USAGE: " + str(sys.argv[0]) + " <filename>")
		exit(-1)


	try:
		ifile = open(sys.argv[1], "r")
		ifileLines = ifile.readlines()
		ifile.close()
		Parse(ifileLines)

	except Exception as err:
		PrintError(err)

	exit(0)





main()







