#include "model/dialogue/DialogueNode.h"
#include "model/GameState.h"

bool DialogueChoice::checkCondition(const Player& player) const {
    if      (condition_id == "has_badge") return player.getBadges() >= 1;
    else if (condition_id == "has_money") return player.getMoney() >= 1;
    else if (condition_id == "has_money_2") return player.getMoney() >= 2;
    else if (condition_id == "has_flirt") return player.getFlirt() >= 1;
    else if (condition_id == "has_health") return player.getHealth() >= 1;
    else if (condition_id == "has_flirt_hp") return player.getFlirt() >= 1 && player.getHealth() >= 1;
    else if (condition_id == "has_health_2") return player.getMoney() >= 2;
    else return true;
}

void DialogueChoice::runAction(Player& player) const {
    if      (action_id == "remove_badge") player.changeBadges(-1);
    else if (action_id == "remove_money") player.changeMoney(-1);
    else if (action_id == "remove_money_2") player.changeMoney(-2);
    else if (action_id == "remove_flirt") player.changeFlirt(-1);
    else if (action_id == "remove_flirt_plus_hp") {
        player.changeFlirt(-1);
        player.changeHealth(+1);
    } else if (action_id == "take_damage") player.changeHealth(-1);
    else if (action_id == "take_damage_2") player.changeHealth(-2);
    else if (action_id == "remove_flirt_double") {
        player.changeFlirt(-1);
        player.changeHealth(-1);
    }
    else if (action_id == "remove_flirt_plus_money") {
        player.changeFlirt(-1);
        player.changeMoney(+1);
    }
    else if (action_id == "heal") player.changeHealth(+1);
    else if (action_id == "restart") State::requestRestart();
    else if (action_id == "quit") State::requestQuit();
    else return;
}

const std::string& DialogueNode::id() const { return _id; }
const std::string& DialogueNode::speaker() const { return _speaker; }
const std::string& DialogueNode::text() const { return _text; }
const std::vector<DialogueChoice>& DialogueNode::choices() const { return _choices; }

DialogueNode* DialogueNode::id(std::string value) {
    this->_id = std::move(value);
    return this;
}
DialogueNode* DialogueNode::speaker(std::string value) {
    this->_speaker = std::move(value);
    return this;
}
DialogueNode* DialogueNode::text(std::string value) {
    this->_text = std::move(value);
    return this;
}
DialogueNode* DialogueNode::choice(DialogueChoice value) {
    this->_choices.push_back(std::move(value));
    return this;
}