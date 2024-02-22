/*
 *
 * Learn C Programming
 * C Flow Control
 * https://www.programiz.com/c-programming
 *
 */

#include <stdio.h>

// C If Else Statement

void ifelse(){
	int number;
	printf("Enter an integer: ");
	scanf("%d", &number);

	if(number < 0){
		printf("%d is a negative number\n", number);
	} else {
		printf("%d is a positive number\n", number);
	}
}

// C For Loop

void forloop(){
	for(int i=0; i<10; ++i){
		printf("%d ", i);
	}
	printf("\n");
}

// C While Loop

void whileloop(){
	int i = 0;
	while(i < 10){
		printf("%d ", i);
		++i;
	}
	printf("\n");

	double number, sum = 0;
	do {
		printf("Enter a number: ");
		scanf("%lf", &number);
		sum += number;
	} while(number != 0.0);
	printf("Sum = %.2lf\n", sum);
}

// C Break and Continue

void breakcontinue(){
	double number, sum = 0.0;
	for(int i=0; i<10; ++i){
		printf("Enter a number: ");
		scanf("%lf", &number);
		if(number == 0.0){
			printf("Exiting program...\n");
			break;
		}
		if(number < 0.0){
			printf("Continuing program without negative value...\n");
			continue;
		}
		sum += number;
	}
	printf("Sum = %.2lf", sum);
}

// C Switch Statement

void switchcase(){
	char operator;
	double n1, n2;

	printf("Enter an operator (+, -, *, /): ");
	scanf("%c", &operator);
	printf("Enter two operands: \n");
	scanf("%lf %lf", &n1, &n2);

	switch(operator){
		case '+':
			printf("%.1lf + %.1lf = %.1lf\n",n1, n2, n1+n2);
            break;
        case '-':
            printf("%.1lf - %.1lf = %.1lf\n",n1, n2, n1-n2);
            break;
        case '*':
            printf("%.1lf * %.1lf = %.1lf\n",n1, n2, n1*n2);
            break;
        case '/':
            printf("%.1lf / %.1lf = %.1lf\n",n1, n2, n1/n2);
            break;
        default:
            printf("Invalid operator used...");
	}
}

// Main 	

int main(){
	//
	return 0;
}