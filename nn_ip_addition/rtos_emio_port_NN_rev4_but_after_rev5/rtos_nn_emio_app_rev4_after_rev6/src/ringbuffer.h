/*
 * ringbuffer.h
 *
 *  Created on: Jun 10, 2018
 *      Author: Jerome Pare-Lepine
 */

#ifndef SRC_RINGBUFFER_H_
#define SRC_RINGBUFFER_H_

#include "xil_types.h"

typedef struct buffer buffer_t;

struct buffer {
    int size;
    int start;
    //int end;  // position of last element
    /* Tracking start and end of buffer would waste
     * one position. A full buffer would always have
     * to leave last position empty or otherwise
     * it would look empty. Instead this buffer uses
     * count to track if buffer is empty or full
     */
    int count; // number of elements in buffer
    /* Two ways to make buffer element type opaque
     * First is by using typedef for the element
     * pointer. Second is by using void pointer.
     */
    /* different types of buffer:
    int *element;   // array of integers
    char *element;  // array of characters
    void *element;  // array of void type (could cast to int, char, etc)
    char **element; //array of char pointers (array of strings)
    void **element; // array of void pointers
    Choosing array of void pointers since it's the most flexible */
//    void **element;
    u8 *element;	//array of u8's
};


//void initbuffer(buffer_t *buffer, int size);
void initbuffer(buffer_t *buffer, int size, u8 *array);
int isfull(buffer_t *buffer);
int isempty(buffer_t *buffer);
void push(buffer_t *buffer, u8 data);
u8 popqueue(buffer_t *buffer);
void * popstack(buffer_t *buffer);
int getcount(buffer_t *buffer);


#endif /* SRC_RINGBUFFER_H_ */
