#include "blockchain.h"
#include <string>

std::string create_blockchain() {
    return "Blockchain initialized.";
}

extern "C" {
    const char* get_blockchain_message() {
        static std::string message = create_blockchain();
        return message.c_str();
    }
}
