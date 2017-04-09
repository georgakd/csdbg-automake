#ifndef _CSDBG_CHAIN
#define _CSDBG_CHAIN 1

/**
	@file include/chain.hpp

	@brief Class csdbg::chain definition and method implementation
*/

#include "./node.hpp"
#include "./exception.hpp"

namespace csdbg {

/**
	@brief Lightweight, templated, doubly-linked list (using XOR linking)

	A doubly-linked list is a great optimization compared with a singly-linked one
	in node access times and memory references, especially in very big lists. The
	XOR linking implementation, although a bit more complex, uses the same ammount
	of memory (per node) as a singly-linked list. The chain supports shared data
	(multiple chains can point to the same data) but it's not thread safe, callers
	should synchronize thread access. This implementation does not allow a node
	with a NULL or a duplicate data pointer. A node can be detached (dispose the
	node without deleting its data) or removed (dispose both node and data). A
	chain can be traversed using simple callbacks	and method chain::foreach

	@see csdbg::node

	@todo Implement cached pointers
*/
template <class T>
class chain: virtual public object
{
protected:

	/* Protected variables */

	node<T> *m_head;									/**< @brief Chain head */

	node<T> *m_tail;									/**< @brief Chain tail */

	u32 m_size;												/**< @brief Node count */


	/* Protected generic methods */

	virtual node<T>* node_at(u32) const;

	virtual node<T>* node_with(const T*) const;

	virtual node<T>* detach_node(u32);

public:

	/* Constructors, copy constructors and destructor */

	chain();

	chain(const chain&);

	virtual	~chain();

	virtual chain* clone() const;


	/* Accessor methods */

	virtual	u32 size() const;


	/* Operator overloading methods */

	virtual chain& operator=(const chain&);

	virtual T* operator[](u32) const;


	/* Generic methods */

	virtual chain& add(T*);

	virtual chain& remove(u32);

	virtual chain& clear();

	virtual T* at(u32) const;

	virtual T* detach(u32);

