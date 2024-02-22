/*
 *
 * Learn C Programming
 * C Programming Strings
 * https://www.programiz.com/c-programming
 *
 */

#include <stdio.h>
#include <string.h>

char c[] = "c string";

// Strings

void name(){
	char name[50];
	printf("Enter name: ");
	scanf("%s", name);
	printf("Your name is %s\n", name);
}

void fullname(){
	char fullname[50];
	printf("Enter full name: ");
	fgets(fullname, sizeof(fullname), stdin);
	printf("Your full name is ");
	puts(fullname);
}

void display_string(char s[]){
	printf("String Output: ");
	puts(s);
}

// C String Functions

/*
	strlen() - string length
	strcpy() - copy string to another
	strcat() - concatenates two strings
	strcmp() - compares two strings
	strlwr() - string to lowercase
	strupr() - string to uppercase
*/

void sort_strings(){
	char str[5][50], temp[50];
	printf("Enter 5 words:\n");

   // Getting strings input
	for (int i = 0; i < 5; ++i) {
		fgets(str[i], sizeof(str[i]), stdin);
	}

   // storing strings in the lexicographical order
	for (int i = 0; i < 5; ++i) {
		for (int j = i + 1; j < 5; ++j) {
			if (strcmp(str[i], str[j]) > 0) {
				strcpy(temp, str[i]);
				strcpy(str[i], str[j]);
				strcpy(str[j], temp);
			}
		}
	}

	printf("In the lexicographical order: \n");
	for (int i = 0; i < 5; ++i) {
		fputs(str[i], stdout);
	}
}

// Main 	

int main(){
	name();
	//char greeting[] = "Salutations friend";
	//display_string(greeting);
	//sort_strings();
	return 0;
}