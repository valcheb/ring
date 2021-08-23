#include "ring.h"
#include <string.h>

void ring_init(ring_t *ring, uint8_t *src_buf, size_t size, size_t elem_size)
{
    ring->buffer = src_buf;
    ring->rpos = 0;
    ring->wpos = 0;
    ring->size = size;
    ring->elem_size = elem_size;
    ring->elem_number = 0;
}

bool ring_push(ring_t *ring, uint8_t *elem)
{
    if (ring_is_full(ring))
    {
        return false;
    }

    memcpy(ring->buffer + ring->wpos * ring->elem_size, elem, ring->elem_size);
    ring->elem_number++;
    ring->wpos++;

    if (ring->wpos >= ring->size)
    {
        ring->wpos = 0;
    }

    return true;
}

bool ring_pop(ring_t *ring, uint8_t *elem)
{
    if (ring_is_empty(ring))
    {
        return false;
    }

    memcpy(elem, ring->buffer + ring->rpos * ring->elem_size, ring->elem_size);
    ring->elem_number--;
    ring->rpos++;

    if (ring->rpos >= ring->size)
    {
        ring->rpos = 0;
    }

    return true;
}

bool ring_is_full(ring_t *ring)
{
    return ring->elem_number >= ring->size;
}

bool ring_is_empty(ring_t *ring)
{
    return ring->elem_number == 0;
}
