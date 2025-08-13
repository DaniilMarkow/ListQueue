#include <gtest/gtest.h>

#include <list>

#include "../list/s21_list.h"
template class s21::List<int>;

template <typename T>
void CompareLists(const s21::List<T> &s21_list, const std::list<T> &std_list) {
  ASSERT_EQ(s21_list.Size(), std_list.size());
  auto s21_it = s21_list.Cbegin();
  auto std_it = std_list.begin();
  while (s21_it != s21_list.Cend() && std_it != std_list.end()) {
    ASSERT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  ASSERT_EQ(s21_list.Empty(), std_list.empty());
  if (!s21_list.Empty()) {
    ASSERT_EQ(s21_list.Front(), std_list.front());
    ASSERT_EQ(s21_list.Back(), std_list.back());
  }
}
TEST(ListTest, DefaultConstructor) {
  s21::List<int> s21_l;
  std::list<int> std_l;
  CompareLists(s21_l, std_l);
  ASSERT_TRUE(s21_l.Empty());
  ASSERT_EQ(s21_l.Size(), 0U);
}

TEST(ListTest, ParameterizedConstructor) {
  s21::List<int> s21_l(5);
  std::list<int> std_l(5);
  CompareLists(s21_l, std_l);
  ASSERT_EQ(s21_l.Size(), 5U);
  ASSERT_EQ(s21_l.Front(), 0);
  ASSERT_EQ(s21_l.Back(), 0);

  s21::List<int> s21_empty(0);
  std::list<int> std_empty(0);
  CompareLists(s21_empty, std_empty);
  ASSERT_TRUE(s21_empty.Empty());

  s21::List<int> s21_large(1000);
  ASSERT_EQ(s21_large.Size(), 1000U);
}

TEST(ListTest, InitializerListConstructor) {
  s21::List<int> s21_l = {1, 2, 3, 4};
  std::list<int> std_l = {1, 2, 3, 4};
  CompareLists(s21_l, std_l);
  ASSERT_EQ(s21_l.Size(), 4U);
  ASSERT_EQ(s21_l.Front(), 1);
  ASSERT_EQ(s21_l.Back(), 4);

  s21::List<int> s21_empty = {};
  std::list<int> std_empty = {};
  CompareLists(s21_empty, std_empty);
  ASSERT_TRUE(s21_empty.Empty());
}

TEST(ListTest, CopyConstructor) {
  s21::List<int> s21_src = {1, 2, 3};
  s21::List<int> s21_copy(s21_src);
  std::list<int> std_src = {1, 2, 3};
  std::list<int> std_copy(std_src);
  CompareLists(s21_copy, std_copy);
  ASSERT_EQ(s21_copy.Size(), 3U);

  s21_src.Push_back(4);
  ASSERT_EQ(s21_copy.Size(), 3U);
  ASSERT_EQ(s21_copy.Back(), 3);

  s21::List<int> s21_empty;
  s21::List<int> s21_empty_copy(s21_empty);
  ASSERT_TRUE(s21_empty_copy.Empty());
}

TEST(ListTest, MoveConstructor) {
  s21::List<int> s21_src = {1, 2, 3};
  s21::List<int> s21_move(std::move(s21_src));
  std::list<int> std_src = {1, 2, 3};
  std::list<int> std_move(std::move(std_src));
  CompareLists(s21_move, std_move);
  ASSERT_EQ(s21_move.Size(), 3U);
  ASSERT_TRUE(s21_src.Empty());

  s21::List<int> s21_empty;
  s21::List<int> s21_empty_move(std::move(s21_empty));
  ASSERT_TRUE(s21_empty_move.Empty());
}

TEST(ListTest, MoveAssignmentOperator) {
  s21::List<int> s21_src = {1, 2, 3};
  s21::List<int> s21_dest = {4, 5};
  s21_dest = std::move(s21_src);
  std::list<int> std_src = {1, 2, 3};
  std::list<int> std_dest = {4, 5};
  std_dest = std::move(std_src);
  CompareLists(s21_dest, std_dest);
  ASSERT_EQ(s21_dest.Size(), 3U);
  ASSERT_TRUE(s21_src.Empty());

  s21::List<int> s21_empty;
  s21::List<int> s21_dest_empty = {1};
  s21_dest_empty = std::move(s21_empty);
  ASSERT_TRUE(s21_dest_empty.Empty());
}

TEST(ListTest, FrontBack) {
  s21::List<int> s21_l = {1, 2, 3};
  std::list<int> std_l = {1, 2, 3};
  ASSERT_EQ(s21_l.Front(), std_l.front());
  ASSERT_EQ(s21_l.Back(), std_l.back());

  s21::List<int> s21_empty;
  ASSERT_THROW(s21_empty.Front(), std::out_of_range);
  ASSERT_THROW(s21_empty.Back(), std::out_of_range);
}

TEST(ListTest, BeginEnd) {
  s21::List<int> s21_l = {1, 2, 3};
  std::list<int> std_l = {1, 2, 3};
  auto s21_it = s21_l.Begin();
  auto std_it = std_l.begin();
  ASSERT_EQ(*s21_it, *std_it);
  ++s21_it;
  ++std_it;
  ASSERT_EQ(*s21_it, *std_it);
  --s21_it;
  --std_it;
  ASSERT_EQ(*s21_it, *std_it);

  s21::List<int> s21_empty;
  ASSERT_EQ(s21_empty.Begin(), s21_empty.End());

  ASSERT_EQ(s21_l.Begin(), s21_l.Begin());
  ASSERT_NE(s21_l.Begin(), s21_l.End());
}

TEST(ListTest, EmptySizeMaxSize) {
  s21::List<int> s21_l = {1, 2};
  std::list<int> std_l = {1, 2};
  ASSERT_FALSE(s21_l.Empty());
  ASSERT_EQ(s21_l.Size(), std_l.size());
  ASSERT_GT(s21_l.Max_size(), 0U);

  s21::List<int> s21_empty;
  ASSERT_TRUE(s21_empty.Empty());
  ASSERT_EQ(s21_empty.Size(), 0U);
}

TEST(ListTest, Clear) {
  s21::List<int> s21_l = {1, 2, 3};
  std::list<int> std_l = {1, 2, 3};
  s21_l.Clear();
  std_l.clear();
  CompareLists(s21_l, std_l);
  ASSERT_TRUE(s21_l.Empty());

  s21::List<int> s21_empty;
  s21_empty.Clear();
  ASSERT_TRUE(s21_empty.Empty());
}

TEST(ListTest, Insert) {
  s21::List<int> s21_l = {1, 3};
  std::list<int> std_l = {1, 3};
  auto s21_it = s21_l.Insert(++s21_l.Begin(), 2);
  auto std_it = std_l.insert(++std_l.begin(), 2);
  CompareLists(s21_l, std_l);
  ASSERT_EQ(*s21_it, *std_it);
  s21_l.Insert(s21_l.Begin(), 0);
  std_l.insert(std_l.begin(), 0);
  CompareLists(s21_l, std_l);
  ASSERT_EQ(s21_l.Front(), 0);

  s21_l.Insert(s21_l.End(), 4);
  std_l.insert(std_l.end(), 4);
  CompareLists(s21_l, std_l);
  ASSERT_EQ(s21_l.Back(), 4);

  s21::List<int> s21_empty;
  auto it_empty = s21_empty.Insert(s21_empty.End(), 5);
  ASSERT_EQ(s21_empty.Size(), 1U);
  ASSERT_EQ(*it_empty, 5);
  ASSERT_EQ(s21_empty.Front(), 5);
}

TEST(ListTest, Swap) {
  s21::List<int> s21_l1 = {1, 2};
  s21::List<int> s21_l2 = {3, 4, 5};
  s21_l1.Swap(s21_l2);
  std::list<int> std_l1 = {1, 2};
  std::list<int> std_l2 = {3, 4, 5};
  std_l1.swap(std_l2);
  CompareLists(s21_l1, std_l1);
  CompareLists(s21_l2, std_l2);

  s21::List<int> s21_empty;
  s21_l1.Swap(s21_empty);
  ASSERT_TRUE(s21_l1.Empty());
  ASSERT_EQ(s21_empty.Size(), 3U);
}

TEST(ListTest, Merge) {
  s21::List<int> s21_l1 = {1, 3, 5};
  s21::List<int> s21_l2 = {2, 4, 6};
  s21_l1.Merge(s21_l2);
  std::list<int> std_l1 = {1, 3, 5};
  std::list<int> std_l2 = {2, 4, 6};
  std_l1.merge(std_l2);
  CompareLists(s21_l1, std_l1);
  ASSERT_TRUE(s21_l2.Empty());

  s21::List<int> s21_empty;
  s21_l1.Merge(s21_empty);
  ASSERT_EQ(s21_l1.Size(), 6U);

  s21::List<int> s21_self = {1, 2};
  s21_self.Merge(s21_self);
  ASSERT_EQ(s21_self.Size(), 2U);
}

TEST(ListTest, Splice) {
  s21::List<int> s21_l1 = {3, 4, 5};
  s21::List<int> s21_l2 = {1, 2};
  s21::List<int> s21_l3 = {6};
  s21::List<int> s21_l4 = {7, 8};
  s21::List<int> s21_empty;
  std::list<int> std_l1 = {3, 4, 5};
  std::list<int> std_l2 = {1, 2};
  std::list<int> std_l3 = {6};
  std::list<int> std_l4 = {7, 8};
  std::list<int> std_empty;

  s21_l1.Splice(++s21_l1.Begin(), s21_l2);
  std_l1.splice(++std_l1.begin(), std_l2);
  CompareLists(s21_l1, std_l1);
  ASSERT_TRUE(s21_l2.Empty());

  s21_l1.Splice(s21_l1.Begin(), s21_l3);
  std_l1.splice(std_l1.begin(), std_l3);
  CompareLists(s21_l1, std_l1);

  s21_l1.Splice(s21_l1.End(), s21_l4);
  std_l1.splice(std_l1.end(), std_l4);
  CompareLists(s21_l1, std_l1);

  s21_l1.Splice(s21_l1.Begin(), s21_empty);
  std_l1.splice(std_l1.begin(), std_empty);
  CompareLists(s21_l1, std_l1);
}

TEST(ListTest, Reverse) {
  s21::List<int> s21_l = {1, 2, 3};
  std::list<int> std_l = {1, 2, 3};
  s21_l.Reverse();
  std_l.reverse();
  CompareLists(s21_l, std_l);

  s21::List<int> s21_empty;
  s21_empty.Reverse();
  ASSERT_TRUE(s21_empty.Empty());

  s21::List<int> s21_one = {42};
  s21_one.Reverse();
  ASSERT_EQ(s21_one.Front(), 42);
}

TEST(ListTest, Unique) {
  s21::List<int> s21_l = {1, 1, 2, 2, 2, 3};
  std::list<int> std_l = {1, 1, 2, 2, 2, 3};
  s21_l.Unique();
  std_l.unique();
  CompareLists(s21_l, std_l);

  s21::List<int> s21_no_dup = {1, 2, 3};
  s21_no_dup.Unique();
  ASSERT_EQ(s21_no_dup.Size(), 3U);

  s21::List<int> s21_all_dup = {5, 5, 5};
  s21_all_dup.Unique();
  ASSERT_EQ(s21_all_dup.Size(), 1U);

  s21::List<int> s21_empty;
  s21_empty.Unique();
  ASSERT_TRUE(s21_empty.Empty());
}

TEST(ListTest, Sort) {
  s21::List<int> s21_l = {3, 1, 4, 1, 5, 9};
  std::list<int> std_l = {3, 1, 4, 1, 5, 9};
  s21_l.Sort();
  std_l.sort();
  CompareLists(s21_l, std_l);

  s21::List<int> s21_sorted = {1, 2, 3};
  s21_sorted.Sort();
  ASSERT_EQ(s21_sorted.Front(), 1);
  ASSERT_EQ(s21_sorted.Back(), 3);

  s21::List<int> s21_dup = {2, 1, 2, 3};
  s21_dup.Sort();
  auto it = s21_dup.Begin();
  ASSERT_EQ(*it++, 1);
  ASSERT_EQ(*it++, 2);
  ASSERT_EQ(*it++, 2);
  ASSERT_EQ(*it, 3);

  s21::List<int> s21_empty;
  s21_empty.Sort();
  ASSERT_TRUE(s21_empty.Empty());

  s21::List<int> s21_one = {42};
  s21_one.Sort();
  ASSERT_EQ(s21_one.Front(), 42);
}

// 1
TEST(List, Constructor_Default) {
  s21::List<int> our_list;
  std::list<int> std_list;
  EXPECT_EQ(our_list.Empty(), std_list.empty());
}

TEST(List, Constructor_Size) {
  s21::List<int> our_list(5);
  std::list<int> std_list(5);
  EXPECT_EQ(our_list.Size(), std_list.size());
}

TEST(List, Constructor_List) {
  s21::List<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
}

TEST(List, Constructor_Copy) {
  s21::List<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::List<int> our_copy(our_list);
  std::list<int> std_copy(std_list);
  EXPECT_EQ(our_copy.Front(), std_copy.front());
  EXPECT_EQ(our_copy.Back(), std_copy.back());
}

TEST(List, Constructor_Move) {
  s21::List<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::List<int> our_copy(std::move(our_list));
  std::list<int> std_copy(std::move(std_list));
  EXPECT_EQ(our_copy.Front(), std_copy.front());
  EXPECT_EQ(our_copy.Back(), std_copy.back());
  EXPECT_EQ(our_list.Empty(), std_list.empty());
}

TEST(List, Operator_Move) {
  s21::List<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::List<int> our_copy;
  our_copy = std::move(our_list);
  std::list<int> std_copy;
  std_copy = std::move(std_list);
  EXPECT_EQ(our_copy.Front(), std_copy.front());
  EXPECT_EQ(our_copy.Back(), std_copy.back());
  EXPECT_EQ(our_list.Empty(), std_list.empty());
}

TEST(List, Size) {
  s21::List<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  EXPECT_EQ(our_list.Size(), std_list.size());
}

TEST(List, Push_Front) {
  s21::List<int> our_list;
  std::list<int> std_list;
  our_list.Push_front(1);
  std_list.push_front(1);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Push_front(2);
  std_list.push_front(2);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Push_front(3);
  std_list.push_front(3);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
}

TEST(List, Push_Back) {
  s21::List<int> our_list;
  std::list<int> std_list;
  our_list.Push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
}

TEST(List, Pop_Front) {
  s21::List<int> our_list;
  std::list<int> std_list;
  our_list.Push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Pop_front();
  std_list.pop_front();
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
}

TEST(List, Pop_Back) {
  s21::List<int> our_list;
  std::list<int> std_list;
  our_list.Push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Pop_back();
  std_list.pop_back();
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
}

TEST(List, Splice) {
  s21::List<int> our_list_first = {1};
  s21::List<int> our_list_second = {2, 3, 4, 5};
  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};
  s21::List<int>::iterator our_it = our_list_first.Begin();
  std::list<int>::iterator std_it = std_list_first.begin();
  our_list_first.Splice(our_it, our_list_second);
  std_list_first.splice(std_it, std_list_second);
  EXPECT_EQ(our_list_first.Front(), std_list_first.front());
  EXPECT_EQ(our_list_first.Back(), std_list_first.back());
}

