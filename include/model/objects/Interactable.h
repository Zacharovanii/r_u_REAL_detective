#pragma once
#include "Object.h"
#include "helpers/Types.h"

class Interactable : public Object {
public:
    Interactable(
        Position initial_pos,
        std::string name,
        std::string description
        );

    virtual dialogueID interact() = 0;
};
