/** Unit test of ArrayDisjointSet
 *
 *  Written by: Yan-Song Chen
 *  Created on: March 10 2019
 */

#include "array_disjointset.h"
#include <gtest/gtest.h>

TEST(ArrayDisjointSetTest, Constructor) {
  disjoint_set::ArrayDisjointSet<int> djoint(3);
  ASSERT_EQ(djoint.Find(0), 0);
  ASSERT_EQ(djoint.Find(1), 1);
  ASSERT_EQ(djoint.Find(2), 2);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
