#include "CMDMapping.h"

/*template <typename T>
CMDMapping<T>::CMDMapping()
{

}
*/

std::map<std::string, int> CMDMapping::GetMapping() const
{
	return mapping;
}

void CMDMapping::SetMapParam(std::map <std::string, int> inpmap)
{
		mapping = inpmap;
}


bool CMDMapping::CheckExistingElement(const std::string& key) const
{
	return (mapping.find(key) != mapping.end());;
}
