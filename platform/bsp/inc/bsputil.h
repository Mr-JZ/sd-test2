/*
 * bsputil.h
 *
 *  Created on: Jul 19, 2022
 *      Author: michael
 */

#ifndef BSP_INC_BSPUTIL_H_
#define BSP_INC_BSPUTIL_H_

namespace Platform::BSP {

	/* --Base class of non-copyable and non-movable objects. */
	class NonCopyable {
	public:

		/* --Construction/destruction is ok. */
		NonCopyable() = default;
		~NonCopyable() = default;

		/* --Copying/moving is not ok. */
	    NonCopyable(const NonCopyable&) = delete;
	    NonCopyable(NonCopyable&&) = delete;
	    NonCopyable& operator=(const NonCopyable&) = delete;
	    const NonCopyable& operator=(NonCopyable&) = delete;

	};

}


#endif /* BSP_INC_BSPUTIL_H_ */
