#include <gtest/gtest.h>

#include "DoublyLinkedList.h"

using ds::DoublyLinkedList;

class DoublyLinkedListTest : public ::testing::Test
{
  protected:
    DoublyLinkedList<int> list;
};

// --- Constructors and Assignment ---
TEST_F(DoublyLinkedListTest, DefaultConstructor_WhenCalled_ShouldCreateEmptyList)
{
    EXPECT_TRUE(list.isEmpty());
}
TEST_F(DoublyLinkedListTest, CopyConstructor_WhenSourceIsEmpty_ShouldCreateEmptyList)
{
    DoublyLinkedList<int> copiedList(list);
    EXPECT_TRUE(copiedList.isEmpty());
}
TEST_F(DoublyLinkedListTest, CopyConstructor_WhenSourceHasElements_ShouldCopyAllElements)
{
    list.pushBack(0);
    list.pushBack(1);

    DoublyLinkedList<int> copiedList(list);
    EXPECT_EQ(copiedList.popFront(), 0);
    EXPECT_EQ(copiedList.popFront(), 1);
    EXPECT_TRUE(copiedList.isEmpty());
}
TEST_F(DoublyLinkedListTest, CopyAssignmentOperator_WhenSourceIsEmpty_ShouldClearDestination)
{
    DoublyLinkedList<int> otherList;
    otherList.pushBack(0);

    otherList = list;
    EXPECT_TRUE(otherList.isEmpty());
}
TEST_F(DoublyLinkedListTest, CopyAssignmentOperator_WhenSourceHasElements_ShouldCopyAllElements)
{
    list.pushBack(0);
    list.pushBack(1);

    DoublyLinkedList<int> copiedList;
    copiedList = list;
    EXPECT_EQ(copiedList.popFront(), 0);
    EXPECT_EQ(copiedList.popFront(), 1);
    EXPECT_TRUE(copiedList.isEmpty());
}
TEST_F(DoublyLinkedListTest,
       MoveConstructor_WhenSourceHasElements_ShouldTransferOwnershipAndClearSource)
{
    list.pushBack(0);
    list.pushBack(1);

    DoublyLinkedList<int> movedList(std::move(list));
    EXPECT_EQ(movedList.popFront(), 0);
    EXPECT_EQ(movedList.popFront(), 1);
    EXPECT_TRUE(movedList.isEmpty());
    EXPECT_TRUE(list.isEmpty());
}
TEST_F(DoublyLinkedListTest,
       MoveAssignmentOperator_WhenSourceHasElements_ShouldTransferOwnershipAndClearSource)
{
    list.pushBack(0);
    list.pushBack(1);

    DoublyLinkedList<int> movedList;
    movedList = std::move(list);
    EXPECT_EQ(movedList.popFront(), 0);
    EXPECT_EQ(movedList.popFront(), 1);
    EXPECT_TRUE(movedList.isEmpty());
    EXPECT_TRUE(list.isEmpty());
}

// --- Element Insertion ---
TEST_F(DoublyLinkedListTest, PushFront_WhenListIsEmpty_ShouldAddElementAndSetHeadAndTail)
{
    list.pushFront(0);
    EXPECT_EQ(list.getFront(), 0);
    EXPECT_EQ(list.getBack(), 0);
}
TEST_F(DoublyLinkedListTest, PushFront_WhenListHasElements_ShouldAddElementAtFront)
{
    list.pushFront(0);
    EXPECT_EQ(list.getFront(), 0);

    list.pushFront(1);
    EXPECT_EQ(list.getFront(), 1);
}
TEST_F(DoublyLinkedListTest, PushBack_WhenListIsEmpty_ShouldAddElementAndSetHeadAndTail)
{
    list.pushBack(0);
    EXPECT_EQ(list.getFront(), 0);
    EXPECT_EQ(list.getBack(), 0);
}
TEST_F(DoublyLinkedListTest, PushBack_WhenListHasElements_ShouldAddElementAtEnd)
{
    list.pushBack(0);
    EXPECT_EQ(list.getBack(), 0);

    list.pushBack(1);
    EXPECT_EQ(list.getBack(), 1);
}

