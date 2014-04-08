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
SOURCES += syntax/Type.cpp syntax/SymbolScope.cpp syntax/MethodScope.cpp
SOURCES += syntax/Expression.cpp syntax/Class.cpp
SOURCES += syntax/Attribute.cpp syntax/Symbol.cpp syntax/Method.cpp
SOURCES += syntax/Arithmetic.cpp syntax/Assignment.cpp syntax/Block.cpp
SOURCES += syntax/Case.cpp syntax/Comparison.cpp syntax/Conditional.cpp
SOURCES += syntax/Let.cpp syntax/While.cpp

HEADERS = CoolCompiler.h Semantic.h Headers.h
HEADERS += syntax/Type.h syntax/SymbolScope.h syntax/MethodScope.h
HEADERS += syntax/Expression.h syntax/Class.h
HEADERS += syntax/Attribute.h syntax/Symbol.h syntax/Method.h
HEADERS += syntax/Arithmetic.h syntax/Assignment.h syntax/Block.h
HEADERS += syntax/Case.h syntax/Comparison.h syntax/Conditional.h
HEADERS += syntax/Let.h syntax/While.h
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