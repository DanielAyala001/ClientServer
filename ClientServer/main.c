#include <stdio.h>
#include <string.h>
#include "shared.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s [server|client] [hostname]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "server") == 0) {
        run_server();
    }
    else if (strcmp(argv[1], "client") == 0) {
        const char* hostname = (argc >= 3) ? argv[2] : "127.0.0.1";
        run_client(hostname);
    }
    else {
        printf("Unknown option: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
