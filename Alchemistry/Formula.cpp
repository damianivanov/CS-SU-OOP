#include "Formula.h"
Formula::Formula(){
	result = NULL;
}
Formula::~Formula(){

}
string Formula::to_string() {
	string sb = "";
	for (size_t i=0;i<elements.size()-2;++i)
	{
		sb.append(elements[i]->get_name());
		sb += ", ";
	}
	sb.append(elements[elements.size() - 2]->get_name());
	return sb;
}