#ifndef BRICK_HPP
# define BRICK_HPP


class Brick
{
public:
    struct Position
    {
    public:
        long double x = 0.0;
        long double y = 0.0;

        constexpr inline Position() noexcept = default;

        constexpr inline Position(long double x, long double y) noexcept: x(x), y(y)
        {}
    };

    Brick::Position pos;
    long double mass;
    char const *name = nullptr;

    inline Brick(long double x, long double y, long double mass) noexcept: pos(Brick::Position(x, y)), mass(mass)
    {}

    inline Brick(long double x, long double y, long double mass, char const *name) noexcept: pos(Brick::Position(x, y)), mass(mass), name(name)
    {}
};

#endif /* BRICK_HPP */
