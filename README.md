# KnapTruck - Delivery Truck Pallet Packing Optimization

This repository contains implementations and experiments for solving a packing/knapsack-style problem (truck and pallets) using several algorithmic approaches. The project is implemented primarily in C++ with helper Python scripts and includes multiple algorithmic strategies for comparison.

## Contents

- **C++ project**: main program, modular design with separate approaches in the `Approaches/` directory.
- **Approaches**: `Greedy`, `DynamicProgramming`, `Exhaustive`, `Backtracking` implementations (see `Approaches/`).
- **Python helper**: `knapsack_solver.py` (present in `Approaches/` and `build/`) provides an alternate solver/utility.
- **Datasets**: CSV test files in the `datasets/` and `datasets-extra/` directories.

## Repository structure (important files)

- [main.cpp](main.cpp) — program entry point.
- [Approaches/](Approaches/) — contains algorithm implementations:
  - `Greedy.cpp`, `DynamicProgramming.cpp`, `Exhaustive.cpp`, `Backtracking.cpp` and headers.
- [ReadData/](ReadData/) — input parsing utilities.
- [Output/](Output/) — result and progress utilities.
- [Menu/](Menu/) — CLI / menu interface.
- [datasets/](datasets/) and [datasets-extra/](datasets-extra/) — input instances and reference optimal solutions.

## Build

### Quick build (Linux) — CMake

1. Create a build directory and run CMake:

```bash
cd /path/to/DA2025_PROJ2_G02_03

mkdir build && cd build

cmake .. && make
```

### Build output

The build will produce an executable named `DA2425_PROJ2` in the build directory (or `cmake-build-debug/` depending on your IDE).

## Running the program

### Usage

From the build directory:

```bash
./DA2425_PROJ2 [input-file] [output-file]
```

The program uses a menu-driven interface so you can also run it without arguments and follow on-screen prompts.

## Python helper

`Approaches/knapsack_solver.py` is a lightweight Python solver and utility script. Run it with Python 3:

```bash
python3 Approaches/knapsack_solver.py --help
```

(to use ILP you have to have pulp installed (pip install pulp))

## Datasets and examples
Example input files are in `datasets/` and `datasets-extra/`. Use these to test and benchmark different approaches.

### Reference outputs

Reference output files (optimal solutions) are in `datasets-extra/` (e.g., `OptimalSolution_05.txt`).

## Approaches implemented

### Greedy

- Fast heuristic; not guaranteed optimal but useful for large instances.

### Dynamic Programming

- Exact algorithm that uses DP for classic 0/1 knapsack-style instances.

### Exhaustive

- Brute-force search for small instances; guarantees optimality but exponential time.

### Backtracking

- Pruned search using bounding heuristics to reduce search space.

## Testing and evaluation

Use the datasets to compare run time and solution quality for each approach.

For reproducible experiments, run the same input across approaches and record objective value and runtime.

## Development Team

This project was developed by:

- [Francisca Portugal](https://github.com/franpts2)
- [Gabriela de Mattos](https://github.com/gab1demattos)
- [Maria Luiza Vieira](https://github.com/maluviieira)

## Course Information

Developed for the DA (Algorithm Design) course at FEUP (Faculty of Engineering, University of Porto).
