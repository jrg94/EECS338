# Assignment 6 Makefile
CC = gcc
CFLAGS = -Wall

# Client source
CSOURCE = main.c tina.c judy.c cookies_clnt.c cookies_xdr.c

# Server source TODO add server source
SSOURCE = cookies_svc.c cookies_xdr.c

RPCSRC = cookies.x
RPCGEN = cookies.h cookies_clnt.c cookies_svc.c cookies_xdr.c

CLIENT = main
SERVER = server

all: $(CLIENT) $(SERVER)

server: $(SSOURCE) $(RPCGEN)
	$(CC) $(CFLAGS) -o $(SERVER) $(SSOURCE)

# Run to execute rpcgen
$(RPCGEN): $(RPCSRC)
	rpcgen $(RPCSRC)
