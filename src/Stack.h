#pragma once

#include <memory>
#include <stdexcept>

#include "Array.h"

namespace ds
{

template <typename T>
class Stack
{
  public:
    class Iterator;

    Stack() = default;

    Stack(const Stack<T>& other)
    {
        Array<T> values;
        for (auto it = other.topNode.get(); it; it = it->next.get())
        {
            values.pushBack(it->data);
        }

        for (auto it = values.rbegin(); it != values.rend(); --it)
        {
            push(*it);
        }
    }

    Stack(Stack<T>&& other) : topNode(std::move(other.topNode)), count(other.count)
    {
        other.count = 0;
    }

    Stack& operator=(const Stack<T>& other)
    {
        if (this != &other)
        {
            topNode.reset();
            count = 0;

            Array<T> values;
            for (auto it = other.topNode.get(); it; it = it->next.get())
            {
                values.pushBack(it->data);
            }

            for (auto it = values.rbegin(); it != values.rend(); --it)
            {
                push(*it);
            }
        }

        return *this;
    }

    Stack& operator=(Stack<T>&& other)
    {
        if (this != &other)
        {
            topNode = std::move(other.topNode);
            count = other.count;
            other.count = 0;
        }

        return *this;
    }

    ~Stack() = default;

    T& top()
    {
        if (!topNode)
        {
            throw std::runtime_error("top() method called on an empty Stack");
        }

        return topNode->data;
    }

    bool isEmpty()
    {
        return !topNode;
    }

    size_t size()
    {
        return count;
    }

    void push(const T& data)
    {
        auto newNode = std::make_unique<Node>(data, std::move(topNode));
        topNode = std::move(newNode);
        count++;
    }

    T pop()
    {
        if (!topNode)
        {
            throw std::runtime_error("pop() method called on an empty Stack");
        }

        T data = std::move(topNode->data);
        topNode = std::move(topNode->next);
        count--;
        return data;
    }

    Iterator begin() const
    {
        return Iterator(topNode.get());
    }

    Iterator end() const
    {
        return Iterator(nullptr);
    }

  private:
    class Node
    {
      public:
        explicit Node(const T& iData, std::unique_ptr<Node> iNext)
            : data(iData), next(std::move(iNext))
        {
        }

        T data;
        std::unique_ptr<Node> next;

        friend class Iterator;
    };

    std::unique_ptr<Node> topNode;
    size_t count = 0;
};

template <typename T>
class Stack<T>::Iterator
{
  public:
    const T& operator*() const
    {
        return currentNode->data;
    }
    const T* operator->() const
    {
        return &currentNode->data;
    }
    bool operator==(const Iterator& other) const
    {
        return currentNode == other.currentNode;
    }
    bool operator!=(const Iterator& other) const
    {
        return currentNode != other.currentNode;
    }
    Iterator& operator++()
    {
        currentNode = currentNode->next.get();
        return *this;
    }
    Iterator operator++(int)
    {
        Iterator tmp(*this);
        ++(*this);
        return tmp;
    }

  private:
    explicit Iterator(Node* node) : currentNode(node)
    {
    }

    Node* currentNode;

    friend class Stack;
};
} // namespace ds