//
// Created by John Sullivan on 10/5/18.
//

#include "list.h"

static car_t *front = NULL;

/* put(): place a car at the beginning of the list
 * returns 0 if successful; nonzero otherwise
 */
int32_t lput(car_t *cp) {
    cp->next = front;
    front = cp;
    return 0;
}
// TODO: how to return another number other than 0, also for other functions?

/* get(): remove and return the first car in the list;
 * return NULL if the list is empty
 */
car_t *lget() {
    if (front == NULL) return NULL;

    car_t *tmp = front;
    car_t *next = tmp->next;

    front = next;
    tmp->next = NULL;

    return tmp;
}

/* apply a function to every car in the list */
void lapply(void (*fn)(car_t *cp)) {
    car_t *curr = front;

    while (curr != NULL) {
        (*fn)(curr);
        curr = curr->next;
    }
}

/* remove(): find, remove, and return any car with
 * the designated plate; return NULL if not present
 */
car_t *lremove(char *platep) {
    car_t *prev = NULL;
    car_t *curr = front;

    // Case if at front of list
    if (curr != NULL && strcmp(platep,curr->plate)==0) {
        front = curr->next;

        // Delinking curr's next ptr
        curr->next = NULL;
        return(curr);
    }

    // Searching rest of list
    while (curr != NULL) {

        if (strcmp(platep,curr->plate) == 0) {
            prev->next = curr->next;
            curr->next = NULL;
            return curr;
        }

        // Delinking curr's next ptr
        prev = curr;
        curr = curr->next;
    }

    return NULL;
}
