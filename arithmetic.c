/******************************************************************************
 *
 * arithmetic.c
 *
 * Author: mSatyam
 *
 * May, 2014
 *
 * Implements functions for arithmetic operation using 'number' data type 
 * for large number arithmetic operations which usual C data-types can't handle.
 *
 *****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "arithmetic.h"

void get_number(number** num)
{
	// string buffer to hold number first
	char buf[MAX_LENGTH];

	// get number in string buffer
	fgets(buf, MAX_LENGTH, stdin);

	// validate input
	// TODO
	
	// remove newline character from the buffer
	buf[strlen(buf) - 1] = '\0';

	// insert each index of string buffer in number list
	set_number(num, buf);
}

void set_number(number** num, const char* buf)
{
	// represent's whether a number is +ve or -ve
	int sign;

	// init the number list
	(*num) = NULL;

	// get sign to be set for number
	sign = get_sign(&buf);

	// number of items to insert
	int length = strlen(buf);

	// temporary var to hold each item while list creation
	number *new = NULL;

	// add number from string to our number data struct
	for (int i = 0; i < length; i++)
	{
		new = malloc(sizeof(number));
		new->item = (int) buf[i] - 48;
		new->sign = sign;
		new->next = *(num);
		*(num) = new;
	}
}

signed int get_sign(const char **buf)
{
/* double pointer is taken as argument because we might want
 * to increment pointer by 1 byte as we don't want negative sign(-) in
 * buf ASCII value 45 as a number->item in our number list
 */
	signed int sign = 1;

	if ((**buf) == '-')
	{
		// increment buf pointer so that it points to actual number
		(*buf)++;
		sign = -1;
	}

return sign;	
}

void print(number* num)
{
	char buf[MAX_LENGTH] = {'\0'};
	char ch[2];
	
	// set sign
	int sign = num->sign;

	for (int i = 0; num != NULL; i++)
	{
		sprintf(ch,"%d", num->item);
		buf[i] = *ch;
		num = num->next;
	}

	// print in reverse order
	int len = strlen(buf);

	// append '-' in result if sign is -ve
	if (sign == -1)
		printf("-");

	for (int i = len - 1; i >= 0; i--)
		printf("%c", buf[i]);
printf("\n");		
}

void append_number(number** num, int item, int sign)
{
	if ((*num) == NULL)
	{
		(*num) = malloc(sizeof(number));
		(*num)->item = item;
		(*num)->sign = sign;
		(*num)->next = NULL;
		return;
	}

	number* crawler = *num;

	// move to the end and insert
	while(crawler->next != NULL)
		crawler = crawler->next;

	crawler->next = malloc(sizeof(number));
	crawler = crawler->next;
	crawler->item = item;
	crawler->sign = sign;
	crawler->next = NULL;
}

number* add(number* num1, number* num2)
{
	number* result = NULL;

	// check if its rather a subtraction
	if (num1->sign == -1 &&  num2->sign == 1)
	{
		// change sign of num1
		set_sign(num1, 1);

		/* call subtract with arguments swapped as num1 
		 * is to be subtracted from num1 
		 */
		result = subtract(num2, num1);
		return result;
	}
	if (num1->sign == 1 &&  num2->sign == -1)
	{
		// change sign of num1
		set_sign(num2, 1);

		// call subtract with arguments
		result = subtract(num1, num2);
		return result;
	}
	

	int sum = 0, carry = 0, item1 = 0 , item2 = 0, sign = 1;
	
	// both -ve sum also -ve
	if (num1->sign == -1 && num2->sign == -1)
		sign = -1;

	// till digits exists in any of the list
	while (num1 != NULL || num2 != NULL)
	{
		// get each digit in number lists
		if (num1 != NULL)
		{
			item1 = num1->item;
			num1 = num1->next;
		}
		else
		{
			item1 = 0;
		}

		if (num2 != NULL)
		{
			item2 = num2->item;
			num2 = num2->next;
		}
		else
		{
			item2 = 0;
		}

		// perform unit addition
		sum = item1 + item2 + carry;
	
		// make new number list using each unit data
		append_number(&result, sum % 10, sign);

		// preserve carry
		carry = (sum / 10);
	}

	// append the left over carry (if any)
	if (carry != 0)
		append_number(&result, carry, sign);

return result;
}

