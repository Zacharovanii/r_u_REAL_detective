#include "helpers/DialogueInitializer.h"
#include "model/dialogue/Dialogue.h"
#include <iostream>

void DialogueInitializer::initializeDialogues(DialogueManager& manager) {
    Dialogue robertDialogue("robert_dialogue");

    // Стартовый узел
    DialogueNode start;
    start.id = "start";
    start.speaker = "Роберт";
    start.text = "Ты кто такой? Убирайся отсюда! Я не хочу с тобой разговаривать.";
    start.choices = {
        {"Я детектив, расследую исчезновение", "detective", nullptr},
        {"Просто осматриваюсь, не обращайте внимания", "ignore", nullptr},
        {"Ладно, я ухожу", "end", nullptr}
    };

    // Узел детектива
    DialogueNode detective;
    detective.id = "detective";
    detective.speaker = "Роберт";
    detective.text = "Детектив? Хм... Ладно, что тебе нужно? Но говори быстро.";
    detective.choices = {
        {"Расскажите о вчерашнем вечере", "end", nullptr},
        {"Вы видели что-то подозрительное?", "end", nullptr},
        {"Извините, побеспокоил", "end", nullptr}
    };

    // Узел завершения
    DialogueNode end;
    end.id = "end";
    end.speaker = "Роберт";
    end.text = "До свидания.";
    end.choices = {};

    robertDialogue.addNode(start);
    robertDialogue.addNode(detective);
    robertDialogue.addNode(end);

    manager.registerDialogue(std::move(robertDialogue));
}