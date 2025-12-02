#include "bitreader.h"

void bitreader_init(bitreader_t *br, const u8 *data, int size_bytes)
{
    br->data       = data;
    br->size_bytes = size_bytes;
    br->bit_pos    = 0;
}

u32 bitreader_read_bits(bitreader_t *br, int num_bits)
{
    u32 val = 0;
    for (int i = 0; i < num_bits; ++i)
    {
        if (br->bit_pos >= br->size_bytes * 8)
            break;

        int byte_idx = br->bit_pos >> 3;
        int bit_idx  = 7 - (br->bit_pos & 7); /* MSB-first */

        u8 byte = br->data[byte_idx];
        u32 bit = (byte >> bit_idx) & 1u;

        val = (val << 1) | bit;
        br->bit_pos++;
    }
    return val;
}
