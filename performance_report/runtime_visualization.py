#!/usr/bin/env python3
"""
Runtime Visualization Script for Knapsack Algorithms

This script creates visualizations of algorithm runtime execution for different datasets
as part of Project 2 requirements. It works with the data collected by save_performance_data.py.
"""

import os
import sys
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from pathlib import Path

# Set up styles for better-looking charts
plt.style.use('ggplot')
sns.set_palette("viridis")
sns.set_context("talk")

def load_performance_data(filepath):
    """
    Load performance data from the CSV file.
    
    Args:
        filepath: Path to the CSV file containing performance data
        
    Returns:
        DataFrame with the performance data
    """
    try:
        df = pd.read_csv(filepath)
        print(f"Successfully loaded data with {len(df)} entries.")
        return df
    except Exception as e:
        print(f"Error loading data: {e}")
        sys.exit(1)

def plot_execution_times_by_algorithm(df, output_dir):
    """
    Generate bar chart of execution times grouped by algorithm.
    
    Args:
        df: DataFrame with performance data
        output_dir: Directory to save the output files
    """
    plt.figure(figsize=(14, 8))
    
    # Calculate average execution time by algorithm
    avg_times = df.groupby('algorithm')['execution_time_ms'].mean().sort_values()
    
    # Create the bar plot
    ax = avg_times.plot(kind='bar', color=sns.color_palette("viridis", len(avg_times)))
    
    # Add labels and title
    plt.title('Average Execution Time by Algorithm', fontsize=16)
    plt.xlabel('Algorithm', fontsize=14)
    plt.ylabel('Execution Time (ms)', fontsize=14)
    plt.xticks(rotation=45, ha='right')
    
    # Add values on top of each bar
    for i, v in enumerate(avg_times):
        ax.text(i, v + 0.1, f'{v:.2f}', ha='center', fontsize=10)
    
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'avg_execution_time_by_algorithm.png'), dpi=300)
    plt.close()
    
    # Also create a log scale version for better comparison
    plt.figure(figsize=(14, 8))
    ax = avg_times.plot(kind='bar', color=sns.color_palette("viridis", len(avg_times)))
    plt.yscale('log')
    plt.title('Average Execution Time by Algorithm (Log Scale)', fontsize=16)
    plt.xlabel('Algorithm', fontsize=14)
    plt.ylabel('Execution Time (ms) - Log Scale', fontsize=14)
    plt.xticks(rotation=45, ha='right')
    
    # Add values on top of each bar
    for i, v in enumerate(avg_times):
        ax.text(i, v * 1.2, f'{v:.2f}', ha='center', fontsize=10)
    
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'avg_execution_time_by_algorithm_log.png'), dpi=300)
    plt.close()

def plot_execution_times_by_dataset(df, output_dir):
    """
    Generate line chart showing execution times across different datasets.
    
    Args:
        df: DataFrame with performance data
        output_dir: Directory to save the output files
    """
    plt.figure(figsize=(16, 10))
    
    # Sort datasets by number to ensure correct order
    df['dataset'] = df['dataset'].astype(int)
    df = df.sort_values('dataset')
    
    # Create pivot table with datasets as columns and algorithms as rows
    pivot_df = df.pivot_table(index='algorithm', columns='dataset', values='execution_time_ms')
    
    # Plot each algorithm as a line
    for algorithm in pivot_df.index:
        plt.plot(pivot_df.columns, pivot_df.loc[algorithm], marker='o', linewidth=2, label=algorithm)
    
    plt.title('Algorithm Execution Time by Dataset', fontsize=16)
    plt.xlabel('Dataset Number', fontsize=14)
    plt.ylabel('Execution Time (ms)', fontsize=14)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend(title='Algorithm')
    plt.xticks(pivot_df.columns)
    
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'execution_time_by_dataset.png'), dpi=300)
    plt.close()
    
    # Create log scale version
    plt.figure(figsize=(16, 10))
    for algorithm in pivot_df.index:
        plt.plot(pivot_df.columns, pivot_df.loc[algorithm], marker='o', linewidth=2, label=algorithm)
    
    plt.yscale('log')
    plt.title('Algorithm Execution Time by Dataset (Log Scale)', fontsize=16)
    plt.xlabel('Dataset Number', fontsize=14)
    plt.ylabel('Execution Time (ms) - Log Scale', fontsize=14)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend(title='Algorithm')
    plt.xticks(pivot_df.columns)
    
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'execution_time_by_dataset_log.png'), dpi=300)
    plt.close()

