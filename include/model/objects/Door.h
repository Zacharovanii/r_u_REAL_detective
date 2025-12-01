#pragma once
#include <string>
#include <utility>
#include "Interactable.h"

class Door : public Interactable {
    std::string target_location;
    Position target_pos;
    bool is_open;

public:
    Door(const Position& initial_pos, const std::string& name, const std::string& description,
         const std::string& target_location, const Position& target_pos, bool open = true);

    void interact(Player& player) override;

    [[nodiscard]] std::string getTargetLocation() const;
    [[nodiscard]] Position getTargetPosition() const;
    [[nodiscard]] bool isOpen() const;

    void open();
    void close();
};