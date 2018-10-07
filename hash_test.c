//
// Created by John Sullivan on 10/6/18.
//

#include <stdio.h>
#include "hash.h"
#include "queue.h"
#include "list.h"


car_t *make_car(char *plate, double price, int year) {
    car_t *pp;
    // Allocating memory, returning if fails
    if (!(pp = (car_t *) malloc(sizeof(car_t)))) {
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

bool searchfn(void *elementp, const void *keyp) {
    car_t *carp = (car_t *) elementp;

    return strcmp(carp->plate, keyp) == 0;
}

int main() {
    car_t *p1 = make_car("123456789", 20000, 2016);
    car_t *p2 = make_car("098765432", 15000, 2015);
    car_t *p3 = make_car("543216789", 17000, 2017);
    car_t *p4 = make_car("678905432", 12000, 2012);

    hashtable_t *hash = hopen(1024);

    hput(hash, p1, p1->plate, sizeof(p1->plate));
    hput(hash, p2, p2->plate, sizeof(p2->plate));
    hput(hash, p3, p3->plate, sizeof(p3->plate));
    hput(hash, p4, p4->plate, sizeof(p4->plate));

    printf("printing hash...\n");
    happly(hash, (void (*)(void *)) print_plate);

    printf("Searching for hash with search function\n");
    car_t *tmp = hsearch(hash, searchfn, "123456789", sizeof("123456789"));
    printf("%s\n", tmp->plate);

    hclose(hash);

    return 0;
}