// --- Element Removal ---
TEST_F(DoublyLinkedListTest, PopFront_WhenListHasOneElement_ShouldReturnElementAndEmptyList)
{
    list.pushFront(0);

    EXPECT_EQ(list.popFront(), 0);
    EXPECT_TRUE(list.isEmpty());
}
TEST_F(DoublyLinkedListTest,
       PopFront_WhenListHasMultipleElements_ShouldReturnFirstElementAndUpdateHead)
{
    list.pushFront(1);
    list.pushFront(0);

    EXPECT_EQ(list.popFront(), 0);
    EXPECT_EQ(list.getFront(), 1);
}
TEST_F(DoublyLinkedListTest, PopFront_WhenListIsEmpty_ShouldThrowRuntimeError)
{
    EXPECT_ANY_THROW(list.popFront());
}
TEST_F(DoublyLinkedListTest, PopBack_WhenListHasOneElement_ShouldReturnElementAndEmptyList)
{
    list.pushFront(0);
    EXPECT_EQ(list.popFront(), 0);
    EXPECT_TRUE(list.isEmpty());
}
TEST_F(DoublyLinkedListTest,
       PopBack_WhenListHasMultipleElements_ShouldReturnLastElementAndUpdateTail)
{
    list.pushFront(1);
    list.pushFront(0);

    EXPECT_EQ(list.popBack(), 1);
    EXPECT_EQ(list.getBack(), 0);
}
TEST_F(DoublyLinkedListTest, PopBack_WhenListIsEmpty_ShouldThrowRuntimeError)
{
    EXPECT_ANY_THROW(list.popBack());
}

// --- Element Access ---
TEST_F(DoublyLinkedListTest, GetFront_WhenListHasElements_ShouldReturnReferenceToFirstElement)
{
    list.pushFront(1);
    list.pushFront(0);

    EXPECT_EQ(list.getFront(), 0);
}
TEST_F(DoublyLinkedListTest, GetFront_WhenListIsEmpty_ShouldThrowRuntimeError)
{
    EXPECT_ANY_THROW(list.getFront());
}
TEST_F(DoublyLinkedListTest, GetBack_WhenListHasElements_ShouldReturnReferenceToLastElement)
{
    list.pushBack(0);
    list.pushBack(1);

    EXPECT_EQ(list.getBack(), 1);
}
TEST_F(DoublyLinkedListTest, GetBack_WhenListIsEmpty_ShouldThrowRuntimeError)
{
    EXPECT_ANY_THROW(list.getBack());
}

// --- Clear and State Checks ---
TEST_F(DoublyLinkedListTest, Clear_WhenListHasElements_ShouldRemoveAllNodesAndResetTail)
{
    list.pushFront(1);
    list.pushFront(0);

    list.clear();
    EXPECT_TRUE(list.isEmpty());
    EXPECT_ANY_THROW(list.getBack());
}
TEST_F(DoublyLinkedListTest, Clear_WhenListIsEmpty_ShouldDoNothing)
{
    EXPECT_TRUE(list.isEmpty());
}
TEST_F(DoublyLinkedListTest, IsEmpty_WhenListHasNoElements_ShouldReturnTrue)
{
    EXPECT_TRUE(list.isEmpty());
}
TEST_F(DoublyLinkedListTest, IsEmpty_WhenListHasElements_ShouldReturnFalse)
{
    list.pushFront(1);
    list.pushFront(0);

    EXPECT_FALSE(list.isEmpty());
}

TEST_F(DoublyLinkedListTest, Erase_WhenSingleElement_ShouldEmptyList)
{
    list.pushFront(0);
    auto it = list.begin();
    list.erase(it);

    EXPECT_TRUE(list.isEmpty());
}

