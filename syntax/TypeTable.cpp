#include "TypeTable.h"

TypeTable::TypeTable(){}
TypeTable::~TypeTable(){
	table.clear();
}

int TypeTable::find(const std::string &str){
	int index = -1;
	std::vector<std::string>::iterator it;
	it = std::find(table.begin(), table.end(), str);
	if(it != table.end()){
		index = (it - table.begin());
	}
	return index;
}

// If force = true, skip the call to find
int TypeTable::add(const std::string &str, bool force){
	if(!force){
		int index = find(str);
		if(index != -1){
			return index;
		}
	}
	
	table.push_back(std::string(str));
	return (table.size() - 1);
}