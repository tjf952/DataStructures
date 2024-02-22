/*
 *
 * Learn C Programming
 * C Arrays
 * https://www.programiz.com/c-programming
 *
 */

#include <stdio.h>

// One Dimensional Arrays

int data[10];

void initarray(){
	for(int i=0; i<10; ++i){
		printf("Enter value %d of the array: ", i+1);
		scanf("%d", &data[i]);
	}
}

void printarray(){
	for(int i=0; i<10; ++i){
		printf("%d ", data[i]);
	}
	printf("\n");
}

// Multi Dimensional Array

int table[3][3];

const int CITY = 3;
const int DAY = 3;

void inittable(){
	for(int i=0; i<CITY; ++i){
		for(int j=0; j<DAY; ++j){
			printf("City %d, Day %d: ", i+1, j+1);
			scanf("%d", &table[i][j]);
		}
	}
}

void printtable(){
	printf("Printing table...");
	for(int i=0; i<CITY; ++i){
		printf("City %d: [ ", i+1);
		for(int j=0; j<DAY; ++j){
			printf("%d ", table[i][j]);
		}
		printf("]\n");
	}
}

// Array Functions

int sum(int data[]){
	int sum = 0;
	for(int i=0; i<10; ++i){
		sum += data[i];
	}
	return sum;
}

void arraysum(int table[3][3]){
	int sumarray[3];
	printf("Summing...\n");
	for(int i=0; i<CITY; ++i){
		int sum = 0;
		for(int j=0; j<DAY; ++j){
			sum += table[i][j];
		}
		sumarray[i] = sum;
	}
	printf("Displaying...\n");
	for(int i=0; i<3; ++i){
		printf("%d ", sumarray[i]);
	}
	printf("\n");

}

// Main 	

int main(){
	inittable();
	printtable();
	arraysum(table);
	return 0;
}