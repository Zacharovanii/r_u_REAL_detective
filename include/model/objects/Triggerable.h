#pragma once
#include "Object.h"
#include "model/Player.h"

class Triggerable : public Object {
public:
    Triggerable(
        Position initial_pos,
        std::string name,
        std::string description
        );

    virtual void trigger(Player& player) = 0;
};
