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

bool searchfn(void *elementp, const void *keyp) {
    car_t *carp = (car_t *) elementp;

    return strcmp(carp->plate, keyp) == 0;
}

int main(int argc, char **argv) {
    if (argc != 2) exit(EXIT_FAILURE);

    int input = atoi(argv[1]);

    hashtable_t *hash = hopen(1024);

    car_t *p1 = make_car("123456789", 20000, 2016);
    car_t *p2 = make_car("098765432", 15000, 2015);
    car_t *p3 = make_car("543216789", 17000, 2017);
    car_t *p4 = make_car("678905432", 12000, 2012);

    switch (input) {
        case 1:
            printf("Putting to an empty hashtable...\n");

            if (hput(hash, p1, p1->plate, sizeof(p1->plate)) == 0) {
                printf("Good\n");
                hclose(hash);
                exit(EXIT_SUCCESS);
            } else {
                printf("Bad\n");
                hclose(hash);
                exit(EXIT_FAILURE);
            }
        case 2:
            printf("Putting to a non-empty hashtable...\n");

            hput(hash, p1, p1->plate, sizeof(p1->plate));

            if (hput(hash, p2, p2->plate, sizeof(p2->plate)) == 0) {
                printf("Good\n");
                hclose(hash);
                exit(EXIT_SUCCESS);
            } else {
                printf("Bad\n");
                hclose(hash);
                exit(EXIT_FAILURE);
            }
        case 3:
            printf("Searching empty hashtable...\n");

            car_t *tmp1 = hsearch(hash, searchfn, "123456789", sizeof("123456789"));

            if (tmp1 == NULL) {
                printf("Good\n");
                hclose(hash);
                exit(EXIT_SUCCESS);
            } else {
                printf("Bad\n");
                hclose(hash);
                exit(EXIT_FAILURE);
            }
        case 4:
            printf("Searching non-empty hashtable...\n");

            hput(hash, p1, p1->plate, sizeof(p1->plate));
            hput(hash, p2, p2->plate, sizeof(p2->plate));

            car_t *tmp2 = hsearch(hash, searchfn, "123456789", sizeof("123456789"));

            if (tmp2 != NULL) {
                printf("Got plate: \n");
                printf("%s\n", tmp2->plate);
                
                printf("Good\n");
                hclose(hash);
                exit(EXIT_SUCCESS);
            } else {
                printf("Bad\n");
                hclose(hash);
                exit(EXIT_FAILURE);
            }
        case 5:
            printf("Printing an empty hashtable...\n");

            happly(hash, (void (*)(void *)) print_plate);

            printf("Good\n");
            hclose(hash);
            exit(EXIT_SUCCESS);
        case 6:
            printf("Printing from a non-empty hashtable...\n");

            hput(hash, p1, p1->plate, sizeof(p1->plate));
            hput(hash, p2, p2->plate, sizeof(p2->plate));
            hput(hash, p3, p3->plate, sizeof(p3->plate));
            hput(hash, p4, p4->plate, sizeof(p4->plate));

            happly(hash, (void (*)(void *)) print_plate);

            printf("Good\n");
            hclose(hash);
            exit(EXIT_SUCCESS);
        case 7:
            printf("Removing from empty hashtable...\n");

            car_t *tmp3 = hremove(hash, searchfn, "123456789", sizeof("123456789"));

            if (tmp3 == NULL) {
                printf("Good\n");

                free(tmp3);
                hclose(hash);
                exit(EXIT_SUCCESS);
            } else {
                printf("Bad\n");

                free(tmp3);
                hclose(hash);
                exit(EXIT_FAILURE);
            }
        case 8:
            printf("Removing last element added from hashtable...\n");

            hput(hash, p1, p1->plate, sizeof(p1->plate));
            hput(hash, p2, p2->plate, sizeof(p2->plate));
            hput(hash, p3, p3->plate, sizeof(p3->plate));
            hput(hash, p4, p4->plate, sizeof(p4->plate));

            printf("Printing all plates\n");
            happly(hash, (void (*)(void *)) print_plate);

            free(hremove(hash, searchfn, "678905432", sizeof("678905432")));

            printf("Printing all plates with last one removed...\n");
            happly(hash, (void (*)(void *)) print_plate);

            printf("Good\n");
            hclose(hash);
            exit(EXIT_SUCCESS);
        case 9:
            printf("Removing first element added from hashtable...\n");

            hput(hash, p1, p1->plate, sizeof(p1->plate));
            hput(hash, p2, p2->plate, sizeof(p2->plate));
            hput(hash, p3, p3->plate, sizeof(p3->plate));
            hput(hash, p4, p4->plate, sizeof(p4->plate));

            printf("Printing all plates\n");
            happly(hash, (void (*)(void *)) print_plate);

            free(hremove(hash, searchfn, "123456789", sizeof("123456789")));

            printf("Printing all plates with first one removed...\n");
            happly(hash, (void (*)(void *)) print_plate);

            printf("Good\n");
            hclose(hash);
            exit(EXIT_SUCCESS);
        case 10:
            printf("Removing element added in middle from hashtable...\n");

            hput(hash, p1, p1->plate, sizeof(p1->plate));
            hput(hash, p2, p2->plate, sizeof(p2->plate));
            hput(hash, p3, p3->plate, sizeof(p3->plate));
            hput(hash, p4, p4->plate, sizeof(p4->plate));

            printf("Printing all plates\n");
            happly(hash, (void (*)(void *)) print_plate);

            free(hremove(hash, searchfn, "543216789", sizeof("543216789")));

            printf("Printing all plates with 543... removed\n");
            happly(hash, (void (*)(void *)) print_plate);

            printf("Good\n");
            hclose(hash);
            exit(EXIT_SUCCESS);
        default:
            printf("Bad\n");
            hclose(hash);
            exit(EXIT_FAILURE);
    }
}
