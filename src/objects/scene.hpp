#ifndef SCENE_HPP
# define SCENE_HPP

# include "brick.hpp"
# include "rope.hpp"
# include "buffer.hpp"

class Scene
{
public:
    Buffer<Brick> bricks;
    Buffer<Rope> ropes;

    inline Scene() : bricks(Buffer<Brick>()), ropes(Buffer<Rope>())
    {}

    inline Scene(Buffer<Brick> bricks, Buffer<Rope> ropes) : bricks(bricks), ropes(ropes)
    {}

    inline Scene copy() const noexcept
    {
        return {this->bricks.copy(), this->ropes.copy()};
    }
};

#endif /* SCENE_HPP */