TEST(List, Merge) {
  s21::List<int> our_list_first = {1};
  s21::List<int> our_list_second = {2, 3, 4, 5};
  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};
  our_list_first.Merge(our_list_second);
  std_list_first.merge(std_list_second);
  EXPECT_EQ(our_list_first.Front(), std_list_first.front());
  EXPECT_EQ(our_list_first.Back(), std_list_first.back());
  EXPECT_EQ(our_list_second.Empty(), std_list_second.empty());
}

TEST(List, Reverse) {
  s21::List<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.Reverse();
  std_list.reverse();
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
}

TEST(ListTest, Default2) {
  s21::List<int> list_int;
  s21::List<double> list_double;

  EXPECT_EQ(list_int.Empty(), 1);
  EXPECT_EQ(list_double.Empty(), 1);
}

TEST(ListTest, Size2) {
  s21::List<int> list_int(3);
  s21::List<double> list_double(5);

  EXPECT_EQ(list_int.Empty(), 0);
  EXPECT_EQ(list_double.Empty(), 0);
}

TEST(ListTest, Initializer_List2) {
  s21::List<int> list_int = {1, 3, 5};
  s21::List<double> list_double = {2, 1.5, -2};

  EXPECT_EQ(list_int.Empty(), 0);
  EXPECT_EQ(list_double.Empty(), 0);
}

