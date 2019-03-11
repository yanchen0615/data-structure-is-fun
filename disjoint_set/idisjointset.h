/** Interface of disjoint set data structures
 *
 * Written by: Yan-Song Chen
 * Created on: March 10 2019
 */

#ifndef I_DISJOINT_SET_H
#define I_DISJOINT_SET_H

namespace disjoint_set {

template <typename T> class IDisjointSet {
public:
  virtual const T &Find(const T &) const = 0;
  virtual void Union(const T &, const T &) = 0;
};

} // namespace disjoint_set

#endif