number* subtract(number *num1, number *num2)
{
	number* result = NULL;

	// check if its rather a addition
	if (num1->sign == -1 && num2->sign == 1)
	{
		// set num2 sign as -ve and do addition
		set_sign(num2, -1);
		result = add(num1, num2);
		return result;
		
	}
	else if(num1->sign == 1 && num2->sign == -1)
	{
		// set num2 sign as +ve and do addition
		set_sign(num2, 1);
		result = add(num1, num2);
		return result;
	}

	int diff = 0, borrow = 0, item1 = 0 , item2 = 0, sign = 0;

	// determine greater number
	int greater = greater_irrespective_of_sign(num1, num2);
	
	// first arg sent to greater_i_o_s() was greater(num1)
	if (greater == 1)
	{
		if (num1->sign == -1)
			sign = -1;
		else
			sign = 1;
	}
	// second arg sent to greater_i_o_s() was greater(num2)
	else if (greater == -1)
	{
		if (num2->sign == -1)
			sign = 1;
		else
			sign = -1;

		/* swap num1 and num2 as greater number should be pointed 
 		 * by num1 to make proper subtraction
 		 */
		number *temp = num1;
		num1 = num2;
		num2 = temp;
	}
	// both are same
	else
	{
		// answer is zero
		append_number(&result, 0, sign);
		return result;
	}


	// till digits exists in any of the list
	while (num1 != NULL || num2 != NULL)
	{
		// get each digit in number lists
		if (num1 != NULL)
		{
			item1 = num1->item;
			num1 = num1->next;
		}
		else
		{
			item1 = 0;
		}

		if (num2 != NULL)
		{
			item2 = num2->item;
			num2 = num2->next;
		}
		else
		{
			item2 = 0;
		}

		// subtract borrow from item1 left from prev subtraction
		item1 = item1 - borrow;

		// check if borrow is necessary for item1
		if (item1 < item2)
		{
			// add borrow
			item1 = item1 + 10;

			// I borrowed
			borrow = 1;
		}
		else
		{
			// I didn't borrowed
			borrow = 0;
		}

		// make unit subtraction
		diff = item1 - item2;

		// make new number list using each unit data
		append_number(&result, diff, sign);
	}

return result;
}

/*
 * Sets the sign of a number as sign in argument
 */
void set_sign(number *num, int sign)
{
	while (num != NULL)
	{
		num->sign = sign;
		num = num->next;
	}
}

/*
 * Returns 1, -1 or 0, if arg1 is greater than arg2, arg2 is 
 * greater than arg1, both are same. Ignoring sign of number.
 * This Function definetly needs improvement
 */
int greater_irrespective_of_sign(number *num1, number *num2)
{
	int num1_len = 0, num2_len = 0, greater = 0;
	short int buf_num1[MAX_LENGTH] = {0}, buf_num2[MAX_LENGTH] = {0};

	while (num1 != NULL || num2 != NULL)
	{
		if (num1 != NULL)
		{
			buf_num1[num1_len++] = num1->item;
			num1 = num1->next;
		}

		if (num2 != NULL)
		{
			buf_num2[num2_len++] = num2->item;
			num2 = num2->next;
		}
	}

	if (num1_len > num2_len)
	{
		greater = 1;
	}
	else if (num2_len > num1_len)
	{
		greater = -1;
	}
	else
	{
		for (int i = num1_len - 1; i >= 0; i--)
		{
			if (buf_num1[i] > buf_num2[i])
			{
				greater = 1;
				break;
			}
			else if (buf_num2[i] > buf_num1[i])
			{
				greater = -1;
				break;
			}
		}
	}

return greater;
}
