#include <stdio.h>
#include "deblock.h"

/* Clamp helper */
static inline i32 clip_i32(i32 val, i32 min_v, i32 max_v)
{
    if (val < min_v) return min_v;
    if (val > max_v) return max_v;
    return val;
}

void deblock_vertical_edge_u8(u8 *block, int stride, int edge_x)
{
    /* We assume an 8x8 block for this demo. In a real decoder this would be generic. */
    const int height = 8;

    /* Edge is between columns edge_x-1 and edge_x. We adjust p (left) and q (right). */
    if (edge_x <= 0 || edge_x >= 8)
        return;

    int px = edge_x - 1;
    int qx = edge_x;

    for (int y = 0; y < height; ++y)
    {
        u8 *row = block + y * stride;

        i32 p1 = row[px - 1 >= 0 ? px - 1 : px];
        i32 p0 = row[px];
        i32 q0 = row[qx];
        i32 q1 = row[qx + 1 < 8 ? qx + 1 : qx];

        /* Simple gradient-based decision: if edge is too strong, skip filter. */
        i32 diff_pq = (i32)p0 - (i32)q0;
        if (diff_pq < 0) diff_pq = -diff_pq;

        i32 diff_p1p0 = (i32)p1 - (i32)p0;
        if (diff_p1p0 < 0) diff_p1p0 = -diff_p1p0;

        i32 diff_q0q1 = (i32)q0 - (i32)q1;
        if (diff_q0q1 < 0) diff_q0q1 = -diff_q0q1;

        /* Tunable thresholds (simplified) */
        const i32 edge_thresh = 10;
        const i32 flat_thresh = 8;

        if (diff_pq < edge_thresh && diff_p1p0 < flat_thresh && diff_q0q1 < flat_thresh)
        {
            /* Mild filter: average with a limited strength */
            i32 avg = (p0 + q0 + 1) >> 1;

            /* Limit change to avoid over-smoothing */
            const i32 max_delta = 6;
            i32 new_p0 = clip_i32(avg, p0 - max_delta, p0 + max_delta);
            i32 new_q0 = clip_i32(avg, q0 - max_delta, q0 + max_delta);

            row[px] = (u8)clip_i32(new_p0, 0, 255);
            row[qx] = (u8)clip_i32(new_q0, 0, 255);
        }
    }
}
