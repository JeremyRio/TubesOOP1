TC_FOLDER = tests
EXT_IN = in
EXT_OUT = out
EXT_ANS = ans
EXECUTABLE_FILENAME = main
ALL_SRCS := $(wildcard src/class/*.cpp)

all: compile test check

# Compile all cpp files except check.cpp
compile:
	g++ -std=c++17 -o ./bin/$(EXECUTABLE_FILENAME) ./src/main.cpp $(ALL_SRCS)

# Test
test: $(TC_FOLDER)/*.$(EXT_IN) ./bin/$(EXECUTABLE_FILENAME)
	for inputfile in $(TC_FOLDER)/*.$(EXT_IN); do \
		./bin/$(EXECUTABLE_FILENAME) < $$inputfile; \
	done;

# Check
check: FORCE ./src/check.cpp
	g++ -std=c++17 -o ./bin/check ./src/check.cpp
	./bin/check

FORCE: ;
