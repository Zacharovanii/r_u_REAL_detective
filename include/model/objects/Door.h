#pragma once
#include <string>
#include "Triggerable.h"

class Door : public Triggerable {
    std::string target_location;
    Position target_pos;
    Position end_line_point;
    bool isLine;

    Door(Position initial_pos,
        std::string target_location,
        Position target_pos,
        Position end_line_point,
        bool isLine
        );
public:
    Door(
        Position initial_pos,
        std::string target_location,
        Position target_pos
        );
    Door(Position initial_pos,
        std::string target_location,
        Position target_pos,
        Position end_line_point
        );

    void trigger(Player& player) override;

    [[nodiscard]] std::string getTargetLocation() const;
    [[nodiscard]] Position getTargetPosition() const;
    bool isTriggered(Position pos) const;
};