#include <gtest/gtest.h>

#include "LinkedList.h"

TEST(LinkedListTest, isEmpty_whenNewLinkedList_ShouldReturnTrue)
{
    ds::LinkedList<int> list;
    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListTest, isEmpty_WhenItemInList_ShouldReturnFalse)
{
    ds::LinkedList<int> list;
    list.pushFront(1);
    EXPECT_FALSE(list.isEmpty());
}

TEST(LinkedListTest, clear_WhenNonEmpty_ShouldClearList)
{
    ds::LinkedList<int> list;
    list.pushFront(0);
    list.pushFront(1);
    list.clear();
    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListTest, pushFront_WhenUsed_ShouldInsertValue)
{
    ds::LinkedList<int> list;
    int value = 0;
    list.pushFront(value);
    EXPECT_EQ(value, list.getFront());
}

TEST(LinkedListTest, pushFront_WhenMultipleValues_ShouldInsertValuesInReverseOrder)
{
    ds::LinkedList<int> list;
    int values[] = {0, 1, 2};
    list.pushFront(values[0]);
    list.pushFront(values[1]);
    list.pushFront(values[2]);

    EXPECT_EQ(values[2], list.popFront());
    EXPECT_EQ(values[1], list.popFront());
    EXPECT_EQ(values[0], list.popFront());
}

TEST(LinkedListTest, popFront_WhenNonEmptyList_ShouldReturnCorrectValue)
{
    ds::LinkedList<int> list;
    int value = 0;
    list.pushFront(value);
    EXPECT_EQ(value, list.popFront());
}

TEST(LinkedListTest, popFront_WhenNonEmptyList_ShouldRemoveValue)
{
    ds::LinkedList<int> list;
    int firstValue = 0;
    int secondValue = 1;
    list.pushFront(secondValue);
    list.pushFront(firstValue);
    list.popFront();
    EXPECT_EQ(secondValue, list.getFront());
}

TEST(LinkedListTest, popFront_WhenEmptyList_ShouldThrow)
{
    ds::LinkedList<int> list;
    EXPECT_ANY_THROW(list.popFront());
}

TEST(LinkedListTest, getFront_WhenNonEmptyList_ShouldReturnCorrectValue)
{
    ds::LinkedList<int> list;
    int value = 0;
    list.pushFront(value);
    EXPECT_EQ(value, list.getFront());
}

TEST(LinkedListTest, getFront_WhenEmptyList_ShouldThrow)
{
    ds::LinkedList<int> list;
    EXPECT_ANY_THROW(list.getFront());
}

TEST(LinkedListTest, pushFront_WhenNonPrimitiveType_insertsValue)
{
    ds::LinkedList<std::string> list;
    std::string value = "test";
    list.pushFront(value);
    EXPECT_EQ(value, list.getFront());
}

TEST(LinkedListTest, popFront_WhenNonPrimitiveType_removesValue)
{
    ds::LinkedList<std::string> list;
    std::string value = "test";
    list.pushFront(value);
    EXPECT_EQ(value, list.popFront());
    EXPECT_TRUE(list.isEmpty());
}