#include "model/dialogue/Dialogue.h"
#include <iostream>

Dialogue::Dialogue(std::string id) : dialogue_id(std::move(id)) {}

void Dialogue::addNode(const DialogueNode& node) { nodes[node.id] = node; }
bool Dialogue::isActive() const { return !finished && !current_node_id.empty(); }

DialogueNode* Dialogue::getCurrentNode() {
    auto it = nodes.find(current_node_id);
    return it != nodes.end() ? &it->second : nullptr;
}
void Dialogue::start(const std::string& start_node_id) {
    current_node_id = start_node_id;
    finished = false;
}
void Dialogue::end() {
    finished = true;
    current_node_id.clear();
}

bool Dialogue::makeChoice(size_t choice_index, Player& player) {
    auto node = getCurrentNode();
    if (!node || choice_index >= node->choices.size()) {
        return false;
    }

    auto& choice = node->choices[choice_index];

    if (choice.checkCondition(player))
        choice.runAction(player);
    else if (nodes.contains("no_resources")) {
        current_node_id = "no_resources";
        return false;
    }

    if (choice.next_node_id.empty() || choice.next_node_id == "end")
        end();
    else
        current_node_id = choice.next_node_id;

    return true;
}