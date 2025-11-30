#include "model/Model.h"
#include "helpers/MapLoader.h"
#include "helpers/GameInitializer.h"
#include "helpers/DialogueInitializer.h"
#include "helpers/ServiceLocator.h"

Model::Model() : player(1, 1){
    GameInitializer::initGameWorld(game_map, dialogue_manager);
    GameInitializer::loadStartLocation(game_map, player, "hotel_1f");
    DialogueInitializer::initializeDialogues(dialogue_manager);

    ServiceLocator::provide(&dialogue_manager);
}

const Player& Model::getPlayer() const {
    return player;
}

const Map& Model::getMap() const {
    return game_map;
}

const Location* Model::getCurrentLocation() const {
    return game_map.getCurrentLocation();
}

const std::string& Model::getCurrentLocationName() const {
    return game_map.getCurrentLocationName();
}

void Model::moveUp() {
    const Location* location = getCurrentLocation();
    if (!location) return;

    size_t new_x = player.getX();
    size_t new_y = player.getY() - 1;

    if (location->canMoveTo(new_x, new_y)) {
        player.setPositionAt(new_x, new_y);
    }
}

void Model::moveDown() {
    const Location* location = getCurrentLocation();
    if (!location) return;

    size_t new_x = player.getX();
    size_t new_y = player.getY() + 1;

    if (location->canMoveTo(new_x, new_y)) {
        player.setPositionAt(new_x, new_y);
    }
}

void Model::moveLeft() {
    const Location* location = getCurrentLocation();
    if (!location) return;

    size_t new_x = player.getX() - 1;
    size_t new_y = player.getY();

    if (location->canMoveTo(new_x, new_y)) {
        player.setPositionAt(new_x, new_y);
    }
}

void Model::moveRight() {
    const Location* location = getCurrentLocation();
    if (!location) return;

    size_t new_x = player.getX() + 1;
    size_t new_y = player.getY();

    if (location->canMoveTo(new_x, new_y)) {
        player.setPositionAt(new_x, new_y);
    }
}

void Model::update() {
    game_map.interactWithDoorAt(player, player.getX(), player.getY());

    size_t x = player.getX();
    size_t y = player.getY();
    if (game_map.getCurrentLocation()->hasInteractableAt(x, y)) {
        game_map.interactAt(player, x, y);
    }
}

DialogueManager& Model::getDialogueManager() { return dialogue_manager; }
const DialogueManager& Model::getDialogueManager() const { return dialogue_manager; }
bool Model::isInDialogue() const { return dialogue_manager.isInDialogue(); }

// Утилиты для отображения (можно оставить для совместимости)
size_t Model::getMapSizeY() const {
    const Location* location = getCurrentLocation();
    if (!location) return 0;

    const auto& tiles = location->getTiles();
    return tiles.size();
}

size_t Model::getMapSizeX() const {
    const Location* location = getCurrentLocation();
    if (!location) return 0;

    const auto& tiles = location->getTiles();
    return tiles.empty() ? 0 : tiles[0].size();
}

size_t Model::getMapSizeX(size_t y) const {
    const Location* location = getCurrentLocation();
    if (!location) return 0;

    const auto& tiles = location->getTiles();
    return y < tiles.size() ? tiles[y].size() : 0;
}