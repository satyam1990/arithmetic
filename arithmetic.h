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
	short int sign;
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
void set_number(number**, const char*);

/*
 * Appends single digit results into number list passed
 */
void append_number(number**, int, int);

/*
 * To get sum of two values of number type
 */
number* add(number*, number*);

/*
 * To get difference of two values of number type
 */
number* subtract(number*, number*);

/*
 * Prints Number variable data onto screen
 */
void print(number*);

/*
 * Gets the sign that should be set for the number -ve or +ve
 */
signed int get_sign(const char**);

/*
 * Sets the sign of a number as sign in argument
 */
void set_sign(number*, int);

/*
 * Returns 1, -1 or 0, if arg1 is greater than arg2, arg2 is 
 * greater than arg1, both are same. Ignoring sign of number.
 */
int greater_irrespective_of_sign(number*, number*);

#endif
