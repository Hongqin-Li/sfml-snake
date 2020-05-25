#ifndef SRC_UTILS_NON_MOVEABLE_H_
#define SRC_UTILS_NON_MOVEABLE_H_

struct NonMoveable {
  NonMoveable() = default;
  NonMoveable(NonMoveable&&) = delete;
  NonMoveable& operator=(NonMoveable&&) = delete;
};

#endif  // SRC_UTILS_NON_MOVEABLE_H_