TEST(ListTest, Copy2) {
  s21::List<int> list_int = {1, 3, 5};
  s21::List<int> list_copy(list_int);

  EXPECT_EQ(list_copy.Empty(), 0);
  EXPECT_EQ(list_copy.Size(), 3);
}

TEST(ListTest, Move2) {
  s21::List<int> list_int = {1, 3, 5};
  s21::List<int> list_move(std::move(list_int));

  EXPECT_EQ(list_int.Empty(), 1);
  EXPECT_EQ(list_move.Empty(), 0);
  EXPECT_EQ(list_move.Size(), 3);
}

TEST(ListTest, Operator_Eq2) {
  s21::List<int> list_int = {1, 3, 5};
  s21::List<int> list_eq;
  list_eq = std::move(list_int);

  EXPECT_EQ(list_eq.Empty(), 0);
  EXPECT_EQ(list_eq.Size(), 3);
}

TEST(ListTest, Front2) {
  s21::List<int> list_int = {1, 3, 5};

  EXPECT_EQ(list_int.Front(), 1);
}

TEST(ListTest, Front_Empty2) {
  s21::List<int> list_int;

  EXPECT_THROW(list_int.Front(), std::out_of_range);
}

TEST(ListTest, Back2) {
  s21::List<int> list_int = {1, 3, 5};

  EXPECT_EQ(list_int.Back(), 5);
}

