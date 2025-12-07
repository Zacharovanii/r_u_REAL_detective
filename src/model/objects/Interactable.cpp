#include "model/objects/Interactable.h"

Interactable::Interactable(
    Position initial_pos,
    std::string name,
    std::string description
    ) : Object(initial_pos, std::move(name), std::move(description)) {}