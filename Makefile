CXX      = clang++
CXXFLAGS = -std=c++17 -Wall -Isrc -I/opt/homebrew/include
LDFLAGS  = -L/opt/homebrew/lib -lraylib
TARGET   = space-invaders

SRCS     = $(wildcard src/*.cpp src/*/*.cpp)
HEADERS  = $(wildcard src/*.hpp src/*/*.hpp)

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(LDFLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean
