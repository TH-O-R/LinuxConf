#include <omp.h>
#include <stdio.h>
#include <time.h>

int main() {
  // Set the maximum duration for the calculation (10 seconds)
  clock_t start_time = clock();
  clock_t max_duration = 10 * CLOCKS_PER_SEC;

  // Initial Fibonacci numbers
  long long a = 0, b = 1;
  int count = 0;

// Parallelized Fibonacci calculation
#pragma omp parallel
  {
    long long local_a = a, local_b = b;
    int local_count = 0;

    while (clock() - start_time < max_duration) {
      local_a = local_a + local_b;
      local_b = local_a + local_b;
      local_count++;
    }

// Critical section to update the global count
#pragma omp atomic
    count += local_count;
  }

  // Print the results
  printf("Calculated %d Fibonacci numbers in 10 seconds using Multi-threading "
         "(OpenMP)\n",
         count);

  return 0;
}
