# Runtime Visualization for Truck Packing Algorithms

This feature provides graphical representations of algorithm execution times for the Truck Packing Optimization project.

## Overview

The visualization script analyzes runtime performance data collected from different algorithms (Exhaustive Search, Dynamic Programming, Backtracking, Greedy approaches, and Integer Linear Programming) across various datasets (1-10).

## Features

- **Algorithm Execution Time Comparison**: Bar charts comparing average execution times across algorithms (both linear and logarithmic scales)
- **Dataset Performance Analysis**: Line charts showing how execution times scale with different dataset sizes 
- **Performance Heatmap**: Visual representation of algorithm performance across all datasets
- **Efficiency Comparison**: Analysis of algorithm efficiency (profit/time)
- **Profit Comparison**: Comparison of solution quality (profit) between algorithms
- **HTML Report**: Comprehensive report with all visualizations and summary statistics
- **Individual Dataset Analysis**: Detailed visualizations for specific datasets (1-10)

## Usage

### Option 1: Analyze a specific dataset

```bash
# Visualize a specific dataset (replace N with the dataset number, 1-10)
python3 performance_report/runtime_visualization.py --dataset N
```

This will generate detailed visualizations for the specified dataset only, including execution times, profits, and efficiency metrics.

### Option 2: Analyze all datasets (1-10)

```bash
# Generate visualizations for all datasets, including datasets 5-10 in datasets-extra
python3 performance_report/runtime_visualization.py --all-datasets
```

This will generate visualizations for all datasets 1-10, creating sample data for any datasets that don't have actual performance measurements.

### Option 3: Run the complete analysis

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

### Option 4: Specify a particular data file

```bash
# Use a specific performance data file
python3 performance_report/runtime_visualization.py --file /path/to/your/data.csv
```

You can also combine options:

```bash
# Visualize dataset 6 using a specific data file
python3 performance_report/runtime_visualization.py --dataset 6 --file /path/to/your/data.csv
```

## Output Files

All output files are stored in the `performance_results` directory:

### Overall Analysis Files
- `avg_execution_time_by_algorithm.png`: Bar chart showing average execution time by algorithm
- `avg_execution_time_by_algorithm_log.png`: Log-scale version of execution time comparison
- `execution_time_by_dataset.png`: Line chart showing execution time trends across datasets
- `execution_time_by_dataset_log.png`: Log-scale version of dataset trends
- `execution_time_heatmap.png`: Heatmap visualization of all execution times
- `execution_time_heatmap_log.png`: Log-scale version of the heatmap
- `algorithm_efficiency.png`: Efficiency comparison (profit/time)
- `avg_profit_by_algorithm.png`: Solution quality comparison
- `runtime_report.html`: Comprehensive HTML report with all visualizations

### Individual Dataset Analysis Files
For each dataset N (1-10), a directory `dataset_N` is created containing:
- `dataset_N_execution_time.png`: Execution time comparison for this dataset
- `dataset_N_execution_time_log.png`: Log-scale version of execution times
- `dataset_N_profit.png`: Profit comparison for this dataset
- `dataset_N_efficiency.png`: Efficiency analysis for this dataset
- `dataset_N_report.html`: HTML report specific to this dataset

## Dataset Support

The script supports visualization for:
- Datasets 1-4: Standard datasets in the `datasets` folder
- Datasets 5-10: Additional datasets in the `datasets-extra` folder

If actual performance data is not available for any dataset, the script will generate realistic sample data based on algorithmic complexity patterns to enable visualization.

## Requirements

- Python 3
- Required Python packages: pandas, matplotlib, seaborn
- Build of the Truck Packing project

## Notes

- Some algorithms (particularly Exhaustive Search) may take very long on larger datasets
- The logarithmic scale visualizations help compare algorithms with vastly different performance characteristics
- Sample data for datasets 5-10 is generated using realistic scaling factors based on algorithmic complexity when actual performance data is not available
