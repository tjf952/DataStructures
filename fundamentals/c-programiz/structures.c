/*
 *
 * Learn C Programming
 * C Structure and Union
 * https://www.programiz.com/c-programming
 *
 */

#include <stdio.h>
#include <stdlib.h>

// Structures

struct employee {
	char name[30];
	int id;
	float salary;
};

typedef struct Distance {
	int feet;
	float inch;
} dist;

void org(){
	struct employee p1, p2, p[5];
}

void distance_sum(){
	dist d1 = (dist) {.feet=5, .inch=2.5};
	dist d2 = (dist) {.feet=4, .inch=11.0};
	dist sum;
	sum.feet = d1.feet + d2.feet;
	sum.inch = d1.inch + d2.inch;
	while(sum.inch>=12){
		++sum.feet;
		sum.inch -= 12;
	}
	printf("Sum of distances = %d\' %.1f\"\n", sum.feet, sum.inch);
}

// Structures and Pointers

struct person {
	char name[30];
	int age;
	float weight;
};

void structpointer(){
	struct person *ptr;
	int n;

	printf("Enter the number of persons: ");
	scanf("%d", &n);

	ptr = (struct person*) malloc(n * sizeof(struct person));

	for(int i=0; i<n; ++i)
	{
		printf("Enter first name, age, and weight respectively: ");
		scanf("%s %d %f", (ptr+i)->name, &(ptr+i)->age, &(ptr+i)->weight);
	}

	printf("Displaying Information:\n");
	for(int i = 0; i < n; ++i){
		printf("Name: %s\tAge: %d\tWeight: %.2f\n", (ptr+i)->name, (ptr+i)->age, (ptr+i)->weight);
	}

	free(ptr);
}

// Structures and Functions

struct student {
	char name[50];
	int age;
};

void display(struct student s){
	printf("\n---------------\n");
	printf("Student Information\n");
	printf("Name: %s", s.name);
	printf("\nAge: %d\n", s.age);
	printf("---------------\n");
}

void structfunction(){
	struct student st;
	printf("Enter name: ");
	scanf("%[^\n]%*c", st.name);
	printf("Enter age: ");
	scanf("%d", &st.age);
	display(st);
}

// Unions

union unionjob {
	char name[32];
	float salary;
	int id;
} ujob;

struct structjob {
	char name[32];
	float salary;
	int id;
} sjob;

void union_structure() {
	printf("Size of union -> %lu bytes\n", sizeof(ujob));
	printf("Size of structure -> %lu bytes\n", sizeof(sjob)); 
}

// Main 	

int main(){
	//distance_sum();
	//structpointer();
	//structfunction();
	union_structure();
	return 0;
}