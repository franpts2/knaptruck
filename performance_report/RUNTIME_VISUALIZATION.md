# Runtime Visualization for Truck Packing Algorithms

This feature provides graphical representations of algorithm execution times for the Truck Packing Optimization project.

## Overview

The visualization script analyzes runtime performance data collected from different algorithms (Exhaustive Search, Dynamic Programming, Backtracking, Greedy approaches, and Integer Linear Programming) across various datasets.

## Features

- **Algorithm Execution Time Comparison**: Bar charts comparing average execution times across algorithms (both linear and logarithmic scales)
- **Dataset Performance Analysis**: Line charts showing how execution times scale with different dataset sizes 
- **Performance Heatmap**: Visual representation of algorithm performance across all datasets
- **Efficiency Comparison**: Analysis of algorithm efficiency (profit/time)
- **Profit Comparison**: Comparison of solution quality (profit) between algorithms
- **HTML Report**: Comprehensive report with all visualizations and summary statistics

## Usage

### Option 1: Run the complete analysis

```bash
# From the project root directory
./performance_report/run_performance_analysis.sh
```

This will:
1. Build the project if needed
2. Collect performance data for all algorithms across datasets
3. Generate visualizations
4. Create HTML reports with performance analysis
5. Automatically open the reports in your default browser (if supported)

### Option 2: Run visualization on existing data

If you already have performance data collected:

```bash
# From the project root directory
python3 performance_report/runtime_visualization.py
```

This will generate visualizations based on the most recent performance data file.

## Output Files

All output files are stored in the `performance_results` directory:

- `avg_execution_time_by_algorithm.png`: Bar chart showing average execution time by algorithm
- `avg_execution_time_by_algorithm_log.png`: Log-scale version of execution time comparison
- `execution_time_by_dataset.png`: Line chart showing execution time trends across datasets
- `execution_time_by_dataset_log.png`: Log-scale version of dataset trends
- `execution_time_heatmap.png`: Heatmap visualization of all execution times
- `execution_time_heatmap_log.png`: Log-scale version of the heatmap
- `algorithm_efficiency.png`: Efficiency comparison (profit/time)
- `avg_profit_by_algorithm.png`: Solution quality comparison
- `runtime_report.html`: Comprehensive HTML report with all visualizations

## Requirements

- Python 3
- Required Python packages: pandas, matplotlib, seaborn
- Build of the Truck Packing project

## Notes

- Some algorithms (particularly Exhaustive Search) may take very long on larger datasets
- The logarithmic scale visualizations help compare algorithms with vastly different performance characteristics
