CC = ccache g++ -g -Wall -std=c++11
CFLAGS = -I./
LIBS = -lboost_system -lboost_program_options -pthread

CLIENT_TARGET = client
SERVER_TARGET = server

CLIENT_SRCDIR = src/
SERVER_SRCDIR = srv/src/

all: $(CLIENT_TARGET) $(SERVER_TARGET)

$(CLIENT_TARGET): $(CLIENT_SRCDIR)Main.o $(CLIENT_SRCDIR)Client.o
	$(CC) $(LIBS) -o $@ $^

$(SERVER_TARGET): $(SERVER_SRCDIR)Main.o $(SERVER_SRCDIR)HolePunchServer.o
	$(CC) $(LIBS) -o $@ $^

$(CLIENT_SRCDIR)%.o: $(CLIENT_SRCDIR)%.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(SERVER_SRCDIR)%.o: $(SERVER_SRCDIR)%.cpp
	$(CC) -c $(CFLAGS) -o $@ $<


run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(CLIENT_SRCDIR)*.o
	rm -rf $(SERVER_SRCDIR)*.o
	rm -rf $(CLIENT_TARGET)
	rm -rf $(SERVER_TARGET)
