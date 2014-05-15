/******************************************************************************
 *
 * arithmetic.h
 *
 * Author: mSatyam
 *
 * May, 2014
 *
 * Conatins data structures and prototypes for various functions used in
 * arithmetic.c.
 *
 *****************************************************************************/

#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#define MAX_LENGTH 65535

typedef struct number
{
	int item;
	struct number* next;
}number;


/*
 * To store input in number data type
 */
void get_number(number**);

/*
 * Helping function used by get_number to actually store data in 
 * number data type
 */
void insert(number**, const char*);

/*
 * Puts single digit results in new number list passed
 */
void put(number**, int);

/*
 * To get sum of two values of number type
 */
number* sum(number*, number*);

/*
 * Prints Number variable data onto screen
 */
void print(number*);

#endif
