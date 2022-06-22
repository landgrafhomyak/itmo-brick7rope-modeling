#ifndef BRICK7ROPE_MODELING_BUFFER_HPP
# define BRICK7ROPE_MODELING_BUFFER_HPP

# include <cstddef>
# include <cstdint>
# include <cstdlib>
#include <cstring>

template<typename elem_t>
class Buffer
{
private:
    struct Node
    {
    public:
        Buffer<elem_t>::Node *prev = nullptr;
        Buffer<elem_t>::Node *next = nullptr;
        elem_t value;

        constexpr inline explicit Node(elem_t value) noexcept: value(value)
        {}
    };

    struct Page
    {
    public:
        static constexpr size_t page_capacity = 255;

        Buffer<elem_t>::Page *next;
        Buffer<elem_t>::Node nodes[Buffer<elem_t>::Page::page_capacity];

        constexpr inline explicit Page(Buffer<elem_t>::Page *next = nullptr) noexcept: next(next)
        {
            for (size_t i = 1; i < Buffer<elem_t>::Page::page_capacity; i++)
            {
                this->nodes[i].next = &(this->nodes[i - 1]);
                /* Setting prev doesn't need because free nodes couldn't be removed via pointer */
            }
            this->last()->next = nullptr;
        };

        constexpr inline Buffer<elem_t>::Node &operator[](size_t i) noexcept
        { return this->nodes[i]; }

        constexpr inline Buffer<elem_t>::Node *last() noexcept
        { return &(this->nodes[0]); }

        constexpr inline Buffer<elem_t>::Page &operator=(Buffer<elem_t>::Page const &other)
        {
            this->next = other.next;
            return *this;
        }
    };

    Buffer<elem_t>::Page *last_page = nullptr;
    Buffer<elem_t>::Node *last_used = nullptr;
    Buffer<elem_t>::Node *last_free = nullptr;

public:
    constexpr inline Buffer() noexcept = default;

private:
    inline elem_t *_add(elem_t value) noexcept
    {
        if (this->last_free == nullptr)
        {
            Buffer<elem_t>::Page *const p = (Buffer<elem_t>::Page *) (malloc(sizeof(Buffer<elem_t>::Page)));
            *p = Buffer<elem_t>::Page(this->last_page);
            this->last_page = p;
            this->last_free = p->last();
        }

        Buffer<elem_t>::Node *n = this->last_free;
        this->last_free = n->next;
        *n = Buffer<elem_t>::Node(value);
        if (this->last_used != nullptr)
        { this->last_used->next = n; }
        n->prev = this->last_used;
        n->next = nullptr;
        this->last_used = n;
        return &(n->value);
    }

public:
    elem_t *add(elem_t value) noexcept
    { return this->_add(value); }

    Buffer<elem_t> copy() const noexcept
    {
        Buffer<elem_t> the_copy{};

        for (Buffer<elem_t>::Node *p = this->last_used; p != nullptr; p = p->prev)
        {
            the_copy._add(p->value);
        }

        return the_copy;
    }

    void remove(elem_t *value) noexcept
    {
        Buffer<elem_t>::Node *p = ((uintptr_t) value) - offsetof(Buffer<elem_t>::Node, value);

        if (p->prev != nullptr)
        { p->prev->next = p->next; }

        if (p->next != nullptr)
        { p->next->prev = p->prev; }

        p->next = this->last_free;
        this->last_free = p;
    }
};

#endif /* BRICK7ROPE_MODELING_BUFFER_HPP */
