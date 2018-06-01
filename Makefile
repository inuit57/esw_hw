EXAMPLES = hw7.out 


all : $(EXAMPLES)

hw7.out : hw7.c
	gcc -Wall -W -pthread -lrt -lpigpiod_if2 -Wno-unused-parameter $^ -o $@

cJSON_build_ex1.out : cJSON_build_ex1.c cJSON.c
	gcc -Wall -W $^ -o $@
hw8_1.out : hw8_1.c cJSON.c
	gcc -Wall -W $^ -o $@
	
hw8_2.out : hw8_2.c cJSON.c
	gcc -Wall -W $^ -o $@
