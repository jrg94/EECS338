# Assignment 6 Makefile
CC = gcc
CFLAGS = -Wall

# Client source
TSOURCE = main.c tina.c cookies_clnt.c cookies_xdr.c
JSOURCE = main.c judy.c cookies_clnt.c cookies_xdr.c

# Server source
SSOURCE = mother.c cookies_svc.c cookies_xdr.c

# RPC code
RPCSRC = cookies.x
RPCGEN = cookies.h cookies_clnt.c cookies_svc.c cookies_xdr.c

# Client and server processes
TCLIENT = tina
JCLIENT = judy
SERVER = mother

all: $(JCLIENT) $(TCLIENT) $(SERVER)

tina: $(TSOURCE)
	$(CC) -o $(TCLIENT) $(TSOURCE)

judy: $(JSOURCE)
	$(CC) -o $(JCLIENT) $(JSOURCE)	

mother: $(SSOURCE) $(RPCGEN)
	$(CC) -o $(SERVER) $(SSOURCE)

# Run to execute rpcgen
$(RPCGEN): $(RPCSRC)
	rpcgen $(RPCSRC)

.PHONY: clean
clean:
	rm -f $(JCLIENT) $(TCLIENT) $(SERVER) 
