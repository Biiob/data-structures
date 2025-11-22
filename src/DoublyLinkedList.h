#pragma once

#include <memory>
#include <stdexcept>

namespace ds
{

template <typename T>
class DoublyLinkedList
{
  public:
    class Iterator;

    DoublyLinkedList() = default;

    DoublyLinkedList(const DoublyLinkedList<T>& other)
    {
        for (auto it = other.begin(); it != other.end(); ++it)
        {
            pushBack(*it);
        }
    }

    DoublyLinkedList(DoublyLinkedList<T>&& other) noexcept
        : head(std::move(other.head)), tail(other.tail)
    {
        other.tail = nullptr;
    }

    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other)
    {
        if (this != &other)
        {
            clear();
            for (auto it = other.begin(); it != other.end(); ++it)
            {
                pushBack(*it);
            }
        }
        return *this;
    }

    DoublyLinkedList<T>& operator=(DoublyLinkedList<T>&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            head = std::move(other.head);
            tail = other.tail;
            other.tail = nullptr;
        }
        return *this;
    }

    ~DoublyLinkedList() = default;

    bool isEmpty() const
    {
        return !head;
    }

    void clear()
    {
        head.reset();
        tail = nullptr;
    }

    void pushFront(const T& data)
    {
        auto newNode = std::make_unique<Node>(data, std::move(head), nullptr);

        if (newNode->next)
        {
            newNode->next->prev = newNode.get();
        }

        head = std::move(newNode);

        if (!tail)
        {
            tail = head.get();
        }
    }

    void pushBack(const T& data)
    {
        auto newNode = std::make_unique<Node>(data, nullptr, tail);

        if (!head)
        {
            head = std::move(newNode);
            tail = head.get();
        }
        else
        {
            tail->next = std::move(newNode);
            tail = tail->next.get();
        }
    }

    T popFront()
    {
        if (!head)
        {
            throw std::runtime_error("popFront() method called on an empty list");
        }

        T data = std::move(head->data);
        std::unique_ptr<Node> oldHead = std::move(head);
        head = std::move(oldHead->next);

        if (!head)
        {
            tail = nullptr;
        }

        return data;
    }

    T popBack()
    {
        if (!head)
        {
            throw std::runtime_error("popBack() method called on an empty list");
        }

        T data = std::move(tail->data);

        if (head.get() == tail)
        {
            head.reset();
            tail = nullptr;

            return data;
        }

        tail = tail->prev;
        tail->next.reset();

        return data;
    }

    T& getFront() const
    {
        if (!head)
        {
            throw std::runtime_error("getFront() method called on an empty list");
        }

        return head->data;
    }

    T& getBack() const
    {
        if (!head)
        {
            throw std::runtime_error("getBack() method called on an empty list");
        }

        return tail->data;
    }

    void erase(const Iterator& itToDelete)
    {
        if (itToDelete.currentNode == nullptr)
        {
            return;
        }

        Node* prev = itToDelete.currentNode->prev;
        std::unique_ptr<Node> nodeToDelete = std::move(prev != nullptr ? prev->next : head);

        if (prev == nullptr)
        {
            head = std::move(nodeToDelete->next);
            if (!head)
            {
                tail = nullptr;
            }
            else
            {
                head->prev = nullptr;
            }
            return;
        }

        prev->next = std::move(nodeToDelete->next);
        Node* next = prev->next.get();

        if (next != nullptr)
        {
            next->prev = prev;
        }
        else
        {
            tail = prev;
        }
    }

    Iterator begin() const
    {
        return Iterator(head.get());
    }

    Iterator end() const
    {
        return Iterator(nullptr);
    }

    Iterator rbegin() const
    {
        return Iterator(tail);
    }

    Iterator rend() const
    {
        return Iterator(nullptr);
    }

  private:
    class Node
    {
      public:
        explicit Node(const T& iData, std::unique_ptr<Node> iNext, Node* iPrev)
            : data(iData), next(std::move(iNext)), prev(iPrev)
        {
        }

        T data;
        std::unique_ptr<Node> next;
        Node* prev;
    };

    std::unique_ptr<Node> head;
    Node* tail = nullptr;
};

template <typename T>
class DoublyLinkedList<T>::Iterator
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
    Iterator& operator--()
    {
        currentNode = currentNode->prev;
        return *this;
    }
    Iterator operator--(int)
    {
        Iterator tmp(*this);
        --(*this);
        return tmp;
    }

  private:
    explicit Iterator(Node* node) : currentNode(node)
    {
    }

    Node* currentNode;

    friend class DoublyLinkedList;
};
} // namespace ds