#include "set_associative_cache_simulator.h"

int main(int argc, char **argv){
    
    
    struct simulator *s = malloc(sizeof(struct simulator));
    read_argc_and_init(s, argc, argv);
    start_simulation(s);
    
    // init_simulator(s, "input.txt", input);
    // int input[3] = {1,2,3};
    // for(int i = 128; i <= 1024; i*=2){
    //     input[0] = i; 
    //     for(int j = 8; j <= 64; j*=2){
    //         input[1] = j;
    //         for(int k=2; k<=8; k*=2){
    //             printf("%d, %d, %d\n", i, j, k);
    //             input[2] = k;
    //             init_simulator(s, "input.txt", input);
    //             start_simulation(s);
    //             printf("\n");
    //         }
    //     }
    // }
    

    
    // free(s); 
    return 0;
} 