#pragma once

#include <memory>

namespace ds
{

template<class T>
class LinkedList
{
    private:

    class Node
    {
        public:
        Node(const T& iData, std::unique_ptr<Node> iNext)
            : data(iData), next(std::move(iNext))
        {}
        T data;
        std::unique_ptr<Node> next;    

        friend class Iterator;
    };

    std::unique_ptr<Node> head;
    Node* tail = nullptr;


    public:

    LinkedList() = default;
    ~LinkedList() = default;

    LinkedList(const LinkedList<T>& other)
    {
        for(Iterator it = other.begin(); it != other.end(); it++)
        {
            pushBack(*it);
        }
    }

    LinkedList<T>& operator=(const LinkedList<T>& other)
    {
        if(this != &other)
        {
            clear();
            for(Iterator it = other.begin(); it != other.end(); it++)
            {
                pushBack(*it);
            }
        }

        return *this;
    }

    LinkedList(LinkedList<T>&& other) noexcept
        : head(std::move(other.head)), 
          tail(other.tail)
    {
        other.tail = nullptr;
    }

    LinkedList<T>& operator=(LinkedList<T>&& other) noexcept
    {
        if(this != &other)
        {
            clear();
            head = std::move(other.head);
            tail = other.tail;
            other.tail = nullptr;
        }

        return *this;
    }

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
        auto newNode = std::make_unique<Node>(data, std::move(head));
        head = std::move(newNode);

        if(!tail)
        {
            tail = head.get();
        }
    }

    void pushBack(const T& data)
    {
        auto newNode = std::make_unique<Node>(data, nullptr);

        if(!head)
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
        if(!head)
        {
            throw std::runtime_error("Method popFront() called on an empty list");
        }

        T data = std::move(head->data);
        std::unique_ptr<Node> oldHead = std::move(head);
        head = std::move(oldHead->next);
        
        if(!head)
        {
            tail = nullptr;
        }

        return std::move(data);
    }

    T popBack()
    {
        if(!head)
        {
            throw std::runtime_error("Method popBack() called on an empty list");
        }

        T data = std::move(tail->data);

        if(head.get() == tail)
        {
            head.reset();
            tail = nullptr;

            return data;
        }
 
        Node* it = head.get();
        while(it->next.get() != tail)
        {
            it = it->next.get();
        }
        it->next.reset();
        tail = it;

        return std::move(data);
    }

    T& getFront() const
    {
        if(!head)
        {
            throw std::runtime_error("Method getFront() called on an empty list");
        }

        return head->data;
    }

    T& getBack() const
    {
        if(!head)
        {
            throw std::runtime_error("Method getBack() called on an empty list");
        }

        return tail->data;
    }

    class Iterator
    {
        public:

        T& operator*() const
        {
            return currentNode->data;
        }
        T* operator->() const
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

        explicit Iterator(Node* node) : currentNode(node) {}

        Node* currentNode;

        friend class LinkedList;
    };

    Iterator begin()
    {
        return Iterator(head.get());
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

    const Iterator begin() const
    {
        return Iterator(head.get());
    }

    const Iterator end() const
    {
        return Iterator(nullptr);
    }
};

}