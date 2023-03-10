#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"
#include <iostream>
#include "less.hpp"

namespace ft{
	template<
			class Key,
			class T,
			class Compare = ft::less<Key>,
			class Allocator = std::allocator<ft::pair<const Key, T> >
	> class map {
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		typedef typename allocator_type::size_type       size_type;
		typedef typename allocator_type::difference_type difference_type;
		//TODO iterator but you need red black tree for it
		class value_compare: std::binary_function<value_type, value_type, bool> {
		protected:
			Compare comp;
		public:
			bool operator()( const value_type& lhs, const value_type& rhs ) const {
				return comp(lhs.first_type, rhs.first_type);
			}
			friend map<Key, T, Compare>;
			explicit value_compare(Compare c): comp(c) {}
		};
		/**
		 * constructors for the map
		 */
		 map() {}

		template< class InputIt >
		map(InputIt first, InputIt last,
			 const Compare& comp = Compare(),
			 const Allocator& alloc = Allocator() ) {

		 }

		map(const map& other) {*this = other;}


	};
}

#endif