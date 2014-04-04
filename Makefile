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

SOURCES = Main.cpp CoolCompiler.cpp Semantic.cpp
SOURCES += syntax/Type.cpp syntax/SymbolTable.cpp
SOURCES += syntax/Class.cpp syntax/Attribute.cpp 
SOURCES += syntax/Symbol.cpp syntax/Method.cpp syntax/Expression.cpp
SOURCES += syntax/Assignment.cpp
HEADERS = CoolCompiler.h Semantic.h
HEADERS += syntax/Type.h syntax/SymbolTable.h
HEADERS += syntax/Class.h syntax/Attribute.h syntax/Symbol.h
HEADERS += syntax/Method.h syntax/Expression.h
HEADERS += syntax/Assignment.h
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