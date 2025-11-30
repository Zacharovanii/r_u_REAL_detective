// helpers/ServiceLocator.cpp
#include "helpers/ServiceLocator.h"
#include "model/DialogueManager.h"

// Определение статической переменной
DialogueManager* ServiceLocator::dialogue_manager = nullptr;

void ServiceLocator::provide(DialogueManager* manager) {
    dialogue_manager = manager;
}

DialogueManager* ServiceLocator::getDialogueManager() {
    return dialogue_manager;
}