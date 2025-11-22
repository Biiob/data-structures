#pragma once

#include <memory>
#include <stdexcept>

namespace ds
{

template <typename T>
class Array
{
  public:
    class Iterator;
    class ConstIterator;

    Array() = default;

    Array(const Array<T>& other)
        : array(std::make_unique<T[]>(other.currentCapacity)), count(other.count),
          currentCapacity(other.currentCapacity)
    {
        for (size_t i = 0; i < other.size(); i++)
        {
            array[i] = other[i];
        }
    }

    Array(Array<T>&& other) noexcept
        : array(std::move(other.array)), count(other.count), currentCapacity(other.currentCapacity)
    {
        other.count = 0;
        other.currentCapacity = 0;
    }

    Array<T>& operator=(const Array<T>& other)
    {
        if (this != &other)
        {
            array = std::make_unique<T[]>(other.currentCapacity);
            count = other.count;
            currentCapacity = other.currentCapacity;
            for (size_t i = 0; i < other.size(); i++)
            {
                array[i] = other[i];
            }
        }
        return *this;
    }

    Array<T>& operator=(Array<T>&& other) noexcept
    {
        if (this != &other)
        {
            array = std::move(other.array);
            count = other.count;
            currentCapacity = other.currentCapacity;
            other.count = 0;
            other.currentCapacity = 0;
        }
        return *this;
    }

    ~Array() = default;

    void swap(Array<T>& other) noexcept
    {
        using std::swap;

        swap(array, other.array);
        swap(count, other.count);
        swap(currentCapacity, other.currentCapacity);
    }

    T& operator[](size_t i) const
    {
        return array[i];
    }

    T& at(size_t i) const
    {
        if (i >= count)
        {
            throw std::out_of_range("Out of bounds in at() method");
        }
        return array[i];
    }

    bool isEmpty() const
    {
        return count == 0;
    }

    size_t size() const
    {
        return count;
    }

    size_t capacity() const
    {
        return currentCapacity;
    }

    void reserve(size_t newCapacity)
    {
        if (newCapacity <= currentCapacity)
        {
            return;
        }
        auto newArray = std::make_unique<T[]>(newCapacity);
        for (size_t i = 0; i < count; i++)
        {
            newArray[i] = std::move(array[i]);
        }
        array = std::move(newArray);
        currentCapacity = newCapacity;
    }

    void resize(size_t newSize)
    {
        if (newSize <= currentCapacity)
        {
            count = newSize;
            return;
        }

        if (newSize > currentCapacity)
        {
            reserve(newSize);
        }

        for (size_t i = count; i < newSize; ++i)
        {
            array[i] = T{};
        }

        count = newSize;
    }

    void clear()
    {
        count = 0;
    }

    void pushBack(const T& data)
    {
        if (count == currentCapacity)
        {
            reserve(currentCapacity == 0 ? DEFAULT_SIZE : currentCapacity * 2);
        }
        array[count++] = data;
    }

    T popBack()
    {
        if (count == 0)
        {
            throw std::runtime_error("Method popBack() called on an empty array");
        }

        T data = std::move(array[--count]);
        return data;
    }

    Iterator begin()
    {
        return Iterator(array.get());
    }

    Iterator end()
    {
        return Iterator(array.get() + count);
    }

    Iterator rbegin()
    {
        return Iterator(array.get() + count - 1);
    }

    Iterator rend()
    {
        return Iterator(array.get() - 1);
    }

    ConstIterator cbegin() const
    {
        return ConstIterator(array.get());
    }

    ConstIterator cend() const
    {
        return ConstIterator(array.get() + count);
    }

    ConstIterator crbegin() const
    {
        return ConstIterator(array.get() + count - 1);
    }

    ConstIterator crend() const
    {
        return ConstIterator(array.get() - 1);
    }

  private:
    constexpr static size_t DEFAULT_SIZE = 32;
    std::unique_ptr<T[]> array;
    size_t count = 0;
    size_t currentCapacity = 0;
};

template <typename T>
class Array<T>::Iterator
{
  public:
    T& operator*() const
    {
        return *data;
    }
    T* operator->() const
    {
        return data;
    }
    bool operator==(const Iterator& other) const
    {
        return data == other.data;
    }
    bool operator!=(const Iterator& other) const
    {
        return data != other.data;
    }
    Iterator& operator++()
    {
        data++;
        return *this;
    }
    Iterator operator++(int)
    {
        Iterator tmp(*this);
        ++(*this);
        return tmp;
    }
    Iterator& operator--()
    {
        data--;
        return *this;
    }
    Iterator operator--(int)
    {
        Iterator tmp(*this);
        --(*this);
        return tmp;
    }

  private:
    explicit Iterator(T* iData) : data(iData)
    {
    }

    T* data;

    friend class Array;
};

template <typename T>
class Array<T>::ConstIterator
{
  public:
    const T& operator*() const
    {
        return *data;
    }
    const T* operator->() const
    {
        return data;
    }
    bool operator==(const ConstIterator& other) const
    {
        return data == other.data;
    }
    bool operator!=(const ConstIterator& other) const
    {
        return data != other.data;
    }
    ConstIterator& operator++()
    {
        data++;
        return *this;
    }
    ConstIterator operator++(int)
    {
        ConstIterator tmp(*this);
        ++(*this);
        return tmp;
    }
    ConstIterator& operator--()
    {
        data--;
        return *this;
    }
    ConstIterator operator--(int)
    {
        ConstIterator tmp(*this);
        --(*this);
        return tmp;
    }

  private:
    explicit ConstIterator(T* iData) : data(iData)
    {
    }

    T* data;

    friend class Array;
};
} // namespace ds