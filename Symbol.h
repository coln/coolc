#ifndef COOL_SYMBOL_H_
#define COOL_SYMBOL_H_

#include <string>

class Symbol;
class Terminal;
class NonTerminal;

struct SymbolType {
	enum Enum {
		SYMBOL,
		TERMINAL,
		NONTERMINAL
	} e;
	SymbolType(Enum e = SYMBOL) : e(e) {}
	operator Enum() { return e; }
	bool operator==(const SymbolType &s) const {
		return (e == s.e);
	}
	static const char* toString(const SymbolType &t) {
		switch(t.e){
			case SYMBOL: return "SYMBOL";
			case TERMINAL: return "TERMINAL";
			case NONTERMINAL: return "NONTERMINAL";
		}
		return "";
	}
};

class Symbol {
public:
	SymbolType type;
	std::string value;
	Symbol(const SymbolType type = SymbolType::SYMBOL, const std::string value = "")
			: type(type), value(value) {}
	Symbol& operator=(const Symbol& s){
		type = s.type;
		value = s.value;
		return *this;
	}
	bool operator==(const Symbol& s) const {
		return (type == s.type && value.compare(s.value) == 0);
	}
	bool operator<(const Symbol& s) const {
		return (value.compare(s.value) < 0);
	}
};

class Terminal : public Symbol {
public:
	Terminal(const std::string value) : Symbol(SymbolType::TERMINAL, value) {}
};

class NonTerminal : public Symbol {
public:
	NonTerminal(const std::string value) : Symbol(SymbolType::NONTERMINAL, value) {}
};

#endif