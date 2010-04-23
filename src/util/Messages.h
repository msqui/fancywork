#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <string>

namespace fw {
namespace util {

class Messages
{
public:
	static std::string usage();	
	
private:
	Messages ();
	Messages (const Messages&);
	void operator= (const Messages&);
};

}}

#endif /* __MESSAGES_H__ */

