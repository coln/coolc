CXX = g++
CXXFLAGS = -Wall
RM = rm -rf

PARSER = parser.y
PARSER_OUT = $(PARSER:.y=.c)
PARSER_H = $(PARSER:.y=.h)
LEXER = lexer.l
LEXER_OUT = $(LEXER:.l=.c)

LIBS = -lfl

SOURCES = CoolCompiler.c CoolMath.c Symbol.c
HEADERS = CoolCompiler.h CoolMath.h Symbol.h
OBJECTS = $(SOURCES:.c=.o)
TARGET = coolc

make: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS) $(PARSER) $(LEXER)
	bison -o $(PARSER_OUT) --defines=$(PARSER_H) $(PARSER)
	flex -o $(LEXER_OUT) $(LEXER)
	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $(SOURCES) $(PARSER_OUT) $(LEXER_OUT)

clean:
	$(RM) $(OBJECTS) $(TARGET)
	$(RM) $(PARSER_OUT) $(PARSER_H) $(LEXER_OUT)