TEST(ListTest, Back_Empty2) {
  s21::List<int> list_int;

  EXPECT_THROW(list_int.Back(), std::out_of_range);
}

TEST(ListTest, Begin2) {
  s21::List<int> list_int = {1, 3, 5};

  EXPECT_EQ(*(list_int.Begin()), 1);
}

TEST(ListTest, End2) {
  s21::List<int> list_int = {1, 3, 5};
  s21::List<int>::iterator it = list_int.End();
  s21::List<int>::iterator it_2 = list_int.Begin();
  for (int i = 0; i < 3; ++i) it_2++;

  EXPECT_EQ(it, it_2);
}

TEST(ListTest, Empty2) {
  s21::List<int> list_not_empty = {1, 3, 5};
  s21::List<int> list_empty;

  EXPECT_EQ(list_not_empty.Empty(), 0);
  EXPECT_EQ(list_empty.Empty(), 1);
}

TEST(ListTest, Size3) {
  s21::List<int> list_int = {1, 3, 5};
  s21::List<int> list_empty;

  EXPECT_EQ(list_int.Size(), 3);
  EXPECT_EQ(list_empty.Size(), 0);
}

TEST(ListTest, Max_Size2) {
  s21::List<int> list_int = {1, 3, 5};

  EXPECT_EQ(list_int.Max_size() > list_int.Size(), 1);
}

