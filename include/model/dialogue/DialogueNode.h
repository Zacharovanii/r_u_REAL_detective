#pragma once
#include "model/Player.h"
#include <string>
#include <vector>
#include <functional>

struct DialogueChoice {
    std::string text;
    std::string next_node_id;
    std::string condition_id;
    std::string action_id;

    DialogueChoice(
        std::string t,
        std::string next,
        std::string c_id = "",
        std::string a_id = ""
    ):
        text(std::move(t)),
        next_node_id(std::move(next)),
        condition_id(std::move(c_id)),
        action_id(std::move(a_id))
    {}

    [[nodiscard]] bool checkCondition(const Player& player) const;
    void runAction(Player& player) const;
};

class DialogueNode {
private:
    std::string _id;
    std::string _speaker;
    std::string _text;
    std::vector<DialogueChoice> _choices;

public:
    DialogueNode() = default;

    [[nodiscard]] const std::string& id() const;
    [[nodiscard]] const std::string& speaker() const;
    [[nodiscard]] const std::string& text() const;
    [[nodiscard]] const std::vector<DialogueChoice>& choices() const;

    DialogueNode* id(std::string value);
    DialogueNode* speaker(std::string value);
    DialogueNode* text(std::string value);
    DialogueNode* choice(DialogueChoice value);
};