/******************************************************************************
 *
 * main.c
 *
 * Author: mSatyam
 *
 * May, 2014
 *
 * Shows how to use data type 'number' used to do big calculations.
 *
 *****************************************************************************/

#include <stdio.h>
#include "arithmetic.h"

int main()
{
	number* num1, *num2, *result;

	// get two numbers	
	printf("Enter a number: ");
	get_number(&num1);
	printf("Enter another number: ");
	get_number(&num2);

	// perform sum and display
	result = add(num1, num2);
	print(result);

return 0;
}
