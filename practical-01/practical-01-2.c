//
// Created by lenovo on 7/29/2025.
//

#include <stdio.h>
#include <omp.h>

void print_sequential(const int num){
    printf("\tSequential: %d\n", num);
}

void print_parallel() {
    #pragma omp parallel
    {
        const int thread_id = omp_get_thread_num();
        printf("\tParallel : %d\n", thread_id);
    }
}

int main(){
    printf(" Sequential Execution \n\n");
    for (int i = 1; i <= 4; i++) {
        print_sequential(i);
    }
    printf("\n Parallel Execution \n\n");
    omp_set_num_threads(4);
    print_parallel();
    return 0;
}
