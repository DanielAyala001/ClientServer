#include "shared.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

void run_client(const char* hostname) {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in sn;
    struct hostent* h;
    char b[256];
    int x, c;

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

    h = gethostbyname(hostname);
    if (h == NULL) {
        printf("gethostbyname failed.\n");
        closesocket(s);
        WSACleanup();
        return;
    }

    memset(&sn, 0, sizeof(sn));
    memcpy(&sn.sin_addr, h->h_addr, h->h_length);
    sn.sin_family = AF_INET;
    sn.sin_port = htons(2223);

    if (connect(s, (struct sockaddr*)&sn, sizeof(sn)) < 0) {
        printf("Connect failed: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return;
    }

    DataPacket packet;
    recv(s, (char*)&packet, sizeof(DataPacket), 0);

    printf("Received from server:\n");
    printf("String: %s\nChar: %c\nShort: %d\nInt: %d\nLong: %ld\nFloat: %.2f\nDouble: %.2f\n",
        packet.str, packet.ch, packet.sh, packet.i, packet.l, packet.f, packet.d);

    // Modify values
    // Reverse string
    int len = strlen(packet.str);
    for (int i = 0; i < len / 2; i++) {
        char tmp = packet.str[i];
        packet.str[i] = packet.str[len - 1 - i];
        packet.str[len - 1 - i] = tmp;
    }

    // Uppercase character
    if (packet.ch >= 'a' && packet.ch <= 'z') {
        packet.ch = packet.ch - ('a' - 'A');
    }

    packet.sh += 1;
    packet.i *= 2;
    packet.l *= 3;
    packet.f /= 2.0f;
    packet.d /= 4.0;

    printf("\nModified data:\n");
    printf("String: %s\nChar: %c\nShort: %d\nInt: %d\nLong: %ld\nFloat: %.2f\nDouble: %.2f\n",
        packet.str, packet.ch, packet.sh, packet.i, packet.l, packet.f, packet.d);

    send(s, (char*)&packet, sizeof(DataPacket), 0);
}
