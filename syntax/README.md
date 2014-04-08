Syntax Tree
===========
The files in this directory make up the syntax tree like so:

- Type
- Symbol Scope
- Method Scope
- Expression
	- Class
	- Symbol
	- Attribute
	- Method
	- Assignment
	- Conditional
	- Loop
	- Block

Their addition is handled by parser.yy, and their deletion is handled by each
destructor.

### Scopes
There are two scopes, SymbolScope and MethodScope, because in Cool, a symbol
and a method may have the same name

### Note on Symbols
Symbols are created by declarations and assignments in Cool. I have given them 
a value parameter, however this is only set by the compiler. This way, I can 
have Attribute and Assignment, and leave the SymbolScope table the way it is.