CXX = g++
CXXFLAGS = -Wall -g
CXXLIBS = -lfl
RM = rm -rf

PARSER = parser.yy
PARSER_OUT = $(PARSER:.yy=.cpp)
PARSER_H = $(PARSER:.yy=.h)
LEXER = lexer.ll
LEXER_OUT = $(LEXER:.ll=.cpp)

BISON_FLAGS = -o $(PARSER_OUT) --defines=$(PARSER_H)
FLEX_FLAGS = -o $(LEXER_OUT)

SOURCES = Main.cpp CoolCompiler.cpp
SOURCES += TypeTable.cpp
SOURCES += Class.cpp Features.cpp Attribute.cpp Symbol.cpp Method.cpp Expression.cpp
HEADERS = CoolCompiler.h
HEADERS += TypeTable.h
HEADERS += Class.h Features.h Attribute.h Symbol.h Method.h Expression.h
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = coolc

make: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS) $(PARSER) $(LEXER)
	bison $(BISON_FLAGS) $(PARSER)
	flex $(FLEX_FLAGS) $(LEXER)
	$(CXX) $(CXXFLAGS) $(CXXLIBS) -o $@ $(SOURCES) $(PARSER_OUT) $(LEXER_OUT)

clean:
	$(RM) $(OBJECTS) $(TARGET)
	$(RM) $(PARSER_OUT) $(PARSER_H) $(LEXER_OUT)
	$(RM) location.hh position.hh stack.hh