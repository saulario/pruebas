#include "MessageTypes.h"

using namespace iot::messaging;

Message::Message() {
    
}

Message::Message(const char * cdn) {
    raw.reset(new std::string(cdn));
}

Message::Message(const std::string & str) {
    raw.reset(new std::string(str));
}

void Message::fromString(const std::string & str) {
    raw.reset(new std::string(str));
}

std::string Message::toString(void) {
    std::string value = "null";
    if (raw.get() != nullptr) {
        value = *raw;
    }
    return value;
}