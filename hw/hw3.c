#include<stdio.h>
#include<pigpiod_if2.h>
#define PINNO1 23
#define PINNO3 6
#define PINNO2 13

int count;
uint32_t falling_tick , rising_tick;

void cb_falling_func(int pi, unsigned user_gpio, unsigned level, uint32_t tick){
	falling_tick = tick;
}

void cb_rising_func(int pi, unsigned user_gpio, unsigned level, uint32_t tick){
	rising_tick = tick;
	if(rising_tick - falling_tick < 1000) return ;
	else{
		count++;
	}
	printf("count : %d period : %d\n", count, rising_tick - falling_tick);

}

void btn2_falling_func(int pi, unsigned user_gpio, unsigned level, uint32_t tick){
	printf("total btn_count : %d\n", count);
	int i;
	for(i=0; i<count; i++){
		gpio_write(pi, PINNO3, 1);
		sleep(1);
		gpio_write(pi, PINNO3, 0);
		sleep(1);
	}
}

int main(void){
	int pi;
	if((pi = pigpio_start(NULL, NULL)) <0){
		fprintf("stderr, %s\n", pigpio_error(pi));
		return 1;
	}
	set_mode(pi, PINNO1, PI_INPUT);
	set_pull_up_down(pi, PINNO1, PI_PUD_UP);
	set_mode(pi, PINNO2, PI_INPUT);
	set_pull_up_down(pi, PINNO2, PI_PUD_UP);

	set_mode(pi, PINNO3, PI_OUTPUT);

	callback(pi, PINNO1, FALLING_EDGE , cb_falling_func);
	callback(pi, PINNO1, RISING_EDGE , cb_rising_func);


	callback(pi, PINNO2, FALLING_EDGE, btn2_falling_func);

	getchar();
	pigpio_stop(pi);
	return 0;
}

