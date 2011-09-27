/**
 *  Entity/EntitySystem.cpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#include "EntitySystem.hpp"
#include "Components/Components.hpp"
#include <algorithm>
#if defined( DEBUG ) || defined( _DEBUG )
#include <cassert>
#endif

#include <Windows.h>
#include <sstream>

EntitySystem::~EntitySystem()
{
	EntityComponentMap::iterator ec_iter =
		_entity_map.begin();

	while( ec_iter != _entity_map.end() )
	{
		BaseComponentPtrSet set = ec_iter->second;
		BaseComponentPtrSet::iterator set_iter =
			set.begin();

		while( set_iter != set.end() )
		{
			delete ( *set_iter );
			// set_iter is const for some reason, so I can't set it to 0.
			//( *set_iter ) = 0;

			++set_iter;
		}

		++ec_iter;
	}
}

Entity EntitySystem::CreateNewEntity()
{
	if( _dead_entities.size() > 0 )
	{
		Entity e = _dead_entities.back();
		_dead_entities.pop_back();
		_entities.push_back( e );

		return e;
	}
	else if( _entities.size() > 0 )
	{
		Entity e = _entities.back();
		++e;
		_entities.push_back( e );

		return e;
	}
	else
	{
		Entity e = 1;
		_entities.push_back( e );

		return e;
	}
}

void EntitySystem::DestroyEntity( Entity e )
{
	EntityComponentMap::iterator ec_iter = _entity_map.find( e );

	if( ec_iter != _entity_map.end() )
	{
		// remove all references to the entity in the component_type map
		// and delete the entity's components
		BaseComponentPtrSet::iterator c_iter = ec_iter->second.begin();
		while( c_iter != ec_iter->second.end() )
		{
			ComponentTypeEntityMap::iterator ce_iter =
				_component_type_map.find( ( *c_iter )->GetType() );

			std::set< Entity > set = ce_iter->second;
			set.erase( e );

			delete *c_iter;
			//c_iter is const for some reason...
			///*c_iter = 0;

			++c_iter;
		}
	}

	_entity_map.erase( e );

	_entities.erase( std::remove( _entities.begin(), _entities.end(), e ), _entities.end() );
}

void EntitySystem::CreateAndAttachComponent(
	Entity e,
	COMPONENT_TYPE type,
	BaseComponent::BaseComponentData& data )
{
	// unfortunately, it appears we have to create the component
	// and try to insert it. It's easier than iterating through the set.
	BaseComponent* c = _create_component_map()[ type ]();
	c->SetData( data );

	// result.second indicates success
	std::pair< BaseComponentPtrSet::iterator, bool > result =
		_entity_map[ e ].insert( c );
	if( !result.second )
	{
		delete c;
		c = 0;
	}
	else
	{
		// The insertion succeeded, so we need to add the entity to the 
		// component's list now
		_component_type_map[ type ].insert( e );
	}
}

void EntitySystem::GetEntitiesByComponentType( COMPONENT_TYPE type, std::vector< Entity >& v )
{
	ComponentTypeEntityMap::iterator ce_iter =
		_component_type_map.find( type );

	if( ce_iter != _component_type_map.end() )
		v.insert( v.end(), ce_iter->second.begin(), ce_iter->second.end() );
}

void EntitySystem::GetEntityComponents( Entity e, std::vector< BaseComponent* >& v )
{
	EntityComponentMap::iterator ec_iter =
		_entity_map.find( e );

	if( ec_iter != _entity_map.end() )
		v.insert( v.end(), ec_iter->second.begin(), ec_iter->second.end() );
}

bool EntitySystem::GetComponent(
	Entity entity,
	COMPONENT_TYPE type,
	BaseComponent** component )
{
	*component = 0;

	EntityComponentMap::iterator ec_iter =
		_entity_map.find( entity );

	int count = 0;
	if( ec_iter != _entity_map.end() )
	{
		BaseComponentPtrSet::iterator bc_iter = ec_iter->second.begin();
		while( bc_iter != ec_iter->second.end() )
		{
			if( ( *bc_iter )->GetType() == type )
			{
				*component = const_cast< BaseComponent* >( ( *bc_iter ) );
				++count;
				break;
			}

			++bc_iter;
		}
	}
	
	return *component != 0;
}

void EntitySystem::Register( COMPONENT_TYPE type, ComponentCreator creator_fn )
{
	_create_component_map()[ type ] = creator_fn;
}
