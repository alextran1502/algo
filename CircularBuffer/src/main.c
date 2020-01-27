#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "circular_buffer.h"

#define BUFFER_SIZE 10
/* Structure */
typedef struct
{
    char buffer[BUFFER_SIZE];
    uint8_t write_pointer;
    uint8_t read_pointer;
    uint8_t buffer_length;
} circular_buf_t;

typedef enum
{
    BUFFER_OK = 0,
    BUFFER_ERROR,
    BUFFER_FULL,
    BUFFER_EMPTY,
} BUFFER_STATUS;

/* Prototype Functions */
BUFFER_STATUS init_buffer(circular_buf_t *buffer, uint8_t buffer_length);
BUFFER_STATUS buffer_read(circular_buf_t *buffer, char *data);
BUFFER_STATUS init_buffer(circular_buf_t *buffer, uint8_t buffer_length);
void print_buffer_info(circular_buf_t *buffer);

/* API Implementation */
BUFFER_STATUS init_buffer(circular_buf_t *buffer, uint8_t buffer_length)
{
    printf("Start Init Buffer\n");

    assert(buffer != NULL);

    buffer->write_pointer = 0;
    buffer->read_pointer = 0;
    buffer->buffer_length = buffer_length;

    for (int i = 0; i < buffer_length; i++)
    {
        buffer->buffer[i] = 0;
    }

    printf("Done Init Buffer\n");

    return BUFFER_OK;
}

BUFFER_STATUS buffer_write(circular_buf_t *buffer, uint8_t data)
{

    if (buffer == NULL)
    {
        return BUFFER_ERROR;
    }

    /* Check if buffer is full */
    uint8_t next_index = (buffer->write_pointer + 1) % buffer->buffer_length;

    if (next_index == buffer->read_pointer)
    {
        printf("Buffer is Full %d\n", next_index);
        return BUFFER_FULL;
    }

    buffer->buffer[buffer->write_pointer] = data;
    buffer->write_pointer = next_index;

    return BUFFER_OK;
}

BUFFER_STATUS buffer_read(circular_buf_t *buffer, char *data)
{
    printf("-------------------- READ \n");
    uint8_t next_index = (buffer->read_pointer + 1) % buffer->buffer_length;

    if (buffer == NULL)
    {
        return BUFFER_ERROR;
    }

    /* Check if buffer is EMPTY */
    if (buffer->read_pointer == buffer->write_pointer)
    {
        printf("BUFFER EMPTY\n");
        return BUFFER_EMPTY;
    }

    *data = buffer->buffer[buffer->read_pointer];
    buffer->read_pointer = next_index;

    return BUFFER_OK;
}
int main()
{
    BUFFER_STATUS status;

    circular_buf_t myBuffer;
    printf("Buffer address: %p\n", &myBuffer);
    uint8_t data_return;

    /* Initialization of buffer */
    status = init_buffer(&myBuffer, BUFFER_SIZE);
    if (status != BUFFER_OK)
    {
        printf("Init Buffer Failed\n");
    }

    print_buffer_info(&myBuffer);

    buffer_write(&myBuffer, 'd');
    print_buffer_info(&myBuffer);

    buffer_write(&myBuffer, 'e');
    print_buffer_info(&myBuffer);

    buffer_write(&myBuffer, 'a');
    print_buffer_info(&myBuffer);

    
    buffer_read(&myBuffer, &data_return);
    print_buffer_info(&myBuffer);
    printf("DATA %c\n", data_return);

    buffer_read(&myBuffer, &data_return);
    print_buffer_info(&myBuffer);
    printf("DATA %c\n", data_return);

    buffer_read(&myBuffer, &data_return);
    print_buffer_info(&myBuffer);
    printf("DATA %c\n", data_return);

    buffer_read(&myBuffer, &data_return);
    print_buffer_info(&myBuffer);
    printf("DATA %c\n", data_return);

    buffer_write(&myBuffer, 'd');
    print_buffer_info(&myBuffer);
    return 0;
}

void print_buffer_info(circular_buf_t *buffer)
{
    printf("\n----------Buffer Info----------\n");

    for (int i = 0; i < buffer->buffer_length; i++)
    {

        printf("|\t Buffer[%d]: %c[%d] \t|", i, buffer->buffer[i], buffer->buffer[i]);

        if (buffer->write_pointer == i)
        {
            printf(" <= WRITE|HEAD \t");
        }

        if (buffer->read_pointer == i)
        {
            printf(" <= READ|TAIL \n");
        }
        else
        {
            printf("\n");
        }
    }

    printf("write pointer: %d\n", buffer->write_pointer);
    printf("read pointer: %d\n", buffer->read_pointer);
    printf("buffer length: %d\n", buffer->buffer_length);
    printf("----------**----------\n\n");
}