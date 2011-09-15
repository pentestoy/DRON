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

class EntitySystem
{
	public:
		EntitySystem() { }
		~EntitySystem();
		
		typedef BaseComponent* ( *ComponentCreator )();
		typedef std::vector< Entity > EntityVector;
		typedef std::vector< BaseComponent* > BaseComponentPtrVector;

		/**********************************************************************
		 * CreateNewEntity()
		 * Creates and returns a new Entity. The EntitySystem keeps track of
		 * and reuses IDs of destroyed Entities.
		 */
		Entity CreateNewEntity();

		/**********************************************************************
		 * DestroyEntity( Entity e )
		 * Calls delete on all components attached to the Entity. Removes the
		 * Entity from any ComponentType lists it is associated with. Then
		 * moves the Entity to the dead entities list.
		 */
		void DestroyEntity( Entity );

		/**********************************************************************
		 * AttachComponent( Entity e, COMPONENT_TYPE type )
		 * If the Entity does not have the requested component type, it creates
		 * a new one, associates it with the Entity, and associates the Entity
		 * with the component type's list.
		 *
		 * If the Entity already has a component of the requested type
		 * associated with it, the function does nothing.
		 */
		void AttachComponent( Entity e, COMPONENT_TYPE type );

		/**********************************************************************
		 * GetEntitiesByComponentType( COMPONENT_TYPE type, EntityVector& v )
		 * Populates v with all entities that have a component of requested
		 * type attached.
		 */
		void GetEntitiesByComponentType( COMPONENT_TYPE type, EntityVector& v );

		/**********************************************************************
		 * GetEntityComponents( Entity e, BaseComponentPtrVector& v )
		 * Populates v with all components attached to Entity e.
		 */
		void GetEntityComponents( Entity e, BaseComponentPtrVector& v );

		/**********************************************************************
		 * Register( COMPONENT_TYPE type, ComponentCreator creator )
		 * Registers a function that creates a component of the given type.
		 */
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
};

#endif  //ENTITY_SYSTEM_HPP
