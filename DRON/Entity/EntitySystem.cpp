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
EntitySystem::EntitySystem()
{
	MessageBox( 0, L"Constructing ec", L"", MB_OK );
}

EntitySystem::~EntitySystem()
{
	std::map< Entity, std::vector< BaseComponent* >* >::iterator ec_iter =
		_ec_map.begin();

	while( ec_iter != _ec_map.end() )
	{
		std::vector< BaseComponent* >* v = ec_iter->second;
		std::vector< BaseComponent* >::iterator v_iter =
			v->begin();

		while( v_iter != v->end() )
		{
			delete *v_iter;
			*v_iter = 0;

			++v_iter;
		}

		delete v;
		v = 0;

		++ec_iter;
	}

	std::map< COMPONENT_TYPE, std::vector< Entity >* >::iterator ce_iter =
		_ce_map.begin();

	while( ce_iter != _ce_map.end() )
	{
		delete ce_iter->second;
		ce_iter->second = 0;
		 
		++ce_iter;
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
		Entity e = 0;
		_entities.push_back( e );

		return e;
	}
}

void EntitySystem::DestroyEntity( Entity e )
{
	std::map< Entity, std::vector< BaseComponent* >* >::iterator ec_iter =
		_ec_map.find( e );

	if( ec_iter != _ec_map.end() )
	{
		// remove all references to the entity in the component_type map
		// and delete the entity's components
		std::vector< BaseComponent* >::iterator c_iter = ec_iter->second->begin();
		while( c_iter != ec_iter->second->end() )
		{
			std::map< COMPONENT_TYPE, std::vector< Entity >* >::iterator ce_iter =
				_ce_map.find( ( *c_iter )->GetType() );

			std::vector< Entity >* v = ce_iter->second;
			v->erase( std::remove( v->begin(), v->end(), e ), v->end() );

			delete *c_iter;
			*c_iter = 0;

			++c_iter;
		}
	}

	delete ec_iter->second;
	ec_iter->second = 0;

	_ec_map.erase( e );

	_entities.erase( std::remove( _entities.begin(), _entities.end(), e ), _entities.end() );
}

void EntitySystem::AttachComponent( Entity e, COMPONENT_TYPE type )
{
	// look for the entity
	std::map< Entity, std::vector< BaseComponent* >* >::iterator ec_iter =
		_ec_map.find( e );

	// if we didn't find it, then we add it and give it the component
	if( ec_iter == _ec_map.end() )
	{
		std::vector< BaseComponent* >* v = new std::vector< BaseComponent* >;
		BaseComponent* c = CreateNewComponent( type );
		if( c )
			v->push_back( c );

		_ec_map.insert(
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
		_ce_map.find( type );

	// if we didn't find the component type, then we create it and add the entity to it
	if( ce_iter == _ce_map.end() )
	{
		std::vector< Entity >* v = new std::vector< Entity >;
		v->push_back( e );

		_ce_map.insert(
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
}

BaseComponent* EntitySystem::CreateNewComponent( COMPONENT_TYPE type )
{
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
}

void EntitySystem::GetEntitiesByComponentType( COMPONENT_TYPE type, std::vector< Entity >& v )
{
	std::map< COMPONENT_TYPE, std::vector< Entity >* >::iterator ce_iter =
		_ce_map.find( type );

	if( ce_iter != _ce_map.end() )
		v.insert( v.end(), ce_iter->second->begin(), ce_iter->second->end() );
}

void EntitySystem::GetEntityComponents( Entity e, std::vector< BaseComponent* >& v )
{
	std::map< Entity, std::vector< BaseComponent* >* >::iterator ec_iter =
		_ec_map.find( e );

	if( ec_iter != _ec_map.end() )
		v.insert( v.end(), ec_iter->second->begin(), ec_iter->second->end() );
}
