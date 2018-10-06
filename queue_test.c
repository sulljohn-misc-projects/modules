//
// Created by John Sullivan on 10/5/18.
//

#include <stdio.h>
#include "queue.h"
#include "list.h"

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

    queue_t* queue = qopen();

    qput(queue,p1);
    qput(queue,p2);
    qput(queue,p3);
    qput(queue,p4);

    printf("Printing queue...\n");
    qapply(queue,(void (*)(void*))print_plate);

    printf("Getting plate of first-added element\n");
    car_t *tmp = qget(queue);
    printf("%s\n", tmp->plate);
    free(tmp);

    printf("Printing queue after element removed\n");
    qapply(queue,(void (*)(void*))print_plate);

    qclose(queue);

    return 0;
}