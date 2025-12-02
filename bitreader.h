#ifndef BITREADER_H
#define BITREADER_H

#include "codec_types.h"

typedef struct bitreader_t
{
    const u8 *data;
    int       size_bytes;
    int       bit_pos;   /* bit position from start: 0 .. size_bytes*8 - 1 */
} bitreader_t;

void bitreader_init(bitreader_t *br, const u8 *data, int size_bytes);
u32  bitreader_read_bits(bitreader_t *br, int num_bits);

#endif /* BITREADER_H */
