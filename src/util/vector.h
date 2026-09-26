#ifndef THALLIUM_VECTOR_H
#define THALLIUM_VECTOR_H

#include <vector>
#include <iterator>

template <typename T, size_t N>
std::vector<T> vectorFromArray(const T (&arr)[N]);

#endif
