#include "helpers/DialogueInitializer.h"
#include "model/dialogue/Dialogue.h"
#include <iostream>
#include "model/Player.h"

void DialogueInitializer::initializeDialogues(DialogueManager& manager, Player& player) {
    DialogueNode end;
    end.id = "end";
    end.speaker = "";
    end.text = "Вы уходите.";
    end.choices = {};

    // ========================= ХОЗЯИН ОТЕЛЯ (Х) =========================
    Dialogue hotelOwner("hotel_owner");
    DialogueNode no_resources;
    no_resources.id = "no_resources";
    no_resources.speaker = "Хозяин отеля";
    no_resources.text = "Вам не хватает необходимых ресурсов.";
    no_resources.choices = { {"Назад", "start", "", "",nullptr} };

    DialogueNode start;
    start.id = "start";
    start.speaker = "Хозяин отеля";
    start.text = "Я всю ночь простоял за барной стойкой...";
    start.choices = {
        {"Показать жетон", "badge", "has_badge", "remove_badge", nullptr},
        {"Дать деньги", "money", "has_money", "remove_money", nullptr},
        {"Флиртовать", "flirt", "has_flirt", "remove_flirt", nullptr},
        {"Применить силу", "force", "has_health", "take_damage", nullptr}
    };

    DialogueNode badge;
    badge.id = "badge";
    badge.speaker = "Хозяин отеля";
    badge.text = "Вы не просто полицейский, а ФБР? До свидания!";
    badge.choices = { {"Уйти", "end", "", "", nullptr} };

    DialogueNode money;
    money.id = "money";
    money.speaker = "Хозяин отеля";
    money.text = "Слепец с собакой — мой второй подозреваемый.";
    money.choices = { {"Уйти", "end", "", "", nullptr} };

    DialogueNode flirt;
    flirt.id = "flirt";
    flirt.speaker = "Хозяин отеля";
    flirt.text = "Вот вам обед за счет заведения.";
    flirt.choices = { {"Уйти", "end", "", "", nullptr} };

    DialogueNode force;
    force.id = "force";
    force.speaker = "Хозяин отеля";
    force.text = "Вытирая кровь с губ...";
    force.choices = { {"Уйти", "end", "", "", nullptr} };

    hotelOwner.addNode(start);
    hotelOwner.addNode(badge);
    hotelOwner.addNode(money);
    hotelOwner.addNode(flirt);
    hotelOwner.addNode(force);
    hotelOwner.addNode(no_resources);
    hotelOwner.addNode(end);

    manager.registerDialogue(std::move(hotelOwner));

    // ========================= ОХРАННИК (О) =========================
    // Dialogue guard("guard");
    //
    // DialogueNode o_start;
    // o_start.id = "start";
    // o_start.speaker = "Охранник";
    // o_start.text =
    //     "Я всю смену был в баре. Подозреваю старика с собакой.";
    // o_start.choices = {
    //     {"Показать жетон", "badge", nullptr},
    //     {"Дать деньги", "money", nullptr},
    //     {"Флиртовать", "flirt", nullptr},
    //     {"Применить силу", "force", nullptr}
    // };
    //
    // DialogueNode o_badge;
    // o_badge.id = "badge";
    // o_badge.speaker = "Охранник";
    // o_badge.text =
    //     "Подозреваю тихого очкарика слева от убитого. (-1 жетон)";
    // o_badge.choices = {{"Уйти", "end", nullptr}};
    //
    // DialogueNode o_money;
    // o_money.id = "money";
    // o_money.speaker = "Охранник";
    // o_money.text =
    //     "Я не продаюсь! (-1 деньга)";
    // o_money.choices = {{"Уйти", "end", nullptr}};
    //
    // DialogueNode o_flirt;
    // o_flirt.id = "flirt";
    // o_flirt.speaker = "Охранник";
    // o_flirt.text =
    //     "Ты на что намекаешь?! Вы погибли. (КОНЦОВКА)";
    // o_flirt.choices = {{"Уйти", "end", nullptr}};
    //
    // DialogueNode o_force;
    // o_force.id = "force";
    // o_force.speaker = "Охранник";
    // o_force.text =
    //     "Очкарик слева — сталкер. (-2 силы)";
    // o_force.choices = {{"Уйти", "end", nullptr}};
    //
    // guard.addNode(o_start);
    // guard.addNode(o_badge);
    // guard.addNode(o_money);
    // guard.addNode(o_flirt);
    // guard.addNode(o_force);
    // manager.registerDialogue(std::move(guard));
    //
    // // ========================= СТРИПТИЗЁРША (С) =========================
    // Dialogue stripper("stripper");
    //
    // DialogueNode s_start;
    // s_start.id = "start";
    // s_start.speaker = "Стриптизёрша";
    // s_start.text =
    //     "Я всю ночь танцевала. Очкарик — псих, у него фото поп-идола в комнате.";
    // s_start.choices = {
    //     {"Показать жетон", "badge", nullptr},
    //     {"Дать деньги", "money", nullptr},
    //     {"Флиртовать", "flirt", nullptr},
    //     {"Применить силу", "force", nullptr}
    // };
    //
    // DialogueNode s_badge;
    // s_badge.id = "badge";
    // s_badge.speaker = "Стриптизёрша";
    // s_badge.text = "Ничего тебе не скажу! (-1 жетон)";
    // s_badge.choices = {{"Уйти", "end", nullptr}};
    //
    // DialogueNode s_money;
    // s_money.id = "money";
    // s_money.speaker = "Стриптизёрша";
    // s_money.text = "Хозяин зол на поп-идола. (-1 деньга)";
    // s_money.choices = {{"Уйти", "end", nullptr}};
    //
    // DialogueNode s_flirt;
    // s_flirt.id = "flirt";
    // s_flirt.speaker = "Стриптизёрша";
    // s_flirt.text = "Отвали! (-1 флирт)";
    // s_flirt.choices = {{"Уйти", "end", nullptr}};
    //
    // DialogueNode s_force;
    // s_force.id = "force";
    // s_force.speaker = "Стриптизёрша";
    // s_force.text = "Хозяин зол на поп-идола. (-1 сила)";
    // s_force.choices = {{"Уйти", "end", nullptr}};
    //
    // stripper.addNode(s_start);
    // stripper.addNode(s_badge);
    // stripper.addNode(s_money);
    // stripper.addNode(s_flirt);
    // stripper.addNode(s_force);
    // manager.registerDialogue(std::move(stripper));
    //
    // // ========================= СЛЕПОЙ ДЕД (Д) =========================
    // Dialogue blind("blind_man");
    //
    // DialogueNode d_start;
    // d_start.id = "start";
    // d_start.speaker = "Слепой дед";
    // d_start.text =
    //     "Я был у себя. Присмотритесь к хозяину отеля.";
    // d_start.choices = {
    //     {"Показать жетон", "badge", nullptr},
    //     {"Дать деньги", "money", nullptr},
    //     {"Флиртовать", "flirt", nullptr},
    //     {"Применить силу", "force", nullptr}
    // };
    //
    // DialogueNode d_badge;
    // d_badge.id = "badge";
    // d_badge.speaker = "Слепой дед";
    // d_badge.text = "Старуха опасна. (-1 жетон)";
    // d_badge.choices = {{"Уйти", "end", nullptr}};
    //
    // DialogueNode d_money;
    // d_money.id = "money";
    // d_money.speaker = "Слепой дед";
    // d_money.text = "Убирайся! (-1 деньга)";
    // d_money.choices = {{"Уйти", "end", nullptr}};
    //
    // DialogueNode d_flirt;
    // d_flirt.id = "flirt";
    // d_flirt.speaker = "Слепой дед";
    // d_flirt.text = "Собака покусала вас. (-1 флирт, -1 сила)";
    // d_flirt.choices = {{"Уйти", "end", nullptr}};
    //
    // DialogueNode d_force;
    // d_force.id = "force";
    // d_force.speaker = "Слепой дед";
    // d_force.text = "Собака разорвала вас. (-2 силы)";
    // d_force.choices = {{"Уйти", "end", nullptr}};
    //
    // blind.addNode(d_start);
    // blind.addNode(d_badge);
    // blind.addNode(d_money);
    // blind.addNode(d_flirt);
    // blind.addNode(d_force);
    // manager.registerDialogue(std::move(blind));
    //
    // // ========================= ОЧКАРИК (П) =========================
    // Dialogue fan("fan");
    //
    // DialogueNode p_start;
    // p_start.id = "start";
    // p_start.speaker = "Постоялец";
    // p_start.text =
    //     "Я спал. Охранник ненавидел поп-идола.";
    // p_start.choices = {
    //     {"Показать жетон", "badge", nullptr},
    //     {"Дать деньги", "money", nullptr},
    //     {"Флиртовать", "flirt", nullptr},
    //     {"Применить силу", "force", nullptr}
    // };
    //
    // DialogueNode p_info;
    // p_info.id = "badge";
    // p_info.speaker = "Постоялец";
    // p_info.text =
    //     "Стриптизёрша бывала у него в номере. (-1 жетон)";
    // p_info.choices = {{"Уйти", "end", nullptr}};
    //
    // fan.addNode(p_start);
    // fan.addNode(p_info);
    // manager.registerDialogue(std::move(fan));
    //
    // // ========================= БАБУЛЬКА (Б) =========================
    // Dialogue granny("granny");
    //
    // DialogueNode b_start;
    // b_start.id = "start";
    // b_start.speaker = "Бабушка";
    // b_start.text =
    //     "Я была в комнате. Стриптизёрша — позор!";
    // b_start.choices = {
    //     {"Показать жетон", "badge", nullptr},
    //     {"Дать деньги", "money", nullptr},
    //     {"Флиртовать", "flirt", nullptr},
    //     {"Применить силу", "force", nullptr}
    // };
    //
    // DialogueNode b_flirt;
    // b_flirt.id = "flirt";
    // b_flirt.speaker = "Бабушка";
    // b_flirt.text =
    //     "Подозреваю охранника. (+1 деньги, -1 флирт)";
    // b_flirt.choices = {{"Уйти", "end", nullptr}};
    //
    // DialogueNode b_force;
    // b_force.id = "force";
    // b_force.speaker = "Бабушка";
    // b_force.text =
    //     "Вы убили старушку. Вы арестованы. (КОНЦОВКА)";
    // b_force.choices = {{"Уйти", "end", nullptr}};
    //
    // granny.addNode(b_start);
    // granny.addNode(b_flirt);
    // granny.addNode(b_force);
    // manager.registerDialogue(std::move(granny));
}