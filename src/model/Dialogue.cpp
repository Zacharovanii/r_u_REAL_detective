#include "model/Dialogue.h"
#include <iostream>

Dialogue::Dialogue(const std::string& id) : dialogue_id(id) {}

void Dialogue::addNode(const DialogueNode& node) {
    nodes[node.id] = node;
}

void Dialogue::start(const std::string& start_node_id) {
    current_node_id = start_node_id;
    finished = false;
    
    if (auto node = getCurrentNode()) {
        if (node->on_enter) {
            node->on_enter();
        }
    }
}

bool Dialogue::makeChoice(size_t choice_index) {
    auto node = getCurrentNode();
    if (!node || choice_index >= node->choices.size()) {
        return false;
    }
    
    const auto& choice = node->choices[choice_index];
    if (choice.on_select) {
        choice.on_select();
    }
    
    if (choice.next_node_id.empty() || choice.next_node_id == "end") {
        end();
    } else {
        current_node_id = choice.next_node_id;
        if (auto next_node = getCurrentNode()) {
            if (next_node->on_enter) {
                next_node->on_enter();
            }
        }
    }
    
    return true;
}

void Dialogue::end() {
    // std::cout << "Debug: Dialogue::end() called for dialogue: " << dialogue_id << std::endl;
    finished = true;
    current_node_id.clear();
    // std::cout << "Debug: Dialogue finished, current_node_id cleared" << std::endl;
}

bool Dialogue::isActive() const {
    bool result = !finished && !current_node_id.empty();
    // std::cout << "Debug: Dialogue::isActive() = " << result << " (finished: " << finished << ", current_node_id: '" << current_node_id << "')" << std::endl;
    return result;
}

const DialogueNode* Dialogue::getCurrentNode() const {
    auto it = nodes.find(current_node_id);
    return it != nodes.end() ? &it->second : nullptr;
}