#include "graph.h"
#include <string>

std::string render_graph() {
    return "Graph rendered successfully!";
}

extern "C" {
    const char* get_graph_message() {
        static std::string message = render_graph();
        return message.c_str();
    }
}
