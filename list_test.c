#include <stdio.h>
#include "list.h"
#include "queue.h"
#include "hash.h"

car_t *make_car(char* plate, double price, int year) {
    car_t* pp;

    // Allocating memory, returning if fails
    if (!(pp = (car_t*)malloc(sizeof(car_t)))) {
        printf("[Error: malloc failed allocating car]\n");
        exit(EXIT_FAILURE);
    }

    // Setting parts of object based on criteria
    pp->next = NULL;
    pp->price = price;
    pp->year = year;
    strcpy(pp->plate, plate);
    return pp;
}

void print_plate(car_t *cp) {
    printf("%s\n", cp->plate);
}

int main(int argc, char **argv) {
  
	int input = atoi(argv[1]);

	printf("%d\n", input);
  
  car_t *p1 = make_car("123456789",20000,2016);
  car_t *p2 = make_car("098765432",15000,2015);
  car_t *p3 = make_car("543216789",17000,2017);
  car_t *p4 = make_car("678905432",12000,2012);

	switch (input) {
	case 1:
		printf("Putting to an empty list..\n");

		if (lput(p1) == 0) {
			printf("Good\n");
			exit(EXIT_SUCCESS);
		} else {
			printf("Bad\n");
			exit(EXIT_FAILURE);

		}
	case 2:
		printf("Putting to a non-empty list...\n");

		lput(p1);

		if(lput(p2) == 0) {
			printf("Good\n");
			exit(EXIT_SUCCESS);
		} else {
			printf("Bad\n");
			exit(EXIT_FAILURE);
		}
	case 3:
		printf("Getting from an empty list...\n");

		car_t *tmp1 = lget();
		free(tmp1);

		if(tmp1 == NULL) {
			printf("Good\n");
			exit(EXIT_SUCCESS);
		} else {
			printf("Bad\n");
			exit(EXIT_FAILURE);
		}
	case 4:
		printf("Getting from a non-empty list...\n");

		lput(p1);

		car_t *tmp2 = lget();

		if(tmp2 != NULL) {
			printf("Got plate: \n");
			printf("%s\n", tmp2->plate);
			free(tmp2);
			printf("Good\n");
			exit(EXIT_SUCCESS);
		} else {
			printf("Bad\n");
			exit(EXIT_FAILURE);
		}
	case 5:
		printf("lapply() on an empty list...\n");

		lapply(print_plate);

		printf("Good\n");
		exit(EXIT_SUCCESS);
	case 6:
		printf("lapply() from a non-empty list...\n");

		lput(p1);

		lapply(print_plate);

		printf("Good\n");
		exit(EXIT_SUCCESS);
	case 7:
		printf("lremove() from an empty list...\n");

		car_t *tmp3 = lremove("123456789");
		free(tmp3);

		if (tmp3 == NULL) {
			free(tmp3);
			printf("Good\n");
			exit(EXIT_SUCCESS);
		} else {
			printf("Bad\n");
			exit(EXIT_FAILURE);
		}
	case 8:
		printf("Removing last element (tail) in list...\n");

		lput(p1);
		lput(p2);
		lput(p3);
		lput(p4);

		printf("Printing all plates\n");
		lapply(print_plate);

		free(lremove("678905432"));

		printf("Printing all plates with the last one removed...\n");
		lapply(print_plate);

		printf("Good\n");
		exit(EXIT_SUCCESS);
	case 9:
		printf("Removing first element (head of the list...\n");

		lput(p1);
		lput(p2);
		lput(p3);
		lput(p4);

		printf("Printing all plates\n");
		lapply(print_plate);

		free(lremove("123456789"));

		printf("Printing all plates with the first one removed...\n");
		lapply(print_plate);

		printf("Good\n");
		exit(EXIT_SUCCESS);
	case 10:
		printf("Removing a middle element of the queue...\n");                   

		lput(p1);
		lput(p2);
		lput(p3);
		lput(p4);

		printf("Printing all plates\n");
		lapply(print_plate);

		printf("Good\n");
		exit(EXIT_SUCCESS);
	default:
		printf("Bad\n");
		exit(EXIT_FAILURE);
	}
} 
