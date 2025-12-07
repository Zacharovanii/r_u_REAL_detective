#include "model/objects/Triggerable.h"

Triggerable::Triggerable(
    Position initial_pos,
    std::string name,
    std::string description
    ) : Object(initial_pos, std::move(name), std::move(description)) {}