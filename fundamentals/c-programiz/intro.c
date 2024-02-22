/*
 *
 * Learn C Programming
 * C Introduction
 * https://www.programiz.com/c-programming
 *
 */

#include <stdio.h>

// C Keywords and Identifiers
void keywords(){
	int money;
	double account_balance;
}

// C Variables, Constants, and Literals

const double PI = 3.14;

void variables(){
	int player_score = 95;
	char ch = 'a';
	ch = 'b';
	printf("%c\n", ch);
}

// C Data Types

void types(){
	int i = 22; // %d, %i
	char c = 'T'; // %c
	float f = 22.442e2; // %f
	double d = 6.022; // %lf
	short int si = 1; // %hd
	unsigned int ui = 999; // %u
	long int li; // %ld, %li
	long double ld; // %Lf
}

// C Input and Output

void io(){
	printf("C Programming\n");
	float number = 2.7182818;
	printf("Float number: %f\n", number);

	int test_int;
	printf("Enter an integer: ");
	scanf("%d", &test_int);
	printf("Number = %d\n", test_int);

	int a;
	float b;
	printf("Enter integer followed by float:\n");
	scanf("%d%f", &a, &b);
	printf("You entered %d and %f\n", a, b);
}

// C Programming Operators

void operators(){
	int a = 10, b = 100;
	float c = 10.5;

	printf("++a = %d \n", ++a);
	printf("--b = %d \n", --b);

	c *= 2;
	printf("c*2 == %f \n", c);

	a = 5, b = 5, c = 10;
	int result;
	result = (a == b) && (c > b);
    printf("(a == b) && (c > b) is %d \n", result);
}

// Main 	

int main(){
	//
	return 0;
}