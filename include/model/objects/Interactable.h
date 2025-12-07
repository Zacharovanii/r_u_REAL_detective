#pragma once
#include "Object.h"

class Interactable : public Object {
public:
    Interactable(
        Position initial_pos,
        std::string name,
        std::string description
        );

    virtual void interact() = 0;
};
