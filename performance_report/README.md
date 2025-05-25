# Performance Analysis for Truck Packing Algorithms

This directory contains scripts to analyze the performance of different algorithms for the Truck Packing Optimization problem.

## Scripts

1. **save_performance_data.py**: Runs the truck packing program with different datasets and algorithms, collecting execution times and saving them to CSV files.

2. **visualization.py**: Generates visualizations and a comprehensive HTML report from the collected performance data.

3. **run_performance_analysis.sh**: A shell script that orchestrates the entire performance analysis process.

## How to Use

### Option 1: Run the complete analysis

```bash
# Make the script executable
chmod +x run_performance_analysis.sh

# Run the analysis
./run_performance_analysis.sh
```

This will:
1. Build the project if needed
2. Collect performance data by running all algorithms on all datasets
3. Generate visualizations
4. Create an HTML report
5. Open the report in your default browser (if supported)

### Option 2: Run the steps individually

```bash
# 1. First collect the performance data
python3 save_performance_data.py

# 2. After the data is collected, generate visualizations
python3 visualization.py /path/to/generated/csv/file
```

## Generated Visualizations

The script generates several visualizations:

1. **Execution Time per Algorithm**: Bar charts comparing execution times across algorithms.
2. **Execution Time Heatmap**: A heatmap showing execution times for each algorithm and dataset.
3. **Profit Comparison**: Bar charts comparing profit achieved by each algorithm.
4. **Algorithm Performance by Dataset**: Line charts showing how performance scales with different datasets.
5. **Algorithm Efficiency**: Charts showing efficiency (profit/time) for each algorithm.

## Requirements

- Python 3
- Required Python packages: pandas, matplotlib, seaborn
- Build of the Truck Packing project

## Note

- Some algorithms may take a long time to run on larger datasets, particularly the Exhaustive Search on datasets with many pallets.
- You can modify the `save_performance_data.py` script to run only specific algorithms or datasets if needed.
