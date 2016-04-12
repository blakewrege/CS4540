// git@github.com:kmcallister/embedded-breakpoints.git

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#define BLOCK_SIZE 20
#define align4(x) (((((x)-1)>>2)<<2)+4)


static unsigned char our_memory[1024 * 1024]; //reserves 1 MB for malloc
static size_t next_index = 0;

void *mymalloc(size_t);
void myfree();


void *base=NULL;



struct rec
{
		int i;
		float PI;
		char A;
};

 /* block struct */
struct b_cake {
 size_t size;
 struct b_cake *next;
 struct b_cake *prev;
 int free;
 void *ptr;
 /* A pointer to the allocated block */
 char data [1];
};
typedef struct b_cake *a_cake;



int main()
{

struct rec *num_one;
num_one =(struct rec *) mymalloc (sizeof(struct rec));

num_one->i = 10;
num_one->PI = 3.14;
num_one->A = 'a';

printf("First value: %d\n", num_one->i);
printf("Second value: %f\n", num_one->PI);
printf("Third value: %c\n", num_one->A);

myfree(num_one);

return 0;


}


a_cake find_block (a_cake *last , size_t size ){
 a_cake b = base;
 
 while (b && !(b->free && b->size >= size )) {
 	*last = b;
 	b = b->next;
 	}
 return (b);
}





a_cake extend_heap (a_cake last , size_t s)
 {
 int sb;
 a_cake b;
 b = sbrk (0);
 sb = (int)sbrk( BLOCK_SIZE + s);
 if (sb < 0)
 	return (NULL );
 b->size = s;
 b->next = NULL;
 b->prev = last;
 b->ptr = b->data;
 if (last)
 	last ->next = b;
 b->free = 0;
 return (b);
}






/* Split block according to size. */
/* The b block must exist. */
void split_block (a_cake b, size_t s){
 a_cake new;
 new = (a_cake )(b->data + s);
 new ->size = b->size - s - BLOCK_SIZE ;
 new ->next = b->next;
 new ->prev = b;
 new ->free = 1;
 new ->ptr = new ->data;
 b->size = s;
 b->next = new;
 if (new ->next)
 	new ->next ->prev = new;
}



void *mymalloc(size_t size ){
 a_cake b,last;
 size_t s;
 s = align4(size );
 if (base) {
 	last = base;
 	b = find_block (&last ,s);
 	if (b){
 		if ((b->size - s) >= ( BLOCK_SIZE + 4))
 			split_block (b,s);
 		b->free =0;
 		} else {
 			b = extend_heap (last ,s);
 			if (!b)
 		return(NULL );
 		}
 	} else {
 		b = extend_heap (NULL ,s);
 		if (!b)
 			return(NULL );
 		base = b;
 		}
 return(b->data );
} 



void *calloc(size_t number , size_t size ){
 size_t *new;
 size_t s4 ,i;
 new = malloc(number * size );
 if (new) {
 	s4 = align4(number * size) << 2;
 	for (i=0; i<s4 ; i++)
 	new[i] = 0;
 	}
 return (new);
}

a_cake fusion(a_cake b){
 if (b->next && b->next ->free ){
 	b->size += BLOCK_SIZE + b->next ->size;
 	b->next = b->next ->next;
 	if (b->next)
 		b->next ->prev = b;
 	}
 return (b);
}

 a_cake get_block (void *p){
 char *tmp;
 tmp = p;
 return (p = tmp -= BLOCK_SIZE );
}


int valid_addr (void *p)
 {
 if (base){
 	if ( p>base && p<sbrk (0)){
 		return (p == ( get_block (p))->ptr );
 		}
 	}
 return (0);
}


void myfree(void *p){
 a_cake b;
 if ( valid_addr (p)){
 	b = get_block (p);
 	b->free = 1;
 if(b->prev && b->prev ->free)
 	b = fusion(b->prev );
 if (b->next)
 	fusion(b);
 else{
 	if (b->prev)
 		b->prev ->next = NULL;
 	else
 		base = NULL;
 	brk(b);
 }
 } 
}

void copy_block (a_cake src , a_cake dst)
 {
 int *sdata ,* ddata;
 size_t i;
 sdata = src ->ptr;
 ddata = dst ->ptr;
 for (i=0; i*4<src ->size && i*4<dst ->size; i++)
 ddata[i] = sdata[i];
}



void *realloc(void *p, size_t size){
 size_t s;
 a_cake b, new;
 void *newp;
 if (!p)
 return (malloc(size ));
 if ( valid_addr (p)){
 	s = align4(size );
 	b = get_block (p);
 	if (b->size >= s){
 		if (b->size - s >= ( BLOCK_SIZE + 4))
 			split_block (b,s);
 	}
 	else
 	{
 	if (b->next && b->next ->free && (b->size + BLOCK_SIZE + b->next ->size) >= s){
 		fusion(b);
 		if (b->size - s >= ( BLOCK_SIZE + 4))
 			split_block (b,s);
 		}
 	else{
 		newp = malloc(s);
 		if (! newp)
 		return (NULL );
 		new = get_block (newp );
 		copy_block (b,new );
 		free(p);
 		return (newp );
 		}
 	}
 	return (p);
 	}
 return (NULL );
}



