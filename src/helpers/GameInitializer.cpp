#include "helpers/GameInitializer.h"
#include "helpers/MapLoader.h"
#include "model/Location.h"
#include "model/objects/Door.h"
#include "model/objects/NPC.h"

void GameInitializer::initGameWorld(Map& map, DialogueManager& dialogue_manager) {
    // Создаем и настраиваем локации
    Location hotel_1f(MapLoader::loadByName("hotel_1f"), "Hotel First Floor");
    Location hotel_2f(MapLoader::loadByName("hotel_2f"), "Hotel Second Floor");
    Location street(MapLoader::loadByName("street"), "Street");

    // Добавляем двери в локации
    // Дверь с 1 этажа на 2 этаж
    hotel_1f.addDoor(Door(
        Position{28, 3},
        "Stairs to 2F",
        "A staircase leading to the second floor",
        "hotel_2f",
        Position{23, 8},  // позиция появления на 2 этаже
        true
    ));

    hotel_1f.addDoor(Door(
        Position{35, 5},
        "Main Entrance",
        "The main entrance to the hotel",
        "street",
        Position{1, 1},
        true
    ));

    hotel_1f.addInteractable(std::make_unique<NPC>(
        Position(20, 4),
        "Robert",
        "The hotel receptionist",
        "Suspicious",
        "robert_dialogue",
        [&dialogue_manager](const std::string& dialogue_id) {
            dialogue_manager.startDialogue(dialogue_id);
        }
    ));

    // Дверь со 2 этажа на 1 этаж
    hotel_2f.addDoor(Door(
        Position{23, 7},
        "Stairs to 1F",
        "A staircase leading to the first floor",
        "hotel_1f",
        Position{28, 4},
        true
    ));


    street.addDoor(Door(
        Position{1, 3},
        "Hotel Entrance",
        "The entrance to the hotel",
        "hotel_1f",
        Position{34, 5},
        true
    ));

    // Добавляем локации в карту
    map.addLocation("hotel_1f", std::move(hotel_1f));
    map.addLocation("hotel_2f", std::move(hotel_2f));
    map.addLocation("street", std::move(street));
}

std::string GameInitializer::loadStartLocation(Map& map, Player& player, const std::string& initial_location_name) {
    map.setCurrentLocation(initial_location_name);
    player.setPositionAt(1, 1);

    return initial_location_name;
}