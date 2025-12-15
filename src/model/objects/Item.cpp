#include "model/objects/Item.h"

Item::Item(
    Position initial_pos,
    std::string name,
    std::string description,
    std::string dialogue_id
):
    Interactable(initial_pos, std::move(name), std::move(description)),
    dialogue_id(std::move(dialogue_id))
{}
std::string Item::getDialogueId() const { return dialogue_id; }

dialogueID Item::interact() {
    return dialogue_id;
}