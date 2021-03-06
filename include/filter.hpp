#ifndef _CSDBG_FILTER
#define _CSDBG_FILTER 1

/**
	@file include/filter.hpp

	@brief Class csdbg::filter definition
*/

#include "./object.hpp"

namespace csdbg {

/**
	@brief Instrumentation filter

	An object of this class is used to filter out whole modules or sets of methods
	by matching a POSIX extended regular expression against their absolute path or
	their signature, respectively

	@todo <b style="color: #ff0000">[ ? ]</b> Make the object copyable
*/
class filter: virtual public object
{
protected:

	/* Protected variables */

	regex_t m_expr;										/**< @brief Filter expression */

	bool m_mode;											/**< @brief Filter type switch */


	/* Protected copy constructors */

	filter(const filter&);

	virtual filter* clone() const;


	/* Protected operator overloading methods */

	virtual filter& operator=(const filter&);

public:

	/* Friend classes and functions */

	template <class F> friend class node;

	template <class F> friend class chain;


	/* Constructors, copy constructors and destructor */

	filter(const i8*, bool, bool = true);

	virtual ~filter();


	/* Accessor methods */

	virtual bool mode() const;

	virtual filter& set_expr(const i8*, bool);

	virtual filter& set_mode(bool);


	/* Generic methods */

	virtual bool apply(const i8*) const;
};

}

#endif

