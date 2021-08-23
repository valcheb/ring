#ifndef RING_H_
#define RING_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    uint8_t *buffer;
    size_t rpos;
    size_t wpos;
    size_t size;
    size_t elem_size;
    size_t elem_number;
} ring_t;

void ring_init(ring_t *ring, uint8_t *src_buf, size_t buf_size, size_t elem_size);
bool ring_push(ring_t *ring, uint8_t *elem);
bool ring_pop(ring_t *ring, uint8_t *elem);
bool ring_is_full(ring_t *ring);
bool ring_is_empty(ring_t *ring);

#endif /*RING_H_*/
