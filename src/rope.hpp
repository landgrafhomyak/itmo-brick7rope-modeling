#ifndef ROPE_HPP
# define ROPE_HPP

# include "brick.hpp"


class Rope {
public:
    Brick *const left;
    Brick *const right;

    long double young_modulus;

    constexpr inline Rope(Brick *const left, Brick *const right, long double young_modulus) noexcept : left(left), right(right), young_modulus(young_modulus)
    {}
};


#endif /* ROPE_HPP */
