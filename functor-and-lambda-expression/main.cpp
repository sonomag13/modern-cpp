#include <algorithm>
#include <iostream>
#include <vector>
#include <type_traits>

auto data = std::vector{94, 40, 78, 60, 66, 79, 79, 70, 37, 60, 84, 48, 9, 100, 42, 56, 91, 26, 90, 98};

template<class T>
concept isCompariable = requires(T) {
    std::is_floating_point_v<T>;
    std::is_integral_v<T>;
};

template<class T>
requires isCompariable<T>
struct AscendingComparatorFunctor {
public:
    bool operator()(T & first, T & second) const {
        return first < second;
    }
};

template<class T>
std::ostream & operator << (std::ostream & os, const std::vector<T> & vec) {

    for (auto & el : vec) {
        std::cout << el << " ";
    }

    return os;
}

int main() {

    std::cout << "original data\n\t" << data << '\n';

    std::vector<int> data1(data);
    std::sort(data1.begin(), data1.end(), AscendingComparatorFunctor<int>());
    std::cout << "data sorted by functor\n\t" << data1 << '\n';

    auto AscendingComparatorLambdaExp = []<class T>(const T & first, const T & second) -> bool {
        return first < second;
    };
    std::vector<int> data2(data);
    std::sort(data2.begin(), data2.end(), AscendingComparatorLambdaExp);
    std::cout << "data sorted by lambda expression\n\t" << data2 << '\n';

    return 0;
}
