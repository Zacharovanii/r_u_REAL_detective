#include "model/dialogue/DialogueNode.h"

bool DialogueChoice::checkCondition(const Player& player) const {
    if      (condition_id == "has_badge") return player.getBadges() >= 1;
    else if (condition_id == "has_money") return player.getMoney() >= 1;
    else if (condition_id == "has_flirt") return player.getFlirt() >= 1;
    else if (condition_id == "has_health") return player.getHealth() > 0;
    else return true;
}

void DialogueChoice::runAction(Player& player) const {
    if      (action_id == "remove_badge") player.changeBadges(-1);
    else if (action_id == "remove_money") player.changeMoney(-1);
    else if (action_id == "remove_flirt") player.changeFlirt(-1);
    else if (action_id == "take_damage") player.changeHealth(-1);
    else if (action_id == "heal") player.changeHealth(+1);
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