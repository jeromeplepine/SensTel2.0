/*
 * ringbuffer.c
 *
 *  Created on: Jun 10, 2018
 *      Author: Jerome Pare-Lepine
 *      Notes: Generic implementation ported from the web.
 *      Source: https://jlmedina123.wordpress.com/2013/08/19/circular-buffer-queue/
 */

//==============================================================================
// INCLUDES
//==============================================================================
#include <stdio.h>
#include <stdlib.h>
#include "ringbuffer.h"
#include "xil_printf.h"

void initbuffer(buffer_t *buffer, int size, u8 *array) {
    buffer->size = size;
    buffer->start = 0;
    buffer->count = 0;
    buffer->element = array;
}

int isfull(buffer_t *buffer) {
    if (buffer->count == buffer->size) {
        return 1;
    } else {
        return 0;
    }
}

int isempty(buffer_t *buffer) {
    if (buffer->count == 0) {
        return 1;
    } else {
        return 0;
    }
}

int getcount(buffer_t *buffer) {
	return buffer->count;
}

void push(buffer_t *buffer, u8 data) {
    int index;
    if (isfull(buffer)) {
        printf("Buffer overflow\n");
    } else {
        index = buffer->start + buffer->count++;
        if (index >= buffer->size) {
            index = 0;
        }
        buffer->element[index] = data;
    }
}


u8 popqueue(buffer_t *buffer) {
    u8 element;
    if (isempty(buffer)) {
        printf("Buffer underflow\n");
        return 0;
    } else {
       /* FIFO implementation */
       element = buffer->element[buffer->start];
       buffer->start++;
       buffer->count--;
       if (buffer->start == buffer->size) {
           buffer->start = 0;
       }

       return element;
    }
}

void * popstack(buffer_t *buffer) {
    int index;
    if (isempty(buffer)) {
        printf("Buffer underflow\n");
        return "0";
    } else {
        /* LIFO implementation */
        index = buffer->start + buffer->count - 1;
        if (index >= buffer->size) {
           index = buffer->count - buffer->size - 1;
        }
        buffer->count--;
        return buffer->element[index];
    }
}


