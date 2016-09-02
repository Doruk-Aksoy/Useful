#include "MemPool.h"

void* find_free_chunk(mp_size_t size) {
	char* addr = MP.maddr_ptr;
	if(addr < (char *)&MP.pool_address[0] + MEMPOOL_SIZE - size) {
		MP.maddr_ptr += size;
		return (char *) addr;
	}
	dprintf("Out of memory, returning NULL!\n");
	return NULL;
}

void* pool_alloc(mp_size_t size) {
	// round to nearest power of 2 (at least 16)
    size = (size + sizeof(free_block) + (mem_align - 1)) & ~ (mem_align - 1);
    free_block* block = free_block_list_head.next;
    // help unlink memory
    free_block** head = &(free_block_list_head.next);
    // if there exists a free block just overwrite content, don't bother with maddr_ptr
    while (block) {
        if (block->size >= size) {
        	dprintf("Found free block fitting for size %d\n", size);
            *head = block->next;
            return ((char*)block) + sizeof(free_block);
        }
        head = &(block->next);
        block = block->next;
    }
	// no free spot, allocate
    block = (free_block*) find_free_chunk(size);
    block->size = size;
	// dont overwrite metadata
    return ((char*)block) + sizeof(free_block);
}

void pool_free(void* ptr) {
	if(!ptr) { // NULL shouldnt cause segfault
		dprintf("NULL ptr found!\n");
		return;
	}
    free_block* block = (free_block*)(((char*)ptr) - sizeof(free_block));
    free_block* temp = &free_block_list_head;
    if(temp) {
    	while(temp->next)
    		temp = temp->next;
    	temp->next = block;
	}
	else {
		dprintf("updated head next\n");
		temp = block;
		temp->next = block->next;
	}
}

void Construct_Memory_Pool() {
	int i;
	MP.mp_alloc = pool_alloc;
	MP.mp_free = pool_free;
	MP.maddr_ptr = &MP.pool_address[0];
	// initialize to null size
	for(i = 0; i < MEMPOOL_SIZE; ++i)
		MP.pool_address[i] = 0;
}