def plot_execution_time_heatmap(df, output_dir):
    """
    Generate a heatmap showing execution times for each algorithm and dataset.
    
    Args:
        df: DataFrame with performance data
        output_dir: Directory to save the output files
    """
    plt.figure(figsize=(14, 10))
    
    # Ensure dataset is properly sorted
    df['dataset'] = df['dataset'].astype(int)
    
    # Create pivot table
    pivot_df = df.pivot_table(index='algorithm', columns='dataset', values='execution_time_ms')
    
    # Create heatmap
    sns.heatmap(pivot_df, annot=True, fmt='.2f', cmap='viridis', 
                linewidths=0.5, cbar_kws={'label': 'Execution Time (ms)'})
    
    plt.title('Execution Time Heatmap', fontsize=16)
    plt.xlabel('Dataset Number', fontsize=14)
    plt.ylabel('Algorithm', fontsize=14)
    
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'execution_time_heatmap.png'), dpi=300)
    plt.close()
    
    # Create a log-scale version
    plt.figure(figsize=(14, 10))
    log_values = np.log10(pivot_df)
    
    sns.heatmap(log_values, annot=pivot_df, fmt='.2f', cmap='viridis',
                linewidths=0.5, cbar_kws={'label': 'Log10 Execution Time'})
    
    plt.title('Execution Time Heatmap (Log Scale)', fontsize=16)
    plt.xlabel('Dataset Number', fontsize=14)
    plt.ylabel('Algorithm', fontsize=14)
    
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'execution_time_heatmap_log.png'), dpi=300)
    plt.close()

def plot_algorithm_efficiency(df, output_dir):
    """
    Plot algorithm efficiency (profit/execution time) for each algorithm.
    
    Args:
        df: DataFrame with performance data
        output_dir: Directory to save the output files
    """
    # Calculate efficiency (profit per ms)
    df['efficiency'] = df['profit'] / df['execution_time_ms']
    
    # Group by algorithm and calculate mean efficiency
    efficiency_df = df.groupby('algorithm')['efficiency'].mean().sort_values(ascending=False)
    
    plt.figure(figsize=(14, 8))
    ax = efficiency_df.plot(kind='bar', color=sns.color_palette("viridis", len(efficiency_df)))
    
    plt.title('Algorithm Efficiency (Profit/Time)', fontsize=16)
    plt.xlabel('Algorithm', fontsize=14)
    plt.ylabel('Efficiency (Profit/ms)', fontsize=14)
    plt.xticks(rotation=45, ha='right')
    
    # Add values on top of each bar
    for i, v in enumerate(efficiency_df):
        ax.text(i, v * 1.05, f'{v:.4f}', ha='center', fontsize=10)
    
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'algorithm_efficiency.png'), dpi=300)
    plt.close()

def plot_profit_comparison(df, output_dir):
    """
    Plot profit comparison between algorithms.
    
    Args:
        df: DataFrame with performance data
        output_dir: Directory to save the output files
    """
    # Calculate average profit by algorithm
    avg_profit = df.groupby('algorithm')['profit'].mean().sort_values(ascending=False)
    
    plt.figure(figsize=(14, 8))
    ax = avg_profit.plot(kind='bar', color=sns.color_palette("viridis", len(avg_profit)))
    
    plt.title('Average Profit by Algorithm', fontsize=16)
    plt.xlabel('Algorithm', fontsize=14)
    plt.ylabel('Average Profit', fontsize=14)
    plt.xticks(rotation=45, ha='right')
    
    # Add values on top of each bar
    for i, v in enumerate(avg_profit):
        ax.text(i, v * 1.01, f'{v:.1f}', ha='center', fontsize=10)
    
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'avg_profit_by_algorithm.png'), dpi=300)
    plt.close()

