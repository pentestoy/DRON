/**
 *  Entity/EntitySystem.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef _ENTITY_SYSTEM_HPP_
#define _ENTITY_SYSTEM_HPP_

#include <vector>
#include <map>

enum COMPONENT_TYPE;
typedef unsigned int Entity;

class BaseComponent;
class EntitySystem
{
	public:
		EntitySystem() { }
		~EntitySystem();

		Entity CreateNewEntity();
		void DestroyEntity( Entity );
		void AttachComponent( Entity, COMPONENT_TYPE );

		void GetEntitiesByComponentType( COMPONENT_TYPE, std::vector< Entity >& );
		void GetEntityComponents( Entity, std::vector< BaseComponent* >& );

	private:
		EntitySystem( const EntitySystem& );
		EntitySystem& operator=( const EntitySystem& );

		BaseComponent* CreateNewComponent( COMPONENT_TYPE );

		std::vector< Entity > _entities;
		std::vector< Entity > _dead_entities;

		std::map< Entity, std::vector< BaseComponent* >* > _ec_map;

		std::map< COMPONENT_TYPE, std::vector< Entity >* > _ce_map;
};

#endif  _ENTITY_SYSTEM_HPP_
