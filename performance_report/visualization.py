#!/usr/bin/env python3
"""
Performance Data Visualizer

This script generates visualizations from the collected performance data.
"""

import sys
import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from pathlib import Path
import argparse

# Set up styles
plt.style.use('ggplot')
sns.set_palette("Set2")
sns.set_context("talk")

def load_data(csv_path):
    """Load performance data from a CSV file."""
    try:
        df = pd.read_csv(csv_path)
        return df
    except Exception as e:
        print(f"Error loading data: {e}")
        return None

def create_execution_time_per_algorithm_chart(df, output_dir):
    """
    Create a chart showing execution time for each algorithm across datasets.
    Uses a logarithmic scale for better visualization.
    """
    plt.figure(figsize=(14, 10))
    
    # Group by dataset and algorithm, then calculate mean time for repeated runs
    avg_times = df.groupby(['dataset', 'algorithm'])['execution_time_ms'].mean().reset_index()
    
    # Convert dataset to string for better labeling
    avg_times['dataset'] = avg_times['dataset'].astype(str)
    
    # Create the plot
    ax = sns.barplot(x='algorithm', y='execution_time_ms', hue='dataset', data=avg_times)
    
    # Use log scale for y-axis
    plt.yscale('log')
    
    # Add labels and title
    plt.title('Algorithm Execution Time by Dataset (Log Scale)')
    plt.xlabel('Algorithm')
    plt.ylabel('Execution Time (ms, log scale)')
    plt.xticks(rotation=45, ha='right')
    
    # Add a grid for better readability
    plt.grid(True, which="both", ls="--", alpha=0.3)
    
    # Adjust layout to prevent label cutoff
    plt.tight_layout()
    
    # Save the figure
    output_path = output_dir / 'execution_time_per_algorithm_log.png'
    plt.savefig(output_path, dpi=300)
    print(f"Chart saved to {output_path}")
    
    # Also create a non-log version for small datasets
    plt.figure(figsize=(14, 10))
    ax = sns.barplot(x='algorithm', y='execution_time_ms', hue='dataset', data=avg_times)
    plt.title('Algorithm Execution Time by Dataset (Linear Scale)')
    plt.xlabel('Algorithm')
    plt.ylabel('Execution Time (ms)')
    plt.xticks(rotation=45, ha='right')
    plt.grid(True, ls="--", alpha=0.3)
    plt.tight_layout()
    
    output_path = output_dir / 'execution_time_per_algorithm_linear.png'
    plt.savefig(output_path, dpi=300)
    print(f"Chart saved to {output_path}")

def create_execution_time_heatmap(df, output_dir):
    """Create a heatmap showing execution time for each algorithm and dataset."""
    plt.figure(figsize=(16, 10))
    
    # Create a pivot table with algorithms as rows and datasets as columns
    pivot = df.pivot_table(
        index='algorithm', 
        columns='dataset', 
        values='execution_time_ms', 
        aggfunc='mean'
    )
    
    # Create the heatmap with logarithmic color scale
    ax = sns.heatmap(
        pivot, 
        annot=True, 
        fmt='.2f', 
        cmap='YlOrRd', 
        norm=plt.colors.LogNorm(),
        cbar_kws={'label': 'Execution Time (ms)'}
    )
    
    # Add labels and title
    plt.title('Algorithm Execution Time Heatmap (Log Scale)')
    plt.xlabel('Dataset')
    plt.ylabel('Algorithm')
    
    # Adjust layout to prevent label cutoff
    plt.tight_layout()
    
    # Save the figure
    output_path = output_dir / 'execution_time_heatmap.png'
    plt.savefig(output_path, dpi=300)
    print(f"Heatmap saved to {output_path}")

def create_profit_comparison_chart(df, output_dir):
    """Create a chart comparing profit achieved by each algorithm."""
    plt.figure(figsize=(14, 10))
    
    # Group by dataset and algorithm, then get the mean profit
    avg_profit = df.groupby(['dataset', 'algorithm'])['profit'].mean().reset_index()
    
    # Convert dataset to string for better labeling
    avg_profit['dataset'] = avg_profit['dataset'].astype(str)
    
    # Create the plot
    ax = sns.barplot(x='algorithm', y='profit', hue='dataset', data=avg_profit)
    
    # Add labels and title
    plt.title('Profit Achieved by Each Algorithm')
    plt.xlabel('Algorithm')
    plt.ylabel('Profit')
    plt.xticks(rotation=45, ha='right')
    
    # Add a grid for better readability
    plt.grid(True, axis='y', ls="--", alpha=0.3)
    
    # Adjust layout to prevent label cutoff
    plt.tight_layout()
    
    # Save the figure
    output_path = output_dir / 'profit_comparison.png'
    plt.savefig(output_path, dpi=300)
    print(f"Profit comparison chart saved to {output_path}")

