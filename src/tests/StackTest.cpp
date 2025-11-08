#include <gtest/gtest.h>
#include "Stack.h"

using ds::Stack;

class StackTest : public ::testing::Test
{
  protected:
    Stack<int> stack;
};

// Construction
TEST_F(StackTest, DefaultConstructor_WhenCreated_ShouldBeEmpty)
{
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 0u);
}

// Push
TEST_F(StackTest, Push_WhenElementsPushed_ShouldIncreaseSize)
{
    int a = 10;
    int b = 20;

    stack.push(a);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 1u);
    EXPECT_EQ(stack.top(), 10);

    stack.push(b);
    EXPECT_EQ(stack.size(), 2u);
    EXPECT_EQ(stack.top(), 20);
}

// Pop
TEST_F(StackTest, Pop_WhenElementsPopped_ShouldReturnTopAndDecreaseSize)
{
    int a = 1;
    int b = 2;

    stack.push(a);
    stack.push(b);

    EXPECT_EQ(stack.pop(), 2);
    EXPECT_EQ(stack.size(), 1u);
    EXPECT_EQ(stack.top(), 1);

    EXPECT_EQ(stack.pop(), 1);
    EXPECT_TRUE(stack.isEmpty());
}

// Copy constructor
TEST_F(StackTest, CopyConstructor_WhenStackHasElements_ShouldDuplicateElements)
{
    int a = 5;
    int b = 6;

    stack.push(a);
    stack.push(b);

    Stack<int> copiedStack(stack);

    EXPECT_FALSE(copiedStack.isEmpty());
    EXPECT_EQ(copiedStack.size(), 2u);
    EXPECT_EQ(copiedStack.top(), 6);

    copiedStack.pop();
    EXPECT_EQ(copiedStack.top(), 5);
    EXPECT_EQ(stack.top(), 6);
}

// Copy assignment
TEST_F(StackTest, CopyAssignment_WhenStackHasElements_ShouldDuplicateElements)
{
    int a = 7;
    int b = 8;

    stack.push(a);
    stack.push(b);

    Stack<int> assignedStack;
    assignedStack = stack;

    EXPECT_EQ(assignedStack.size(), 2u);
    EXPECT_EQ(assignedStack.top(), 8);

    assignedStack.pop();
    EXPECT_EQ(assignedStack.top(), 7);
    EXPECT_EQ(stack.top(), 8);
}

// Move constructor
TEST_F(StackTest, MoveConstructor_WhenStackHasElements_ShouldTransferOwnership)
{
    int a = 9;
    int b = 10;

    stack.push(a);
    stack.push(b);

    Stack<int> movedStack(std::move(stack));

    EXPECT_EQ(movedStack.size(), 2u);
    EXPECT_EQ(movedStack.top(), 10);

    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 0u);
}

// Move assignment
TEST_F(StackTest, MoveAssignment_WhenStackHasElements_ShouldTransferOwnership)
{
    int a = 11;
    int b = 12;

    stack.push(a);
    stack.push(b);

    Stack<int> movedTo;
    movedTo = std::move(stack);

    EXPECT_EQ(movedTo.size(), 2u);
    EXPECT_EQ(movedTo.top(), 12);
    EXPECT_TRUE(stack.isEmpty());
}

// Top
TEST_F(StackTest, Top_WhenCalled_ShouldReturnLastElement)
{
    int a = 13;
    int b = 14;
    stack.push(a);
    stack.push(b);

    EXPECT_EQ(stack.top(), 14);
}

// isEmpty and size consistency
TEST_F(StackTest, SizeAndEmpty_ShouldStayConsistentAcrossOperations)
{
    EXPECT_TRUE(stack.isEmpty());
    int a = 42;
    stack.push(a);
    EXPECT_EQ(stack.size(), 1u);
    EXPECT_FALSE(stack.isEmpty());
    stack.pop();
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 0u);
}

// Iterators
TEST_F(StackTest, IteratorsLoop_WhenIterating_ShouldVisitAllElementsInOrder)
{
    for (int i = 0; i < 5; ++i)
    {
        stack.push(i);
    }

    int i = 0;
    for (auto it = stack.begin(); it != stack.end(); ++it, ++i)
    {
        EXPECT_EQ(*it, 4 - i);
    }
}
