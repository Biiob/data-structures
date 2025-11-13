#pragma once

#include <memory>
#include <stdexcept>

namespace ds
{

template <typename T>
class Array
{
  private:
    constexpr static size_t DEFAULT_SIZE = 32;
    std::unique_ptr<T[]> array;
    size_t count = 0;
    size_t currentCapacity = 0;

  public:
    Array() = default;
    ~Array() = default;

    Array(const Array<T>& other)
        : array(std::make_unique<T[]>(other.currentCapacity)), count(other.count),
          currentCapacity(other.currentCapacity)
    {
        for (size_t i = 0; i < other.size(); i++)
        {
            array[i] = other[i];
        }
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

    Array(Array<T>&& other) noexcept
        : array(std::move(other.array)), count(other.count), currentCapacity(other.currentCapacity)
    {
        other.count = 0;
        other.currentCapacity = 0;
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

    class Iterator
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

    Iterator begin()
    {
        return Iterator(array.get());
    }

    Iterator end()
    {
        return Iterator(array.get() + count);
    }

    const Iterator begin() const
    {
        return Iterator(array.get());
    }

    const Iterator end() const
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

    const Iterator rbegin() const
    {
        return Iterator(array.get() + count - 1);
    }

    const Iterator rend() const
    {
        return Iterator(array.get() - 1);
    }
};
} // namespace ds