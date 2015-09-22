#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <pthread.h>

#include "philosopher.h"

pthread_mutex_t chopsticks[5];
/*
 * Performs necessary initialization of mutexes.
 */
void chopsticks_init(){
 	int i=0;
	for (i=0;i<5;i++){
		pthread_mutex_init(&chopsticks[i],NULL);
	}
}

/*
 * Cleans up mutex resources.
 */
void chopsticks_destroy(){
	int i=0;
	for (i=0;i<5;i++){
		pthread_mutex_destroy(&chopsticks[i]);
	}
}

/*
 * Uses pickup_left_chopstick and pickup_right_chopstick
 * to pick up the chopsticks
 */
void pickup_chopsticks(int phil_id){
	if(phil_id == 4) {
		pthread_mutex_lock(&chopsticks[(phil_id + 1) % 5]);
		pickup_right_chopstick(phil_id);
		pthread_mutex_lock(&chopsticks[(phil_id) % 5]);
		pickup_left_chopstick(phil_id);
	}
	else {
		pthread_mutex_lock(&chopsticks[(phil_id) % 5]);
		pickup_left_chopstick(phil_id);
		pthread_mutex_lock(&chopsticks[(phil_id+1)%5]);
		pickup_right_chopstick(phil_id);
	}
}

/*
 * Uses putdown_left_chopstick and putdown_right_chopstick
 * to put down the chopsticks
 */   
void putdown_chopsticks(int phil_id){
	if(phil_id == 4){
		putdown_right_chopstick(phil_id);
		pthread_mutex_unlock(&chopsticks[(phil_id + 1) % 5]);
		putdown_left_chopstick(phil_id);
		pthread_mutex_unlock(&chopsticks[(phil_id) % 5]);
	}
	else {
		putdown_left_chopstick(phil_id);
		pthread_mutex_unlock(&chopsticks[(phil_id) % 5]);
		putdown_right_chopstick(phil_id);
		pthread_mutex_unlock(&chopsticks[(phil_id + 1) % 5]);
	}
}