def create_algorithm_performance_by_dataset(df, output_dir):
    """
    Create line charts showing how each algorithm's performance 
    changes across datasets of different sizes.
    """
    plt.figure(figsize=(14, 10))
    
    # Group by dataset and algorithm
    dataset_perf = df.groupby(['dataset', 'algorithm'])['execution_time_ms'].mean().reset_index()
    
    # Create a line plot for each algorithm
    ax = sns.lineplot(
        x='dataset', 
        y='execution_time_ms', 
        hue='algorithm', 
        markers=True, 
        style='algorithm',
        data=dataset_perf
    )
    
    # Use log scale for y-axis
    plt.yscale('log')
    
    # Add labels and title
    plt.title('Algorithm Performance Across Datasets (Log Scale)')
    plt.xlabel('Dataset')
    plt.ylabel('Execution Time (ms, log scale)')
    
    # Add a grid for better readability
    plt.grid(True, which="both", ls="--", alpha=0.3)
    
    # Adjust layout to prevent label cutoff
    plt.tight_layout()
    
    # Save the figure
    output_path = output_dir / 'algorithm_performance_by_dataset.png'
    plt.savefig(output_path, dpi=300)
    print(f"Performance by dataset chart saved to {output_path}")

def create_efficiency_metric(df, output_dir):
    """
    Create a chart showing efficiency metric (profit/time) for each algorithm.
    This gives a sense of how efficient each algorithm is at generating profit.
    """
    plt.figure(figsize=(14, 10))
    
    # Calculate efficiency metric (profit per millisecond)
    df['efficiency'] = df['profit'] / df['execution_time_ms']
    
    # Replace infinite values (from division by zero) with NaN
    df['efficiency'] = df['efficiency'].replace([np.inf, -np.inf], np.nan)
    
    # Group by dataset and algorithm
    efficiency_data = df.groupby(['dataset', 'algorithm'])['efficiency'].mean().reset_index()
    
    # Convert dataset to string for better labeling
    efficiency_data['dataset'] = efficiency_data['dataset'].astype(str)
    
    # Create the plot
    ax = sns.barplot(x='algorithm', y='efficiency', hue='dataset', data=efficiency_data)
    
    # Add labels and title
    plt.title('Algorithm Efficiency (Profit per Millisecond)')
    plt.xlabel('Algorithm')
    plt.ylabel('Efficiency (profit/ms)')
    plt.xticks(rotation=45, ha='right')
    
    # Add a grid for better readability
    plt.grid(True, axis='y', ls="--", alpha=0.3)
    
    # Adjust layout to prevent label cutoff
    plt.tight_layout()
    
    # Save the figure
    output_path = output_dir / 'algorithm_efficiency.png'
    plt.savefig(output_path, dpi=300)
    print(f"Efficiency chart saved to {output_path}")

