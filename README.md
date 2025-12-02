# video-codec-vvc-demo
# High-Performance VVC Decoder Components (Portfolio Demo)

This repository demonstrates, in a simplified and open-source–compliant form, the kinds of
components I developed and optimized while working on a high-performance VVC (H.266) decoder
in C/ARM at Ittiam Systems.

The production code is proprietary and cannot be shared. Instead, this repository contains
clean, self-contained C examples inspired by concepts from the VTM and VVdec reference
implementations, focusing on:

- Header parsing and CABAC-style bit decoding
- Coding unit (CU) parsing and intra/inter prediction structure
- A deblocking filter to reduce visible blocking artifacts

The goal is to give a realistic view of how I design and optimize performance-critical
video codec components without exposing any confidential code.

---

## Scope of This Demonstration

In my industry work, I contributed to:

- A high-performance VVC decoder in C/ARM that significantly improved speed over baseline
  open-source implementations and enabled smooth 4K playback on constrained devices.
- Header parsing and CABAC-style algorithms that improved decode efficiency by reducing
  branching and memory traffic in bit decoding paths.
- Coding-unit parsing logic with support for intra and inter prediction, structured to be
  cache-friendly and thread-friendly.
- A deblocking filter that reduced blocking artifacts and integrated cleanly into the
  reconstruction pipeline.

This repository focuses on small, representative kernels and driver code for those areas.

---

## Repository Layout

```text
vvc-decoder-components-demo/
│
├── src/
│   ├── codec_types.h          # Common typedefs and small helpers
│   ├── bitreader.c            # Simple CABAC-style bit reader demo
│   ├── bitreader.h
│   ├── cu_parser_demo.c       # Skeleton CU parsing and prediction hooks
│   ├── cu_parser_demo.h
│   ├── deblock.c              # Deblocking filter for an 8-bit luma edge
│   ├── deblock.h
│   └── main.c                 # Driver: constructs a toy block and runs deblocking
│
└── README.md
