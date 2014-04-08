Syntax Tree
===========
The files in this directory make up the syntax tree like so:

- Type
- Symbol Table
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
destructor

### Note on Symbols
Symbols are created by declarations and assignments in Cool. I have given them 
a value parameter, however this is only set by the compiler. This way, I can 
have Attribute and Assignment, and leave the SymbolScope table the way it is.