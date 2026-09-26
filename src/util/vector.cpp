#include "vector.h"

template <typename T, size_t N>
std::vector<T> vectorFromArray(const T (&arr)[N])
{
    return std::vector<T>(std::begin(arr), std::end(arr));
}
