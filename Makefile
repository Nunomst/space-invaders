CXX      = clang++
CXXFLAGS = -std=c++17 -Wall -I/opt/homebrew/include
LDFLAGS  = -L/opt/homebrew/lib -lraylib
TARGET   = hello

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp $(LDFLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean
