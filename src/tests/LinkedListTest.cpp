#include <gtest/gtest.h>

#include "LinkedList.h"

using ds::LinkedList;

class LinkedListTest : public ::testing::Test {
protected:
    LinkedList<int> list;
};

// --- Constructors and Assignment ---
TEST_F(LinkedListTest, DefaultConstructor_WhenCalled_ShouldCreateEmptyList)
{
    EXPECT_TRUE(list.isEmpty());
}
TEST_F(LinkedListTest, CopyConstructor_WhenSourceIsEmpty_ShouldCreateEmptyList)
{
    LinkedList<int> copiedList(list);
    EXPECT_TRUE(copiedList.isEmpty());
}
TEST_F(LinkedListTest, CopyConstructor_WhenSourceHasElements_ShouldCopyAllElements)
{
    list.pushBack(0);
    list.pushBack(1);

    LinkedList<int> copiedList(list);
    EXPECT_EQ(copiedList.popFront(), 0);
    EXPECT_EQ(copiedList.popFront(), 1);
    EXPECT_TRUE(copiedList.isEmpty());
}
TEST_F(LinkedListTest, CopyAssignmentOperator_WhenSourceIsEmpty_ShouldClearDestination)
{
    LinkedList<int> otherList;
    otherList.pushBack(0);

    otherList = list;
    EXPECT_TRUE(otherList.isEmpty());
}
TEST_F(LinkedListTest, CopyAssignmentOperator_WhenSourceHasElements_ShouldCopyAllElements)
{
    list.pushBack(0);
    list.pushBack(1);

    LinkedList<int> copiedList;
    copiedList = list;
    EXPECT_EQ(copiedList.popFront(), 0);
    EXPECT_EQ(copiedList.popFront(), 1);
    EXPECT_TRUE(copiedList.isEmpty());
}
TEST_F(LinkedListTest, MoveConstructor_WhenSourceHasElements_ShouldTransferOwnershipAndClearSource)
{
    list.pushBack(0);
    list.pushBack(1);

    LinkedList<int> movedList(std::move(list));
    EXPECT_EQ(movedList.popFront(), 0);
    EXPECT_EQ(movedList.popFront(), 1);
    EXPECT_TRUE(movedList.isEmpty());
    EXPECT_TRUE(list.isEmpty());

}
TEST_F(LinkedListTest, MoveAssignmentOperator_WhenSourceHasElements_ShouldTransferOwnershipAndClearSource)
{
    list.pushBack(0);
    list.pushBack(1);

    LinkedList<int> movedList;
    movedList = std::move(list);
    EXPECT_EQ(movedList.popFront(), 0);
    EXPECT_EQ(movedList.popFront(), 1);
    EXPECT_TRUE(movedList.isEmpty());
    EXPECT_TRUE(list.isEmpty());
}

// --- Element Insertion ---
TEST_F(LinkedListTest, PushFront_WhenListIsEmpty_ShouldAddElementAndSetHeadAndTail)
{
    list.pushFront(0);
    EXPECT_EQ(list.getFront(), 0);
    EXPECT_EQ(list.getBack(), 0);
}
TEST_F(LinkedListTest, PushFront_WhenListHasElements_ShouldAddElementAtFront)
{
    list.pushFront(0);
    EXPECT_EQ(list.getFront(), 0);

    list.pushFront(1);
    EXPECT_EQ(list.getFront(), 1);
}
TEST_F(LinkedListTest, PushBack_WhenListIsEmpty_ShouldAddElementAndSetHeadAndTail)
{
    list.pushBack(0);
    EXPECT_EQ(list.getFront(), 0);
    EXPECT_EQ(list.getBack(), 0);
}
TEST_F(LinkedListTest, PushBack_WhenListHasElements_ShouldAddElementAtEnd)
{
    list.pushBack(0);
    EXPECT_EQ(list.getBack(), 0);

    list.pushBack(1);
    EXPECT_EQ(list.getBack(), 1);
}

// --- Element Removal ---
TEST_F(LinkedListTest, PopFront_WhenListHasOneElement_ShouldReturnElementAndEmptyList)
{
    list.pushFront(0);

    EXPECT_EQ(list.popFront(), 0);
    EXPECT_TRUE(list.isEmpty());
}
TEST_F(LinkedListTest, PopFront_WhenListHasMultipleElements_ShouldReturnFirstElementAndUpdateHead)
{
    list.pushFront(1);
    list.pushFront(0);

    EXPECT_EQ(list.popFront(), 0);
    EXPECT_EQ(list.getFront(), 1);
}
TEST_F(LinkedListTest, PopFront_WhenListIsEmpty_ShouldThrowRuntimeError)
{
    EXPECT_ANY_THROW(list.popFront());
}
TEST_F(LinkedListTest, PopBack_WhenListHasOneElement_ShouldReturnElementAndEmptyList)
{
    list.pushFront(0);
    EXPECT_EQ(list.popFront(), 0);
    EXPECT_TRUE(list.isEmpty());
}
TEST_F(LinkedListTest, PopBack_WhenListHasMultipleElements_ShouldReturnLastElementAndUpdateTail)
{
    list.pushFront(1);
    list.pushFront(0);

    EXPECT_EQ(list.popBack(), 1);
    EXPECT_EQ(list.getBack(), 0);
}
TEST_F(LinkedListTest, PopBack_WhenListIsEmpty_ShouldThrowRuntimeError)
{
    EXPECT_ANY_THROW(list.popBack());
}

