# Makefile to build single executable April14.exe with both client/server modes

CC = cl
CFLAGS = /nologo /W3 /Zi
LFLAGS = ws2_32.lib /DEBUG

OBJS = main.obj SimpleServer.obj SimpleClient.obj

all: April14.exe

April14.exe: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) /FeApril14.exe

main.obj: main.c shared.h
	$(CC) $(CFLAGS) /c main.c

SimpleServer.obj: SimpleServer.c shared.h
	$(CC) $(CFLAGS) /c SimpleServer.c

SimpleClient.obj: SimpleClient.c shared.h
	$(CC) $(CFLAGS) /c SimpleClient.c

clean:
	del *.obj *.exe *.pdb
