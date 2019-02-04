#include "null.h"
#include "node.h"

namespace SK_YAML
{
	_Null Null;

	bool IsNull(const Node& node)
	{
		return node.Read(Null);
	}
}
