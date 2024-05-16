#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cache_block
{
    bool valid_bit;
    uint32_t tag;
    uint16_t last_used;
};


struct set_associative_cache
{
    uint32_t Kbyte_cache_size;
    uint32_t word_block_size;
    uint32_t set_degree;
    uint32_t entries;
    struct cache_block **cache;
};

void init_cache(struct set_associative_cache* c){

    c->entries = c->Kbyte_cache_size * 1024 / (c->word_block_size * 4) / c->set_degree;
    // printf("entrty : %d\n", c->entries);
    c->cache = malloc(c->entries * sizeof(struct cache_block*));
    // malloc and init with 0
    for(int i=0; i<c->entries; i++)
        c->cache[i] = calloc(c->set_degree , sizeof(struct cache_block));
        
    
    return;
}

void show_current_cache(struct set_associative_cache* c){
    printf("         ");
    for(int j=0; j<c->set_degree; j++)
        printf("       %3d         ", j+1);
    printf("\n         ");
    for(int j=0; j<c->set_degree; j++)
        printf("------------------ ");
    printf("\n enrties ");
    for(int j=0; j<c->set_degree; j++)
        printf("| v,   tag, used | ");
    printf("\n         ");
    for(int j=0; j<c->set_degree; j++)
        printf("------------------ ");
    printf("\n");

    for(int i=0; i<c->entries; i++){
        printf("%5d :  ",i);
        for(uint32_t j=0; j<c->set_degree; j++){
            struct cache_block b = c->cache[i][j];
            printf("| %u, %5u, %4u | ", b.valid_bit, b.tag, b.last_used);
        }
        printf("\n");
    }
}

bool read_or_write_cache(struct set_associative_cache* c, uint32_t mem_addr, uint16_t cycle){

    uint32_t block_idx = mem_addr / 4 / c->word_block_size;
    uint32_t entries_idx = block_idx % c->entries, t = block_idx / c->entries;

    bool is_hit = false;
    for(uint32_t i=0; i<c->set_degree; i++){
        if(c->cache[entries_idx][i].valid_bit && c->cache[entries_idx][i].tag == t){
            is_hit = true;
            c->cache[entries_idx][i].last_used = cycle;
            break;
        }
    }

    // if(is_hit)
        // printf("%d cycles, entries : %d , tag : %d\n", cycle, entries_idx, t);

    return is_hit;

}

void get_block_from_memory(struct set_associative_cache* c, uint32_t mem_addr, uint16_t cycle){

    uint32_t block_idx = mem_addr / 4 / c->word_block_size;
    uint32_t entries_idx = block_idx % c->entries, t = block_idx / c->entries;

    uint16_t min_last_used  = 1e5;
    uint32_t target_set = 0;

    for(uint32_t i=0; i<c->set_degree; i++){
        if(!c->cache[entries_idx][i].valid_bit){
            target_set = i;
            break;
        }
        else if(c->cache[entries_idx][i].last_used < min_last_used)
            target_set = i, min_last_used = c->cache[entries_idx][i].last_used;
    }

    c->cache[entries_idx][target_set] = (struct cache_block) {.tag = t, .last_used = cycle, .valid_bit = 1};

    return;

}
