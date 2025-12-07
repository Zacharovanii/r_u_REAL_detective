#pragma once
#include <string>
#include <utility>
#include "Triggerable.h"

class Door : public Triggerable {
    std::string target_location;
    Position target_pos;
    bool is_open;

public:
    Door(
        Position initial_pos,
        std::string name,
        std::string description,
        std::string target_location,
        Position target_pos,
        bool open = true);

    void trigger(Player& player) override;

    [[nodiscard]] std::string getTargetLocation() const;
    [[nodiscard]] Position getTargetPosition() const;
    [[nodiscard]] bool isOpen() const;

    void open();
    void close();
};