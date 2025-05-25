#!/bin/bash

# Make sure we're in the project root directory
cd "$(dirname "$0")/.."

# Check if Python is available
if ! command -v python3 &> /dev/null; then
    echo "Python 3 is required but not found. Please install Python 3."
    exit 1
fi

# Check if required Python packages are installed
echo "Checking for required Python packages..."
python3 -c "import pandas, matplotlib, seaborn" 2>/dev/null || {
    echo "Installing required Python packages..."
    pip3 install pandas matplotlib seaborn
}

# Check if program is built
if [ ! -f "build/DA2425_PROJ2" ]; then
    echo "Building the project..."
    mkdir -p build
    cd build
    cmake ..
    make
    cd ..
fi

# Make script files executable
chmod +x performance_report/save_performance_data.py
chmod +x performance_report/visualization.py
chmod +x performance_report/runtime_visualization.py

# Run the data collection script
echo "Collecting performance data..."
python3 performance_report/save_performance_data.py

# Get the most recent CSV file
latest_csv=$(ls -t performance_results/*.csv 2>/dev/null | head -n 1)

if [ -z "$latest_csv" ]; then
    echo "No performance data was collected. Check for errors and try again."
    exit 1
fi

# Generate visualizations
echo "Generating visualizations from $latest_csv..."
python3 performance_report/visualization.py "$latest_csv"

# Generate runtime visualizations
echo "Generating runtime visualizations..."
python3 performance_report/runtime_visualization.py

# Open the HTML report if possible
report_dir=$(dirname "$latest_csv")/visualization_$(basename "$latest_csv" .csv)
report_html="$report_dir/performance_report.html"
runtime_html="$(dirname "$latest_csv")/runtime_report.html"

if [ -f "$report_html" ] || [ -f "$runtime_html" ]; then
    echo "Reports generated:"
    
    if [ -f "$report_html" ]; then
        echo "- Performance report: $report_html"
    fi
    
    if [ -f "$runtime_html" ]; then
        echo "- Runtime report: $runtime_html"
    fi
    
    # Try to open the reports based on the OS
    if [[ "$OSTYPE" == "darwin"* ]]; then
        # macOS
        if [ -f "$report_html" ]; then
            open "$report_html"
        fi
        if [ -f "$runtime_html" ]; then
            open "$runtime_html"
        fi
    elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
        # Linux
        if command -v xdg-open &> /dev/null; then
            if [ -f "$report_html" ]; then
                xdg-open "$report_html"
            fi
            if [ -f "$runtime_html" ]; then
                xdg-open "$runtime_html"
            fi
        else
            echo "To view the reports, open them in your browser."
        fi
    else
        echo "To view the reports, open them in your browser."
    fi
else
    echo "Failed to generate reports."
fi
