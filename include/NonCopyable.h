#ifndef _NON_COPYABLE_H_
#define _NON_COPYABLE_H_

namespace aelzns {
	/**
	 * a class that is to be inherited with disabled copy constructor and assignement 
	 * operators
	 */
  class NonCopyable {
		protected:
			NonCopyable() {}
			~NonCopyable() {}

		private:
			// no copy constructor
			NonCopyable(const NonCopyable&);

			// no assignment
			const NonCopyable& operator=(const NonCopyable&);
	};
}
#endif