TEST_F(DoublyLinkedListTest, Erase_WhenListHasElements_ShouldEraseRightElement)
{
    list.pushFront(2);
    list.pushFront(1);
    list.pushFront(0);

    auto it = list.begin();
    ++it;
    list.erase(it);

    EXPECT_EQ(list.popFront(), 0);
    EXPECT_EQ(list.popFront(), 2);
}

// --- Iterator Behavior ---
TEST_F(DoublyLinkedListTest, Begin_WhenListIsEmpty_ShouldEqualEnd)
{
    EXPECT_EQ(list.begin(), list.end());
}
TEST_F(DoublyLinkedListTest, Begin_WhenListHasElements_ShouldPointToFirstElement)
{
    list.pushFront(0);
    EXPECT_EQ(*(list.begin()), 0);
}
TEST_F(DoublyLinkedListTest, IteratorIncrement_WhenAdvanced_ShouldTraverseAllElements)
{
    list.pushFront(2);
    list.pushFront(1);
    list.pushFront(0);

    auto it = list.begin();
    EXPECT_EQ(*(++it), 1);
    EXPECT_EQ(*(++it), 2);
}
TEST_F(DoublyLinkedListTest, IteratorPostIncrement_WhenUsed_ShouldReturnPreviousPosition)
{
    list.pushFront(2);
    list.pushFront(1);
    list.pushFront(0);

    auto it = list.begin();
    EXPECT_EQ(*(it++), 0);
    EXPECT_EQ(*(it++), 1);
    EXPECT_EQ(*it, 2);
}
TEST_F(DoublyLinkedListTest, IteratorComparison_WhenAtSamePosition_ShouldBeEqual)
{
    list.pushFront(1);
    list.pushFront(0);

    auto it1 = list.begin();
    auto it2 = list.begin();

    EXPECT_TRUE(it1 == it2);
}
TEST_F(DoublyLinkedListTest, IteratorComparison_WhenAtDifferentPositions_ShouldBeNotEqual)
{
    list.pushFront(1);
    list.pushFront(0);

    auto it1 = list.begin();
    auto it2 = ++list.begin();

    EXPECT_TRUE(it1 != it2);
}
TEST_F(DoublyLinkedListTest, RangeBasedFor_WhenIterating_ShouldVisitAllElementsInOrder)
{
    for (int i = 0; i < 5; i++)
    {
        list.pushBack(i);
    }

    int i = 0;
    for (auto it : list)
    {
        EXPECT_EQ(it, i);
        i++;
    }
}

TEST_F(DoublyLinkedListTest, IteratorLoop_WhenReverseIterating_ShouldVisitAllElementsInReverseOrder)
{
    for (int i = 0; i < 5; i++)
    {
        list.pushBack(i);
    }

    int i = 4;
    for (auto it = list.rbegin(); it != list.rend(); --it, --i)
    {
        EXPECT_EQ(*it, i);
    }
}

// --- Complex Scenarios ---
TEST_F(DoublyLinkedListTest, MultiplePushAndPop_WhenInterleaved_ShouldMaintainCorrectOrder)
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
TEST_F(DoublyLinkedListTest, CopyConstructor_WhenSourceModifiedAfterCopy_ShouldNotAffectCopy)
{
    list.pushFront(0);
    list.pushFront(1);
    list.pushFront(2);

    DoublyLinkedList<int> other(list);

    list.pushFront(3);
    EXPECT_EQ(other.getFront(), 2);
}
TEST_F(DoublyLinkedListTest, PushFrontAndPushBack_MixedSequence_ShouldMaintainCorrectHeadAndTail)
{
    list.pushBack(0);
    list.pushFront(1);
    list.pushFront(2);
    list.pushBack(3);
    list.pushFront(4);

    EXPECT_EQ(list.getFront(), 4);
    EXPECT_EQ(list.getBack(), 3);
}