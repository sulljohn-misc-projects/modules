//
// Created by John Sullivan on 10/6/18.
//

#include <stdio.h>
#include "hash.h"

car *make_car(char* plate, double price, int year) {
	car_t* pp;      
    // Allocating memory, returning if fails
    if (!(pp = (car_t*)malloc(sizeof(car_t)))) {                               
			printf("[Error: malloc failed allocating car]\n");
			return NULL;                                            
    }
	
	// Setting parts of object based on criteria                            
	pp->next = NULL;                          
	pp->price = price;                            
	pp->year = year;                   
	strcpy(pp->plate, plate);
	return pp;                                               
}

int main() {
	car_t *p1 = make_car("123456789",20000,2016);
	car_t *p2 = make_car("098765432",15000,2015);
	car_t *p3 = make_car("543216789",17000,2017);
	car_t *p4 = make_car("678905432",12000,2012);

	hashtable_t* hash = hopen();

	hput(hash,p1);
	hput(hash,p2);
	hput(hash,p3);
	hput(hash,p4);

	printf("printing hash...\n");
	happly(hash,(void (*)(void*))print_plate);

	hclose(hash);
	
	return 0;
}
