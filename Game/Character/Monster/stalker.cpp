#include "stalker.h"

void Stalker::stalk(int end_i, int end_j)
{
    std::stack<Direction> directions_stack;
    directions_stack = shortPass(pos_i, pos_j, end_i, end_j);
    for (int i = 0; i < speed; i++) {
        setDirection(directions_stack.top());
        directions_stack.pop();
        move();
    }
}

Stalker::Stalker(int new_speed, int new_accuracy,
                 int new_dodge, int new_range_damage,
                 int new_critical, int new_pos_i,
                 int new_pos_j, std::string new_img_way, Direction new_eye_direction = DOWN) : Walker(new_speed, new_accuracy,
                                                                             new_dodge, new_range_damage,
                                                                             new_critical, new_pos_i,
                                                                             new_pos_j,new_img_way ,new_eye_direction)
{
}

void Stalker::walkOrStalk(Object *player)
{
    int xb = this->pos_i - 5, xe = this->pos_i + 5, yb = this->pos_j - 5, ye = this->pos_j + 5;
    int end_i = player->getPosI(), end_j = player->getPosJ();
    if (hasPoint(end_i, end_j)) stalk(end_i, end_j);
    else walk();
}
