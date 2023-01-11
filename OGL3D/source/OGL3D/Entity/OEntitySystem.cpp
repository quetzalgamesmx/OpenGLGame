#include <OGL3D/Entity/OEntitySystem.h>
#include <OGL3D/Entity/OEntity.h>

OEntitySystem::OEntitySystem()
{
}

OEntitySystem::~OEntitySystem()
{
}

bool OEntitySystem::createEntityInternal(OEntity* entity, size_t id)
{
	auto ptr = std::unique_ptr<OEntity>(entity);

	m_entities[id].emplace(entity, std::move(ptr));

	entity->onCreate();

	return true;
}
