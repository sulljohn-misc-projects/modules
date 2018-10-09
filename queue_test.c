//
// Created by John Sullivan on 10/5/18.
//
#include <stdio.h>
#include <stdlib.h>
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

bool searchfn(void *elementp, const void *keyp) {
    car_t *carp = (car_t *) elementp;

    return strcmp(carp->plate, keyp) == 0;
}

void print_plate(car_t *cp) {
    printf("%s\n", cp->plate);
}

int main(int argc, char **argv) {
    queue_t *queue = qopen();

    if (atoi(argv[1]) == 1) {
        printf("Getting from an empty list.\n");
        car_t *tmp = qget(queue);
        free(tmp);

        qclose(queue);

        if (tmp == NULL) {
            printf("Good\n");
            exit(EXIT_SUCCESS);
        } else {
            exit(EXIT_FAILURE);
        }
    } else if (atoi(argv[1]) == 10) {
        printf("Printing an empty list\n");
        qapply(queue, (void (*)(void *)) print_plate);

        exit(EXIT_SUCCESS);
    } else if (atoi(argv[1]) == 6) {
        printf("Removing from empty list\n");
        car_t *tmp = qremove(queue, searchfn, "123456789");
        free(tmp);

        qclose(queue);

        if (tmp == NULL) {
            free(tmp);
            printf("Good\n");
            exit(EXIT_SUCCESS);
        } else {
            exit(EXIT_FAILURE);
        }
    }

    // Now, non-empty list

    car_t *p1 = make_car("123456789", 20000, 2016);
    car_t *p2 = make_car("098765432", 15000, 2015);
    car_t *p3 = make_car("543216789", 17000, 2017);
    car_t *p4 = make_car("678905432", 12000, 2012);

    if (atoi(argv[1]) == 2) {
        printf("Putting to an empty list");

        if (qput(queue, p1) == 0) {
            exit(EXIT_SUCCESS);
        } else {
            exit(EXIT_FAILURE);
        }
    } else if (atoi(argv[1]) == 3) {
        printf("Putting to a non-empty list");

        qput(queue, p1);

        if (qput(queue, p2) == 0) {
            exit(EXIT_SUCCESS);
        } else {
            exit(EXIT_FAILURE);
        }
    } else if (atoi(argv[1]) == 4) {
        qput(queue, p1); //get() from a non-empty list
        qput(queue, p2);

        car_t *tmp = qget(queue);

        if (tmp != NULL) {
            printf("Got plate: \n");
            printf("%s\n", tmp->plate);
            free(tmp);
            exit(EXIT_SUCCESS);
        } else {
            exit(EXIT_FAILURE);
        }
    }

    // Putting all elements into the queue

    qput(queue, p1);
    qput(queue, p2);
    qput(queue, p3);
    qput(queue, p4);

    if (atoi(argv[1]) == 5) {
        printf("Printing from a non-empty list.\n");
        qapply(queue,
               (void (*)(void *)) print_plate);
    } else if (atoi(argv[1]) == 7) {
        free(qremove(queue, searchfn, "123456789"));

        printf("Printing all plates with 123... removed\n");
        qapply(queue, (void (*)(void *)) print_plate);
    } else if (atoi(argv[1]) == 8) {
        printf("Removing head\n");
        free(qremove(queue, searchfn, "543216789"));

        printf("Printing all plates with 543... removed\n");
        qapply(queue, (void (*)(void *)) print_plate);
    } else if (atoi(argv[1]) == 9) {
        printf("Removing last element in linked list\n");
        free(qget(queue));

        printf("Should print nothing ...\n");
        qapply(queue, (void (*)(void *)) print_plate);
    }

    exit(EXIT_SUCCESS);
}
