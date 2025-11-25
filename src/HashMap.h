#pragma once

#include <stdexcept>

#include "Array.h"
#include "DoublyLinkedList.h"

namespace ds
{
template <typename Key, typename Value>
class HashMap
{
  public:
    using ValueType = std::pair<const Key, Value>;

    HashMap() : capacity(DEFAULT_SIZE), count(0)
    {
        array.resize(capacity);
    }

    HashMap(const HashMap<Key, Value>& other)
    {
        capacity = 0;
        resize(other.capacity);

        count = other.count;

        for (size_t i = 0; i < capacity; ++i)
        {
            array[i] = other.array[i];
        }
    }

    HashMap(HashMap<Key, Value>&& other) noexcept
        : array(std::move(other.array)), capacity(other.capacity), count(other.count)
    {
        other.array.resize(DEFAULT_SIZE);
        other.count = 0;
    }

    ~HashMap() = default;

    HashMap<Key, Value>& operator=(const HashMap<Key, Value>& other)
    {
        if (this != &other)
        {
            resize(other.capacity);
            count = other.count;

            for (size_t i = 0; i < capacity; ++i)
            {
                array[i] = other.array[i];
            }
        }

        return *this;
    }

    HashMap<Key, Value>& operator=(HashMap<Key, Value>&& other) noexcept
    {
        if (this != &other)
        {
            array = std::move(other.array);
            capacity = other.capacity;
            count = other.count;

            other.resize(DEFAULT_SIZE);
            other.count = 0;
        }

        return *this;
    }

    bool isEmpty() const
    {
        return count == 0;
    }

    size_t size() const
    {
        return count;
    }

    Value& at(const Key& key) const
    {
        size_t index = computeIndex(key);
        DoublyLinkedList<ValueType>& bucket = array[index];

        if (bucket.isEmpty())
        {
            throw std::out_of_range("No value associated to the given key in HashMap");
        }

        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (it->first == key)
            {
                return it->second;
            }
        }

        throw std::runtime_error("No value associated to the given key in HashMap");
    }

    Value& operator[](const Key& key)
    {
        size_t index = computeIndex(key);
        DoublyLinkedList<ValueType>& bucket = array[index];

        for (ValueType& pair : bucket)
        {
            if (pair.first == key)
            {
                return pair.second;
            }
        }

        ValueType& value = insert(std::pair<Key, Value>(key, Value{}));
        return value.second;
    }

    void clear()
    {
        for (auto it = array.begin(); it != array.end(); ++it)
        {
            it->clear();
        }

        count = 0;
    }

    ValueType& insert(const ValueType& pair)
    {
        if ((static_cast<float>(count + 1) / capacity) >= maxLoadFactor)
        {
            resize(capacity * 2);
        }

        size_t index = computeIndex(pair.first);
        DoublyLinkedList<ValueType>& bucket = array[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (it->first == pair.first)
            {
                throw std::runtime_error(
                    "A value associated to this key already exists in HashMap");
            }
        }

        array[index].pushBack(pair);
        ++count;

        return array[index].getBack();
    }

    void erase(const Key& key)
    {
        size_t index = computeIndex(key);
        DoublyLinkedList<ValueType>& bucket = array[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (it->first == key)
            {
                bucket.erase(it);
                --count;
                return;
            }
        }
    }

    void resize(const size_t newCapacity)
    {
        if (newCapacity <= capacity)
        {
            return;
        }

        Array<DoublyLinkedList<ValueType>> oldArray{};
        oldArray.swap(array);

        array.resize(newCapacity);
        capacity = newCapacity;
        count = 0;

        for (DoublyLinkedList<ValueType>& bucket : oldArray)
        {
            for (ValueType& pair : bucket)
            {
                size_t index = computeIndex(pair.first);
                array[index].pushBack(pair);
                ++count;
            }
        }
    }

  private:
    constexpr static size_t DEFAULT_SIZE = 256;
    constexpr static float maxLoadFactor = 0.75;
    Array<DoublyLinkedList<ValueType>> array;
    size_t capacity = 0;
    size_t count = 0;

    size_t computeIndex(const Key& key) const
    {
        return (std::hash<Key>{}(key) % capacity);
    }
};
} // namespace ds