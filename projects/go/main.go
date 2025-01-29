package main

import (
	"fmt"
	"time"
)

func main() {
	// Set the maximum duration for the calculation
	maxDuration := 10 * time.Second
	startTime := time.Now()

	// Initial Fibonacci numbers
	a, b := 0, 1
	count := 0

	// Keep calculating Fibonacci numbers until 10 seconds have passed
	for time.Since(startTime) < maxDuration {
		a, b = b, a+b
		count++
	}

	// Print the results
	fmt.Printf("Calculated %d Fibonacci numbers in %v\n", count, maxDuration)
}

