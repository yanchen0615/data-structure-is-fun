/**
 * Textbook example of disjoint set from Data Structures and Algorithm Analysis
 * in Java (3rd Edition)
 *
 * Written by: Yan-Song Chen
 * Created on: March 11 2019
 */

#include <iostream>
#include <limits>
#include <vector>

#include <gtest/gtest.h>

/**
 * Represents the nodes as an array of integers.
 */
class IDisjointSets {
public:
  virtual void Union(int, int) = 0;
  virtual int Find(int) = 0;
  virtual ~IDisjointSets(){};
};

/**
 * Minimal implementation of disjoint set interface.
 */
class NaiveDisjointSets : public IDisjointSets {
private:
  std::vector<int> sets_;

public:
  void Union(int root1, int root2) { sets_[root2] = root1; }
  // The recursive solution in textbook runs exhaust memory. Use iterative
  // solution instead.
  int Find(int x) {
    while (sets_[x] >= 0) {
      x = sets_[x];
    }
    return x;
  }

public:
  NaiveDisjointSets(int num_elements) : sets_(num_elements, -1) {}
};

/**
 * Disjoints sets using the height heuristic. The array stores
 * 1. Negative number -h: means the entry is root of a tree of height h.
 * 2. Non-negative number i: means that the parent of the entry is entry i.
 */
class RankHeuristicDisjointSets : public IDisjointSets {
private:
  std::vector<int> sets_;

public:
  void Union(int root1, int root2) {
    if (sets_[root2] < sets_[root1]) {
      // root2 is deeper, attach root1 under root2
      sets_[root1] = root2;
    } else {
      if (sets_[root1] == sets_[root2]) {
        // Increase the height of root1 if two roots are the same height
        sets_[root1]--;
      }
      // Attach root2 under root1
      sets_[root2] = root1;
    }
  }

  // Same implementation as NaiveDisjointSetsTest.
  int Find(int x) {
    while (sets_[x] >= 0) {
      x = sets_[x];
    }
    return x;
  }

public:
  RankHeuristicDisjointSets(int num_elements) : sets_(num_elements, -1) {}
};

/**
 * Improves the efficiency of Find operation by path compression. With such
 * technique, the negative value of sets_ is no longer the real height, but
 * a type of heuristic called "rank".
 */
class PathCompressionDisjointSets : public IDisjointSets {

private:
  std::vector<int> sets_;

public:
  // Same implementation as RankHeuristicDisjointSetsTest
  void Union(int root1, int root2) {
    if (sets_[root2] < sets_[root1]) {
      sets_[root1] = root2;
    } else {
      if (sets_[root1] == sets_[root2]) {
        sets_[root1]--;
      }
      sets_[root2] = root1;
    }
  }

  // Path compression is a very variation of the original algorithm.
  // Simply caches the root after every look up.
  int Find(int x) override {
    int root = x;
    while (sets_[root] >= 0) {
      root = sets_[root];
    }
    while (sets_[x] >= 0) {
      int temp = sets_[x];
      sets_[x] = root;
      x = temp;
    }
    return root;
  }

public:
  PathCompressionDisjointSets(int num_elements) : sets_(num_elements, -1) {}
};

TEST(NaiveDisjointSetsTest, Constructor) {
  NaiveDisjointSets djs(3);
  ASSERT_EQ(djs.Find(0), 0);
  ASSERT_EQ(djs.Find(1), 1);
  ASSERT_EQ(djs.Find(2), 2);
}

TEST(NaiveDisjointSetsTest, Union) {
  NaiveDisjointSets djs(3);
  djs.Union(0, 2);
  ASSERT_EQ(djs.Find(0), djs.Find(2));
  ASSERT_TRUE(djs.Find(0) != djs.Find(1));

  djs.Union(djs.Find(1), djs.Find(2));
  ASSERT_EQ(djs.Find(1), djs.Find(2));
  ASSERT_EQ(djs.Find(0), djs.Find(1));
}

TEST(RankHeuristicDisjointSetsTest, Constructor) {
  RankHeuristicDisjointSets djs(3);
  ASSERT_EQ(djs.Find(0), 0);
  ASSERT_EQ(djs.Find(1), 1);
  ASSERT_EQ(djs.Find(2), 2);
}

TEST(RankHeuristicDisjointSetsTest, Union) {
  RankHeuristicDisjointSets djs(3);
  djs.Union(0, 2);
  ASSERT_EQ(djs.Find(0), djs.Find(2));
  ASSERT_TRUE(djs.Find(0) != djs.Find(1));

  djs.Union(djs.Find(1), djs.Find(2));
  ASSERT_EQ(djs.Find(1), djs.Find(2));
  ASSERT_EQ(djs.Find(0), djs.Find(1));
}

