#ifndef SCENE_HPP
# define SCENE_HPP

# include <QLinkedList>
# include "brick.hpp"
# include "rope.hpp"

class Scene
{
public:
    QLinkedList<Brick> bricks;
    QLinkedList<Rope> rope;

    inline Scene() : bricks(QLinkedList<Brick>()), rope(QLinkedList<Rope>())
    {}

    inline Scene(QLinkedList<Brick> bricks, QLinkedList<Rope> rope) : bricks(bricks), rope(rope)
    {}
};

#endif /* SCENE_HPP */
