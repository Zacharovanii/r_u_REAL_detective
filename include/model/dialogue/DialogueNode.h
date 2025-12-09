#pragma once
#include <string>
#include <vector>
#include <functional>

struct DialogueChoice {
    std::string text;
    std::string next_node_id;
    std::function<bool()> on_select = nullptr;

    DialogueChoice(std::string t, std::string next, std::function<bool()> on_sel = nullptr)
        : text(std::move(t)), next_node_id(std::move(next)), on_select(std::move(on_sel)) {}
};

struct DialogueNode {
    std::string id;
    std::string speaker;
    std::string text;
    std::vector<DialogueChoice> choices;
    std::function<void()> on_enter;
};