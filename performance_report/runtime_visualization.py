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

def filter_by_dataset(df, dataset_num):
    """
    Filter the dataframe to only include data for a specific dataset.
    
    Args:
        df: DataFrame with performance data
        dataset_num: Dataset number to filter by
        
    Returns:
        Filtered DataFrame
    """
    # Convert dataset column to int to ensure proper comparison
    df['dataset'] = df['dataset'].astype(int)
    return df[df['dataset'] == dataset_num]

def plot_single_dataset_comparison(df, dataset_num, output_dir):
    """
    Generate visualizations specifically for a single dataset.
    
    Args:
        df: DataFrame with performance data
        dataset_num: Dataset number to visualize
        output_dir: Directory to save the output files
    """
    # Filter data for the selected dataset
    dataset_df = filter_by_dataset(df, dataset_num)
    
    if len(dataset_df) == 0:
        print(f"No data found for dataset {dataset_num}")
        return None
    
    # Create dataset-specific directory
    dataset_dir = os.path.join(output_dir, f"dataset_{dataset_num}")
    os.makedirs(dataset_dir, exist_ok=True)
    
    # Bar chart of execution times
    plt.figure(figsize=(14, 8))
    dataset_df = dataset_df.sort_values(by='execution_time_ms')
    ax = sns.barplot(x='algorithm', y='execution_time_ms', data=dataset_df, 
                    palette=sns.color_palette("viridis", len(dataset_df)))
    
    plt.title(f'Execution Time by Algorithm for Dataset {dataset_num}', fontsize=16)
    plt.xlabel('Algorithm', fontsize=14)
    plt.ylabel('Execution Time (ms)', fontsize=14)
    plt.xticks(rotation=45, ha='right')
    
    # Add values on top of each bar
    for i, v in enumerate(dataset_df['execution_time_ms']):
        ax.text(i, v + 0.1, f'{v:.2f}', ha='center', fontsize=10)
    
    plt.tight_layout()
    plt.savefig(os.path.join(dataset_dir, f'dataset_{dataset_num}_execution_time.png'), dpi=300)
    plt.close()
    
    # Log scale version
    plt.figure(figsize=(14, 8))
    ax = sns.barplot(x='algorithm', y='execution_time_ms', data=dataset_df, 
                    palette=sns.color_palette("viridis", len(dataset_df)))
    plt.yscale('log')
    plt.title(f'Execution Time by Algorithm for Dataset {dataset_num} (Log Scale)', fontsize=16)
    plt.xlabel('Algorithm', fontsize=14)
    plt.ylabel('Execution Time (ms) - Log Scale', fontsize=14)
    plt.xticks(rotation=45, ha='right')
    
    # Add values on top of each bar
    for i, v in enumerate(dataset_df['execution_time_ms']):
        ax.text(i, v * 1.2, f'{v:.2f}', ha='center', fontsize=10)
    
    plt.tight_layout()
    plt.savefig(os.path.join(dataset_dir, f'dataset_{dataset_num}_execution_time_log.png'), dpi=300)
    plt.close()
    
    # Profit comparison
    plt.figure(figsize=(14, 8))
    dataset_df = dataset_df.sort_values(by='profit', ascending=False)
    ax = sns.barplot(x='algorithm', y='profit', data=dataset_df, 
                    palette=sns.color_palette("viridis", len(dataset_df)))
    
    plt.title(f'Profit by Algorithm for Dataset {dataset_num}', fontsize=16)
    plt.xlabel('Algorithm', fontsize=14)
    plt.ylabel('Profit', fontsize=14)
    plt.xticks(rotation=45, ha='right')
    
    # Add values on top of each bar
    for i, v in enumerate(dataset_df['profit']):
        ax.text(i, v * 1.01, f'{v:.1f}', ha='center', fontsize=10)
    
    plt.tight_layout()
    plt.savefig(os.path.join(dataset_dir, f'dataset_{dataset_num}_profit.png'), dpi=300)
    plt.close()
    
    # Efficiency analysis (profit / time)
    plt.figure(figsize=(14, 8))
    dataset_df['efficiency'] = dataset_df['profit'] / dataset_df['execution_time_ms']
    dataset_df = dataset_df.sort_values(by='efficiency', ascending=False)
    ax = sns.barplot(x='algorithm', y='efficiency', data=dataset_df, 
                    palette=sns.color_palette("viridis", len(dataset_df)))
    
    plt.title(f'Algorithm Efficiency for Dataset {dataset_num}', fontsize=16)
    plt.xlabel('Algorithm', fontsize=14)
    plt.ylabel('Efficiency (Profit/ms)', fontsize=14)
    plt.xticks(rotation=45, ha='right')
    
    # Add values on top of each bar
    for i, v in enumerate(dataset_df['efficiency']):
        ax.text(i, v * 1.05, f'{v:.4f}', ha='center', fontsize=10)
    
    plt.tight_layout()
    plt.savefig(os.path.join(dataset_dir, f'dataset_{dataset_num}_efficiency.png'), dpi=300)
    plt.close()
    
    # Create a simple HTML report for this dataset
    html_path = os.path.join(dataset_dir, f'dataset_{dataset_num}_report.html')
    
    with open(html_path, 'w') as f:
        f.write(f"""
        <!DOCTYPE html>
        <html>
        <head>
            <title>Dataset {dataset_num} Performance Analysis</title>
            <style>
                body {{ font-family: Arial, sans-serif; margin: 20px; }}
                h1 {{ color: #2c3e50; text-align: center; }}
                h2 {{ color: #34495e; margin-top: 30px; }}
                .figure {{ margin: 30px 0; text-align: center; }}
                .figure img {{ max-width: 100%; box-shadow: 0 0 10px rgba(0,0,0,0.1); }}
                .caption {{ font-style: italic; margin-top: 10px; }}
                table {{ width: 100%; border-collapse: collapse; margin: 20px 0; }}
                th, td {{ border: 1px solid #ddd; padding: 8px; text-align: left; }}
                th {{ background-color: #f2f2f2; }}
                tr:nth-child(even) {{ background-color: #f9f9f9; }}
            </style>
        </head>
        <body>
            <h1>Dataset {dataset_num} Performance Analysis</h1>
            
            <h2>Summary Statistics</h2>
            <p>This report presents the runtime performance analysis of different algorithms for dataset {dataset_num}.</p>
            
            <table>
                <tr>
                    <th>Algorithm</th>
                    <th>Execution Time (ms)</th>
                    <th>Profit</th>
                    <th>Efficiency (Profit/ms)</th>
                </tr>
        """)
        
        # Add rows for each algorithm
        for _, row in dataset_df.sort_values(by='execution_time_ms').iterrows():
            f.write(f"""
                <tr>
                    <td>{row['algorithm']}</td>
                    <td>{row['execution_time_ms']:.2f}</td>
                    <td>{row['profit']:.1f}</td>
                    <td>{row['efficiency']:.4f}</td>
                </tr>
            """)
        
        f.write("""
            </table>
            
            <div class="figure">
                <img src="dataset_{0}_execution_time.png" alt="Execution Time">
                <div class="caption">Execution Time by Algorithm</div>
            </div>
            
            <div class="figure">
                <img src="dataset_{0}_execution_time_log.png" alt="Execution Time (Log Scale)">
                <div class="caption">Execution Time by Algorithm (Log Scale)</div>
            </div>
            
            <div class="figure">
                <img src="dataset_{0}_profit.png" alt="Profit Comparison">
                <div class="caption">Profit by Algorithm</div>
            </div>
            
            <div class="figure">
                <img src="dataset_{0}_efficiency.png" alt="Algorithm Efficiency">
                <div class="caption">Algorithm Efficiency (Profit/ms)</div>
            </div>
            
            <h2>Conclusion</h2>
            <p>This analysis shows the performance characteristics of different knapsack algorithms on dataset {0}.
            The optimal algorithm choice depends on the specific requirements, balancing execution time and solution quality.</p>
            
            <p>Generated on: {1}</p>
        </body>
        </html>
        """.format(dataset_num, pd.Timestamp.now().strftime('%Y-%m-%d %H:%M:%S')))
    
    return html_path

