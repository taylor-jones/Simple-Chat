# Taylor Jones - CS372 - Project 1 - Makefile - Chat Client

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

LDFLAGS = -lboost_date_time

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
HEADERS = $(wildcard *.hpp)

EXEC = ChatClient

build: ${OBJS} ${HEADERS}
	${CXX} ${OBJS} -o ${EXEC}

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm -f *o ${EXEC}
