#ifndef __TRANSFORMATIONTABLE_H__
#define __TRANSFORMATIONTABLE_H__

#include "FileConfig.h"

#include <string>
#include <map>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

#include "types/Color.h"
#include "types/Symbol.h"
#include "types/Correspondence.h"

namespace fw {
namespace config {

class TransformationTable : public FileConfig
{
public:
	typedef boost::shared_ptr<TransformationTable> TransformationTablePtrT;
	
	static TransformationTablePtrT create(const std::string& filename);
	
	void add(const fw::types::Correspondence& corr);
	
	std::ostream& to_stream(std::ostream& ostr) const;
	std::string str() const;
	
	friend std::ostream& operator<< (std::ostream& ostr, const TransformationTable& tt);
	
private:
	TransformationTable(const std::string& filename);
	
	typedef std::map<fw::types::Color, fw::types::Symbol> SymbolMapT;
	SymbolMapT _table;
};

}}

#endif /* end of include guard: __TRANSFORMATIONTABLE_H__ */
