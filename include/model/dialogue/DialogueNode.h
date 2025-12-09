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
    std::function<bool()> on_select = nullptr;

    DialogueChoice(
        std::string t, std::string next,
        std::string c_id, std::string a_id,
        std::function<bool()> on_sel = nullptr)
        :
    text(std::move(t)),
    next_node_id(std::move(next)),
    condition_id(std::move(c_id)),
    action_id(std::move(a_id)),
    on_select(std::move(on_sel))
    {}

    bool checkCondition(Player& player) {
        if (condition_id == "has_badge") return player.getBadges() >= 1;
        if (condition_id == "has_money") return player.getMoney() >= 1;
        if (condition_id == "has_flirt") return player.getFlirt() >= 1;
        if (condition_id == "has_health") return player.getHealth() > 0;
        return true; // если условие пустое или неизвестное
    }

    // Выполнение действий
    void runAction(Player& player) {
        if (action_id == "remove_badge") player.changeBadges(-1);
        if (action_id == "remove_money") player.changeMoney(-1);
        if (action_id == "remove_flirt") player.changeFlirt(-1);
        if (action_id == "take_damage") player.changeHealth(-1);
        if (action_id == "heal") player.changeHealth(+1);
    }
};

struct DialogueNode {
    std::string id;
    std::string speaker;
    std::string text;
    std::vector<DialogueChoice> choices;
    std::function<void()> on_enter;
};