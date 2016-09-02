#ifndef MEMPOOL_IN
#define MEMPOOL_IN

// 1024 bytes allowed to be allocated in memory
#define MEMPOOL_SIZE 1024

#define DEBUG 1
// compiler should optimize this away in this case, if it's good :)
#define dprintf if(DEBUG) printf
// size of the void ptr (should be same across all pointers)
#define vptr_size sizeof(void *)

typedef unsigned int mp_size_t;

// Meta data for the memory chunks
typedef struct free_block {
    mp_size_t size;
    struct free_block* next;
} free_block;

// dummy node
static free_block free_block_list_head = { 0, 0 };
// Memory alignment byte count
static const mp_size_t mem_align = 16;

// This indexes the memory begin and end locations
// begin index is how to access this index

typedef struct {
	char			pool_address[MEMPOOL_SIZE];
	char*			maddr_ptr;
	// methods
	void*			(*mp_alloc)(mp_size_t);
	void			(*mp_free)(void*);
	
} mem_pool;

// create the global memory pool
static mem_pool			MP;

void* find_free_chunk(mp_size_t);
void Construct_Memory_Pool();
// refers to these
void* pool_alloc(mp_size_t);
void pool_free(void*);

#endif
