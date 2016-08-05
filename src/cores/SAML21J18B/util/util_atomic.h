#include <util/compiler.h>

namespace util
{
	namespace atomic
	{
		typedef uint32_t atomic_t;

		void EnterCriticalSection( atomic_t volatile *atomic );
		void ExitCriticalSection( atomic_t volatile *atomic );
	}
}

// Helper functions for entering and exiting critical sections. Use these instead of the functions defined in the source file.

#define CRITICAL_SECTION_ENTER() \
		{volatile util::atomic::atomic_t __atomic; util::atomic::EnterCriticalSection(&__atomic);

#define CRITICAL_SECTION_LEAVE() \
		util::atomic::ExitCriticalSection(&__atomic);}

// Use:
//
// CRITICAL_SECTION_ENTER()
// ... your code
// CRITICAL_SECTION_LEAVE()
//