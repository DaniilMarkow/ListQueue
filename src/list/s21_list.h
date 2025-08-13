#ifndef S21_LIST_H
#define S21_LIST_H

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class List {
 private:
  struct ListNode {
    T value;
    ListNode *next;
    ListNode *prev;
    ListNode(const T &val = T(), ListNode *nxt = nullptr,
             ListNode *prv = nullptr)
        : value(val), next(nxt), prev(prv) {}
  };

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  class ListConstIterator {
   public:
    using value_type = T;
    using reference = const T &;
    using pointer = const T *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    ListConstIterator(const ListNode *ptr = nullptr) : ptr_(ptr) {}
    ListConstIterator(const ListConstIterator &other) : ptr_(other.ptr_) {}
    ListConstIterator &operator=(const ListConstIterator &other) {
      if (this != &other) {
        ptr_ = other.ptr_;
      }
      return *this;
    }
    reference operator*() const {
      if (!ptr_) throw std::out_of_range("Iterator dereference null pointer");
      return ptr_->value;
    }
    pointer operator->() const {
      if (!ptr_) throw std::out_of_range("Iterator dereference null pointer");
      return &ptr_->value;
    }
    ListConstIterator &operator++() {
      if (ptr_) ptr_ = ptr_->next;
      return *this;
    }
    ListConstIterator operator++(int) {
      ListConstIterator tmp = *this;
      ++(*this);
      return tmp;
    }
    ListConstIterator &operator--() {
      if (ptr_) ptr_ = ptr_->prev;
      return *this;
    }
    ListConstIterator operator--(int) {
      ListConstIterator tmp = *this;
      --(*this);
      return tmp;
    }
    bool operator==(const ListConstIterator &other) const {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const ListConstIterator &other) const {
      return ptr_ != other.ptr_;
    }

   private:
    const ListNode *ptr_;
    friend class List;
  };

  class ListIterator {
   public:
    using value_type = T;
    using reference = T &;
    using pointer = T *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    ListIterator(ListNode *ptr = nullptr) : ptr_(ptr) {}
    ListIterator(const ListIterator &other) : ptr_(other.ptr_) {}
    ListIterator(const ListConstIterator &it)
        : ptr_(const_cast<ListNode *>(it.ptr_)) {}
    reference operator*() const {
      if (!ptr_) throw std::out_of_range("Iterator dereference null pointer");
      return ptr_->value;
    }
    pointer operator->() const {
      if (!ptr_) throw std::out_of_range("Iterator dereference null pointer");
      return &ptr_->value;
    }
    ListIterator &operator++() {
      if (ptr_) ptr_ = ptr_->next;
      return *this;
    }
    ListIterator operator++(int) {
      ListIterator tmp = *this;
      ++(*this);
      return tmp;
    }
    ListIterator &operator--() {
      if (ptr_) ptr_ = ptr_->prev;
      return *this;
    }
    ListIterator operator--(int) {
      ListIterator tmp = *this;
      --(*this);
      return tmp;
    }
    bool operator==(const ListIterator &other) const {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const ListIterator &other) const {
      return ptr_ != other.ptr_;
    }
    ListIterator &operator=(const ListIterator &other) {
      if (this != &other) {
        ptr_ = other.ptr_;
      }
      return *this;
    }

   private:
    ListNode *ptr_;
    friend class List;
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  List();
  List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List &l);
  List(List &&l);
  ~List();
  List &operator=(List &&l);

  const_reference Front() const;
  const_reference Back() const;

  iterator Begin();
  const_iterator Cbegin() const;
  iterator End() { return iterator(nullptr); }
  const_iterator Cend() const { return const_iterator(nullptr); }

  bool Empty() const { return size_ == 0 && head_ == nullptr; }
  size_type Size() const;
  size_type Max_size();

  void Clear();
  iterator Insert(iterator pos, const_reference value);
  void Erase(iterator pos);
  void Push_back(const_reference value);
  void Pop_back();
  void Push_front(const_reference value);
  void Pop_front();
  void Swap(List &other);
  void Merge(List &other);
  void Splice(iterator pos, List &other);
  void Reverse();
  void Unique();
  void Sort();

  template <typename... Args>
  iterator Insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void Insert_many_back(Args &&...args);
  template <typename... Args>
  void Insert_many_front(Args &&...args);

 private:
  ListNode *head_;
  ListNode *tail_;
  size_type size_;
};
}

#include "s21_list.tpp"

#endif