def create_report_html(output_dir, csv_path):
    """Create an HTML report with all visualizations and analysis."""
    
    # Get list of all charts
    charts = sorted([f for f in output_dir.glob('*.png')])
    
    # Load data for additional stats
    df = pd.read_csv(csv_path)
    
    # Calculate some statistics
    fastest_algo = df.groupby('algorithm')['execution_time_ms'].mean().idxmin()
    slowest_algo = df.groupby('algorithm')['execution_time_ms'].mean().idxmax()
    best_profit = df.groupby('algorithm')['profit'].mean().idxmax()
    
    html_content = f"""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Truck Packing Algorithm Performance Report</title>
    <style>
        body {{
            font-family: Arial, sans-serif;
            line-height: 1.6;
            margin: 0;
            padding: 20px;
            color: #333;
        }}
        .container {{
            max-width: 1200px;
            margin: 0 auto;
        }}
        h1, h2, h3 {{
            color: #2c3e50;
        }}
        .chart-container {{
            margin: 30px 0;
            text-align: center;
        }}
        .chart-container img {{
            max-width: 100%;
            height: auto;
            border: 1px solid #ddd;
            border-radius: 4px;
        }}
        .stats {{
            background-color: #f8f9fa;
            padding: 20px;
            border-radius: 4px;
            margin: 20px 0;
        }}
        table {{
            width: 100%;
            border-collapse: collapse;
            margin: 20px 0;
        }}
        table, th, td {{
            border: 1px solid #ddd;
            padding: 8px;
        }}
        th {{
            background-color: #f2f2f2;
            text-align: left;
        }}
        tr:nth-child(even) {{
            background-color: #f9f9f9;
        }}
    </style>
</head>
<body>
    <div class="container">
        <h1>Truck Packing Algorithm Performance Report</h1>
        
        <div class="stats">
            <h2>Key Findings</h2>
            <p><strong>Fastest Algorithm:</strong> {fastest_algo}</p>
            <p><strong>Slowest Algorithm:</strong> {slowest_algo}</p>
            <p><strong>Best Profit Algorithm:</strong> {best_profit}</p>
            <p>This report provides a visual analysis of the performance of different algorithms 
            for the Truck Packing Optimization problem.</p>
        </div>
        
        <h2>Performance Visualizations</h2>
"""
    
    # Add each chart to the HTML
    for chart in charts:
        chart_name = chart.stem.replace('_', ' ').title()
        html_content += f"""
        <div class="chart-container">
            <h3>{chart_name}</h3>
            <img src="{chart.name}" alt="{chart_name}">
            <p>Figure: {chart_name}</p>
        </div>
"""
    
    # Add a summary table of algorithm characteristics
    html_content += """
        <h2>Algorithm Characteristics Summary</h2>
        <table>
            <tr>
                <th>Algorithm</th>
                <th>Space Complexity</th>
                <th>Time Complexity</th>
                <th>Optimality</th>
            </tr>
            <tr>
                <td>Exhaustive Search</td>
                <td>O(2^n)</td>
                <td>O(2^n)</td>
                <td>Optimal</td>
            </tr>
            <tr>
                <td>Dynamic Programming</td>
                <td>O(nW)</td>
                <td>O(nW)</td>
                <td>Optimal</td>
            </tr>
            <tr>
                <td>Backtracking</td>
                <td>O(2^n)</td>
                <td>O(2^n)</td>
                <td>Optimal</td>
            </tr>
            <tr>
                <td>Greedy Ratio</td>
                <td>O(n log n)</td>
                <td>O(n log n)</td>
                <td>Not guaranteed optimal</td>
            </tr>
            <tr>
                <td>Greedy Profit</td>
                <td>O(n log n)</td>
                <td>O(n log n)</td>
                <td>Not guaranteed optimal</td>
            </tr>
            <tr>
                <td>Greedy Maximum</td>
                <td>O(n log n)</td>
                <td>O(n log n)</td>
                <td>Not guaranteed optimal</td>
            </tr>
            <tr>
                <td>Integer LP</td>
                <td>Depends on solver</td>
                <td>Exponential in worst case</td>
                <td>Optimal</td>
            </tr>
        </table>
        
        <h2>Conclusion</h2>
        <p>
            This performance analysis helps in understanding the trade-offs between 
            different algorithms for the Truck Packing Optimization problem. While 
            exact algorithms like Exhaustive Search, Dynamic Programming, and Backtracking 
            provide optimal solutions, they may become computationally expensive for 
            large problem instances. Approximation algorithms like the Greedy approaches 
            offer faster solutions but may not guarantee optimality.
        </p>
        <p>
            The choice of algorithm depends on the specific requirements of the application:
            <ul>
                <li>For small problems where optimality is critical: Exact algorithms</li>
                <li>For large problems where quick solutions are needed: Greedy approaches</li>
                <li>For a balance between optimality and speed: Consider Integer LP</li>
            </ul>
        </p>
    </div>
</body>
</html>
"""
    
    # Write to HTML file
    output_path = output_dir / 'performance_report.html'
    with open(output_path, 'w') as f:
        f.write(html_content)
    
    print(f"HTML report saved to {output_path}")

def main():
    """Main function to generate visualizations."""
    parser = argparse.ArgumentParser(description='Generate visualizations from performance data')
    parser.add_argument('csv_path', help='Path to the CSV file with performance data')
    args = parser.parse_args()
    
    # Convert string path to Path object
    csv_path = Path(args.csv_path)
    
    # Create output directory
    output_dir = csv_path.parent / f"visualization_{csv_path.stem}"
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Load data
    df = load_data(csv_path)
    if df is None:
        sys.exit(1)
    
    # Generate visualizations
    create_execution_time_per_algorithm_chart(df, output_dir)
    create_execution_time_heatmap(df, output_dir)
    create_profit_comparison_chart(df, output_dir)
    create_algorithm_performance_by_dataset(df, output_dir)
    create_efficiency_metric(df, output_dir)
    
    # Generate HTML report
    create_report_html(output_dir, csv_path)
    
    print(f"\nVisualization complete! Results saved to {output_dir}")
    print(f"Open {output_dir/'performance_report.html'} to view the report.")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python visualization.py <csv_path>")
        sys.exit(1)
    main()
