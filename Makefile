TARGET = main
CXX = g++
CXXFLAGS = -std=c++14 -Wall -pthread -O2

SRCS = main.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