TEST(ListTest, Clear2) {
  s21::List<int> list_int = {1, 3, 5};

  EXPECT_EQ(list_int.Empty(), 0);

  list_int.Clear();

  EXPECT_EQ(list_int.Empty(), 1);
}

TEST(ListTest, Insert_Front2) {
  s21::List<int> list_int = {1, 3, 5};
  list_int.Insert(list_int.Begin(), 7);

  EXPECT_EQ(list_int.Front(), 7);
  EXPECT_EQ(list_int.Size(), 4);
}

TEST(ListTest, Insert_Back2) {
  s21::List<int> list_int = {1, 3, 5};
  list_int.Insert(list_int.End(), 7);

  EXPECT_EQ(list_int.Back(), 7);
  EXPECT_EQ(list_int.Size(), 4);
}

TEST(ListTest, Insert_Empty_Front2) {
  s21::List<int> list_int;
  list_int.Insert(list_int.Begin(), 1);

  EXPECT_EQ(list_int.Front(), 1);
  EXPECT_EQ(list_int.Size(), 1);
}

TEST(ListTest, Erase_Front2) {
  s21::List<int> list_int = {1, 3, 5};
  list_int.Erase(list_int.Begin());

  EXPECT_EQ(list_int.Front(), 3);
  EXPECT_EQ(list_int.Size(), 2);
}

