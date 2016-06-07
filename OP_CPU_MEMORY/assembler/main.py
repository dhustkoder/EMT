# Copyright (C) 2016 Rafael Moura



import io
import sys
from parser import *



def main():

	try:
		file = open(sys.argv[1], "r");
	except Exception as err:
		sys.stderr.write("open file failed: " + str(err) + "\n");
	
	lines = file.readlines();
	file.close();
	
	parse(lines);

	try:
		ofile = open("output.bin", "wb")
		ofile.write(bytes(binary))
	except Exception as err:
		sys.stderr.write("Failed to write to output.bin: " + str(err))
	finally: 
		ofile.close()
	
	return 0;



main();

