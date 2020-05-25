#ifndef SRC_UTILS_NON_COPYABLE_H_
#define SRC_UTILS_NON_COPYABLE_H_

struct NonCopyable {
  NonCopyable() = default;
  NonCopyable& operator = (const NonCopyable&) = delete;
  NonCopyable(const NonCopyable&) = delete;
};

#endif  // SRC_UTILS_NON_COPYABLE_H_
