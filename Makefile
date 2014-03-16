CXX = g++
CXXFLAGS = -Wall
RM = rm -rf

PARSER = parser.yy
PARSER_OUT = $(PARSER:=.cpp)
PARSER_H = $(PARSER:=.h)
LEXER = lexer.ll
LEXER_OUT = $(LEXER:=.cpp)

LIBS = -lfl

SOURCES = CoolCompiler.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = coolc

make: $(TARGET)

$(TARGET): $(SOURCES)
	bison -o $(PARSER_OUT) --defines=$(PARSER_H) $(PARSER)
	flex -o $(LEXER_OUT) $(LEXER)
	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $(SOURCES) $(PARSER_OUT) $(LEXER_OUT)

bison:
	bison -o $(PARSER_OUT) --defines=$(PARSER_H) $(PARSER)
	flex -o $(LEXER_OUT) $(LEXER)
	$(CXX) $(CXXFLAGS) $(LIBS) $(PARSER_OUT) -o bisontest

clean:
	$(RM) $(OBJECTS) $(TARGET)
	$(RM) $(PARSER_OUT) $(PARSER_H) $(LEXER_OUT)