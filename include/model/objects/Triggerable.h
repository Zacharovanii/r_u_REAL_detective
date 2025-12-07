#pragma once
#include "Object.h"
#include "model/Player.h"

class Triggerable : public Object {
public:
    Triggerable(
        const Position& initial_pos,
        const std::string& name,
        const std::string& description
        );

    virtual void trigger(Player& player) = 0;
};