TEST(ListTest, Erase_Empty2) {
  s21::List<int> list_int;

  EXPECT_THROW(list_int.Erase(list_int.Begin()), std::out_of_range);
}

TEST(ListTest, Erase_Back2) {
  s21::List<int> list_int = {1, 3, 5};
  auto it = list_int.Begin();
  it++;
  it++;
  list_int.Erase(it);

  EXPECT_EQ(list_int.Size(), 2);
  EXPECT_EQ(list_int.Back(), 3);
}

TEST(ListTest, Push_Back2) {
  s21::List<int> list_int = {1, 3, 5};
  list_int.Push_back(7);

  EXPECT_EQ(list_int.Back(), 7);
  EXPECT_EQ(list_int.Size(), 4);
}

TEST(ListTest, Pop_Back2) {
  s21::List<int> list_int = {1, 3, 5};
  list_int.Pop_back();

  EXPECT_EQ(list_int.Back(), 3);
  EXPECT_EQ(list_int.Size(), 2);
}

TEST(ListTest, Pop_Back_Alone2) {
  s21::List<int> list_int = {1};
  list_int.Pop_back();

  EXPECT_EQ(list_int.Empty(), 1);
}

TEST(ListTest, Pop_Back_Empty2) {
  s21::List<int> list_int;

  EXPECT_THROW(list_int.Pop_back(), std::out_of_range);
}

TEST(ListTest, Push_Front2) {
  s21::List<int> list_int = {1, 3, 5};
  list_int.Push_front(7);

  EXPECT_EQ(list_int.Front(), 7);
  EXPECT_EQ(list_int.Size(), 4);
}

TEST(ListTest, Push_Front_Empty2) {
  s21::List<int> list_int;
  list_int.Push_front(7);

  EXPECT_EQ(list_int.Front(), 7);
  EXPECT_EQ(list_int.Size(), 1);
}

TEST(ListTest, Pop_Front2) {
  s21::List<int> list_int = {1, 3, 5};
  list_int.Pop_front();

  EXPECT_EQ(list_int.Front(), 3);
  EXPECT_EQ(list_int.Size(), 2);
}

TEST(ListTest, Pop_Front_Empty2) {
  s21::List<int> list_int;

  EXPECT_THROW(list_int.Pop_front(), std::out_of_range);
}

TEST(ListTest, Pop_Front_Alone2) {
  s21::List<int> list_int = {1};
  list_int.Pop_front();

  EXPECT_EQ(list_int.Empty(), 1);
}

