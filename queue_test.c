//
// Created by John Sullivan on 10/5/18.
//

#include <stdio.h>
#include <queue.h>
#include <list.h>

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
  queue_t* queue = qopen();
  
  if(argv[1] == 1) {
    printf("Printing from an empty list.\n");
    car_t *tmp1 = qget();
    printf("%s\n", tmp1->plate);
    free(tmp1);
  } else if(argv[1] == 4) {
    printf("Printing all other plates\n"); //apply() from an empty list                          
    qapply(queue,(void (*)(void*))print_plate);
  } else if(argv[1] == 6) {
    free(qremove(queue, searchfn, "123456789", sizeof("123456789"))); //remove() from an empty list                                    
    printf("Printing all plates with 123... removed\n");
    qapply(print_plate);
  }

  car_t *p1 = make_car("123456789",20000,2016);
  car_t *p2 = make_car("098765432",15000,2015);
  car_t *p3 = make_car("543216789",17000,2017);
  car_t *p4 = make_car("678905432",12000,2012);

  //queue_t* queue = qopen();

  if(argv[1] == 2) {
    qput(queue,p1); //put() to an empty list
  } else if(argv[1] == 3) {
    qput(queue,p1);
    qput(queue,p2);
  } else if(argv[1] == 4) {
    qput(p1); //get() from a non-empty list                                                      
    qput(p2);
    printf("Printing from a non-empty list.\n");
    car_t *tmp2 = qget();
    printf("%s\n", tmp2->plate);
    free(tmp2);
  } else if(argv[1] == 5) { //apply() from a non-empty list                                       
    qput(p1);
    printf("Printing all other plates\n");
    qapply(print_plate);
  } else {
    qput(queue,p1);
    qput(queue,p2);
    qput(queue,p3);
    qput(queue,p4);
  }

  if(argv[1] == 7) {
    free(qremove(queue, searchfn, "123456789", sizeof("123456789")));

    printf("Printing all plates with 123... removed\n");
    qapply(queue,(void (*)(void*))print_plate);
  } else if(argv[1] == 8) {
    printf("Removing head\n");
    free(qremove(queue, searchfn, "543216789", sizeof("543216789")));

    printf("Printing all plates with 543... removed\n");
    qapply(queue,(void (*)(void*))print_plate);
  } else if(argv[1] == 9) {
    printf("Removing last element in linked list\n");
    free(qget());

    printf("Should print nothing ...\n");
    qapply(queue,(void (*)(void*))print_plate);
  }

  printf("Printing queue...\n");
  qapply(queue,(void (*)(void*))print_plate);
  
  printf("Getting plate of first-added element\n");
  car_t *tmp = qget(queue);
  printf("%s\n", tmp->plate);
  free(tmp);
  
  printf("Printing queue after element removed\n");
  qapply(queue,(void (*)(void*))print_plate);
  
  qclose(queue);

  exit(EXIT_SUCCESS);
}
