#pragma once

template <class T, class Allocator = std::allocator<T>>
class ForwardList
{
public:
    using value_type = T;
  
    ForwardList() = default;
    ForwardList(ForwardList const&) = default;
    ForwardList(ForwardList&&) noexcept = default;

    ForwardList& operator=(ForwardList&&) noexcept = default;
    ForwardList& operator=(ForwardList const&) = default;

    ForwardList(size_t n) {       
        for (auto i = 0; i < n; ++i) {
            this->push_back(T());
        }     
    }

    ~ForwardList() {
        auto& node = first;

        while (node) {
            auto next = node->next_;
            alloc.destroy(node);
            alloc.deallocate(node, 1);

            node = next;
        }
    }

    bool empty() const { return size() == 0; }

    size_t size() const { return size_; }

    T& front() const
    {
        return first->val_;
    }

    T& back()
    {
        return last->val_;
    }

    void push_back(const T& x)
    {

        Node* data = alloc.allocate(1);
        alloc.construct(data, x);

        if (this->empty()) {
            first = data;
            last = data;
        }
        else {

            last->next_ = data;
            last = data;
        }

        ++size_;
    }

    struct Node {

        Node(const T& val) : val_(val), next_(nullptr) {}

        T val_;
        Node* next_ = nullptr;

    };

    class Iterator
    {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(Node* ptr) : m_ptr(ptr) {}

        reference operator*() const { return m_ptr->val_; }

        Iterator& operator++() { m_ptr = m_ptr->next_; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; m_ptr = m_ptr->next_; return tmp; }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

    private:

        Node* m_ptr;
    };

    Iterator begin() {
        return Iterator(first);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

private:

    using Rebind_Alloc = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;

    std::size_t size_ = 0;
    Node* first = nullptr;
    Node* last = nullptr;

    Rebind_Alloc alloc;
};
