# ==========================================
#   Mostly taken from:
#   https://github.com/ThrowTheSwitch/Unity/tree/master/examples/example_2
#   http://www.throwtheswitch.org/build/make
# ==========================================

#We try to detect the OS we are running on, and adjust commands as needed
ifeq ($(OSTYPE),cygwin)
	CLEANUP = rm -f
	CLEANUP_DIR = rm -rf
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
elseifeq ($(OSTYPE),msys)
	CLEANUP = rm -f
	CLEANUP_DIR = rm -rf
	MKDIR = mkdir -p
	TARGET_EXTENSION=.exe
elseifeq ($(OS),Windows_NT)
	CLEANUP = del /F /Q
	MKDIR = mkdir
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	CLEANUP_DIR = rm -rf
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
endif

COMPILE=gcc

CFLAGS = -std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror 
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition
CFLAGS += -Wmissing-prototypes
CFLAGS += -Wmissing-declarations
CFLAGS += -DUNITY_FIXTURES
CFLAGS += -g

#####################################################
# PATHS
#####################################################
#app
PATH_APP_SRC = src/
#tests
PATH_TEST_SRC = test/src/
PATH_TEST_RUNNERS = $(PATH_TEST_SRC)test_runners/
#unity
PATH_UNITY_ROOT=test/unity/
#Directories to create
PATH_BUILD          = build/
PATH_BUILD_RESULTS  = $(PATH_BUILD)results/
PATH_BUILD_OBJS     = $(PATH_BUILD)objs/ #TODO
PATH_BUILD_DEPENDS  = $(PATH_BUILD)depends/ #TODO
PATH_DOCS           = docs/
#Variable used during build call
BUILD_THE_PATHS     =\
   $(PATH_BUILD) \
   $(PATH_BUILD_RESULTS) \
   $(PATH_BUILD_OBJS) \
   $(PATH_BUILD_DEPENDS)

#####################################################
# SOURCE CODE
#####################################################
SOURCE_TEST = $(wildcard $(PATH_TEST_SRC)*.c)
SOURCE_TEST_RUNNERS = $(wildcard $(PATH_TEST_RUNNERS)*.c)
SOURCE_APP = $(wildcard $(PATH_APP_SRC)*.c)

#####################################################
# RESULTS 
#####################################################
RESULTS_TEST = $(PATH_BUILD_RESULTS)results_tests.txt

TARGET_BASE1=all_tests
TARGET_BASE2=calculator
TARGET1 = $(PATH_BUILD)$(TARGET_BASE1)$(TARGET_EXTENSION)
TARGET2 = $(PATH_BUILD)$(TARGET_BASE2)$(TARGET_EXTENSION)
SRC_FILES1=\
  $(PATH_UNITY_ROOT)src/unity.c \
  $(PATH_UNITY_ROOT)extras/fixture/src/unity_fixture.c \
  $(SOURCE_APP) \
  $(SOURCE_TEST) \
  $(SOURCE_TEST_RUNNERS)
SRC_FILES2=$(SOURCE_APP) 

INC_DIRS=-Isrc -I$(PATH_UNITY_ROOT)src -I$(PATH_UNITY_ROOT)extras/fixture/src
# we do not want to pull in Unity memory extra by default 
SYMBOLS=-DUNITY_FIXTURE_NO_EXTRAS
PRODUCTION=-DPRODUCTION_BUILD

all: clean default

RESULTS=$(RESULTS_TEST)

default:$(BUILD_THE_PATHS) $(RESULTS)

$(PATH_BUILD):
	$(MKDIR) $(PATH_BUILD)

$(PATH_BUILD_RESULTS):
	$(MKDIR) $(PATH_BUILD_RESULTS)

$(PATH_BUILD_OBJS):
	$(MKDIR) $(PATH_BUILD_OBJS)

$(PATH_BUILD_DEPENDS):
	$(MKDIR) $(PATH_BUILD_DEPENDS)

$(RESULTS_TEST):
	$(COMPILE) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES1) -o $(TARGET1)
	./$(TARGET1) -v 

.PHONY:clean
clean:
	$(CLEANUP_DIR) $(PATH_BUILD)

.PHONY:calculator 
calculator: 
	$(COMPILE) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(PRODUCTION) $(SRC_FILES2) -o $(TARGET2)
	./$(TARGET2)