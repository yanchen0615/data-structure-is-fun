/** Simplest disjoint set implemented using array.
 *
 * Written by: Yan-Song Chen, iSee AI Inc.
 * Created on: March 10 2019
 */

#ifndef ARRAY_DISJOINT_SET_H
#define ARRAY_DISJOINT_SET_H

#include "idisjointset.h"

#include <iostream>
#include <vector>

namespace disjoint_set {

/** Implements disjoint set with an array.
 *
 * Note that it is not possible to separate header and implementation of
 * a template class.
 */
template <typename T> class ArrayDisjointSet : public IDisjointSet<T> {
  // Implements pure virtual functions
public:
  const T &Find(const T &) const override;
  void Union(const T &, const T &) override;

  // Constructor
public:
  ArrayDisjointSet(int num_elements);

  // Member variables
private:
  std::vector<T> s_;

  template <typename U>
  friend std::ostream &operator<<(std::ostream &, const ArrayDisjointSet<U> &);
};

template <typename T>
ArrayDisjointSet<T>::ArrayDisjointSet(int num_elements)
    : s_(num_elements, -1) {}

template <typename T> const T &ArrayDisjointSet<T>::Find(const T &x) const {
  if (s_[x] < 0) {
    return x;
  } else {
    return Find(s_[x]);
  }
}

template <typename T>
void ArrayDisjointSet<T>::Union(const T &root1, const T &root2) {
  s_[root1] = root2;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const ArrayDisjointSet<T> &obj) {
  os << obj.s_.size();
  return os;
}

} // namespace disjoint_set

#endif
