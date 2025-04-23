#ifndef SHARED_H
#define SHARED_H

void run_server(void);
void run_client(const char* hostname);

typedef struct {
    char str[256];
    char ch;
    short sh;
    int i;
    long l;
    float f;
    double d;
} DataPacket;

#endif

