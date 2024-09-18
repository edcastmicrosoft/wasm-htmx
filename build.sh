#!/bin/bash
# clang --target=wasm32 -emit-llvm -c -S add.c
# llc -march=wasm32 -filetype=obj add.ll
# wasm-ld --no-entry --export-all -o add.wasm add.o
clang \
  --target=wasm32 \
  -O3 \
  -flto \
  -nostdlib \
  -Wl,--no-entry \
  -Wl,--export-all \
  -Wl,--lto-O3 \
  -o print.wasm \
  print.c
