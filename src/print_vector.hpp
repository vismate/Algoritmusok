#include <iostream>
#include <vector>

// Egy operátor overload a könnyű kiíratásért
template <typename T>
auto operator<<(std::ostream &stream, const std::vector<T> &vec) -> std::ostream &
{
    stream << "[ ";
    for (const auto &elem : vec)
    {
        stream << elem << " ";
    }
    stream << "]";

    return stream;
}
