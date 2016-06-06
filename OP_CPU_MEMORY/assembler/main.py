# Copyright (C) 2016 Rafael Moura



import io
import sys
from parser import *

def main():

	try:
		file = open(sys.argv[1], "r");
	except Exception as err:
		sys.stderr.write("open file failed: " + str(err) + "\n");
	else:
		parse(file);


	return 0;


main();

