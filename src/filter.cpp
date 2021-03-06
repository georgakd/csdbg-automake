#include "../include/filter.hpp"
#include "../include/util.hpp"

/**
	@file src/filter.cpp

	@brief Class csdbg::filter method implementation
*/

namespace csdbg {

/**
 * @brief Object copy constructor
 *
 * @param[in] src the source object
 */
filter::filter(const filter &src)
{
}


/**
 * @brief Object virtual copy constructor
 *
 * @returns NULL
 */
inline filter* filter::clone() const
{
	return NULL;
}


/**
 * @brief Assignment operator
 *
 * @param[in] rval the assigned object
 *
 * @returns *this
 */
inline filter& filter::operator=(const filter &rval)
{
	return *this;
}


/**
 * @brief Object constructor
 *
 * @param[in] expr the filter expression
 *
 * @param[in] icase true to ignore case on filtering, false otherwise
 *
 * @param[in] mode true to create a symbol filter, false to filter modules
 *
 * @throws csdbg::exception
 */
filter::filter(const i8 *expr, bool icase, bool mode):
m_mode(mode)
{
	util::memset(&m_expr, 0, sizeof(regex_t));
	set_expr(expr, icase);
}


/**
 * @brief Object destructor
 */
filter::~filter()
{
	regfree(&m_expr);
}


/**
 * @brief Get the filter type
 *
 * @returns this->m_mode
 */
inline bool filter::mode() const
{
	return m_mode;
}


/**
 * @brief Set the filter expression
 *
 * @param[in] expr the new expression
 *
 * @param[in] icase true to ignore case on filtering, false otherwise
 *
 * @returns *this
 *
 * @throws csdbg::exception
 */
filter& filter::set_expr(const i8 *expr, bool icase)
{
	if ( unlikely(expr == NULL) )
		throw exception("invalid argument: expr (=%p)", expr);

	regfree(&m_expr);
	i32 flags = REG_EXTENDED | REG_NOSUB;
	if ( unlikely(icase) )
		flags |= REG_ICASE;

	/* Compile the regular expression */
	i32 retval = regcomp(&m_expr, expr, flags);
	if ( likely(retval == 0) )
		return *this;

	/* If the expression compilation failed */
	i32 len = regerror(retval, &m_expr, NULL, 0);
	i8 errbuf[len];
	regerror(retval, &m_expr, errbuf, len);
	regfree(&m_expr);

	throw exception(
		"failed to compile filter '%s' (regex errno %d - %s)",
		expr,
		retval,
		errbuf
	);
}


/**
 * @brief Set the filter type
 *
 * @param[in] mode the new type
 *
 * @returns *this
 */
inline filter& filter::set_mode(bool mode)
{
	m_mode = mode;
	return *this;
}


/**
 * @brief Apply the filter to a function signature or a module absolute path
 *
 * @param[in] target the filtered text
 *
 * @returns true if the target matches the filter, false otherwise
 */
inline bool filter::apply(const i8 *target) const
{
	__D_ASSERT(target != NULL);
	if ( unlikely(target == NULL) )
		return false;

	return !regexec(&m_expr, target, 0, NULL, 0);
}

}

