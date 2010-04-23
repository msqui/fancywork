#include "TransformationTable.h"

#include <sstream>

namespace fw {
namespace config {

TransformationTable::TransformationTable(const std::string& filename) :
	FileConfig(filename)
{}

TransformationTable::TransformationTablePtrT
TransformationTable::create(const std::string& filename)
{
	return TransformationTablePtrT(new TransformationTable(filename));
}

void TransformationTable::add(const fw::types::Correspondence& corr)
{
	_table.insert(corr.pair());
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