TEST(ListTest, Swap2) {
  s21::List<int> list_int = {1, 3, 5};
  s21::List<int> list_int_2 = {2, 4};
  list_int.Swap(list_int_2);

  EXPECT_EQ(list_int.Front(), 2);
  EXPECT_EQ(list_int.Back(), 4);
  EXPECT_EQ(list_int.Size(), 2);
  EXPECT_EQ(list_int_2.Front(), 1);
  EXPECT_EQ(list_int_2.Back(), 5);
  EXPECT_EQ(list_int_2.Size(), 3);
}

TEST(ListTest, Merge2) {
  s21::List<int> list_int = {5, 9, 1, 3, 3};
  s21::List<int> list_int_2 = {8, 7, 2, 3, 4, 4};
  list_int.Merge(list_int_2);
  EXPECT_EQ(list_int.Size(), 11);
  EXPECT_EQ(list_int_2.Empty(), 1);
}

TEST(ListTest, Splice2) {
  s21::List<int> list_int = {1, 2, 3, 4};
  s21::List<int> list_int_2 = {5, 6, 7};
  auto pos = list_int.Begin();
  pos++;
  pos++;
  list_int.Splice(pos, list_int_2);

  EXPECT_EQ(list_int.Front(), 1);
  EXPECT_EQ(list_int.Back(), 4);
  EXPECT_EQ(list_int.Size(), 7);
  EXPECT_EQ(list_int.Empty(), 0);
  EXPECT_EQ(list_int_2.Empty(), 1);
}

TEST(ListTest, Reverse2) {
  s21::List<int> list_int = {1, 3, 7, 4};
  list_int.Reverse();

  EXPECT_EQ(list_int.Empty(), 0);
  EXPECT_EQ(list_int.Size(), 4);
  EXPECT_EQ(list_int.Front(), 4);
  EXPECT_EQ(list_int.Back(), 1);
}

TEST(ListTest, Unique2) {
  s21::List<int> list_int = {1, 2, 2, 3, 3, 2, 1, 1, 2};
  list_int.Unique();

  EXPECT_EQ(list_int.Empty(), 0);
  EXPECT_EQ(list_int.Size(), 6);
  EXPECT_EQ(list_int.Front(), 1);
  EXPECT_EQ(list_int.Back(), 2);
}

TEST(ListTest, Sort2) {
  s21::List<int> list_int = {5, 3, 4, 4, 4, 1, 9, 8};
  list_int.Sort();

  EXPECT_EQ(list_int.Empty(), 0);
  EXPECT_EQ(list_int.Size(), 8);
  EXPECT_EQ(list_int.Front(), 1);
  EXPECT_EQ(list_int.Back(), 9);
}

bool compare_lists(s21::List<int> my_list, std::list<int> std_list) {
  bool result = true;
  if (my_list.Size() == std_list.size()) {
    auto my_it = my_list.Begin();
    auto std_it = std_list.begin();
    for (size_t i = 0; i != my_list.Size(); ++i) {
      if (*my_it != *std_it) {
        result = false;
        break;
      }
      ++my_it;
      ++std_it;
    }
  } else {
    result = false;
  }
  return result;
}

