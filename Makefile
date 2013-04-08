CC=g++
CFLAGS=-c --std=c++11 -Wall -pedantic
LDFLAGS=-lboost_system
SOURCES=bot.cpp connection.cpp logger.cpp main.cpp user.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tbot

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

cleanall: clean

clean:
	rm $(EXECUTABLE) $(OBJECTS)
