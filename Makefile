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
SOURCES += syntax/TypeTable.cpp
SOURCES += syntax/Class.cpp syntax/Features.cpp syntax/Attribute.cpp 
SOURCES += syntax/Symbol.cpp syntax/Method.cpp syntax/Expression.cpp
HEADERS = CoolCompiler.h
HEADERS += syntax/TypeTable.h
HEADERS += syntax/Class.h syntax/Features.h syntax/Attribute.h syntax/Symbol.h
HEADERS += syntax/Method.h syntax/Expression.h
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