def generate_combined_report(df, output_dir):
    """
    Generate a comprehensive HTML report with all visualizations.
    
    Args:
        df: DataFrame with performance data
        output_dir: Directory to save the output files
    """
    # Create the HTML file
    html_path = os.path.join(output_dir, 'runtime_report.html')
    
    with open(html_path, 'w') as f:
        f.write("""
        <!DOCTYPE html>
        <html>
        <head>
            <title>Knapsack Algorithm Runtime Analysis</title>
            <style>
                body { font-family: Arial, sans-serif; margin: 20px; }
                h1 { color: #2c3e50; text-align: center; }
                h2 { color: #34495e; margin-top: 30px; }
                .figure { margin: 30px 0; text-align: center; }
                .figure img { max-width: 100%; box-shadow: 0 0 10px rgba(0,0,0,0.1); }
                .caption { font-style: italic; margin-top: 10px; }
                table { width: 100%; border-collapse: collapse; margin: 20px 0; }
                th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }
                th { background-color: #f2f2f2; }
                tr:nth-child(even) { background-color: #f9f9f9; }
            </style>
        </head>
        <body>
            <h1>Knapsack Algorithm Runtime Analysis</h1>
            
            <h2>Summary Statistics</h2>
            <p>This report presents the runtime performance analysis of different algorithms for the knapsack problem.</p>
        """)
        
        # Add summary statistics table
        f.write("<table>")
        f.write("<tr><th>Algorithm</th><th>Avg. Time (ms)</th><th>Min Time (ms)</th><th>Max Time (ms)</th><th>Avg. Profit</th></tr>")
        
        summary = df.groupby('algorithm').agg({
            'execution_time_ms': ['mean', 'min', 'max'],
            'profit': 'mean'
        })
        
        for algo in summary.index:
            avg_time = summary.loc[algo, ('execution_time_ms', 'mean')]
            min_time = summary.loc[algo, ('execution_time_ms', 'min')]
            max_time = summary.loc[algo, ('execution_time_ms', 'max')]
            avg_profit = summary.loc[algo, ('profit', 'mean')]
            
            f.write(f"<tr><td>{algo}</td><td>{avg_time:.2f}</td><td>{min_time:.2f}</td><td>{max_time:.2f}</td><td>{avg_profit:.2f}</td></tr>")
        
        f.write("</table>")
        
        # Add figures
        figures = [
            ('avg_execution_time_by_algorithm.png', 'Average Execution Time by Algorithm'),
            ('avg_execution_time_by_algorithm_log.png', 'Average Execution Time by Algorithm (Log Scale)'),
            ('execution_time_by_dataset.png', 'Execution Time by Dataset'),
            ('execution_time_by_dataset_log.png', 'Execution Time by Dataset (Log Scale)'),
            ('execution_time_heatmap.png', 'Execution Time Heatmap'),
            ('execution_time_heatmap_log.png', 'Execution Time Heatmap (Log Scale)'),
            ('algorithm_efficiency.png', 'Algorithm Efficiency (Profit/Time)'),
            ('avg_profit_by_algorithm.png', 'Average Profit by Algorithm')
        ]
        
        for filename, caption in figures:
            f.write(f"""
            <div class="figure">
                <img src="{filename}" alt="{caption}">
                <div class="caption">{caption}</div>
            </div>
            """)
        
        f.write("""
            <h2>Conclusion</h2>
            <p>This analysis shows the performance characteristics of different knapsack algorithms across various datasets.
            The optimal algorithm choice depends on the specific requirements of the application, balancing execution time and solution quality.</p>
            
            <p>Generated on: {timestamp}</p>
        </body>
        </html>
        """.format(timestamp=pd.Timestamp.now().strftime('%Y-%m-%d %H:%M:%S')))
    
    print(f"Report generated at: {html_path}")
    return html_path

def main():
    """Main function."""
    # Define paths
    project_root = Path(__file__).parent.parent
    output_dir = project_root / "performance_results"
    
    # Create output directory if it doesn't exist
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Look for CSV files in performance_results directory
    csv_files = list(output_dir.glob("*.csv"))
    
    if not csv_files:
        print("No CSV files found in performance_results directory.")
        print("Please run save_performance_data.py first to collect performance data.")
        return
    
    # Use the most recent CSV file
    latest_csv = max(csv_files, key=os.path.getmtime)
    print(f"Using data from: {latest_csv}")
    
    # Load the data
    df = load_performance_data(latest_csv)
    
    # Generate plots
    print("Generating plots...")
    plot_execution_times_by_algorithm(df, output_dir)
    plot_execution_times_by_dataset(df, output_dir)
    plot_execution_time_heatmap(df, output_dir)
    plot_algorithm_efficiency(df, output_dir)
    plot_profit_comparison(df, output_dir)
    
    # Generate HTML report
    html_path = generate_combined_report(df, output_dir)
    
    print("\nVisualization complete!")
    print(f"All plots saved to: {output_dir}")
    print(f"HTML report: {html_path}")
    print("\nYou can open the HTML report in a web browser for a comprehensive view.")

if __name__ == "__main__":
    main()
