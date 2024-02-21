BINARY = string_driver
CODEDIRS =. my_stringLib
INCDIRS =. /header/	 

CC = gcc
DEPFLAGS =-MP -MD
CFLAGS = -Wall -Wextra -g $(foreach D, $(INCDIRS), -I$(D)) $(DEPFLAGS)

CFILES = $(foreach D, $(CODEDIRS), $(wildcard $(D)/*.c))
OBJECTS = $(patsubst %.c, %.o, $(CFILES))
DEPFILES = $(patsubst %.c, %.d, $(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

%.o:%.c 
	$(CC) $(CFLAGS) -c -o $@ $^

run:
	./string_driver

clean:
	@echo "cleaning all .o files, string_driver, and .d files"
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)

diff:
	@git status
	@git diff --stat