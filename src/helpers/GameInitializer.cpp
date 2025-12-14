#include "helpers/GameInitializer.h"
#include "helpers/MapLoader.h"
#include "model/Location.h"
#include "model/objects/Door.h"
#include "model/objects/NPC.h"

void GameInitializer::initGameWorld(Map& map) {
    Location hotel_1f(MapLoader::loadByName("hotel_1f"), "Hotel First Floor");
    Location hotel_2f(MapLoader::loadByName("hotel_2f"), "Hotel Second Floor");
    Location street(MapLoader::loadByName("street"), "Street");
    Location park(MapLoader::loadByName("park"), "Park");

    // Добавляем двери в локации
    // Дверь с 1 этажа на 2 этаж
    hotel_1f.addDoor(Door(
        Position{28, 3},
        "hotel_2f",
        Position{23, 8}
    ));

    hotel_1f.addDoor(Door(
        Position{35, 5},
        "street",
        Position{1, 1}
    ));

    park.addDoor(Door(
        Position{0, 6},
        "hotel_1f",
        Position{1, 1},
        {0, 8}
    ));

        // ========================= ДОБАВЛЕНИЕ ВСЕХ ПОДОЗРЕВАЕМЫХ NPC =========================
    int startX = 15;
    int y = 7;

    // Х — Хозяин отеля
    hotel_1f.addInteractable(std::make_unique<NPC>(
        Position(startX + 0, y),
        "Роберт",
        "Хозяин отеля",
        "Angry",
        "hotel_owner"
    ));

    // О — Охранник
    hotel_1f.addInteractable(std::make_unique<NPC>(
        Position(startX + 1, y),
        "Виктор",
        "Охранник",
        "Aggressive",
        "guard"
    ));

    // С — Стриптизёрша
    hotel_1f.addInteractable(std::make_unique<NPC>(
        Position(startX + 2, y),
        "Стеффани",
        "Стриптизёрша",
        "Flirty",
        "stripper"
    ));

    // Д — Слепой дед
    hotel_1f.addInteractable(std::make_unique<NPC>(
        Position(startX + 3, y),
        "Димон",
        "Слепой дед",
        "Suspicious",
        "blind_man"
    ));

    // П — Очкарик
    hotel_1f.addInteractable(std::make_unique<NPC>(
        Position(startX + 4, y),
        "Френк",
        "Постоялец",
        "Nervous",
        "fan"
    ));

    // Б — Бабушка
    hotel_1f.addInteractable(std::make_unique<NPC>(
        Position(startX + 5, y),
        "Елизавета",
        "Бабушка",
        "Grumpy",
        "granny"
    ));


    // Дверь со 2 этажа на 1 этаж
    hotel_2f.addDoor(Door(
        Position{23, 7},
        "hotel_1f",
        Position{28, 4}
    ));


    street.addDoor(Door(
        Position{1, 3},
        "hotel_1f",
        Position{34, 5}
    ));

    map.addLocation("hotel_1f", std::move(hotel_1f));
    map.addLocation("hotel_2f", std::move(hotel_2f));
    map.addLocation("street", std::move(street));
    map.addLocation("Park", std::move(park));
}