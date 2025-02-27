#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <parking_spot_cpp/lib/globals.h>

template <typename T>
class vector : public std::vector<T> {
public:
    void push_sorted(const T& r);
    void push_recursive(const vector<T>& v2);
    // void remove_duplicates_unsorted();
    void remove_duplicates();
    void sort();
};

#include "vector.tpp"
#endif // VECTOR_H