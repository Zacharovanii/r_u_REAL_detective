// helpers/ServiceLocator.h
#pragma once

// Forward declaration чтобы избежать циклических зависимостей
class DialogueManager;

class ServiceLocator {
private:
    static DialogueManager* dialogue_manager; // только объявление

public:
    static void provide(DialogueManager* manager);
    static DialogueManager* getDialogueManager();
};