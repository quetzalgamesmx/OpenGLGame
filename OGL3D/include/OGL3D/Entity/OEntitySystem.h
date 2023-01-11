#pragma once
#include <OGL3D/OPrerequisites.h>
#include <map>
using namespace std;

class OEntity;
class OEntitySystem
{
public:
	OEntitySystem();
	~OEntitySystem();


	template<typename T>
	T* createEntity()
	{
		static_assert (is_base_of<OEntity, T>::value, "T must derive from OEntity class");
		auto id = typeid(T).hash_code();
		auto e = new T();

		if (createEntityInternal(e, id))
			return e;

		return nullptr;
	}

private:
	map < size_t, map<OEntity*, unique_ptr<OEntity>>> m_entities;

	bool createEntityInternal(OEntity* entity, size_t id);

};

