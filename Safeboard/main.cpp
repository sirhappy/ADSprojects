#include <iostream>
#include <limits>

using namespace std;

constexpr unsigned fact(unsigned n)
{
    return n == 0 ? 1 : n * fact(n - 1);
}

template<unsigned N>
struct factorial {
    static constexpr unsigned value = fact(N);
};

static_assert(factorial<5>::value == 120);

int main()
{
    string first, second;
    cin >> first >> second;

    string& bigger = first.length() > second.length() ? first : second;
    string& lesser = first.length() > second.length() ? second : first;

    char shift = '0';
    for (size_t i = lesser.length() - 1, j = bigger.length() - 1;
         i != numeric_limits<size_t>::max();
         --i, --j)
    {
        int tmp = bigger[j] - '0';
        bigger[j] = static_cast<char>(((tmp + lesser[i] + shift - 2 * '0') % 10) + '0');
        shift = static_cast<char>(((tmp + lesser[i] + shift - 2 * '0') / 10) + '0');
    }

    if (shift != '0')
        cout << shift;
    for (const auto digit:bigger)
        cout << digit;
    return 0;
}
// Критерием прохождения задания является успешная компиляция кода.

