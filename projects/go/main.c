#include <immintrin.h> // AVX2 header
#include <stdio.h>
#include <time.h>

int main() {
  // Set the maximum duration for the calculation (10 seconds)
  clock_t start_time = clock();
  clock_t max_duration = 10 * CLOCKS_PER_SEC;

  // Initial Fibonacci numbers (a and b arrays for SIMD)
  __m256i a = _mm256_set_epi64x(1, 1, 0, 0); // First two Fibonacci numbers
  __m256i b = _mm256_set_epi64x(2, 3, 1, 1); // Next two Fibonacci numbers
  int count = 0;

  // Loop to calculate Fibonacci numbers in SIMD
  while (clock() - start_time < max_duration) {
    __m256i next = _mm256_add_epi64(a, b); // next = a + b
    a = b;                                 // a = b
    b = next;                              // b = next
    count += 4; // We calculated 4 Fibonacci numbers at once

    // Check the time limit after each batch of calculations
    if (clock() - start_time >= max_duration) {
      break;
    }
  }

  // Print the results
  printf("Calculated %d Fibonacci numbers in 10 seconds using SIMD (AVX2)\n",
         count);

  return 0;
}

