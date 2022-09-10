#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "vector.hpp"

namespace ft{
	template< typename Iter >
class reverse_iterator {
	public:
		typedef Iter iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer pointer;
		typedef typename ft::iterator_traits<Iter>::reference reference;

	public:
		reverse_iterator(): _base(NULL) {}
		explicit reverse_iterator(iterator_type x ) : _base(x) {}
		iterator_type base() const {
			return _base;
		}
		template< class U >
		reverse_iterator(const reverse_iterator<U>& other ) {
			*this = other;
		}
		reverse_iterator& operator=(const reverse_iterator& other) {
			_base = other._base;
			return *this;
		}
		reference operator*() const {
			return *_base;
		}
		pointer operator->() const {
			return _base;
		}
		reference operator[] (difference_type n) const {
			return _base[n - 1];
		};
		reverse_iterator& operator++() {
			_base--;
			return *this;
		}
		reverse_iterator operator++(int) {
			reverse_iterator tmp(*this);
			_base--;
			return tmp;
		}
		reverse_iterator operator+(difference_type n) const {
			return reverse_iterator<iterator_type>(base() - n);
		}
		reverse_iterator operator+=(difference_type n) {
			_base -= n;
			return *this;
		}
		reverse_iterator& operator--() {
			_base++;
			return *this;
		}
		reverse_iterator operator--(int) {
			reverse_iterator tmp(*this);
			_base++;
			return tmp;
		}
		reverse_iterator operator-(difference_type n) const {
			return reverse_iterator<iterator_type>(base() + n);
		}
		reverse_iterator operator-=(difference_type n) {
			_base += n;
			return *this;
		}

	private:
		iterator_type	_base;
	};

	/**
		 * boolean operator for reverse iterator
	*/
	template<class Iterator1, class Iterator2>
	bool operator==(const std::reverse_iterator<Iterator1>& lhs,
					const std::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const std::reverse_iterator<Iterator1>& lhs,
					 const std::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() != rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const std::reverse_iterator<Iterator1>& lhs,
					const std::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() > rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const std::reverse_iterator<Iterator1>& lhs,
					 const std::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() >= rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const std::reverse_iterator<Iterator1>& lhs,
					const std::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() < rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const std::reverse_iterator<Iterator1>& lhs,
					 const std::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() <= rhs.base();
	}

	template< class Iter >
	reverse_iterator<Iter>
	operator+(typename reverse_iterator<Iter>::difference_type n,
			   const reverse_iterator<Iter>& it) {
		return reverse_iterator<Iter>(it.base() - n);
	}

	template< class Iterator >
	typename reverse_iterator<Iterator>::difference_type
	operator-( const reverse_iterator<Iterator>& lhs,
			   const reverse_iterator<Iterator>& rhs ) {
		rhs.base() - lhs.base();
	}
}

#endif
