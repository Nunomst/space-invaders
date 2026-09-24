CXX      = clang++
CXXFLAGS = -std=c++17 -Wall -I/opt/homebrew/include
LDFLAGS  = -L/opt/homebrew/lib -lraylib
TARGET   = hello

SRCS     = $(wildcard *.cpp)
HEADERS  = $(wildcard *.h)

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(LDFLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean
