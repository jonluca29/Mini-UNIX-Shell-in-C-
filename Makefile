CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g

TARGET := miniShell

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)

.PHONY: all clean
