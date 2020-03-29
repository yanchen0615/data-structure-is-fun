#include <iostream>

#include "heapsort.h"

int main(int argc, char **argv) {
  int n;
  std::cin >> n;
  int A[n];
  int B[n];
  int inputsize = n + n;
  for (int i = 0; i < inputsize; i++) {
    int number;
    std::cin >> number;
    // std::cout << i;
    if (i < n) {
      A[i] = number;
    } else {
      B[i - n] = number;
    }
  }

  int len = n * n + 1;
  int toSort[len];
  toSort[0] = 0;
  cartisanProduct(toSort, A, B, n);
  print_array(toSort, len);

  heapSort(toSort, len);
  print_array(toSort, len);

  for (int i = 1; i <= 5; i++) {
    std::cout << toSort[i] << ' ';
  }
  return 0;
}
