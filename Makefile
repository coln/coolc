CXX = g++
CXXFLAGS = -Wall
CXXLIBS = -lfl
RM = rm -rf

PARSER = parser.y
PARSER_OUT = $(PARSER:.y=.c)
PARSER_H = $(PARSER:.y=.h)
LEXER = lexer.l
LEXER_OUT = $(LEXER:.l=.c)

BISON_FLAGS = -o $(PARSER_OUT) --defines=$(PARSER_H)
FLEX_FLAGS = -o $(LEXER_OUT)

SOURCES = CoolCompiler.c CoolMath.c Symbol.c
HEADERS = CoolCompiler.h CoolMath.h Symbol.h
OBJECTS = $(SOURCES:.c=.o)
TARGET = coolc

make: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS) $(PARSER) $(LEXER)
	bison $(BISON_FLAGS) $(PARSER)
	flex $(FLEX_FLAGS) $(LEXER)
	$(CXX) $(CXXFLAGS) $(CXXLIBS) -o $@ $(SOURCES) $(PARSER_OUT) $(LEXER_OUT)

clean:
	$(RM) $(OBJECTS) $(TARGET)
	$(RM) $(PARSER_OUT) $(PARSER_H) $(LEXER_OUT)