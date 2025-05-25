#!/usr/bin/env python3
"""
Performance Data Collector

This script runs the truck packing program for different datasets and algorithms,
collecting execution times and saving them to CSV files for later analysis.
"""

import os
import csv
import subprocess
import time
import re
from pathlib import Path

# Paths
PROJECT_ROOT = Path(__file__).parent.parent
OUTPUT_DIR = PROJECT_ROOT / "performance_results"
PROGRAM_PATH = PROJECT_ROOT / "build" / "DA2425_PROJ2"

# Ensure output directory exists
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

# Dataset numbers to test
DATASETS = range(1, 11)  # Datasets 1-10

# Algorithms to test
ALGORITHMS = [
    "Exhaustive Search",
    "Dynamic Programming",
    "Backtracking",
    "Greedy Ratio",
    "Greedy Profit",
    "Greedy Maximum",
    "Integer LP"
]

def run_algorithm_for_dataset(dataset_num, algorithm_idx):
    """Run the program with a specific dataset and algorithm and capture the results."""
    
    # Prepare the commands to simulate user input
    # Format: 
    # 2 (Use predefined dataset)
    # {dataset_num} (Dataset number)
    # {algorithm_idx + 1} (Algorithm choice)
    # 8 (Exit)
    commands = f"2\n{dataset_num}\n{algorithm_idx + 1}\n8\n"
    
    try:
        # Run the program and pass commands via stdin
        process = subprocess.Popen(
            [PROGRAM_PATH], 
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        
        # Send the commands
        stdout, stderr = process.communicate(commands, timeout=600)  # 10 minutes timeout
        
        # If it's a greedy algorithm (option 4), we need to extract which specific greedy algorithm was used
        if algorithm_idx == 3:  # "Approximation Algorithm (Greedy Approach)"
            # We need to send an additional input to select the specific greedy approach
            # For now we'll use the first option (Greedy Ratio)
            stdout, stderr = process.communicate("1\n", timeout=60)
        
        # Look for execution time in the output
        time_match = re.search(r"Execution time: ([0-9.]+) ms", stdout)
        profit_match = re.search(r"Total profit: ([0-9]+)", stdout)
        
        if time_match:
            execution_time = float(time_match.group(1))
            profit = int(profit_match.group(1)) if profit_match else 0
            return {
                "dataset": dataset_num,
                "algorithm": ALGORITHMS[algorithm_idx],
                "execution_time_ms": execution_time,
                "profit": profit
            }
        else:
            print(f"Warning: Couldn't extract execution time for dataset {dataset_num}, algorithm {ALGORITHMS[algorithm_idx]}")
            return None
            
    except subprocess.TimeoutExpired:
        process.kill()
        print(f"Error: Process timed out for dataset {dataset_num}, algorithm {ALGORITHMS[algorithm_idx]}")
        return None
    except Exception as e:
        print(f"Error running algorithm: {e}")
        return None

def run_comparison_for_dataset(dataset_num):
    """Run the comparison option which executes all algorithms."""
    
    # Prepare the commands to simulate user input
    # Format: 
    # 2 (Use predefined dataset)
    # {dataset_num} (Dataset number)
    # 6 (Compare All Algorithms)
    # Enter (to return to menu)
    # 8 (Exit)
    commands = f"2\n{dataset_num}\n6\n\n8\n"
    
    results = []
    
    try:
        # Run the program and pass commands via stdin
        process = subprocess.Popen(
            [PROGRAM_PATH], 
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        
        # Send the commands
        stdout, stderr = process.communicate(commands, timeout=1800)  # 30 minutes timeout
        
        # Parse the comparison table
        lines = stdout.split('\n')
        table_start = False
        for line in lines:
            if "Algorithm Performance Comparison:" in line:
                table_start = True
                continue
            
            if table_start and "|" in line and not "--------" in line and not "Algorithm " in line:
                parts = line.split('|')
                if len(parts) >= 3:
                    algorithm = parts[0].strip()
                    time_str = parts[1].strip()
                    profit_str = parts[2].strip()
                    
                    # Extract numeric values
                    try:
                        execution_time = float(time_str)
                        profit = int(profit_str.split()[0])  # Remove the "*" if present
                        
                        results.append({
                            "dataset": dataset_num,
                            "algorithm": algorithm,
                            "execution_time_ms": execution_time,
                            "profit": profit
                        })
                    except (ValueError, IndexError):
                        print(f"Warning: Couldn't parse result line: {line}")
        
        return results
            
    except subprocess.TimeoutExpired:
        process.kill()
        print(f"Error: Process timed out for comparison on dataset {dataset_num}")
        return []
    except Exception as e:
        print(f"Error running comparison: {e}")
        return []

def save_results_to_csv(results):
    """Save the collected results to a CSV file."""
    if not results:
        print("No results to save.")
        return
    
    timestamp = time.strftime("%Y%m%d_%H%M%S")
    filename = OUTPUT_DIR / f"performance_data_{timestamp}.csv"
    
    with open(filename, 'w', newline='') as csvfile:
        fieldnames = ["dataset", "algorithm", "execution_time_ms", "profit"]
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        
        writer.writeheader()
        for result in results:
            writer.writerow(result)
    
    print(f"Results saved to {filename}")
    return filename

def run_full_comparison():
    """Run the comparison option for all datasets and save results."""
    all_results = []
    
    for dataset_num in DATASETS:
        print(f"Running comparison for dataset {dataset_num}...")
        results = run_comparison_for_dataset(dataset_num)
        all_results.extend(results)
        
        # Save intermediate results in case of failure
        if results:
            save_results_to_csv(all_results)
            
        print(f"Completed dataset {dataset_num}. {len(results)} algorithm results collected.")
    
    return all_results

def main():
    """Main function to collect performance data."""
    print("Performance Data Collector")
    print("=========================")
    
    # Check if the program exists
    if not PROGRAM_PATH.exists():
        print(f"Error: Program not found at {PROGRAM_PATH}")
        print("Please build the project first using cmake and make.")
        return
    
    # Make the program executable if it's not
    if not os.access(PROGRAM_PATH, os.X_OK):
        os.chmod(PROGRAM_PATH, 0o755)
    
    print(f"Running comparison for all datasets...")
    results = run_full_comparison()
    
    if results:
        csv_path = save_results_to_csv(results)
        print(f"\nData collection complete. Results saved to: {csv_path}")
        print(f"Run 'python visualization.py {csv_path}' to generate visualizations.")
    else:
        print("No results were collected. Check for errors and try again.")

if __name__ == "__main__":
    main()
