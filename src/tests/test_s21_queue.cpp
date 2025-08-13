#include <gtest/gtest.h>

#include "s21_queue.h"
template class s21::Queue<int>;
namespace s21 {
namespace {

TEST(QueueTest, DefaultConstructor) {
  Queue<int> q;
  EXPECT_TRUE(q.Empty());
  EXPECT_EQ(q.Size(), 0);
}

TEST(QueueTest, InitializerListConstructor) {
  Queue<int> q = {1, 2, 3, 4};
  EXPECT_EQ(q.Size(), 4);
  EXPECT_EQ(q.Front(), 1);
  EXPECT_EQ(q.Back(), 4);
}

TEST(QueueTest, CopyConstructor) {
  Queue<int> orig = {5, 6, 7};
  Queue<int> copy(orig);

  EXPECT_EQ(orig.Size(), copy.Size());
  EXPECT_EQ(orig.Front(), copy.Front());
  EXPECT_EQ(orig.Back(), copy.Back());
}

TEST(QueueTest, MoveConstructor) {
  Queue<int> orig = {8, 9, 10};
  Queue<int> moved(std::move(orig));

  EXPECT_TRUE(orig.Empty());
  EXPECT_EQ(moved.Size(), 3);
  EXPECT_EQ(moved.Front(), 8);
  EXPECT_EQ(moved.Back(), 10);
}

TEST(QueueTest, MoveAssignment) {
  Queue<int> orig = {11, 12, 13};
  Queue<int> moved;
  moved = std::move(orig);

  EXPECT_TRUE(orig.Empty());
  EXPECT_EQ(moved.Size(), 3);
  EXPECT_EQ(moved.Front(), 11);
  EXPECT_EQ(moved.Back(), 13);
}

TEST(QueueTest, FrontBack) {
  Queue<int> q = {20, 30, 40};
  EXPECT_EQ(q.Front(), 20);
  EXPECT_EQ(q.Back(), 40);

  q.Pop();
  EXPECT_EQ(q.Front(), 30);
  EXPECT_EQ(q.Back(), 40);
}

TEST(QueueTest, EmptySize) {
  Queue<int> q;
  EXPECT_TRUE(q.Empty());
  EXPECT_EQ(q.Size(), 0);

  q.Push(100);
  EXPECT_FALSE(q.Empty());
  EXPECT_EQ(q.Size(), 1);
}

TEST(QueueTest, PushPop) {
  Queue<int> q;
  q.Push(1);
  q.Push(2);
  q.Push(3);

  EXPECT_EQ(q.Front(), 1);
  EXPECT_EQ(q.Back(), 3);
  EXPECT_EQ(q.Size(), 3);

  q.Pop();
  EXPECT_EQ(q.Front(), 2);
  EXPECT_EQ(q.Size(), 2);

  q.Pop();
  q.Pop();
  EXPECT_TRUE(q.Empty());
}

TEST(QueueTest, Swap) {
  Queue<int> q1 = {1, 2, 3};
  Queue<int> q2 = {4, 5};

  q1.Swap(q2);

  EXPECT_EQ(q1.Size(), 2);
  EXPECT_EQ(q1.Front(), 4);
  EXPECT_EQ(q1.Back(), 5);

  EXPECT_EQ(q2.Size(), 3);
  EXPECT_EQ(q2.Front(), 1);
  EXPECT_EQ(q2.Back(), 3);
}

TEST(QueueTest, InsertManyBack) {
  Queue<int> q = {10, 20};
  q.Insert_many_back(30, 40, 50);

  EXPECT_EQ(q.Size(), 5);
  EXPECT_EQ(q.Front(), 10);
  EXPECT_EQ(q.Back(), 50);

  q.Pop();
  EXPECT_EQ(q.Front(), 20);

  q.Pop();
  EXPECT_EQ(q.Front(), 30);

  q.Pop();
  EXPECT_EQ(q.Front(), 40);

  q.Pop();
  EXPECT_EQ(q.Front(), 50);
}

TEST(QueueTest, FrontException) {
  Queue<int> q;
  EXPECT_THROW(q.Front(), std::out_of_range);
}

TEST(QueueTest, BackException) {
  Queue<int> q;
  EXPECT_THROW(q.Back(), std::out_of_range);
}

TEST(QueueTest, PopException) {
  Queue<int> q;
  EXPECT_THROW(q.Pop(), std::out_of_range);
}

TEST(QueueTest, LargeData) {
  Queue<int> q;
  for (int i = 0; i < 10000; ++i) {
    q.Push(i);
  }

  EXPECT_EQ(q.Size(), 10000);
  EXPECT_EQ(q.Front(), 0);
  EXPECT_EQ(q.Back(), 9999);

  for (int i = 0; i < 10000; ++i) {
    EXPECT_EQ(q.Front(), i);
    q.Pop();
  }

  EXPECT_TRUE(q.Empty());
}

}
}