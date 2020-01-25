#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"

/* Structure */
typedef struct
{
    char *buffer;
    size_t write_pointer;
    size_t read_pointer;
    size_t buffer_length;
} circular_buf_t;

typedef enum
{
    BUFFER_OK = 0,
    BUFFER_ERROR,
    BUFFER_FULL,
    BUFFER_EMPTY,
} BUFFER_STATUS;

/* Prototype Functions */
BUFFER_STATUS init_buffer(circular_buf_t *buffer, size_t buffer_length);
void print_buffer_info(circular_buf_t *buffer);

/* API Implementation */
BUFFER_STATUS init_buffer(circular_buf_t *buffer, size_t buffer_length)
{
    printf("Start Init Buffer\n");

    assert(buffer != NULL);
    buffer->buffer = (char *)malloc(buffer_length * sizeof(char));
    for (int i = 0; i < buffer_length; i++)
    {
        buffer->buffer[i] = 'a' + i;
    }

    buffer->write_pointer = 0;
    buffer->read_pointer = 0;
    buffer->buffer_length = buffer_length;
    printf("Done Init Buffer\n");

    return BUFFER_OK;
}

int main()
{
    BUFFER_STATUS status;

    circular_buf_t myBuffer;
    printf("Buffer address: %p\n", &myBuffer);
    // print_buffer_info(&myBuffer);

    /* Initialization of buffer */
    status = init_buffer(&myBuffer, 10);
    if (status != BUFFER_OK)
    {
        printf("Init Buffer Failed\n");
    }

    print_buffer_info(&myBuffer);

    return 0;
}

void print_buffer_info(circular_buf_t *buffer)
{
    printf("\n----------Buffer Info----------\n");

    for (int i = 0; i < buffer->buffer_length; i++)
    {
        printf("Buffer[%d]: %c\n", i, buffer->buffer[i]);
    }

    printf("write pointer: %ld\n", buffer->write_pointer);
    printf("read pointer: %ld\n", buffer->read_pointer);
    printf("buffer length: %ld\n", buffer->buffer_length);
    printf("----------**----------\n\n");
}