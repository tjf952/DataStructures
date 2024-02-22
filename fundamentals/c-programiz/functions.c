/*
 *
 * Learn C Programming
 * C Functions
 * https://www.programiz.com/c-programming
 *
 */

#include <stdio.h>
#include <stdbool.h>

// Prototype

int addNumbers(int a, int b);

// User Defined Functions

int add_numbers(int a, int b){
	return a + b;
}

bool check_prime(){
	int n, flag = 0;

	printf("Enter a positive integer: ");
	scanf("%d", &n);

	for(int i=2; i<n/2; ++i){
		if(n%i == 0){
			printf("%d is not a prime number.", n);
			return false;
		}
	}
	printf("%d is a prime number.", n);
	return true;
}

// Recursion

int fib(int n){
	if(n <= 1) return n;
	return fib(n-1) + fib(n-2);
}

// C Storage Class

int globalvar = 5;

void display(){
	int localvar = -5;
	++globalvar;
	--localvar;
	printf("%d %d \n", globalvar, localvar);
}

void staticinit(){
	static int staticvar = 1;
	staticvar += 4;
	printf("%d \n", staticvar);
}

// Main 	

int main(){
	staticinit();
	staticinit();
	display();
	return 0;
}