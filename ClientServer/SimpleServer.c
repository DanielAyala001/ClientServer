#include "shared.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

void run_server(void) {
    WSADATA wsa;
    SOCKET s, ns;
    struct sockaddr_in sn, from;
    int sl, c, i;
    char b[256];
    int x = 22;

    printf("Starting server...\n");

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed: %d\n", WSAGetLastError());
        return;
    }

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }

    memset(&sn, 0, sizeof(sn));
    sn.sin_family = AF_INET;
    sn.sin_addr.s_addr = INADDR_ANY;
    sn.sin_port = htons(2223);

    if (bind(s, (struct sockaddr*)&sn, sizeof(sn)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return;
    }

    listen(s, 3);
    sl = sizeof(from);

    printf("Waiting for client connection...\n");
    ns = accept(s, (struct sockaddr*)&from, &sl);
    if (ns == INVALID_SOCKET) {
        printf("Accept failed: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return;
    }

    DataPacket packet = {
     "hello from server",
     'a',
     10,
     20,
     30,
     40.0f,
     50.0
    };

    send(ns, (char*)&packet, sizeof(DataPacket), 0);
    printf("Sent to client:\n");
    printf("String: %s\nChar: %c\nShort: %d\nInt: %d\nLong: %ld\nFloat: %.2f\nDouble: %.2f\n",
        packet.str, packet.ch, packet.sh, packet.i, packet.l, packet.f, packet.d);

    recv(ns, (char*)&packet, sizeof(DataPacket), 0);

    printf("\nReceived back from client:\n");
    printf("String: %s\nChar: %c\nShort: %d\nInt: %d\nLong: %ld\nFloat: %.2f\nDouble: %.2f\n",
        packet.str, packet.ch, packet.sh, packet.i, packet.l, packet.f, packet.d);
}