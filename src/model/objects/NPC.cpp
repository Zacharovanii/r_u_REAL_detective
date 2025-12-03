#include "../../../include/model/objects/NPC.h"
#include "model/dialogue/DialogueManager.h"

NPC::NPC(const Position& initial_pos, const std::string& name,
         const std::string& description, const std::string& attitude,
         const std::string& dialogue_id,
         const std::function<void(const std::string&)>& start_dialogue_callback)
    : Interactable(initial_pos, name, description),
      attitude(attitude),
      dialogue_id(dialogue_id),
      start_dialogue_callback(start_dialogue_callback)
{}

std::string NPC::getDialogueId() const { return dialogue_id; }
std::string NPC::getAttitude() const { return attitude; }
void NPC::setAttitude(const std::string& new_attitude) { attitude = new_attitude; }

void NPC::interact(Player& player) {
    player.setPositionAt(player.getX(), player.getY());
    if (start_dialogue_callback) {
        start_dialogue_callback(dialogue_id);
    }
}