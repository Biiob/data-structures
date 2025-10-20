#pragma once

#include <memory>

namespace ds
{

template<class T>
class LinkedList
{
    public:

    LinkedList() = default;
    ~LinkedList() = default;

    bool isEmpty() const
    {
        return !head;
    }

    void clear()
    {
        head.reset(nullptr);
    }

    void insertFront(const T& data)
    {
        head = std::make_shared<Node>(data, head);  
    }

    T popFront()
    {
        if(!head)
        {
            throw std::runtime_error("Method popFront() called on an empty list");
        }

        T data = head->data;
        head = head->next;
        return data;
    }

    T getFront() const
    {
        if(!head)
        {
            throw std::runtime_error("Method getFront() called on an empty list");
        }

        return head->data;
    }

    private:

    class Node
    {
        public:
        Node(const T& iData, std::shared_ptr<Node> iNext)
            : data(iData), next(std::move(iNext));
        {
            data = iData;
            next = iNext;
        }
        T data;
        std::shared_ptr<Node> next;    
    };

    std::shared_ptr<Node> head;
};

}