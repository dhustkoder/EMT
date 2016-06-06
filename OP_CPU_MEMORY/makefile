
CXX_FLAGS= -std=c++11 -pedantic -Wall -Wextra

ifeq (${MODE}, Release)
	CXX_FLAGS+= -O3 -fomit-frame-pointer -fno-exceptions
else
	CXX_FLAGS+= -g3 -O0 -fno-omit-frame-pointer
endif


compile:
	$(CXX) cpu.cpp -ocpu.out $(CXX_FLAGS)







