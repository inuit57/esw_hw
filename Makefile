EXAMPLES = hw7.out 


all : $(EXAMPLES)

hw7.out : hw7.c
	gcc -Wall -W -pthread -lrt -lpigpiod_if2 -Wno-unused-parameter $^ -o %@
