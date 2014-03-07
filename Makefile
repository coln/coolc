CXX = g++
CXXFLAGS = -Wall
RM = rm -rf
SOURCES = CoolCompiler.cpp Lexer.cpp Parser.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = coolc

make: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)