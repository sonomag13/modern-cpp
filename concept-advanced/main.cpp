#include <iostream>
#include <type_traits>

/*
 * Ref.:
 * https://www.bilibili.com/video/BV1X8A5e8ECA?spm_id_from=333.788.videopod.sections&vd_source=8018741d8c857acba8ff733606fba4b4
 */

class C1 {
public:
    static void f() {
        std::cout << "I am function f" << '\n';
    }
};

class C2 {};

class C3 {
public:
    int f{100};
};

class C4 {
public:
    static int f() {
        return 0;
    };
};

template<class T>
concept hasVoidFuncFunction = requires(T t) {
    {t.f()} -> std::same_as<void>;
};

template<class T>
concept hasIntFuncFunction = requires(T t) {
    {t.f()} -> std::same_as<int>;
};

template<class T>
concept hasIntVar = requires(T t) {
    {t.f} -> std::same_as<int&>;
};

// the simplest way
void callVoidFunc1(hasVoidFuncFunction auto t) {
    t.f();  // we need concept to require T is C1
}

// alternatively, more formal
template<class T>
requires hasVoidFuncFunction<T>
void callVoidFunc2(T t) {
    t.f();  // T::f() works better, but let us just make a point here
}

void callIntFunc(hasIntFuncFunction auto t) {
    auto val = t.f();  // we need concept to require T is C4
    std::cout << val << '\n';
}

void callHasIntVar(hasIntVar auto t) {
    auto val = t.f;  // we need concept to require T is C4
    std::cout << val << '\n';
}

int main() {

    callVoidFunc1(C1{});
    // following classes do not satisfy the concept hasVoidFuncFunction
    // callVoidFunc(C2{});
    // callVoidFunc(C3{});
    // callVoidFunc(C4{});

    callVoidFunc2(C1{});

    callIntFunc(C4{});
    // following classes do not satisfy the concept hasIntFuncFunction
    // callIntFunc(C1{});
    // callIntFunc(C2{});
    // callIntFunc(C3{});

    callHasIntVar(C3{});

    return 0;
}
