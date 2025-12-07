#pragma once
#include <deque>
#include <string>

class DebugLog {
private:
    std::deque<std::string> messages;
    static constexpr size_t MAX_LINES = 5;

    DebugLog() = default; // приватный конструктор

public:
    DebugLog(const DebugLog&) = delete;
    DebugLog& operator=(const DebugLog&) = delete;

    static DebugLog& instance() {
        static DebugLog instance;
        return instance;
    }

    void add(const std::string& msg) {
        if (messages.size() >= MAX_LINES)
            messages.pop_front();
        messages.push_back(msg);
    }

    const std::deque<std::string>& getMessages() const { return messages; }
};
