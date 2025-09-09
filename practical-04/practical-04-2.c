//
// Created by lenovo on 9/9/2025.
//
// Producer-Consumer using OpenMP in C
#include <stdio.h>
#include <omp.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int countItems = 0;
int in = 0;
int out = 0;

int main() {
    omp_set_num_threads(2);

#pragma omp parallel sections
    {
        // Producer section
#pragma omp section
        {
            for (int i = 1; i <= NUM_ITEMS; i++) {
                int producedItem = i;
                int not_produced = 1;

                while (not_produced) {
#pragma omp critical
                    {
                        if (countItems < BUFFER_SIZE) {
                            buffer[in] = producedItem;
                            in = (in + 1) % BUFFER_SIZE;
                            countItems++;
                            printf("Producer Produced item %d | Buffer Count = %d\n",
                                   producedItem, countItems);
                            not_produced = 0;
                        }
                    }
                }
            }
        }

        // Consumer section
#pragma omp section
{
    for (int i = 1; i <= NUM_ITEMS; i++) {
        int consumedItem;
        int not_consumed = 1;

        while (not_consumed) {
#pragma omp critical
            {
                if (countItems > 0) {
                    consumedItem = buffer[out];
                    out = (out + 1) % BUFFER_SIZE;
                    countItems--;
                    printf("Consumer Consumed item %d | Buffer Count = %d\n",
                           consumedItem, countItems);
                    not_consumed = 0;
                }
            }
        }
    }
}
    }

    return 0;
}
