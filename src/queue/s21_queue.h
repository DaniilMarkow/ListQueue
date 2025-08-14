#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <initializer_list>
#include <iostream>

#include "../list/s21_list.h"

namespace s21 {
template <typename T>
class Queue {
 private:
  List<T> container_;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Queue() = default;
  Queue(std::initializer_list<value_type> const &items) : container_(items) {}
  Queue(const Queue &q) = default;
  Queue(Queue &&q) = default;
  ~Queue() = default;
  Queue &operator=(Queue &&q) = default;

  const_reference Front() const { return container_.Front(); }
  const_reference Back() const { return container_.Back(); }

  bool Empty() const { return container_.Empty(); }
  size_type Size() const { return container_.Size(); }

  void Push(const_reference value) { container_.Push_back(value); }
  void Pop() { container_.Pop_front(); }
  void Swap(Queue &other) { container_.Swap(other.container_); }

  template <typename... Args>
  void Insert_many_back(Args &&...args) {
    container_.Insert_many_back(std::forward<Args>(args)...);
  }
};
}  // namespace s21

#endif