BINARY = string_driver
CODEDIRS =. my_stringLib

UNIT_TEST = unit_test 
TESTDIRS =. test_strings

INCDIRS =. /headers/

CC = gcc
DEPFLAGS =-MP -MD
CFLAGS = -Wall -Wextra -g $(foreach D, $(INCDIRS), -I$(D)) $(DEPFLAGS)

CFILES = $(foreach D, $(CODEDIRS), $(wildcard $(D)/*.c))
OBJECTS = $(patsubst %.c, %.o, $(CFILES))
DEPFILES = $(patsubst %.c, %.d, $(CFILES))

TESTFILES = $(foreach D, $(TESTDIRS), $(wildcard $(D)/*.c))
TESTOBJS = $(patsubst %.c, %.o, $(TESTFILES))
TESTDEP = $(patsubst %.c, %.d, $(TESTFILES))


all: $(UNIT_TEST) 

$(UNIT_TEST): $(OBJECTS) $(TESTOBJS)
	$(CC) -o $@ $^

%.o:%.c 
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@echo "cleaning all .o files, string_driver, unit_tests and .d files"
	rm -rf $(UNIT_TEST) $(OBJECTS) $(DEPFILES) $(TESTOBJS)  $(TESTDEP) test_output.txt

diff:
	@git status
	@git diff --stat