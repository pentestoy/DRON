/**
 *  Entity/EntitySystem.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef ENTITY_SYSTEM_HPP
#define ENTITY_SYSTEM_HPP

#include <functional>
#include <map>
#include <set>
#include <vector>
#include "Components/BaseComponent.hpp"

enum COMPONENT_TYPE;
typedef unsigned int Entity;
struct BaseComponentData;
class EntitySystem
{
	public:
		EntitySystem() { }
		~EntitySystem();
		
		typedef BaseComponent* ( *ComponentCreator )();
		typedef std::vector< Entity > EntityVector;
		typedef std::vector< BaseComponent* > BaseComponentPtrVector;

		Entity CreateNewEntity();
		void DestroyEntity( Entity );

		void CreateAndAttachComponent(
			Entity e,
			COMPONENT_TYPE type,
			BaseComponent::BaseComponentData& data );

		void GetEntitiesByComponentType( COMPONENT_TYPE type, EntityVector& v );
		void GetEntityComponents( Entity e, BaseComponentPtrVector& v );

		static void Register( COMPONENT_TYPE type, ComponentCreator creator );

	private:
		// Prevent copying and assignment
		EntitySystem( const EntitySystem& );
		EntitySystem& operator=( const EntitySystem& );

		BaseComponent* CreateNewComponent( COMPONENT_TYPE );

		struct ComponentLess : public std::binary_function< const BaseComponent*,
															const BaseComponent*,
															bool >
		{
			bool operator()( const BaseComponent* lhs, const BaseComponent* rhs )
				{ return lhs < rhs; }
		};

		struct ComponentEquality : public std::binary_function< const BaseComponent*,
																const BaseComponent*,
																bool >
		{
			bool operator()( const BaseComponent* lhs, const BaseComponent* rhs )
			{ return *lhs == *rhs; }
		};

		typedef std::set< BaseComponent*, ComponentLess > BaseComponentPtrSet;
		typedef std::set< Entity > EntitySet;
		typedef std::map< Entity, BaseComponentPtrSet > EntityComponentMap;
		typedef std::map< COMPONENT_TYPE, EntitySet > ComponentTypeEntityMap;
		typedef std::map< COMPONENT_TYPE, ComponentCreator > CreateComponentMap;
		typedef std::vector< BaseComponent* > ComponentVector;

		/**********************************************************************
		 * _create_component_map() wraps the actual map in order to ensure
		 * the map is instantiated when needed. Look at
		 * http://www.parashift.com/c++-faq-lite/ctors.html#faq-10.14
		 * for info on the "static initialization order fiasco.
		 */
		static CreateComponentMap& 	_create_component_map()
		{
			static CreateComponentMap* ccm = new CreateComponentMap();
			return *ccm;
		}
		EntityVector			_entities;
		EntityVector			_dead_entities;
		EntityComponentMap		_entity_map;
		ComponentTypeEntityMap	_component_type_map;
		ComponentVector			_orphaned_components;
};

#endif  //ENTITY_SYSTEM_HPP
