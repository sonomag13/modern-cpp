#include <iostream>
#include <type_traits>

/*
 * Ref.:
 * https://www.bilibili.com/video/BV1WaNDeQEFV/?spm_id_from=333.337.search-card.all.click&vd_source=8018741d8c857acba8ff733606fba4b4
 */

/*
 * the old way to check if a template function should or should not be allowed
 *
 * std::enable_if_t<std::is_integral_v<T>, std::string> is so called alias template, meaning:
 *  - if T is an integer, then the return type is std::string
 *  - if not, the alias does not exist (SFINAE removes it from overload resolution).
 */
template<class T>
std::enable_if_t<std::is_integral_v<T>, std::string>
checkParity(T val) {

    return val % 2 == 0 ? "even" : "odd";
}

/*
 * after C++ 20, concept is introduced to simplify the template alias as shown above
 */
template<std::integral T>
T getRemainder1(T val) {
    return val % 2 == 0 ? 0 : 1;
}

/*
 * Alternatively we can do
 */
template<class T>
constexpr bool isInteger = std::is_integral_v<T>;

template<class T>
requires isInteger<T>
T getRemainder2(T val) {

    return val % 2 == 0 ? 0 : 1;
}

/*
 * but what about we have many constraints? Use concept to make all the constraints in a clean way~!
 */
template<class T>
concept isComputable = requires {
    std::is_integral_v<T>;
    sizeof(T) <= sizeof(void *);
};

template<class T>
requires isComputable<T>
T getRemainder3(T val) {

    return val % 2 == 0 ? 0 : 1;
}

int main() {

    auto parity = checkParity(10);
    std::cout << "parity = " << parity << std::endl;

    /*
     * cannot compile since there is not overloading function for getRemainder(float)
     * To make it better, the error message tells us easy answer why it fails : )
     * note: candidate template ignored: requirement 'std::is_integral_v<float>' was not satisfied [with T = float]
     */
    // auto parity = getRemainder(10.0f);
    // std::cout << "parity = " << parity << std::endl;

    auto remainder1 = getRemainder1(10);
    std::cout << "remainder1 = " << remainder1 << std::endl;

    auto remainder2 = getRemainder2(11);
    std::cout << "remainder2 = " << remainder2 << std::endl;

    auto remainder3 = getRemainder2(11);
    std::cout << "remainder3 = " << remainder3 << std::endl;

    return 0;
}