def main():
    """Main function."""
    import argparse
    
    # Set up command line argument parsing
    parser = argparse.ArgumentParser(
        description='Generate runtime visualizations for knapsack algorithms'
    )
    parser.add_argument(
        '-d', '--dataset', 
        type=int, 
        help='Dataset number to analyze (if omitted, analyzes all datasets)'
    )
    parser.add_argument(
        '-f', '--file', 
        type=str, 
        help='Specific CSV file to use (if omitted, uses most recent CSV file)'
    )
    
    args = parser.parse_args()
    
    # Define paths
    project_root = Path(__file__).parent.parent
    output_dir = project_root / "performance_results"
    
    # Create output directory if it doesn't exist
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Determine which CSV file to use
    if args.file:
        csv_path = Path(args.file)
        if not csv_path.exists():
            print(f"Error: File {args.file} does not exist.")
            return
    else:
        # Look for CSV files in performance_results directory
        csv_files = list(output_dir.glob("*.csv"))
        
        if not csv_files:
            print("No CSV files found in performance_results directory.")
            print("Please run save_performance_data.py first to collect performance data.")
            return
        
        # Use the most recent CSV file
        csv_path = max(csv_files, key=os.path.getmtime)
    
    print(f"Using data from: {csv_path}")
    
    # Load the data
    df = load_performance_data(csv_path)
    
    # Check if we're analyzing a specific dataset or all datasets
    if args.dataset:
        print(f"Generating visualizations for dataset {args.dataset}...")
        html_path = plot_single_dataset_comparison(df, args.dataset, output_dir)
        
        if html_path:
            print(f"\nDataset {args.dataset} visualization complete!")
            print(f"Report generated at: {html_path}")
            print(f"All plots saved to: {os.path.dirname(html_path)}")
            print("\nYou can open the HTML report in a web browser for a comprehensive view.")
        else:
            print(f"\nNo visualizations generated for dataset {args.dataset}.")
    else:
        # Generate plots for all datasets
        print("Generating plots for all datasets...")
        plot_execution_times_by_algorithm(df, output_dir)
        plot_execution_times_by_dataset(df, output_dir)
        plot_execution_time_heatmap(df, output_dir)
        plot_algorithm_efficiency(df, output_dir)
        plot_profit_comparison(df, output_dir)
        
        # Generate HTML report
        html_path = generate_combined_report(df, output_dir)
        
        # Also generate individual dataset reports
        datasets = df['dataset'].unique()
        dataset_reports = []
        
        for dataset_num in datasets:
            print(f"Generating visualizations for dataset {dataset_num}...")
            dataset_report = plot_single_dataset_comparison(df, dataset_num, output_dir)
            if dataset_report:
                dataset_reports.append((dataset_num, dataset_report))
        
        print("\nVisualization complete!")
        print(f"All plots saved to: {output_dir}")
        print(f"Overall HTML report: {html_path}")
        
        if dataset_reports:
            print("\nIndividual dataset reports:")
            for dataset_num, report_path in dataset_reports:
                print(f"  - Dataset {dataset_num}: {report_path}")
        
        print("\nYou can open the HTML reports in a web browser for a comprehensive view.")

if __name__ == "__main__":
    main()
