cc=gcc
AR=ar
OBJECTS_MAIN=main.o client.o
OBJECTS_SERVER=server.o
FLAGS= -Wall -g 

all: main server
# main
main: $(OBJECTS_MAIN)
	$(cc) $(FLAGS) -o main $(OBJECTS_MAIN)

server:$(OBJECTS_SERVER)
	$(cc) $(FLAGS) -o server $(OBJECTS_SERVER)

$(OBJECTS_MAIN): main.c client.c server.c
	$(cc) $(FLAGS) -c main.c client.c server.c

.PHONY: clean all
clean:
	rm -f *.o  *.a *.so main server