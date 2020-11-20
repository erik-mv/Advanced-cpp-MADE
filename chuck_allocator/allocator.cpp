#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Allocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const  T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    template<class U>
    struct rebind {
        typedef allocator<U> other;
    };

    T* allocate(const size_t n) {
        return (T*)(new char[n * sizeof(T)]);
    }

    void deallocate(T* pointer, const size_t n) {
        delete[](char*)pointer;

    }
    template <typename ... Args>
    void construct(T* pointer, const Args&&... args) {
        new (pointer) T(args...);
    }

    void destroy(T* pointer) {
        pointer->~T();
    }
};


class A {
public:
    A(int x, int y) {
        std::cout << x << " " << y << "\n";
    }
    ~A() {
        std::cout << "~\n";
    }

};

int main() {
    Allocator<A> alloc;
    auto p = alloc.allocate(1);

    alloc.construct(p, 1, 2);
    alloc.destroy(p);
    alloc.deallocate(p, 1);

    std::vector <A, Allocator<A>> vec;
    vec.push_back(A(1, 2));

    return 0;
}











/*int main() {
    std::allocator<int> alloc;

    int *arr = alloc.allocate(10);

    alloc.deallocate(arr,10);

    alloc.construct(p, 3);
    alloc.construct(p+1, 4);
    alloc.destroy(p);

    return 0;
}*/














/*void handler() {
    std::cout << "Memory allocation failed, terminating\n";
    std::set_new_handler(nullptr);
}

int main() {

    std::set_new_handler(handler);

    try {
        while (true) {
            new int[100000000ul];
        }
    }
    catch (const std::bad_alloc& e) {
        std::cout << e.what() << "\n";
    }
    return 0;
}*/