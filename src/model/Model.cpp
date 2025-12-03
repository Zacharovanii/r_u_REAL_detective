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

    auto [dx, dy] = offset(direction);

    // Безопасное преобразование и вычисление
    ptrdiff_t new_x = static_cast<ptrdiff_t>(player.getX()) + dx;
    ptrdiff_t new_y = static_cast<ptrdiff_t>(player.getY()) + dy;

    // Защита от отрицательных координат
    if (new_x < 0 || new_y < 0) {
        return;
    }

    auto final_x = static_cast<size_t>(new_x);
    auto final_y = static_cast<size_t>(new_y);

    if (location->canMoveTo(final_x, final_y)) {
        player.setPositionAt(final_x, final_y);
        scanAroundPlayer();
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
    // Нужно снять const для вызова неконстантного метода interact()
    // Безопасно, так как мы владеем объектом
    const_cast<Interactable*>(interactable)->interact(player);
}
