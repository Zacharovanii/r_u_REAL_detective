#include "model/objects/NPC.h"

NPC::NPC(
    Position initial_pos,
    std::string name,
    std::string description,
    std::string attitude,
    std::string dialogue_id,
    const std::function<void(const std::string&)>& start_dialogue_callback
    ) : Interactable(initial_pos, std::move(name), std::move(description)),
      attitude(std::move(attitude)),
      dialogue_id(std::move(dialogue_id)),
      start_dialogue_callback(start_dialogue_callback)
{}

std::string NPC::getDialogueId() const { return dialogue_id; }
std::string NPC::getAttitude() const { return attitude; }
void NPC::setAttitude(const std::string& new_attitude) { attitude = new_attitude; }

void NPC::interact() {
    if (start_dialogue_callback) {
        start_dialogue_callback(dialogue_id);
    }
}