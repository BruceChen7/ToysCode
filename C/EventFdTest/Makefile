.PHONY: all
all: test_event_fd
SRC := $(wildcard *.c)

test_event_fd: *.c
	gcc -o $@  $(SRC) -lpthread
