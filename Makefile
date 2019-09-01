MAKEFLAGS += -r
MAKEFLAGS += -R

CPP=g++

HEADERFILES := $(wildcard *.h)

RADIX_OBJFILES := \
	radix.o \

TEST_OBJFILES := \
	test.o \
	radix.o \

MAIN_OBJFILES := \
	main.o \
	radix.o \

CPP_FLAGS=-Wall -Wno-c++11-extensions

RADIX=radix
MAIN=main
TEST=test

.PHONY: all
all: $(TEST).bin $(MAIN).bin

$(RADIX).bin: $(HEADERFILES) $(RADIX_OBJFILES)
	$(CPP) -o $@ $(RADIX_OBJFILES)

$(TEST).bin: $(HEADERFILES) $(TEST_OBJFILES)
	$(CPP) -o $@ $(TEST_OBJFILES) 

$(MAIN).bin: $(HEADERFILES) $(MAIN_OBJFILES)
	$(CPP) -o $@ $(MAIN_OBJFILES) 

%.o: %.cpp
	$(CPP) -c $(CPP_FLAGS) $^

.PHONY: test
test: $(TEST).bin
	./$(TEST).bin

.PHONY: run
run: $(MAIN).bin
	./$(MAIN).bin

.PHONY: clean
clean:
	rm -f *.o *.bin