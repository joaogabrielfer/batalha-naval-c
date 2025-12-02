CC = gcc
CFLAGS = -Wall -g

SRCS = src/*

OBJS = $(SRCS:.c=.o)

TARGET = build/batalha_naval

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

run:
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	$(TARGET)