TEST(ListTest, Merge_1) {
  s21::List<int> my_list1{1, 9999, 20000};
  s21::List<int> my_list2{500, 15000, 30000};
  my_list1.Merge(my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_2) {
  s21::List<int> my_list1{1, 9999, 20000};
  s21::List<int> my_list2{15000, 30000};
  my_list1.Merge(my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{15000, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_3) {
  s21::List<int> my_list1{1, 20000, 666};
  s21::List<int> my_list2{15000, 154, 124, 30000};
  my_list1.Merge(my_list2);

  std::list<int> std_list1{1, 20000, 666};
  std::list<int> std_list2{15000, 154, 124, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_4) {
  s21::List<int> my_list1;
  s21::List<int> my_list2{15000, 154, 124, 30000};
  my_list1.Merge(my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2{15000, 154, 124, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_5) {
  s21::List<int> my_list1{1, 20000, 666};
  s21::List<int> my_list2;
  my_list1.Merge(my_list2);

  std::list<int> std_list1{1, 20000, 666};
  std::list<int> std_list2;
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_6) {
  s21::List<int> my_list1;
  s21::List<int> my_list2;
  my_list1.Merge(my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2;
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, PopBack) {
  s21::List<int> my_list{1, 2, 3, 4, 5};
  my_list.Pop_back();
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.pop_back();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}
TEST(ListTest, PopFront) {
  s21::List<int> my_list{1, 2, 3, 4, 5};
  my_list.Pop_front();
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.pop_front();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}
TEST(ListTest, PushBack) {
  s21::List<int> my_list{1, 2, 3, 4, 5};
  my_list.Push_back(6);
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.push_back(6);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}
TEST(ListTest, PushFront) {
  s21::List<int> my_list{1, 2, 3, 4, 5};
  my_list.Push_front(0);
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.push_front(0);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Erase_1) {
  s21::List<int> my_list1{1, 9999, 20000};
  my_list1.Erase(my_list1.Begin());

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.erase(std_list1.begin());

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_Many_Back2) {
  s21::List<int> list_int = {1, 2, 6, 7, 8};
  list_int.Insert_many_back(3, 4, 5);
  auto it = list_int.Begin();

  EXPECT_EQ(list_int.Size(), 8);
  for (int i = 0; i < 5; ++i) {
    ++it;
  }
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
}

TEST(ListConstIteratorTest, IncrementOperators) {
  s21::List<int> lst = {1, 2, 3, 4, 5, 6};
  auto it = lst.Begin();
  auto it_post = it++;
  EXPECT_NE(it, it_post);
  EXPECT_EQ(*it_post, 1);
  EXPECT_EQ(*it, 2);

  ++it;
  EXPECT_EQ(*it, 3);

  it++;
  EXPECT_NE(it, lst.End());
}
TEST(ListConstIteratorTest, FullCoverageOperators) {
  s21::List<int> lst = {10, 20, 30};
  auto it = lst.Cbegin();
  auto end_it = lst.Cend();

  EXPECT_EQ(*it, 10);
  EXPECT_EQ(it.operator->(), &(*it));

  ++it;
  EXPECT_EQ(*it, 20);

  auto old_it = it++;
  EXPECT_EQ(*old_it, 20);
  EXPECT_EQ(*it, 30);

  --it;
  EXPECT_EQ(*it, 20);

  old_it = it--;
  EXPECT_EQ(*old_it, 20);
  EXPECT_EQ(*it, 10);

  EXPECT_TRUE(it == lst.Cbegin());
  EXPECT_FALSE(it == end_it);

  EXPECT_TRUE(it != end_it);
  EXPECT_FALSE(it != lst.Cbegin());
}

TEST(ListVariadicInsertBackTest, InsertManyBack) {
  s21::List<int> lst = {1, 2, 3};

  lst.Insert_many_back(10, 20, 30);

  std::vector<int> expected = {1, 2, 3, 10, 20, 30};
  auto cit = lst.Cbegin();
  for (int val : expected) {
    ASSERT_NE(cit, lst.Cend());
    EXPECT_EQ(*cit, val);
    ++cit;
  }
  EXPECT_EQ(cit, lst.Cend());
}

TEST(ListVariadicInsertFrontTest, InsertManyFront) {
  s21::List<int> lst = {4, 5, 6};

  lst.Insert_many_front(1, 2, 3);

  std::vector<int> expected = {3, 2, 1, 4, 5, 6};
  auto cit = lst.Cbegin();
  for (int val : expected) {
    ASSERT_NE(cit, lst.Cend());
    EXPECT_EQ(*cit, val);
    ++cit;
  }
  EXPECT_EQ(cit, lst.Cend());
}
TEST(List_Insert_Many, Insert_Many) {
  s21::List<int> list_int = {1, 2, 6, 7, 8};
  list_int.Insert_many(list_int.Cbegin(), 3, 4, 5);

  EXPECT_EQ(list_int.Size(), 8);
  auto it = list_int.Begin();
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
}
