#include <gtest/gtest.h>
#include <list>
#include "../list/s21_list.h"

template class s21::List<int>;

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
TEST(ListTest, DefaultConstructor) {
  s21::List<int> s21_l;
  std::list<int> std_l;
  compare_lists(s21_l, std_l);
  ASSERT_TRUE(s21_l.Empty());
  ASSERT_EQ(s21_l.Size(), 0U);
}

TEST(ListTest, ParameterizedConstructor) {
  s21::List<int> s21_l(5);
  std::list<int> std_l(5);
  compare_lists(s21_l, std_l);
  ASSERT_EQ(s21_l.Size(), 5U);
  ASSERT_EQ(s21_l.Front(), 0);
  ASSERT_EQ(s21_l.Back(), 0);

  s21::List<int> s21_empty(0);
  std::list<int> std_empty(0);
  compare_lists(s21_empty, std_empty);
  ASSERT_TRUE(s21_empty.Empty());

  s21::List<int> s21_large(1000);
  ASSERT_EQ(s21_large.Size(), 1000U);
}

TEST(ListTest, InitializerListConstructor) {
  s21::List<int> s21_l = {1, 2, 3, 4};
  std::list<int> std_l = {1, 2, 3, 4};
  compare_lists(s21_l, std_l);
  ASSERT_EQ(s21_l.Size(), 4U);
  ASSERT_EQ(s21_l.Front(), 1);
  ASSERT_EQ(s21_l.Back(), 4);

  s21::List<int> s21_empty = {};
  std::list<int> std_empty = {};
  compare_lists(s21_empty, std_empty);
  ASSERT_TRUE(s21_empty.Empty());
}

TEST(ListTest, CopyConstructor) {
  s21::List<int> s21_src = {1, 2, 3};
  s21::List<int> s21_copy(s21_src);
  std::list<int> std_src = {1, 2, 3};
  std::list<int> std_copy(std_src);
  compare_lists(s21_copy, std_copy);
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
  compare_lists(s21_move, std_move);
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
  compare_lists(s21_dest, std_dest);
  ASSERT_EQ(s21_dest.Size(), 3U);
  ASSERT_TRUE(s21_src.Empty());

  s21::List<int> s21_empty;
  s21::List<int> s21_dest_empty = {1};
  s21_dest_empty = std::move(s21_empty);
  ASSERT_TRUE(s21_dest_empty.Empty());
}

TEST(List, Constructor_Default) {
  s21::List<int> our_list;
  std::list<int> std_list;
  EXPECT_EQ(our_list.Empty(), std_list.empty());
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
TEST(ListTest, Unique_TailUpdate) {
  s21::List<int> list = {1, 2, 3, 4, 5, 5};

  list.Unique();

  EXPECT_EQ(list.Size(), 5);

  auto it = list.Begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 5);

  EXPECT_EQ(list.Back(), 5);
}
TEST(ListTest, Splice_InsertIntoEmptyList) {
  s21::List<int> list1;
  s21::List<int> list2 = {1, 2, 3};

  list1.Splice(list1.Begin(), list2);

  EXPECT_EQ(list1.Size(), 3);
  EXPECT_TRUE(list2.Empty());
  EXPECT_EQ(list1.Front(), 1);
  EXPECT_EQ(list1.Back(), 3);
}

TEST(ListTest, Splice_InsertAtEnd) {
  s21::List<int> list1 = {10, 20};
  s21::List<int> list2 = {1, 2};

  list1.Splice(list1.End(), list2);

  EXPECT_EQ(list1.Size(), 4);
  EXPECT_TRUE(list2.Empty());
  EXPECT_EQ(list1.Back(), 2);
}

TEST(ListTest, Splice_InsertInMiddle) {
  s21::List<int> list1 = {10, 30};
  s21::List<int> list2 = {1, 2};

  auto it = list1.Begin();
  ++it;

  list1.Splice(it, list2);

  EXPECT_EQ(list1.Size(), 4);
  EXPECT_TRUE(list2.Empty());

  auto iter = list1.Begin();
  EXPECT_EQ(*iter++, 10);
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 30);
}
TEST(ListTest, PushFront_EmptyList) {
  s21::List<int> list;
  list.Push_front(42);

  EXPECT_EQ(list.Size(), 1);
  EXPECT_EQ(list.Front(), 42);
  EXPECT_EQ(list.Back(), 42);
}

TEST(ListTest, PushFront_NonEmptyList) {
  s21::List<int> list = {1, 2, 3};
  list.Push_front(0);

  EXPECT_EQ(list.Size(), 4);
  EXPECT_EQ(list.Front(), 0);
  auto it = list.Begin();
  ++it;
  EXPECT_EQ(*it, 1);
}
TEST(ListTest, PopBack_EmptyList) {
  s21::List<int> list;
  EXPECT_THROW(list.Pop_back(), std::out_of_range);
}

TEST(ListTest, PopBack_SingleElement) {
  s21::List<int> list = {100};
  list.Pop_back();

  EXPECT_TRUE(list.Empty());
  EXPECT_EQ(list.Size(), 0);
}

TEST(ListTest, PopBack_MultipleElements) {
  s21::List<int> list = {1, 2, 3};
  list.Pop_back();

  EXPECT_EQ(list.Size(), 2);
  EXPECT_EQ(list.Back(), 2);
}
TEST(ListTest, Erase_EndIterator_Throws) {
  s21::List<int> list = {1, 2, 3};
  auto end_it = list.End();
  EXPECT_THROW(list.Erase(end_it), std::out_of_range);
}

TEST(ListTest, Erase_Begin) {
  s21::List<int> list = {1, 2, 3};
  list.Erase(list.Begin());

  EXPECT_EQ(list.Front(), 2);
  EXPECT_EQ(list.Size(), 2);
}

TEST(ListTest, Erase_Back) {
  s21::List<int> list = {1, 2, 3};
  auto it = list.Begin();
  ++it;
  ++it;
  list.Erase(it);

  EXPECT_EQ(list.Back(), 2);
  EXPECT_EQ(list.Size(), 2);
}
TEST(ListTest, Erase_Middle_Alternative) {
  s21::List<int> list = {10, 20, 30, 40, 50};
  auto it = list.Begin();
  ++it;
  ++it;
  ++it;

  list.Erase(it);
  EXPECT_EQ(list.Size(), 4);

  auto iter = list.Begin();
  EXPECT_EQ(*iter++, 10);
  EXPECT_EQ(*iter++, 20);
  EXPECT_EQ(*iter++, 30);
  EXPECT_EQ(*iter++, 50);
}
