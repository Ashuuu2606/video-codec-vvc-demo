
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
├
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

These files are intentionally minimal. They are designed to highlight code structure,
clarity, and the way I think about codec internals and performance, rather than to be
feature-complete.

Deblocking Filter Overview

The deblocking demo implements a simple luma-edge filter for 8-bit samples:

Operates on a configurable edge between two 4×N regions (left/right of the edge).

Uses local gradients to decide whether filtering is applied.

Applies a limited-strength adjustment to samples adjacent to the edge to smooth
visible block boundaries while preserving sharp transitions.

Is implemented in a way that is friendly to later SIMD-ization (e.g., NEON) by
using regular memory access patterns and simple arithmetic.

The structure mirrors how a real VVC deblocking stage is implemented, but the constants
and exact decision rules are intentionally simplified and not copied from any proprietary
code or specification.

Building and Running

A simple build using gcc might look like:

mkdir -p build
cd build
gcc ../main.c ../deblock.c ../bitreader.c ../cu_parser_demo.c -o vvc_demo
./vvc_demo


This will:

Construct a small synthetic 8×8 block with an artificial “blocking” edge.

Print out the block before and after deblocking.

Exercise the bitreader and CU parsing skeleton to show how the components connect.

You can adapt the build commands for clang, add -O2/-O3, or integrate these
files into a larger CMake-based project if needed.

Relation to VTM / VVdec

The conceptual structure of the code (bitreader, CU parsing hooks, deblocking pass)
is inspired by the open-source VTM and VVdec codebases. However:

All code here is written from scratch for demonstration purposes.

No proprietary or internal code from my employer is included.

Exact algorithmic details (e.g., thresholds, clipping rules, prediction modes) are
simplified and are not intended to be bit-exact with any standard or product.
