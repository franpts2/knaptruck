#!/usr/bin/env python3
"""
Greedy Algorithm Comparison

This script generates visualizations specifically comparing the three greedy algorithms.
"""

import sys
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from pathlib import Path
import argparse

# Set up styles
plt.style.use('ggplot')
sns.set_palette("Set2")
sns.set_context("talk")

def compare_greedy_algorithms(csv_path, output_dir):
    """Compare the three greedy algorithms."""
    # Load data
    df = pd.read_csv(csv_path)
    
    # Filter only greedy algorithms
    greedy_df = df[df['algorithm'].str.contains('Greedy')]
    
    if len(greedy_df) == 0:
        print("No greedy algorithm data found in the CSV file.")
        return
    
    # Create output directory if it doesn't exist
    output_dir = Path(output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # 1. Execution time comparison
    plt.figure(figsize=(12, 8))
    ax = sns.barplot(x='dataset', y='execution_time_ms', hue='algorithm', data=greedy_df)
    plt.title('Execution Time Comparison of Greedy Algorithms')
    plt.xlabel('Dataset')
    plt.ylabel('Execution Time (ms)')
    plt.grid(True, axis='y', ls="--", alpha=0.3)
    plt.tight_layout()
    plt.savefig(output_dir / 'greedy_execution_time.png', dpi=300)
    print(f"Greedy execution time chart saved to {output_dir / 'greedy_execution_time.png'}")
    
    # 2. Profit comparison
    plt.figure(figsize=(12, 8))
    ax = sns.barplot(x='dataset', y='profit', hue='algorithm', data=greedy_df)
    plt.title('Profit Comparison of Greedy Algorithms')
    plt.xlabel('Dataset')
    plt.ylabel('Profit')
    plt.grid(True, axis='y', ls="--", alpha=0.3)
    plt.tight_layout()
    plt.savefig(output_dir / 'greedy_profit.png', dpi=300)
    print(f"Greedy profit chart saved to {output_dir / 'greedy_profit.png'}")
    
    # 3. Efficiency comparison (profit/time)
    greedy_df['efficiency'] = greedy_df['profit'] / greedy_df['execution_time_ms']
    plt.figure(figsize=(12, 8))
    ax = sns.barplot(x='dataset', y='efficiency', hue='algorithm', data=greedy_df)
    plt.title('Efficiency Comparison of Greedy Algorithms (Profit/ms)')
    plt.xlabel('Dataset')
    plt.ylabel('Efficiency (Profit/ms)')
    plt.grid(True, axis='y', ls="--", alpha=0.3)
    plt.tight_layout()
    plt.savefig(output_dir / 'greedy_efficiency.png', dpi=300)
    print(f"Greedy efficiency chart saved to {output_dir / 'greedy_efficiency.png'}")
    
    # 4. Create a table with statistics
    stats = pd.DataFrame()
    
    # Average execution time
    avg_time = greedy_df.groupby('algorithm')['execution_time_ms'].mean()
    stats['Avg Time (ms)'] = avg_time
    
    # Average profit
    avg_profit = greedy_df.groupby('algorithm')['profit'].mean()
    stats['Avg Profit'] = avg_profit
    
    # Efficiency
    stats['Avg Efficiency'] = avg_profit / avg_time
    
    # Win count (best profit per dataset)
    win_counts = greedy_df.loc[greedy_df.groupby('dataset')['profit'].idxmax()]['algorithm'].value_counts()
    for algo in stats.index:
        stats.loc[algo, 'Win Count'] = win_counts.get(algo, 0)
    
    # Save statistics to CSV
    stats.to_csv(output_dir / 'greedy_statistics.csv')
    print(f"Greedy statistics saved to {output_dir / 'greedy_statistics.csv'}")
    
    # Print statistics
    print("\nGreedy Algorithm Statistics:")
    print(stats)

def main():
    """Main function to compare greedy algorithms."""
    parser = argparse.ArgumentParser(description='Compare greedy algorithms')
    parser.add_argument('csv_path', help='Path to the CSV file with performance data')
    parser.add_argument('--output-dir', default='greedy_comparison', 
                      help='Directory to save outputs (default: greedy_comparison)')
    args = parser.parse_args()
    
    compare_greedy_algorithms(args.csv_path, args.output_dir)
    
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python compare_greedy.py <csv_path> [--output-dir OUTPUT_DIR]")
        sys.exit(1)
    main()
