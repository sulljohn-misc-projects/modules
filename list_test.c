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
  
<<<<<<< HEAD
  if(atoi(argv[1] == 1) { 
    printf("Printing from an empty list.\n");
    car_t *tmp1 = lget();
		free(tmp1);
		if(*tmp1 == NULL) {
			exit(EXIT_SUCCESS);
		}
  } else if(argv[1] == 10) {
    printf("Printing all other plates\n"); //apply() from an empty list
    if(lapply(print_plate) == NULL) {
			exit(EXIT_SUCCESS);
		} else {
			exit(EXIT_FAILURE);
		}
  } else if(argv[1] == 6) {
=======
  if(atoi(argv[1]) == 1) {
    printf("Printing from an empty list.\n");
    car_t *tmp1 = lget();
    printf("%s\n", tmp1->plate);
    free(tmp1);
  } else if(atoi(argv[1]) == 4) {
    printf("Printing all other plates\n"); //apply() from an empty list
    lapply(print_plate);
  } else if(atoi(argv[1]) == 6) {
>>>>>>> 00cbc3842ec339eb97ba89983508f68bdbe6c41f
    free(lremove("123456789")); //remove() from an empty list
    printf("Printing all plates with 123... removed\n");
    lapply(print_plate);
  }
  
  car_t *p1 = make_car("123456789",20000,2016);
  car_t *p2 = make_car("098765432",15000,2015);
  car_t *p3 = make_car("543216789",17000,2017);
  car_t *p4 = make_car("678905432",12000,2012);

  if(atoi(argv[1]) == 2) {
    lput(p1); //put() to an empty list
  } else if(atoi(argv[1]) == 3) {
    lput(p1);
    lput(p2); //put() to a non-empty list
  } else if(atoi(argv[1]) == 4) {
    lput(p1); //lget() from a non-empty list
    lput(p2);
    printf("Printing from a non-empty list.\n");
    car_t *tmp2 = lget();
    printf("%s\n", tmp2->plate);
    free(tmp2);
  } else if(atoi(argv[1]) == 5) { //apply() from a non-empty list
    lput(p1);
    printf("Printing all other plates\n");
    lapply(print_plate);
  } else {
    lput(p1);
    lput(p2);
    lput(p3);
    lput(p4);
  }

  if(atoi(argv[1]) == 7) {
    free(lremove("123456789"));

    printf("Printing all plates with 123... removed\n");
    lapply(print_plate);
  } else if(atoi(argv[1]) == 8) {
    printf("Removing head\n");
    free(lremove("543216789"));

    printf("Printing all plates with 543... removed\n");
    lapply(print_plate);
  } else if(atoi(argv[1]) == 9) {
    printf("Removing last element in linked list\n");
    free(lget());

    printf("Should print nothing ...\n");
    lapply(print_plate);
  }

  exit(EXIT_SUCCESS);
}
