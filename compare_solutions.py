
def compare_solutions(test_cases, greedy_algorithm, optimal_algorithm):
    """
    Compare the accuracy of the greedy algorithm to the optimal algorithm.

    Args:
        test_cases (list): A list of test cases.
        greedy_algorithm (function): Function implementing the greedy algorithm.
        optimal_algorithm (function): Function implementing the optimal algorithm.

    Returns:
        dict: A dictionary containing accuracy statistics.
    """
    accuracies = []

    for test_case in test_cases:
        # Run both algorithms
        greedy_result = greedy_algorithm(test_case)
        optimal_result = optimal_algorithm(test_case)

        # Avoid division by zero
        if optimal_result == 0:
            accuracy = 1.0 if greedy_result == 0 else 0.0
        else:
            accuracy = greedy_result / optimal_result

        accuracies.append(accuracy)

    # Calculate statistics
    avg_accuracy = sum(accuracies) / len(accuracies)
    min_accuracy = min(accuracies)
    max_accuracy = max(accuracies)

    return {
        "average_accuracy": avg_accuracy,
        "minimum_accuracy": min_accuracy,
        "maximum_accuracy": max_accuracy,
        "individual_accuracies": accuracies,
    }

# Example usage
if __name__ == "__main__":
    # ...existing code for test cases, greedy_algorithm, and optimal_algorithm...
    test_cases = [...]  # Replace with actual test cases
    def greedy_algorithm(test_case):
        # ...existing code...
        pass

    def optimal_algorithm(test_case):
        # ...existing code...
        pass

    results = compare_solutions(test_cases, greedy_algorithm, optimal_algorithm)
    print("Accuracy Comparison:")
    print(f"Average Accuracy: {results['average_accuracy']:.2f}")
    print(f"Minimum Accuracy: {results['minimum_accuracy']:.2f}")
    print(f"Maximum Accuracy: {results['maximum_accuracy']:.2f}")
    print("Individual Accuracies:", results["individual_accuracies"])
