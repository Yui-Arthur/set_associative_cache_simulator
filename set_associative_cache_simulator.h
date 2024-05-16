#include "set_associative_cache.h"
#include <signal.h>

struct simulator{
    char *input_file;
    struct set_associative_cache *c;
};

void read_argc_and_init(struct simulator *s, int argc, char **argv){
    if(argc != 5){
        printf("Error Input Argument Numbers");
        return;
    }
    
    s->input_file = argv[1];

    uint32_t int_input[3] ={0};

    for(int i=0; i<3; i++)
        sscanf(argv[2+i], "%d", &int_input[i]);
    
    s->c = malloc(sizeof(struct set_associative_cache));
    *(s->c) = (struct set_associative_cache) {.Kbyte_cache_size = int_input[0], .word_block_size = int_input[1], .set_degree = int_input[2]};
    init_cache((s->c)); 
}

void init_simulator(struct simulator *s, char *filename, int int_input[3]){
    s->input_file = filename;
    s->c = malloc(sizeof(struct set_associative_cache));
    *(s->c) = (struct set_associative_cache) {.Kbyte_cache_size = int_input[0], .word_block_size = int_input[1], .set_degree = int_input[2]};
    init_cache((s->c)); 
    
}

void start_simulation(struct simulator *s){
    
    FILE *fptr = fopen(s->input_file, "r"); 
    char line[256];
    int decimal = 0;
    int miss = 0, total = 0;
    while (fgets(line, sizeof(line), fptr) != NULL){
        sscanf(line, "%x", &decimal);
        if(!read_or_write_cache((s->c), decimal, total+1)){
            miss++;
            get_block_from_memory((s->c), decimal, total+1);
        }
        total++;
    }

    fclose(fptr);
    printf("%d / %d = %f\n", miss, total, miss / (float)total);


    // free(s->input_file);
    // free(s->c->cache);
}