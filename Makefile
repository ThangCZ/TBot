all:
	g++ --std=c++11 -Wall -lboost_system bot.cpp connection.cpp logger.cpp main.cpp user.cpp -o tbot

clean:
	rm tbot
