#ifndef S21_LIST_TPP
#define S21_LIST_TPP

#include "s21_list.h"

namespace s21 {
template <typename T>
List<T>::List() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
List<T>::List(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
  for (size_type i = 0; i < n; ++i) {
    Push_back(T());
  }
}

template <typename T>
List<T>::List(std::initializer_list<value_type> const &items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (const auto &item : items) {
    Push_back(item);
  }
}

template <typename T>
List<T>::List(const List &l) : head_(nullptr), tail_(nullptr), size_(0) {
  for (const_iterator it = l.Cbegin(); it != l.Cend(); ++it) {
    Push_back(*it);
  }
}

template <typename T>
List<T>::List(List &&l) : head_(l.head_), tail_(l.tail_), size_(l.size_) {
  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.size_ = 0;
}

template <typename T>
List<T> &List<T>::operator=(List &&l) {
  if (this != &l) {
    Clear();
    head_ = l.head_;
    tail_ = l.tail_;
    size_ = l.size_;
    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.size_ = 0;
  }
  return *this;
}

template <typename T>
List<T>::~List() {
  Clear();
}

template <typename T>
typename List<T>::const_reference List<T>::Front() const {
  if (Empty()) throw std::out_of_range("List is empty");
  return head_->value;
}

template <typename T>
typename List<T>::const_reference List<T>::Back() const {
  if (Empty()) throw std::out_of_range("List is empty");
  return tail_->value;
}

template <typename T>
typename List<T>::iterator List<T>::Begin() {
  return iterator(head_);
}

template <typename T>
typename List<T>::const_iterator List<T>::Cbegin() const {
  return const_iterator(head_);
}

template <typename T>
typename List<T>::size_type List<T>::Size() const {
  return size_;
}

template <typename T>
typename List<T>::size_type List<T>::Max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(ListNode);
}

template <typename T>
void List<T>::Clear() {
  while (head_ != nullptr) {
    ListNode *tmp = head_;
    head_ = head_->next;
    delete tmp;
  }
  tail_ = nullptr;
  size_ = 0;
}

template <typename T>
typename List<T>::iterator List<T>::Insert(iterator pos,
                                           const_reference value) {
  iterator result;

  if (pos == End()) {
    Push_back(value);
    result = iterator(tail_);
  } else {
    ListNode *current = pos.ptr_;
    ListNode *new_node = new ListNode(value, current, current->prev);

    if (current->prev) {
      current->prev->next = new_node;
    } else {
      head_ = new_node;
    }
    current->prev = new_node;

    size_++;
    result = iterator(new_node);
  }
  return result;
}
template <typename T>
void List<T>::Reverse() {
  ListNode *current = head_;
  while (current) {
    std::swap(current->prev, current->next);
    current = current->prev;
  }
  std::swap(head_, tail_);
}
template <typename T>
void List<T>::Erase(iterator pos) {
  if (pos == End() || !pos.ptr_) {
    throw std::out_of_range("Cannot erase at end iterator");
  }

  if (pos.ptr_ == head_) {
    Pop_front();
  } else if (pos.ptr_ == tail_) {
    Pop_back();
  } else {
    ListNode *current = pos.ptr_;
    ListNode *prev = current->prev;
    ListNode *next = current->next;
    prev->next = next;
    next->prev = prev;

    delete current;
    size_--;
  }
}

template <typename T>
void List<T>::Pop_back() {
  if (Empty()) throw std::out_of_range("List is empty");

  ListNode *old_tail = tail_;
  tail_ = tail_->prev;
  if (tail_) {
    tail_->next = nullptr;
  } else {
    head_ = nullptr;
  }
  delete old_tail;
  size_--;
}

template <typename T>
void List<T>::Pop_front() {
  if (Empty()) throw std::out_of_range("List is empty");

  ListNode *old_head = head_;
  head_ = head_->next;
  if (head_) {
    head_->prev = nullptr;
  } else {
    tail_ = nullptr;
  }
  delete old_head;
  size_--;
}

