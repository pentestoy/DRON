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

void EntitySystem::AttachComponent( Entity e, COMPONENT_TYPE type )
{
	// unfortunately, it appears we have to create the component
	// and try to insert it. It's easier than iterating through the set.
	BaseComponent* c = CreateNewComponent( type );
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
	/*
	// look for the entity
	std::map< Entity, std::vector< BaseComponent* >* >::iterator ec_iter =
		_entity_map.find( e );

	// if we didn't find it, then we add it and give it the component
	if( ec_iter == _entity_map.end() )
	{
		std::vector< BaseComponent* >* v = new std::vector< BaseComponent* >;
		BaseComponent* c = CreateNewComponent( type );
		if( c )
			v->push_back( c );

		_entity_map.insert(
			std::pair< Entity, std::vector< BaseComponent* >* >( e, v ) );
	}
	else
	{
		// we found it, so we check to see if it already has this component
		bool found = false;
		std::vector< BaseComponent* >::iterator comp_iter =
			ec_iter->second->begin();

		while( comp_iter != ec_iter->second->end() )
		{
			if( ( *comp_iter )->GetType() == type )
				found = true;

			++comp_iter;
		}

		// it doesn't have the component, so we add it.
		if( found == false )
		{
			BaseComponent* c = CreateNewComponent( type );
			if( c )
				ec_iter->second->push_back( c );
		}
	}

	// now we add the entity to the component_type's vector
	std::map< COMPONENT_TYPE, std::vector< Entity >* >::iterator ce_iter =
		_component_type_map.find( type );

	// if we didn't find the component type, then we create it and add the entity to it
	if( ce_iter == _component_type_map.end() )
	{
		std::vector< Entity >* v = new std::vector< Entity >;
		v->push_back( e );

		_component_type_map.insert(
			std::pair< COMPONENT_TYPE, std::vector< Entity >* >( type, v ) );
	}
	else
	{
		// we found it, so we add the entity
#if defined( DEBUG ) || defined( _DEBUG )
		std::vector< Entity >::iterator e_iter =
			std::find( ce_iter->second->begin(),
					   ce_iter->second->end(),
					   e );

		assert( e_iter == ce_iter->second->end() );
#endif
		ce_iter->second->push_back( e );
	}
	*/
}

BaseComponent* EntitySystem::CreateNewComponent( COMPONENT_TYPE type )
{
	//CameraComponent cc;
	return _create_component_map()[ type ]();//_create_component_map[type]();
	/*
	switch( type )
	{
		case COMPONENT_CAMERA:
			return new CameraComponent;

		case COMPONENT_MOVABLE:
			return new MovableComponent;

		case COMPONENT_RENDERABLE:
			return new RenderableComponent;

		case COMPONENT_XFORM:
			return new XformComponent;

		default:
			return 0;
	}
	*/
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

void EntitySystem::Register( COMPONENT_TYPE type, ComponentCreator creator_fn )
{
	_create_component_map()[ type ] = creator_fn;
}
