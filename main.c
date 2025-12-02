#include <stdio.h>
#include <string.h>
#include "codec_types.h"
#include "deblock.h"
#include "bitreader.h"
#include "cu_parser_demo.h"

static void print_block(const char *label, u8 *block, int stride)
{
    printf("%s\n", label);
    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            printf("%3d ", block[y * stride + x]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(void)
{
    /* Synthetic 8x8 block with a strong vertical edge at x = 4. */
    u8 block[8 * 8];
    int stride = 8;

    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            if (x < 4)
                block[y * stride + x] = 80;   /* left side dark */
            else
                block[y * stride + x] = 160;  /* right side bright */
        }
    }

    print_block("Before deblocking:", block, stride);
    deblock_vertical_edge_u8(block, stride, 4);
    print_block("After deblocking:", block, stride);

    u8 bitstream_data[] = { 0b10100000 }; /* mode_bit=1 (intra), size_code=01 => 16x16 */
    bitreader_t br;
    bitreader_init(&br, bitstream_data, (int)sizeof(bitstream_data));

    cu_demo_t cu = {0};
    cu_demo_parse(&br, &cu);

    printf("Parsed CU: intra_flag=%d, width=%d, height=%d\n",
           cu.intra_flag, cu.width, cu.height);

    return 0;
}