// --- Element Access ---
TEST_F(LinkedListTest, GetFront_WhenListHasElements_ShouldReturnReferenceToFirstElement)
{
    list.pushFront(1);
    list.pushFront(0);

    EXPECT_EQ(list.getFront(), 0);
}
TEST_F(LinkedListTest, GetFront_WhenListIsEmpty_ShouldThrowRuntimeError)
{
    EXPECT_ANY_THROW(list.getFront());
}
TEST_F(LinkedListTest, GetBack_WhenListHasElements_ShouldReturnReferenceToLastElement)
{
    list.pushBack(0);
    list.pushBack(1);

    EXPECT_EQ(list.getBack(), 1);
}
TEST_F(LinkedListTest, GetBack_WhenListIsEmpty_ShouldThrowRuntimeError)
{
    EXPECT_ANY_THROW(list.getBack());
}

// --- Clear and State Checks ---
TEST_F(LinkedListTest, Clear_WhenListHasElements_ShouldRemoveAllNodesAndResetTail)
{
    list.pushFront(1);
    list.pushFront(0);

    list.clear();
    EXPECT_TRUE(list.isEmpty());
    EXPECT_ANY_THROW(list.getBack());
}
TEST_F(LinkedListTest, Clear_WhenListIsEmpty_ShouldDoNothing)
{
    EXPECT_TRUE(list.isEmpty());
}
TEST_F(LinkedListTest, IsEmpty_WhenListHasNoElements_ShouldReturnTrue)
{
    EXPECT_TRUE(list.isEmpty());
}
TEST_F(LinkedListTest, IsEmpty_WhenListHasElements_ShouldReturnFalse)
{
    list.pushFront(1);
    list.pushFront(0);

    EXPECT_FALSE(list.isEmpty());
}

// --- Iterator Behavior ---
TEST_F(LinkedListTest, Begin_WhenListIsEmpty_ShouldEqualEnd)
{
    EXPECT_EQ(list.begin(), list.end());
}
TEST_F(LinkedListTest, Begin_WhenListHasElements_ShouldPointToFirstElement)
{
    list.pushFront(0);
    EXPECT_EQ(*(list.begin()), 0);
}
TEST_F(LinkedListTest, IteratorIncrement_WhenAdvanced_ShouldTraverseAllElements)
{
    list.pushFront(2);
    list.pushFront(1);
    list.pushFront(0);

    auto it = list.begin();
    EXPECT_EQ(*(++it), 1);
    EXPECT_EQ(*(++it), 2);
}
TEST_F(LinkedListTest, IteratorPostIncrement_WhenUsed_ShouldReturnPreviousPosition)
{
    list.pushFront(2);
    list.pushFront(1);
    list.pushFront(0);

    auto it = list.begin();
    EXPECT_EQ(*(it++), 0);
    EXPECT_EQ(*(it++), 1);
    EXPECT_EQ(*it, 2);
}
TEST_F(LinkedListTest, IteratorComparison_WhenAtSamePosition_ShouldBeEqual)
{
    list.pushFront(1);
    list.pushFront(0);

    auto it1 = list.begin();
    auto it2 = list.begin();

    EXPECT_TRUE(it1 == it2);
}
TEST_F(LinkedListTest, IteratorComparison_WhenAtDifferentPositions_ShouldBeNotEqual)
{
    list.pushFront(1);
    list.pushFront(0);

    auto it1 = list.begin();
    auto it2 = ++list.begin();

    EXPECT_TRUE(it1 != it2);
}
TEST_F(LinkedListTest, RangeBasedFor_WhenIterating_ShouldVisitAllElementsInOrder)
{
    for(int i = 0; i < 5; i++)
    {
        list.pushBack(i);
    }

    int i = 0;
    for(auto it : list)
    {
        EXPECT_EQ(it, i);
        i++;
    }
}

// --- Complex Scenarios ---
TEST_F(LinkedListTest, MultiplePushAndPop_WhenInterleaved_ShouldMaintainCorrectOrder)
{
    list.pushFront(0);
    list.pushFront(1);
    list.pushFront(2);
    list.popFront();
    list.popFront();
    list.pushFront(3);
    list.pushFront(4);
    list.popFront();

    EXPECT_EQ(list.popFront(), 3);
    EXPECT_EQ(list.popFront(), 0);
}
TEST_F(LinkedListTest, CopyConstructor_WhenSourceModifiedAfterCopy_ShouldNotAffectCopy)
{
    list.pushFront(0);
    list.pushFront(1);
    list.pushFront(2);

    LinkedList<int> other(list);

    list.pushFront(3);
    EXPECT_EQ(other.getFront(), 2);
}
TEST_F(LinkedListTest, PushFrontAndPushBack_MixedSequence_ShouldMaintainCorrectHeadAndTail)
{
    list.pushBack(0);
    list.pushFront(1);
    list.pushFront(2);
    list.pushBack(3);
    list.pushFront(4);

    EXPECT_EQ(list.getFront(), 4);
    EXPECT_EQ(list.getBack(), 3);
}