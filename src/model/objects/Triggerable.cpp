#include "model/objects/Triggerable.h"

Triggerable::Triggerable(
    const Position& initial_pos,
    const std::string& name,
    const std::string& description
    ) : Object(initial_pos, name, description) {}