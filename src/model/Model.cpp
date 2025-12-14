#include "model/Model.h"
#include "helpers/MapLoader.h"
#include "helpers/GameInitializer.h"
#include "helpers/DialogueInitializer.h"

Model::Model() : player(14, 11) {
    GameInitializer::initGameWorld(game_map);
    DialogueInitializer::initializeDialogues(dialogue_manager);
    game_map.setCurrentLocation("Park");
}

const Player& Model::getPlayer() const { return player; }
Location* Model::getCurrentLocation() { return game_map.getCurrentLocation(); }
const std::string& Model::getCurrentLocationName() const { return game_map.getCurrentLocationName(); }

DialogueManager& Model::getDialogueManager() { return dialogue_manager; }
bool Model::isInDialogue() const { return dialogue_manager.isInDialogue(); }

std::vector<Interactable*> Model::getNearbyInteractables() const { return nearby_interactables; }

void Model::movePlayer(Direction direction) {
    const Location* location = getCurrentLocation();
    if (!location) return;

    Offset pos_offset = getOffsetFor(direction);
    int nx = static_cast<int>(player.getX()) + pos_offset.dx;
    int ny = static_cast<int>(player.getY()) + pos_offset.dy;

    if (nx < 0 || ny < 0) {
        return;
    }

    Position new_pos = {static_cast<size_t>(nx), static_cast<size_t>(ny)};
    if (location->canMoveTo(new_pos.x, new_pos.y)) {
        player.setPositionAt(new_pos);
        scanAroundPlayer();
    }
}

void Model::update() {
    Location* location = getCurrentLocation();
    if (!location) return;

    if (Door* door = location->getDoorAt(player.getPosition())) {
        game_map.changeLocation(door->getTargetLocation());
        door->trigger(player);
    }
}

size_t Model::getScanStart(size_t n) const { return n > detection_radius ? n - detection_radius : 0; }
size_t Model::getScanEnd(size_t n) const { return n + detection_radius; }

void Model::scanAroundPlayer() {
    nearby_interactables.clear();

    Location* location = getCurrentLocation();
    if (!location) return;

    size_t player_x = player.getX();
    size_t player_y = player.getY();

    size_t start_y = getScanStart(player_y), start_x = getScanStart(player_x);
    size_t end_y = getScanEnd(player_y), end_x = getScanEnd(player_x);

    for (size_t y = start_y; y <= end_y; ++y) {
        for (size_t x = start_x; x <= end_x; ++x) {
            if (x == player_x && y == player_y) continue;

            if (Interactable* interactable = location->getInteractableAt({x, y}))
                nearby_interactables.push_back(interactable);
        }
    }
}

void Model::interactWithNearby(size_t index) {
    if (index >= nearby_interactables.size()) {
        return;
    }
    Interactable* interactable = nearby_interactables[index];
    dialogue_manager.startDialogue(interactable->interact());
}

void Model::makeChoice(size_t index) {
    dialogue_manager.makeChoice(index, player);
}
