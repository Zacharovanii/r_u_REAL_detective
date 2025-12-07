#include "model/Model.h"
#include "helpers/MapLoader.h"
#include "helpers/GameInitializer.h"
#include "helpers/DialogueInitializer.h"

Model::Model() : player(1, 1){
    GameInitializer::initGameWorld(game_map, dialogue_manager);
    GameInitializer::loadStartLocation(game_map, player, "hotel_1f");
    DialogueInitializer::initializeDialogues(dialogue_manager);
}

const Map& Model::getMap() const {return game_map;}
const Player& Model::getPlayer() const {return player;}

const Location* Model::getCurrentLocation() const {return game_map.getCurrentLocation();}
const std::string& Model::getCurrentLocationName() const {return game_map.getCurrentLocationName();}

const DialogueManager& Model::getDialogueManager() const { return dialogue_manager; }
DialogueManager& Model::getDialogueManager() { return dialogue_manager; }
bool Model::isInDialogue() const { return dialogue_manager.isInDialogue(); }

const std::vector<const Interactable*>& Model::getNearbyInteractables() const {return nearby_interactables;}
size_t Model::getDetectionRadius() const {return detection_radius;}
void Model::setDetectionRadius(size_t radius) {detection_radius = radius;}

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
    game_map.triggerDoorAt(player, player.getX(), player.getY());

    size_t x = player.getX();
    size_t y = player.getY();
    if (game_map.getCurrentLocation()->hasInteractableAt(x, y)) {
        game_map.interactAt(x, y);
    }
}

size_t Model::getScanStart(size_t n) const { return n > detection_radius ? n - detection_radius : 0; }
size_t Model::getScanEnd(size_t n) const { return n + detection_radius; }

void Model::scanAroundPlayer() {
    nearby_interactables.clear();

    const Location* location = getCurrentLocation();
    if (!location) return;

    size_t player_x = player.getX();
    size_t player_y = player.getY();

    size_t start_y = getScanStart(player_y), start_x = getScanStart(player_x);
    size_t end_y = getScanEnd(player_y), end_x = getScanEnd(player_x);

    for (size_t y = start_y; y <= end_y; ++y) {
        for (size_t x = start_x; x <= end_x; ++x) {
            if (x == player_x && y == player_y) continue;

            if (const Interactable* interactable = location->getInteractableAt(x, y))
                nearby_interactables.push_back(interactable);
        }
    }
}

void Model::interactWithNearby(size_t index) {
    if (index >= nearby_interactables.size()) {
        return;
    }
    const Interactable* interactable = nearby_interactables[index];
    const_cast<Interactable*>(interactable)->interact();
}
