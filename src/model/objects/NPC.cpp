#include "model/objects/NPC.h"

NPC::NPC(
    Position initial_pos,
    std::string name,
    std::string description,
    std::string attitude,
    std::string dialogue_id
):
    Interactable(initial_pos, std::move(name), std::move(description)),
    attitude(std::move(attitude)),
    dialogue_id(std::move(dialogue_id))
{}

std::string NPC::getDialogueId() const { return dialogue_id; }
std::string NPC::getAttitude() const { return attitude; }
void NPC::setAttitude(const std::string& new_attitude) { attitude = new_attitude; }

dialogueID NPC::interact() {
    if (alreadyTalked) {
        return "already_talked";
    } else {
        alreadyTalked = true;
        return dialogue_id;
    }
}
