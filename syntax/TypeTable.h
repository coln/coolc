#ifndef COOL_TYPE_TABLE_H_
#define COOL_TYPE_TABLE_H_

#include <algorithm>
#include <string>
#include <vector>

class TypeTable {
private:
	std::vector<std::string> table;
public:
	int find(const std::string&);
	int add(const std::string&, bool = false);
	
	TypeTable();
	~TypeTable();
};

#endif