TEST(PathCompressionDisjointSetsTest, Constructor) {
  PathCompressionDisjointSets djs(3);
  ASSERT_EQ(djs.Find(0), 0);
  ASSERT_EQ(djs.Find(1), 1);
  ASSERT_EQ(djs.Find(2), 2);
}

TEST(PathCompressionDisjointSetsTest, Union) {
  PathCompressionDisjointSets djs(3);
  djs.Union(0, 2);
  ASSERT_EQ(djs.Find(0), djs.Find(2));
  ASSERT_TRUE(djs.Find(0) != djs.Find(1));

  djs.Union(djs.Find(1), djs.Find(2));
  ASSERT_EQ(djs.Find(1), djs.Find(2));
  ASSERT_EQ(djs.Find(0), djs.Find(1));
}

void union_all(IDisjointSets *p_djs, int size) {
  for (int i = 1; i < size; i++) {
    p_djs->Union(p_djs->Find(i), p_djs->Find(i - 1));
  }
}

void find_all(IDisjointSets *p_djs, int size) {
  for (int i = 0; i < size; i++) {
    // std::cout << i << std::endl;
    p_djs->Find(i);
  }
}

constexpr int kMediumSize = 2048;

TEST(Benchmark, NaiveUnion) {
  IDisjointSets *p_naive_baseline = new NaiveDisjointSets(kMediumSize);
  union_all(p_naive_baseline, kMediumSize);
  delete p_naive_baseline;
}

TEST(Benchmark, NaiveFind) {
  IDisjointSets *p_naive_baseline = new NaiveDisjointSets(kMediumSize);
  union_all(p_naive_baseline, kMediumSize);
  for (int i = 0; i < 3; i++) {
    find_all(p_naive_baseline, kMediumSize);
  }
  delete p_naive_baseline;
}

TEST(Benchmark, RankHeuristicUnion) {
  IDisjointSets *p_rank_heuristic = new RankHeuristicDisjointSets(kMediumSize);
  union_all(p_rank_heuristic, kMediumSize);
  delete p_rank_heuristic;
}

TEST(Benchmark, RankHeuristicFind) {
  IDisjointSets *p_rank_heuristic = new RankHeuristicDisjointSets(kMediumSize);
  union_all(p_rank_heuristic, kMediumSize);
  for (int i = 0; i < 3; i++) {
    find_all(p_rank_heuristic, kMediumSize);
  }

  delete p_rank_heuristic;
}

TEST(Benchmark, PathCompressionUnion) {
  IDisjointSets *p_path_compression =
      new PathCompressionDisjointSets(kMediumSize);
  union_all(p_path_compression, kMediumSize);
  delete p_path_compression;
}

TEST(Benchmark, PathCompressionFind) {
  IDisjointSets *p_path_compression =
      new PathCompressionDisjointSets(kMediumSize);
  union_all(p_path_compression, kMediumSize);
  for (int i = 0; i < 3; i++) {
    find_all(p_path_compression, kMediumSize);
  }
  delete p_path_compression;
}

constexpr int kLargeSize = 10240000;

TEST(LargeSizeBenchmark, RankHeuristicUnion) {
  IDisjointSets *p_rank_heuristic = new RankHeuristicDisjointSets(kLargeSize);
  union_all(p_rank_heuristic, kLargeSize);
  find_all(p_rank_heuristic, kLargeSize);
  delete p_rank_heuristic;
}

TEST(LargeSizeBenchmark, RankHeuristicFind) {
  IDisjointSets *p_rank_heuristic = new RankHeuristicDisjointSets(kLargeSize);
  union_all(p_rank_heuristic, kLargeSize);
  for (int i = 0; i < 2; i++) {
    find_all(p_rank_heuristic, kLargeSize);
  }

  delete p_rank_heuristic;
}

TEST(LargeSizeBenchmark, PathCompressionUnion) {
  IDisjointSets *p_path_compression =
      new PathCompressionDisjointSets(kLargeSize);
  union_all(p_path_compression, kLargeSize);
  find_all(p_path_compression, kLargeSize);
  delete p_path_compression;
}

TEST(LargeSizeBenchmark, PathCompressionFind) {
  IDisjointSets *p_path_compression =
      new PathCompressionDisjointSets(kLargeSize);
  union_all(p_path_compression, kLargeSize);
  for (int i = 0; i < 2; i++) {
    find_all(p_path_compression, kLargeSize);
  }
  delete p_path_compression;
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
