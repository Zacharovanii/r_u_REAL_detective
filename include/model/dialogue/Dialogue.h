#pragma once
#include "DialogueNode.h"
#include <unordered_map>

class Dialogue {
private:
    std::unordered_map<std::string, DialogueNode> nodes;
    std::string dialogue_id;
    std::string current_node_id;
    bool finished = false;

    static void callEnterFor(const DialogueNode& node);
    static void callEnterFor(const DialogueNode* node);

public:
    Dialogue() = default;
    Dialogue(const std::string& id);

    void addNode(const DialogueNode& node);
    bool makeChoice(size_t choice_index);
    void start(const std::string& start_node_id);
    void end();

    bool isFinished() const { return finished; }
    bool isActive() const;

    const DialogueNode* getCurrentNode() const;
    std::string getId() const { return dialogue_id; }
};