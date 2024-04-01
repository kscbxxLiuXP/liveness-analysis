# Liveness Analysis

## Introduction

The program takes a simple x86 assembly file as input

```bash
gcc -S example.c
```

first create the control flow graph , export cfg as `.dot` file (graphviz) and then

```bash
dot -Tpng example.dot -o example.png
```

then do the liveness analysis on the control flow graph.

## Build

The project is built with `cmake`.

I use a third party libray `boost` to parse the assembly file.

Use the following command to build on different ARCH:

```bash
mkdir build
cd build
cmake ..
make
./liveness
```
