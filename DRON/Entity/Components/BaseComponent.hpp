/**
 * Entity/BaseComponent.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef BASE_COMPONENT_HPP
#define BASE_COMPONENT_HPP

#include "ComponentTypes.hpp"
#include "../Entity.hpp"
#include "../EntitySystem.hpp"

/*********************************************
 * BaseComponent
 * This simply provides GetType()
 * and a common base class, of course ;)
 */
class BaseComponent
{
	public:
		virtual COMPONENT_TYPE GetType() const = 0;
		virtual bool operator==( const BaseComponent& other ) const = 0;
		virtual bool operator!=( const BaseComponent& other ) const = 0;
		virtual bool operator<( const BaseComponent& other ) const = 0;

		struct Data { };
		virtual BaseComponent::Data& GetData() = 0;
		virtual void SetData( BaseComponent::Data& data ) = 0;
};

/**********************************************************
 * AutoRegistrar< T >
 * When instantiated, the constructor auto-registers
 * Create(), which creates a new T*, with the EntitySystem.
 * Each component type inherits from a templated class that
 * has a static AutoRegistrar< T > member, so that 
 * instantiation occurs at program startup.
 */
template< typename T >
struct AutoRegistrar
{
	AutoRegistrar()
		{ EntitySystem::Register( TplComponent< T >::GetTypeStatic(), AutoRegistrar< T >::Create ); }
	static BaseComponent* Create() { return new T; }
};

/***********************************************
 * TplComponent< T >
 * Each component T derives from this class.
 */
template< class T >
class TplComponent : public BaseComponent
{
	public:
		TplComponent() { &_registrar; }
		virtual COMPONENT_TYPE GetType() const { return _type; }
		static COMPONENT_TYPE GetTypeStatic() { return _type; }

		virtual bool operator==( const BaseComponent& other ) const
			{ return GetType() == other.GetType(); }
		virtual bool operator!=( const BaseComponent& other ) const
			{ return !( *this == other ); }
		virtual bool operator<( const BaseComponent& other ) const
			{ return GetType() < other.GetType(); }

	private:
		static COMPONENT_TYPE		_type;
		static AutoRegistrar< T >	_registrar;
};

#endif  //BASE_COMPONENT_HPP
