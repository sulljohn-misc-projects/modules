#include <stdio.h>
#include "list.h"
// #include "queue.h"
// #include "hash.h"

car_t *make_car(char* plate, double price, int year) {
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

void print_plate(car_t *cp) {
    printf("%s\n", cp->plate);
}

int main() {
    car_t *p1 = make_car("123456789",20000,2016);
    car_t *p2 = make_car("098765432",15000,2015);
    car_t *p3 = make_car("543216789",17000,2017);
    car_t *p4 = make_car("678905432",12000,2012);

    lput(p1);
    lput(p2);
    lput(p3);
    lput(p4);

    printf("Printing first plate\n");
    car_t *tmp = lget();
    printf("%s\n", tmp->plate);
    free(tmp);

    printf("Printing all other plates\n");
    lapply(print_plate);

    free(lremove("123456789"));

    printf("Printing all plates with 123... removed\n");
    lapply(print_plate);

    lremove("Removing head\n");
    free(lremove("543216789"));

    printf("Printing all plates with 543... removed\n");
    lapply(print_plate);

    printf("Removing last element in linked list\n");
    free(lget());

    printf("Should print nothing ...\n");
    lapply(print_plate);

    return 0;
}