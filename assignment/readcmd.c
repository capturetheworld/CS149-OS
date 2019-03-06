#include "util.h"

/** Instruction: Assignment 3: complie like "gcc -o readcmd readcmd
 * Please note I have used a util.h as header file
 * 1)use getline to read a command line option 48,54 , check for user error like no input 
 * 1a) Convert the string to long long
 * 1b) use malloc(), remember to free them memory by calling free() it at the end of program
 * 2) put it in a long long array master_array
 * 3) add 1 to each input and assign master_array[n] =1 where n is the next index after the array is filled to signal 
 * it reaches the end of the array. This trick of mine help you to know when it reaches the end of the array
 * 4) printf the result to stdout
 *
 * */

