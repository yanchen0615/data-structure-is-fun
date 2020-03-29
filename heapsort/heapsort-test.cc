// Test heap sort algorithm
#include <iostream>
#include <vector>

#include "heapsort.h"

struct TestCase {
  bool initialized = false;
  std::vector<int> array1;
  std::vector<int> array2;
  std::vector<int> answer;
};

// Read n integers from std::cin into array
bool readNumbers(std::vector<int> &array, int n) {
  for (int i = 0; i < n; i++) {
    int number;
    std::cin >> number;
    array.push_back(number);
    if (std::cin.eof() && i < n - 1) {
      return false;
    }
  }
  return true;
}

// Test data format    (Example)
// Length of array     5
// Array 1             7 3 1 5 9
// Array 2             10 6 8 2 4
// Expected answer     3 5 5 7 7
TestCase getTestCase() {
  if (std::cin.eof()) {
    return TestCase();
  }
  int length;
  std::cin >> length;
  TestCase testCase;
  testCase.initialized = false;
  if (readNumbers(testCase.array1, length) &&
      readNumbers(testCase.array2, length) &&
      readNumbers(testCase.answer, length)) {
    testCase.initialized = true;
    return testCase;
  }
  return testCase;
}

bool validate(const std::vector<int> &expected,
              const std::vector<int> &actual) {
  for (int i = 0; i < expected.size(); i++) {
    if (expected[i] != actual[i]) {
      return false;
    }
  }
  return true;
}

void printValidationError(const std::vector<int> &expected,
                          const std::vector<int> &actual) {
  std::cerr << "[ERROR] Test case failure\nexpected: ";
  for (auto num : expected) {
    std::cerr << num << ' ';
  }
  std::cerr << "\nactual: ";
  for (auto num : actual) {
    std::cerr << num << ' ';
  }
  std::cerr << std::endl;
}

int main(int argc, char **argv) {
  int pass = 0, total = 0;
  for (TestCase testCase = getTestCase(); testCase.initialized;
       testCase = getTestCase(), total++) {
    for (auto num : testCase.answer) {
      std::cout << num << ' ';
    }
    std::cout << std::endl;
    std::vector<int> cartisonArray = std::vector<int>(
        testCase.array1.size() * testCase.array2.size() + 1, 0);
    std::cout << cartisonArray.size() << std::endl;
    cartisanProduct(cartisonArray.data(), testCase.array1.data(),
                    testCase.array2.data(), testCase.array1.size());
    heapSort(cartisonArray.data(), cartisonArray.size());
    if (validate(testCase.answer, cartisonArray)) {
      pass++;
    } else {
      printValidationError(testCase.answer, cartisonArray);
    }
  }
  std::cout << pass << " / " << total << " cases passed" << std::endl;
}