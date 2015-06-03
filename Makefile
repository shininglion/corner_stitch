SOURCE_CPP_FILES =\
  ./tiles/tile.c\
  ./tiles/search.c\
  ./tiles/search2.c\
  ./utils/geometry.c\
  ./utils/malloc.c\
  ./utils/lookup.c\
  ./utils/update.c\
  ./utils/gdtout.c\
  ./textio/txOutput.c\
  ./main.c
  
CC = gcc -std=c99 -Wall -O2

OUTPUT_OBJECT_OF_CPP_FILES = $(SOURCE_CPP_FILES:.c=.o)

OUTPUT_DEPENDENCY_RULE_OF_CPP_FILES = $(SOURCE_CPP_FILES:.c=.dep)

ALL_OBJECT_FILES = $(OUTPUT_OBJECT_OF_CPP_FILES)

ALL_TARGET = ./cs

all: $(ALL_TARGET)

objects: $(ALL_OBJECT_FILES)

clean: cleantarget cleanobjects cleandep

cleantarget:
	rm -f $(ALL_TARGET)

cleanobjects:
	rm -f $(ALL_OBJECT_FILES)

cleandep:
	rm -f $(OUTPUT_DEPENDENCY_RULE_OF_CPP_FILES)

$(ALL_TARGET): $(ALL_OBJECT_FILES)
	$(CC) -o $@ $(ALL_OBJECT_FILES) -lm

%.dep: %.c
	$(CC) -MM $< -MT $*.o > $@

%.o: %.c
	$(CC) -c -o $@ $< -DSYSV -DHAVE_VA_COPY

-include $(OUTPUT_DEPENDENCY_RULE_OF_CPP_FILES)

