#include "cu_parser_demo.h"

void cu_demo_parse(bitreader_t *br, cu_demo_t *cu)
{
    /* In a real decoder, CU syntax would be parsed from the bitstream.
       Here we just consume a few bits to decide intra/inter and a dummy size. */

    u32 mode_bit = bitreader_read_bits(br, 1);
    cu->intra_flag = (mode_bit != 0);

    u32 size_code = bitreader_read_bits(br, 2); /* 0..3 */
    int size_lut[4] = { 8, 16, 32, 64 };

    cu->width  = size_lut[size_code & 3];
    cu->height = size_lut[size_code & 3];
}
