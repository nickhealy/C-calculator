CFLAGS  = -std=c99
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror
CFLAGS += -Wmissing-declarations
CFLAGS += -DUNITY_SUPPORT_64

SRC_FILES = src/operators.c src/toPostfix.c src/utils.c

calculator: src/*.c src/*.h 
	@echo Compiling $@ 
	@$(CC) $(CFLAGS) src/*.c -o calculator.out 

.PHONY: test
test: tests.out
	@./tests.out

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM src/*.h.gch

tests.out: test/*.c src/*.c src/*.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) -o tests.out $(SRC_FILES) test/vendor/unity.c test/*.c
