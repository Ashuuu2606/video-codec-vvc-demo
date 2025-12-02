#ifndef DEBLOCK_H
#define DEBLOCK_H

#include "codec_types.h"

/*
 * Simple 8-bit luma deblocking across a vertical edge.
 *
 * - block points to the top-left of an 8x8 block stored in raster order.
 * - stride is the line stride in samples.
 * - edge_x is the x-position of the edge (between 0..7), where filtering
 *   modifies samples on both sides of that vertical edge.
 *
 * This is a deliberately simplified model of a deblocking operation.
 */

void deblock_vertical_edge_u8(u8 *block, int stride, int edge_x);

#endif /* DEBLOCK_H */
