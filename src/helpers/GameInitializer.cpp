#include "helpers/GameInitializer.h"
#include "helpers/MapLoader.h"
#include "model/Location.h"
#include "model/objects/Door.h"
#include "model/objects/NPC.h"

void GameInitializer::initGameWorld(Map& map)
{
    Location hotel_1f(MapLoader::loadByName("hotel_1f"));
    Location hotel_2f(MapLoader::loadByName("hotel_2f"));
    Location street(MapLoader::loadByName("street"));
    Location park(MapLoader::loadByName("park"));
    Location waterside(MapLoader::loadByName("waterside"));
    Location bar(MapLoader::loadByName("bar"));

    // ================================PARK===================================
    park.addDoor(Door(
        Position{0, 6},
        "hotel_1f",
        Position{62, 7},
        {0, 8}
    ));
    park.addDoor(Door(
        Position{12, 0},
        "Waterside",
        Position{10, 6},
        {16, 0}
    ));
    park.addDoor(Door(
        Position{28, 6},
        "Bar",
        Position{1, 5},
        Position{28, 8}
    ));
    park.addDoor(Door(
        Position{12,14},
        "Street",
        Position{13, 1},
        Position{16, 14}
    ));

    park.addInteractable(std::make_unique<NPC>(
        Position{14, 7},
        "Предысловие",
        "Рекомендуется к прочтению",
        "",
        "prologue"
    ));
    // =======================================================================

    waterside.addDoor(Door(
        Position{8, 7},
        "Park",
        Position{14, 1},
        {12, 7}
    ));
    bar.addDoor(Door(
        Position{0, 4},
        "Park",
        Position{27, 7},
        Position{0, 6}
    ));
    hotel_1f.addDoor(Door(
        Position{63, 6},
        "Park",
        Position{1, 7},
        Position{63, 8}
    ));
    street.addDoor(Door(
        Position{11, 0},
        "Park",
        Position{14, 13},
        Position{15, 0}
    ));

    hotel_1f.addDoor(Door(
        Position{30, 3},
        "hotel_2f",
        Position{30, 4}
    ));

    hotel_2f.addDoor(Door(
       Position{30, 3},
       "hotel_1f",
       Position{30, 4}
   ));

    // ========================= ДОБАВЛЕНИЕ ВСЕХ ПОДОЗРЕВАЕМЫХ NPC =========================

    // Х — Хозяин отеля
    hotel_1f.addInteractable(std::make_unique<NPC>(
        Position(14, 9),
        "Роберт",
        "Хозяин отеля",
        "Angry",
        "hotel_owner"
    ));

    // О — Охранник
    bar.addInteractable(std::make_unique<NPC>(
        Position(25, 9),
        "Виктор",
        "Охранник",
        "Aggressive",
        "guard"
    ));

    // С — Стриптизёрша
    bar.addInteractable(std::make_unique<NPC>(
        Position(40, 5),
        "Стеффани",
        "Стриптизёрша",
        "Flirty",
        "stripper"
    ));

    // Д — Слепой дед
    waterside.addInteractable(std::make_unique<NPC>(
        Position(18 ,3),
        "Димон",
        "Слепой дед",
        "Suspicious",
        "blind_man"
    ));

    // П — Очкарик
    hotel_2f.addInteractable(std::make_unique<NPC>(
        Position(9, 5),
        "Френк",
        "Постоялец",
        "Nervous",
        "fan"
    ));

    // Б — Бабушка
    street.addInteractable(std::make_unique<NPC>(
        Position(37, 7),
        "Елизавета",
        "Бабушка",
        "Grumpy",
        "granny"
    ));

    map.addLocation("hotel_1f", std::move(hotel_1f));
    map.addLocation("hotel_2f", std::move(hotel_2f));
    map.addLocation("Street", std::move(street));
    map.addLocation("Park", std::move(park));
    map.addLocation("Waterside", std::move(waterside));
    map.addLocation("Bar", std::move(bar));
}