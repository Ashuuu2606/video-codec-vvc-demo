#ifndef CU_PARSER_DEMO_H
#define CU_PARSER_DEMO_H

#include "codec_types.h"
#include "bitreader.h"

/* A toy CU descriptor */
typedef struct cu_demo_t
{
    int x;
    int y;
    int width;
    int height;
    int intra_flag; /* 1 = intra, 0 = inter (for demo purposes) */
} cu_demo_t;

void cu_demo_parse(bitreader_t *br, cu_demo_t *cu);

#endif /* CU_PARSER_DEMO_H */
