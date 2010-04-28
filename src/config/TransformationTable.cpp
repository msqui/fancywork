#include "TransformationTable.h"

#include <sstream>
#include <fstream>
#include <vector>

#include <boost/algorithm/string.hpp>

namespace fw {
namespace config {

TransformationTable::TransformationTable(const std::string& filename)
{
	read(filename);
}

TransformationTable::TransformationTablePtrT
TransformationTable::create(const std::string& filename)
{
	return TransformationTablePtrT(new TransformationTable(filename));
}

void TransformationTable::read(const std::string& filename)
{
	std::ifstream fs;
	fs.open(filename.c_str(), std::ios::in);
	
	std::string line;
	while(!fs.eof())
	{
		std::getline(fs, line);
		add(line);
	}
	
	fs.close();
}

void TransformationTable::add(const std::string& str, const std::string& delimiter)
{
	if(str == "") return;

	std::string trstr = str;
	boost::trim(trstr);
	if(trstr[0] == '#') return;
	
	std::vector<std::string> color_symbol;
	boost::split(color_symbol, str, boost::is_any_of(delimiter));
	
	if(color_symbol.size() < 2)
	{
		throw std::runtime_error("wrong file format");
	}
	
	add(fw::types::Correspondence(color_symbol[0], color_symbol[1]));
}

void TransformationTable::add(const fw::types::Correspondence& corr)
{
	_table.insert(corr.pair());
}

fw::types::Symbol TransformationTable::find(const fw::types::Color& color)
{
	SymbolMapT::const_iterator it = _table.find(color);
	if(it == _table.end())
	{
		return fw::types::NoSymbol();
	}
	
	return it->second;
}

std::ostream& TransformationTable::to_stream(std::ostream& ostr) const
{
	ostr << "[ ";
	for(TransformationTable::SymbolMapT::const_iterator i = _table.begin();
			i != _table.end();
			++i)
	{
		ostr << i->first << " => " << i->second << "; ";
	}
	ostr << "]";
	
	return ostr;
}

std::string TransformationTable::str() const
{
	std::stringstream ss;
	(void) to_stream(ss);
	
	return ss.str();
}

std::ostream& operator<< (std::ostream& ostr, const TransformationTable& tt)
{
	(void) tt.to_stream(ostr);
	return ostr;
}

}}