template <typename T>
void List<T>::Push_back(const_reference value) {
  ListNode *new_node = new ListNode(value);
  if (Empty()) {
    head_ = tail_ = new_node;
  } else {
    tail_->next = new_node;
    new_node->prev = tail_;
    tail_ = new_node;
  }
  size_++;
}

template <typename T>
void List<T>::Push_front(const_reference value) {
  ListNode *new_node = new ListNode(value);
  if (Empty()) {
    head_ = tail_ = new_node;
  } else {
    new_node->next = head_;
    head_->prev = new_node;
    head_ = new_node;
  }
  size_++;
}

template <typename T>
void List<T>::Swap(List &other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <typename T>
void List<T>::Merge(List &other) {
  if (!other.Empty() && this != &other) {
    ListNode dummy;
    ListNode *current = &dummy;
    ListNode *p1 = head_;
    ListNode *p2 = other.head_;

    while (p1 && p2) {
      if (p1->value < p2->value) {
        current->next = p1;
        p1->prev = current;
        p1 = p1->next;
      } else {
        current->next = p2;
        p2->prev = current;
        p2 = p2->next;
      }
      current = current->next;
    }

    current->next = p1 ? p1 : p2;
    if (current->next) {
      current->next->prev = current;
    }

    head_ = dummy.next;
    if (head_) {
      head_->prev = nullptr;
    }

    tail_ = (p1) ? tail_ : other.tail_;
    size_ += other.size_;

    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
  }
}

template <typename T>
void List<T>::Splice(iterator pos, List &other) {
  if (!other.Empty()) {
    ListNode *other_head = other.head_;
    ListNode *other_tail = other.tail_;
    ListNode *next_node = pos.ptr_;
    ListNode *prev_node = (pos.ptr_) ? pos.ptr_->prev : tail_;

    if (prev_node) {
      prev_node->next = other_head;
    } else {
      head_ = other_head;
    }

    other_head->prev = prev_node;

    if (next_node) {
      next_node->prev = other_tail;
    } else {
      tail_ = other_tail;
    }

    other_tail->next = next_node;
    size_ += other.size_;

    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
  }
}

template <typename T>
void List<T>::Unique() {
  if (size_ >= 2) {
    ListNode *current = head_;
    while (current && current->next) {
      if (current->value == current->next->value) {
        ListNode *to_delete = current->next;
        current->next = to_delete->next;

        if (to_delete->next) {
          to_delete->next->prev = current;
        } else {
          tail_ = current;
        }

        delete to_delete;
        size_--;
      } else {
        current = current->next;
      }
    }
  }
}

template <typename T>
void List<T>::Sort() {
  if (size_ >= 2) {
    List left;
    List right;
    const size_t mid = size_ / 2;

    ListNode *current = head_;
    for (size_t i = 0; i < mid; ++i) {
      left.Push_back(current->value);
      current = current->next;
    }
    while (current) {
      right.Push_back(current->value);
      current = current->next;
    }

    left.Sort();
    right.Sort();

    Clear();
    ListNode *p1 = left.head_;
    ListNode *p2 = right.head_;

    while (p1 && p2) {
      if (p1->value < p2->value) {
        Push_back(p1->value);
        p1 = p1->next;
      } else {
        Push_back(p2->value);
        p2 = p2->next;
      }
    }

    while (p1) {
      Push_back(p1->value);
      p1 = p1->next;
    }
    while (p2) {
      Push_back(p2->value);
      p2 = p2->next;
    }

    left.head_ = left.tail_ = nullptr;
    right.head_ = right.tail_ = nullptr;
  }
}

template <typename T>
template <typename... Args>
typename List<T>::iterator List<T>::Insert_many(const_iterator pos,
                                                Args &&...args) {
  iterator mutable_pos(pos);
  iterator result = mutable_pos;
  (Insert(mutable_pos, std::forward<Args>(args)), ...);
  return result;
}

template <typename T>
template <typename... Args>
void List<T>::Insert_many_back(Args &&...args) {
  (Push_back(std::forward<Args>(args)), ...);
}

template <typename T>
template <typename... Args>
void List<T>::Insert_many_front(Args &&...args) {
  (Push_front(std::forward<Args>(args)), ...);
}
}

#endif