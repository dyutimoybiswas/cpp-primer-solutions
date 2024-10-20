#ifndef STRING_HPP
#define STRING_HPP

#include <utility>
#include <memory>
#include <iostream>

using char_allocator_traits = std::allocator_traits<std::allocator<char>>;

// custom string class
class String {
    friend std::ostream& operator<<(std::ostream&, const String&);
    friend std::istream& operator>>(std::istream&, String&);
    friend bool operator==(const String&, const String&);
    friend bool operator!=(const String&, const String&);
    friend bool operator<(const String&, const String&);
    friend bool operator<=(const String&, const String&);
    friend bool operator>(const String&, const String&);
    friend bool operator>=(const String&, const String&);
    friend String operator+(const String&, char);
    friend String operator+(char, const String&);
    friend String operator+(const String&, const String&);
    private:
        using iterator = char*;
        using const_iterator = const char*;
        char* elements {nullptr};     // current position
        char* first_free {nullptr};   // one past last assigned
        char* cap {nullptr};          // last position of allocated memory
        static char_allocator_traits::allocator_type alloc;
        void check_and_allocate() { if (size() == capacity()) reallocate(); }
        void free();                // destroy elements and free space
        void reallocate();          // get more space and copy existing elements
        std::pair<char*, char*> allocate_and_copy(const char*, const char*);
    public:
        // constructors.
        String() = default;
        String(const char*);
        String(std::initializer_list<char>);
        
        // copy control - needed when we have traditional pointers as class members.
        String(const String&);
        String(String&&) noexcept;
        String& operator=(const String&);
        String& operator=(String&&) noexcept;
        ~String() { free(); }

        // modifiers.
        size_t size() const noexcept { return first_free - elements; }
        size_t capacity() const noexcept { return cap - elements; }
        void resize(size_t, char=' ');
        void reserve(size_t);
        bool empty() const noexcept { return elements == first_free; }
        void push_back(const char);
        void pop_back();

        // iterators.
        iterator begin() const noexcept { return elements; }
        iterator end() const noexcept { return first_free; }
        const_iterator cbegin() const noexcept { return const_cast<char*>(elements); }
        const_iterator cend() const noexcept { return const_cast<char*>(first_free); }

        // overloaded subscript.
        char& operator[](size_t n) { return elements[n]; }
        char operator[](size_t n) const { return elements[n]; }

        // overloaded assignment.
        String& operator+=(char);
        String& operator+=(const String&);
};

#endif
