CXX = g++
CXXFLAGS = -Wall
RM = rm -rf

PARSER = parser.y
PARSER_OUT = $(PARSER:.y=.c)
PARSER_H = $(PARSER:.y=.h)
LEXER = lexer.l
LEXER_OUT = $(LEXER:.l=.c)

LIBS = -lfl

SOURCES = CoolCompiler.c CoolMath.c
OBJECTS = $(SOURCES:.c=.o)
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