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
class __declspec( align( 16 ) ) BaseComponent
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

/***********************************************
 * TplComponent< T >
 * Each component T derives from this class.
 */
template< class T >
class TplComponent : public BaseComponent
{
	public:
		TplComponent() { }
		virtual COMPONENT_TYPE GetType() const { return _type; }
		static COMPONENT_TYPE GetTypeStatic() { return _type; }
		static BaseComponent* Create();

		virtual bool operator==( const BaseComponent& other ) const
			{ return GetType() == other.GetType(); }
		virtual bool operator!=( const BaseComponent& other ) const
			{ return !( *this == other ); }
		virtual bool operator<( const BaseComponent& other ) const
			{ return GetType() < other.GetType(); }

	private:
		static COMPONENT_TYPE		_type;
};

template< class T >
BaseComponent* TplComponent< T >::Create()
{
	void* buffer = _aligned_malloc( sizeof( T ), 16 );
	return new( buffer ) T;
}

#endif  //BASE_COMPONENT_HPP
