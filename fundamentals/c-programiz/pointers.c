/*
 *
 * Learn C Programming
 * C Pointers
 * https://www.programiz.com/c-programming
 *
 */

#include <stdio.h>
#include <stdlib.h>

// Pointers

void pointerlogic(){
	int* pc; 
	int c;
	c = 5;
	pc = &c;
	printf("%d %p ::: %d %p \n", c, &c, *pc, pc);
}

// Pointers and Arrays

void pointerarray(){
	int x[3];
	for(int i=0; i<4; ++i){
		printf("&x[%d] = %p\n", i, &x[i]);
		printf("(x+%d) = %p\n", i, (x+i));
	}
	printf("Address of array x: %p\n", x);
}

// Pointers and Functions

void pointersum(){
	int x[5];
	int sum = 0;
	printf("Enter 5 numbers...\n");
	for(int i=0; i<5; ++i){
		scanf("%d", x+i);
		sum += *(x+i);
	}
	printf("Sum = %d\n", sum);
}

void swap(int* n1, int* n2){
	int temp;
	temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

// Memory Allocation

void memalloc(){
	int *malloc_ptr = (int*) malloc(10*sizeof(int));
	int *calloc_ptr = (int*) calloc(10, sizeof(int));

	printf("Reading in elements for malloc...\n");
	for(int i=0; i<10; ++i){
		scanf("%d", malloc_ptr+i);
	}
	printf("Printing elements for malloc...\n");
	for(int i=0; i<10; ++i){
		printf("malloc: %d\n", *(malloc_ptr+i));
	}
	printf("Printing elements for calloc...\n");
	for(int i=0; i<10; ++i){
		printf("calloc: %d\n", *(calloc_ptr+i));
	}

	free(malloc_ptr);
	free(calloc_ptr);
}

void reallocate(){
	int n1, n2;
	printf("Enter first size: ");
	scanf("%d", &n1);

	int *ptr = (int*) malloc(n1*sizeof(int));
	printf("Addresses of allocated memory:\n");
	for(int i=0; i<n1; ++i){
		printf("%p\n", ptr+i);
	}

	printf("Enter second size: ");
	scanf("%d", &n2);

	ptr = realloc(ptr, n2*sizeof(int));
	printf("Addresses of newly allocated memory:\n");
	for(int i=0; i<n2; ++i){
		printf("%p\n", ptr+i);
	}

	free(ptr);
}

// Main 	

int main(){
	//pointerlogic();
	//pointerarray();
	//pointersum();
	/*
	int num1 = 5, num2 = 10;
	swap(&num1, &num2);
	printf("num1 = %d\n", num1);
    printf("num2 = %d\n", num2);
    */
	reallocate();
	return 0;
}