#pragma once

namespace maj::gate {

template<typename T>
constexpr T maj3(T a, T b, T c)
{
    return (a & b) | (a & c) | (b & c);
}

static inline void maj3_static_test()
{
    static_assert(maj3(0, 0, 0) == 0);
    static_assert(maj3(1, 0, 0) == 0);
    static_assert(maj3(1, 1, 0) == 1);
    static_assert(maj3(1, 1, 1) == 1);
    static_assert(maj3(0, 1, 1) == 1);
    static_assert(maj3(0b0101, 0b1100, 0b0011) == 0b0101);
}

template<typename T>
constexpr T inv(T a)
{
    return ~a;
}

template<typename T>
constexpr T aoi222_macro(T a, T b, T c, T d, T e, T f)
{
    return ~((a & b) | (c & d) | (e & f));
}

static inline void maj3_is_aoi222_static_test()
{
    static_assert(
        maj3(0b0101, 0b1100, 0b0011) ==
        inv(aoi222_macro(
            0b0101, 0b1100, 0b0011,
            0b0101, 0b1100, 0b0011)));
}

template<typename T>
constexpr T buf(T a)
{
    return maj3(a, a, a);
}

template<typename T>
constexpr T nbuf(T a)
{
    return maj3(a, ~a, ~a);
}

static inline void buf_static_test()
{
    static_assert(buf(0b0101) == 0b0101);
    static_assert(nbuf(0b0101) == ~0b0101);
}

template<typename T>
constexpr T or2(T a, T b)
{
    return maj3(a, b, ~(T)0);
}

template<typename T>
constexpr T nor2(T a, T b)
{
    return ~or2(a, b);
}

static inline void or2_static_test()
{
    static_assert(or2(0b0101, 0b1100) == 0b1101);
    static_assert(nor2(0b0101, 0b1100) == ~0b1101);
}

template<typename T>
constexpr T and2(T a, T b)
{
    return maj3(a, b, (T)0);
}

template<typename T>
constexpr T nand2(T a, T b)
{
    return ~and2(a, b);
}

static inline void and2_static_test()
{
    static_assert(and2(0b0101, 0b1100) == 0b0100);
    static_assert(nand2(0b0101, 0b1100) == ~0b0100);
}

template<typename T>
constexpr T xor2(T a, T b)
{
    return or2(and2(a,~b), and2(~a,b));
}

static inline void xor2_static_test()
{
    static_assert(xor2(0b0101, 0b1100) == 0b1001);
}

template<typename T>
constexpr T mux2(T a, T b, T sel)
{
    return or2(and2(a,~sel), and2(b,sel));
}

static inline void mux2_static_test()
{
    static_assert(mux2(0b0101, 0b1110, 0b0011) == 0b0110);
}

} // namespace maj::gate
