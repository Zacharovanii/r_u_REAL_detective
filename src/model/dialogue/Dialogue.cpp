#include "model/dialogue/Dialogue.h"
#include <iostream>

Dialogue::Dialogue(std::string id) : dialogue_id(std::move(id)) {}

void Dialogue::callEnterFor(const DialogueNode& node) {
    if (node.on_enter) node.on_enter();
}
void Dialogue::callEnterFor(const DialogueNode* node) {
    if (node && node->on_enter) node->on_enter();
}

void Dialogue::addNode(const DialogueNode& node) {
    nodes[node.id] = node;
}

void Dialogue::start(const std::string& start_node_id) {
    current_node_id = start_node_id;
    finished = false;

    callEnterFor(getCurrentNode());
}

const DialogueNode* Dialogue::getCurrentNode() const {
    auto it = nodes.find(current_node_id);
    return it != nodes.end() ? &it->second : nullptr;
}

bool Dialogue::makeChoice(size_t choice_index) {
    auto node = getCurrentNode();
    if (!node || choice_index >= node->choices.size()) {
        return false;
    }
    
    const auto& choice = node->choices[choice_index];
    if (choice.on_select) choice.on_select();
    
    if (choice.next_node_id.empty() || choice.next_node_id == "end") {
        end();
    } else {
        current_node_id = choice.next_node_id;
        callEnterFor(getCurrentNode());
    }
    
    return true;
}

void Dialogue::end() {
    finished = true;
    current_node_id.clear();
}

bool Dialogue::isActive() const {
    return !finished && !current_node_id.empty();
}