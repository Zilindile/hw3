/*
 * mm_alloc.c
 *
 * Stub implementations of the mm_* routines. Remove this comment and provide
 * a summary of your allocator's design here.
 */
 
#include "mm_alloc.h"

#include <stdlib.h>

/* Your final implementation should comment out this macro. */
#define MM_USE_STUBS

void *p;
int init = 0;

void set_mem()
{
	p = sbrk(0);
	init = 1;
}

void *mm_malloc(size_t size)
{
  struct s_block *s;
	void *curr;
	void *ret;
	
	size += sizeof(struct s_block);
	
	if (!init)    
	    set_mem();
	
	ret = 0;
	curr = p;

	while (curr != p){
	 s = (struct s_block *)curr;
		if (s->free){
			if (s->size >= size){
				s->free = 0;	
				ret = curr;
				break;
			}
		}
		curr += s->size;
	}
	
	if (!ret){
		sbrk(size);  
		ret = p; 
		p += size;  

		s = curr;   
		s->free = 0;
		s->size = size;
	}

	ret += sizeof(struct s_block);  

	return ret;

}

void* mm_realloc(void* i, size_t size)
{

	struct s_block *s;
	s = i - sizeof(struct s_block);

	void *new_size = mm_malloc(size);

	memcpy(i, new_size ,s->size-sizeof(struct s_block));

	mm_free(i);

	return new_size;
}

void mm_free(void* i)
{

	struct s_block *s;
	s = i - sizeof(struct s_block);
	s->free = 1;  
	return;

}