	virtual chain& foreach(void (*)(u32, T*)) const;
};


/**
 * @brief Get the node at a chain offset
 *
 * @param[in] i the offset
 *
 * @returns the i-th node
 *
 * @throws csdbg::exception
 */
template <class T>
node<T>* chain<T>::node_at(u32 i) const
{
	if ( unlikely(i >= m_size) )
		throw exception("offset out of chain bounds (%d >= %d)", i, m_size);

	/* Select traversal direction */
	node<T> *cur = m_head;
	i32 j = i, mid = m_size / 2;
	if (j >= mid) {
		j = m_size - i - 1;
		cur = m_tail;
	}

	node<T> *prev = NULL, *next;
	while ( likely(j-- > 0) ) {
		next = cur->link(prev);
		prev = cur;
		cur = next;
	}

	return cur;
}


/**
 * @brief Get the node with m_data == d
 *
 * @param[in] d the data pointer searched
 *
 * @returns the node with m_data == d or NULL if there's no such node
 */
template <class T>
node<T>* chain<T>::node_with(const T *d) const
{
	__D_ASSERT(d != NULL);
	if ( unlikely(d == NULL) )
		return NULL;

	node<T> *cur = m_head, *prev = NULL, *next;
	while ( likely(cur != NULL) ) {
		if ( unlikely(cur->m_data == d) )
			return cur;

		next = cur->link(prev);
		prev = cur;
		cur = next;
	}

	return NULL;
}


/**
 * @brief Detach the node at a chain offset
 *
 * @param[in] i the offset
 *
 * @returns the detached i-th node
 *
 * @throws csdbg::exception
 */
template <class T>
node<T>* chain<T>::detach_node(u32 i)
{
	if ( unlikely(i >= m_size) )
		throw exception("offset out of chain bounds (%d >= %d)", i, m_size);

	node<T> *cur = m_head, *prev = NULL, *next;
	while ( likely(i-- > 0) ) {
		next = cur->link(prev);
		prev = cur;
		cur = next;
	}

	next = cur->link(prev);

	/* If it's the first in the chain */
	if ( unlikely(cur == m_head) ) {
		m_head = next;

		/* If the chain is left empty */
		if ( unlikely(m_head == NULL) )
			m_tail = NULL;
		else
			m_head->unlink_from(cur);
	}

	/* If it's the last in the chain */
	else if ( unlikely(cur == m_tail) ) {
		m_tail = prev;
		m_tail->unlink_from(cur);
	}

	/* Relink previous and next nodes */
	else {
		prev->unlink_from(cur);
		prev->link_to(next);

		next->unlink_from(cur);
		next->link_to(prev);
	}

	m_size--;
	return cur;
}


/**
 * @brief Object default constructor
 */
template <class T>
inline chain<T>::chain():
m_head(NULL),
m_tail(NULL),
m_size(0)
{
}


/**
 * @brief Object copy constructor
 *
 * @param[in] src the source object
 *
 * @throws std::bad_alloc
 */
template <class T>
inline chain<T>::chain(const chain &src)
try:
m_head(NULL),
m_tail(NULL),
m_size(0)
{
	*this = src;
}

catch (...) {
	clear();
}


/**
 * @brief Object destructor
 */
template <class T>
inline chain<T>::~chain()
{
	clear();
}


/**
 * @brief Object virtual copy constructor
 *
 * @returns the object copy (heap allocated)
 *
 * @throws std::bad_alloc
 */
template <class T>
inline chain<T>* chain<T>::clone() const
{
	return new chain(*this);
}


/**
 * @brief Get the chain size (node count)
 *
 * @returns this->m_size
 */
template <class T>
inline u32 chain<T>::size() const
{
	return m_size;
}


/**
 * @brief Assignment operator
 *
 * @param[in] rval the assigned object
 *
 * @returns *this
 *
 * @throws std::bad_alloc
 *
 * @note
 *	Automatically resolves collisions when the chains overlap (when they have
 *	nodes with the same data pointer)
 */
template <class T>
chain<T>& chain<T>::operator=(const chain &rval)
{
	if ( unlikely(this == &rval) )
		return *this;

	/* Check if the chains overlap and detach shared data pointers */
	node<T> *cur = m_head, *prev = NULL, *next;
	while ( likely(cur != NULL) ) {
		if ( unlikely(rval.node_with(cur->m_data) != NULL) )
			cur->detach();

		next = cur->link(prev);
		prev = cur;
		cur = next;
	}

	clear();
	cur = rval.m_head;
	prev = NULL;
	while ( likely(cur != NULL) ) {
		T *copy = NULL;
		try {
			copy = new T(*cur->m_data);
			add(copy);
		}

		catch (...) {
			delete copy;
			throw;
		}

		next = cur->link(prev);
		prev = cur;
		cur = next;
	}

	return *this;
}


/**
 * @brief Subscript operator
 *
 * @param[in] i the index
 *
 * @returns the i-th node data pointer
 *
 * @throws csdbg::exception
 */
template <class T>
inline T* chain<T>::operator[](u32 i) const
{
	return at(i);
}


/**
 * @brief Add a node to the chain
 *
 * @param[in] d the new node data pointer
 *
 * @returns *this
 *
 * @throws std::bad_alloc
 * @throws csdbg::exception
 */
template <class T>
chain<T>& chain<T>::add(T *d)
{
	if ( unlikely(d == NULL) )
		throw exception("invalid argument: d (=%p)", d);

	/* If the data pointer already exists in the chain */
	if ( unlikely(node_with(d) != NULL) )
		throw exception("chain @ %p already has a node with data @ %p", this, d);

	node<T> *n = new node<T>(d);

	/* Add the node to the chain tail */
	if ( likely(m_head != NULL) ) {
		n->m_link = m_tail;
		m_tail->link_to(n);
		m_tail = n;
	}

	/* If it is the first node */
	else
		m_head = m_tail = n;

	m_size++;
	return *this;
}


/**
 * @brief Dispose the node (and its data) at a chain offset
 *
 * @param[in] i the offset
 *
 * @returns *this
 *
 * @throws csdbg::exception
 */
template <class T>
inline chain<T>& chain<T>::remove(u32 i)
{
	delete detach_node(i);
	return *this;
}


/**
 * @brief Empty the chain
 *
 * @returns *this
 */
template <class T>
chain<T>& chain<T>::clear()
{
	node<T> *cur = m_head, *prev = NULL, *next;
	while ( likely(cur != NULL) ) {
		next = cur->link(prev);
		prev = cur;

		delete cur;
		cur = next;
	}

	m_head = m_tail = NULL;
	m_size = 0;
	return *this;
}


/**
 * @brief Get the node data pointer at a chain offset
 *
 * @param[in] i the offset
 *
 * @returns the i-th node data pointer
 *
 * @throws csdbg::exception
 */
template <class T>
inline T* chain<T>::at(u32 i) const
{
	return node_at(i)->m_data;
}


/**
 * @brief Detach the node at a chain offset
 *
 * @param[in] i the offset
 *
 * @returns the detached i-th node data pointer
 *
 * @throws csdbg::exception
 */
template <class T>
inline T* chain<T>::detach(u32 i)
{
	node<T> *n = detach_node(i);
	T *d = n->detach();
	delete n;
	return d;
}


/**
 * @brief Traverse the chain with a callback for each node
 *
 * @param[in] pfunc the callback
 *
 * @returns *this
 */
template <class T>
chain<T>& chain<T>::foreach(void (*pfunc)(u32, T*)) const
{
	__D_ASSERT(pfunc != NULL);
	if ( unlikely(pfunc == NULL) )
		return const_cast<chain<T>&> (*this);

	u32 i = 0;
	node<T> *cur = m_head, *prev = NULL, *next;
	while ( likely(cur != NULL) ) {
		pfunc(i++, cur->m_data);

		next = cur->link(prev);
		prev = cur;
		cur = next;
	}

	return const_cast<chain<T>&> (*this);
}

}

#endif

