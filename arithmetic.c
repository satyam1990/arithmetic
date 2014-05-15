/******************************************************************************
 *
 * arithmetic.c
 *
 * Author: mSatyam
 *
 * May, 2014
 *
 * Implements addition of large number which usual C data-types can't handle.
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
	buf[strlen(buf) - 1] = '\0';

	// insert each index of string buffer in number list
	insert(num, buf);
}

void insert(number** num, const char* buf)
{
	// add in reverse order so that we can easily carry and sum
	*num = malloc(sizeof(number));
	(*num)->item = (int) buf[0] - 48;
	(*num)->next = NULL;

	int length = strlen(buf);
	number *new = NULL;

	for (int i = 1; i < length; i++)
	{
		// add data to list
		new = malloc(sizeof(number));
		new->item = (int) buf[i] - 48;
		new->next = *num;
		*num = new;
	}
}

void print(number* num)
{
	char buf[MAX_LENGTH] = {'\0'};
	char ch[2];

	for (int i = 0; num != NULL; i++)
	{
		sprintf(ch,"%d", num->item);
		buf[i] = *ch;
		num = num->next;
	}

	// print in reverse order
	int len = strlen(buf);
	for (int i = len - 1; i >= 0; i--)
		printf("%c", buf[i]);
printf("\n");		
}

void put(number** num, int item)
{
	if ((*num) == NULL)
	{
		(*num) = malloc(sizeof(number));
		(*num)->item = item;
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
	crawler->next = NULL;
}

number* sum(number* num1, number* num2)
{
	number* result = NULL;
	int temp = 0, carry = 0, item1 = 0 , item2 = 0;

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
		temp = item1 + item2 + carry;
		
		// make new number list using each unit data
		put(&result, temp % 10);

		// preserve carry
		carry = temp / 10;
	}

	// put the left over carry if any
	if (carry != 0)
		put(&result, carry);

return result;
}

