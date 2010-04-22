#ifndef __MESSAGES_H__
#define __MESSAGES_H__

namespace fw {
namespace util {

class Messages
{
public:
	static void usage();	
	
private:
	Messages ();
	Messages (const Messages&);
	void operator= (const Messages&);
};

}}

#endif /* __MESSAGES_H__ */

