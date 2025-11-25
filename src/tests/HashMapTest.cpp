#include <gtest/gtest.h>

#include "HashMap.h"

using ds::HashMap;

class HashMapTest : public ::testing::Test
{
  protected:
    HashMap<std::string, std::string> map;
};

TEST_F(HashMapTest, constructor_ShouldConstructEmptyMap)
{
    EXPECT_TRUE(map.isEmpty());
}

TEST_F(HashMapTest, copyConstructor_ShouldCopyElementsFromSource)
{
    map.insert(std::pair<std::string, std::string>("Alice", "Engineer"));

    HashMap<std::string, std::string> otherMap(map);

    EXPECT_EQ(otherMap.at("Alice"), "Engineer");
    EXPECT_EQ(map.at("Alice"), "Engineer");
}

TEST_F(HashMapTest, copyAssignmentOperator_ShouldCopyElementsFromSource)
{
    map.insert(std::pair<std::string, std::string>("Alice", "Engineer"));

    HashMap<std::string, std::string> otherMap = map;

    EXPECT_EQ(otherMap.at("Alice"), "Engineer");
    EXPECT_EQ(map.at("Alice"), "Engineer");
}

TEST_F(HashMapTest, moveConstructor_ShouldMoveElementsFromSourceAndKeepItValid)
{
    map.insert(std::pair<std::string, std::string>("Alice", "Engineer"));

    HashMap<std::string, std::string> otherMap(std::move(map));

    EXPECT_EQ(otherMap.at("Alice"), "Engineer");
    EXPECT_TRUE(map.isEmpty());
}

TEST_F(HashMapTest, moveAssignmentOperator_ShouldMoveElementsFromSourceAndKeepItValid)
{
    map.insert(std::pair<std::string, std::string>("Alice", "Engineer"));

    HashMap<std::string, std::string> otherMap = std::move(map);

    EXPECT_EQ(otherMap.at("Alice"), "Engineer");
    EXPECT_TRUE(map.isEmpty());
}

TEST_F(HashMapTest, isEmpty_WhenEmpty_ShouldReturnTrue)
{
    EXPECT_TRUE(map.isEmpty());
}

TEST_F(HashMapTest, isEmpty_WhenNotEmpty_ShouldReturnFalse)
{
    map.insert(std::pair<std::string, std::string>("Alice", "Engineer"));

    EXPECT_FALSE(map.isEmpty());
}

TEST_F(HashMapTest, size_ShouldReturnCurrentSize)
{
    map.insert(std::pair<std::string, std::string>("Alice", "Engineer"));
    map.insert(std::pair<std::string, std::string>("Bob", "Scientist"));

    EXPECT_EQ(map.size(), 2);
}

TEST_F(HashMapTest, at_WhenElementNotPresent_ShouldThrow)
{
    EXPECT_ANY_THROW(map.at("Alice"));
}

TEST_F(HashMapTest, at_WhenElementPresent_ShouldReturnValue)
{
    map.insert(std::pair<std::string, std::string>("Alice", "Engineer"));
    EXPECT_EQ(map.at("Alice"), "Engineer");
}

TEST_F(HashMapTest, bracketOperator_WhenElementNotPresent_ShouldCreateElement)
{
    map["Alice"] = "Engineer";

    EXPECT_EQ(map.at("Alice"), "Engineer");
}

TEST_F(HashMapTest, bracketOperator_WhenElementPresent_ShouldReturnValue)
{
    map.insert(std::pair<std::string, std::string>("Alice", "Engineer"));

    EXPECT_EQ(map["Alice"], "Engineer");
}

TEST_F(HashMapTest, clear_ShouldClearMap)
{
    map.insert(std::pair<std::string, std::string>("Alice", "Engineer"));
    map.insert(std::pair<std::string, std::string>("Bob", "Scientist"));

    map.clear();

    EXPECT_TRUE(map.isEmpty());
}

TEST_F(HashMapTest, insert_ShouldInsertValue)
{
    map.insert(std::pair<std::string, std::string>("Alice", "Engineer"));

    EXPECT_EQ(map.at("Alice"), "Engineer");
}

TEST_F(HashMapTest, insert_WhenValueAlreadyExists_ShouldThrow)
{
    map.insert(std::pair<std::string, std::string>("Alice", "Engineer"));
    EXPECT_ANY_THROW(map.insert(std::pair<std::string, std::string>("Alice", "Engineer")));
}

TEST_F(HashMapTest, insert_WhenMultipleElements_ShouldAddAllElements)
{
    map.insert(std::pair<std::string, std::string>("Alice", "Engineer"));
    map.insert(std::pair<std::string, std::string>("Bob", "Scientist"));
    map.insert(std::pair<std::string, std::string>("Charlie", "Lawyer"));

    EXPECT_EQ(map.at("Alice"), "Engineer");
    EXPECT_EQ(map.at("Bob"), "Scientist");
    EXPECT_EQ(map.at("Charlie"), "Lawyer");
}

TEST_F(HashMapTest, insert_WhenKeysCollide_ShouldKeepBothElements)
{
    HashMap<int, int> intMap;

    intMap.insert(std::pair<int, int>(0, 0));
    // Will break if DEFAULT_SIZE changes
    intMap.insert(std::pair<int, int>(256, 1));

    EXPECT_EQ(intMap.at(0), 0);
    EXPECT_EQ(intMap.at(256), 1);
}

TEST_F(HashMapTest, erase_WhenElementExists_ShouldErase)
{
    map.insert(std::pair<std::string, std::string>("Alice", "Engineer"));

    map.erase("Alice");

    EXPECT_TRUE(map.isEmpty());
}
