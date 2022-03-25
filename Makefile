TC_FOLDER = tests
EXT_IN = in
EXT_OUT = out
EXT_ANS = ans
EXECUTABLE_FILENAME = main
ALL_SRCS := $(wildcard src/class/*.cpp)

# Compile then run main.exe
run: compile
	./$(EXECUTABLE_FILENAME)

all: compile test check

# Compile cpp files
compile:
	g++ -std=c++17 -o ./$(EXECUTABLE_FILENAME) ./src/main.cpp $(ALL_SRCS)

# Test
test: $(TC_FOLDER)/*.$(EXT_IN) ./$(EXECUTABLE_FILENAME)
	for inputfile in $(TC_FOLDER)/*.$(EXT_IN); do \
		./$(EXECUTABLE_FILENAME) < $$inputfile; \
	done;

# Check
check: FORCE ./src/check.cpp
	g++ -std=c++17 -o ./check ./src/check.cpp
	./check

FORCE: ;
