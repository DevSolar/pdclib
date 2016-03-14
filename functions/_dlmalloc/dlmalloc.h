#include "_PDCLIB_glue.h"
#include <threads.h>

typedef mtx_t MLOCK_T;
#define INITIAL_LOCK(lk) mtx_init(lk, mtx_plain)
#define DESTROY_LOCK(lk) mtx_destroy(lk)
#define ACQUIRE_LOCK(lk) mtx_lock(lk)
#define RELEASE_LOCK(lk) mtx_unlock(lk)
#define TRY_LOCK(lk) mtx_trylock(lk)
#define NEED_GLOBAL_LOCK_INIT
static mtx_t malloc_global_mutex;
static once_flag malloc_global_mutex_init_once;

static void init_malloc_global_mutex(void)
{
	mtx_init(&malloc_global_mutex, mtx_plain);
}

static inline void *MMAP( size_t nbytes )
{
    void *p = _PDCLIB_allocpages( nbytes / _PDCLIB_MALLOC_PAGESIZE );
    return p ? p : (void*) (~(size_t)0);
}

#define MMAP(s) MMAP(s)
#define DIRECT_MMAP(s) MMAP(s)
#define MUNMAP(a, s) ((_PDCLIB_freepages((a), (s)/_PDCLIB_MALLOC_PAGESIZE)), 0)
#define MREMAP(a, osz, nsz, mv) _PDCLIB_reallocpages((a), (osz)/_PDCLIB_MALLOC_PAGESIZE, (nsz)/_PDCLIB_MALLOC_PAGESIZE, (mv))

#undef WIN32
#undef _WIN32
#define DLMALLOC_EXPORT  _PDCLIB_API
#define MALLOC_ALIGNMENT _PDCLIB_MALLOC_ALIGN
#define MSPACES 0
#define USE_LOCKS 2
#define USE_SPIN_LOCKS 0
#define USE_RECURSIVE_LOCKS 0
#define FOOTERS 0
#undef USE_DL_PREFIX
#define MALLOC_INSPECT_ALL 0
#define ABORT abort()
#define PROCEED_ON_ERROR 0
#define DEBUG 0
#define ABORT_ON_ASSERT_FAILURE 0
#define MALLOC_FAILURE_ACTION errno = ENOMEM
#define HAVE_MORECORE 0
#define MORECORE __unnamed__
#define MORECORE_CONTIGUOUS 0
#define MORECORE_CANNOT_TRIM 0
#define NO_SEGMENT_TRAVERSAL 0
#define HAVE_MMAP 1
#if defined(_PDCLIB_HAVE_REALLOCPAGES)
	#define HAVE_MREMAP 1
#else
	#define HAVE_MREMAP 0
#endif
#if defined(_PDCLIB_ALLOCPAGES_CLEARS)
	#define MMAP_CLEARS 1
#else
	#define MMAP_CLEARS 0
#endif
#define USE_BUILTIN_FFS 0
#define malloc_getpagesize _PDCLIB_MALLOC_PAGESIZE
#define USE_DEV_RANDOM 0
#define NO_MALLINFO 1
#define MALLINFO_FIELD_TYPE size_t
#define NO_MALLOC_STATS 1
#define DEFAULT_GRANULARITY _PDCLIB_MALLOC_GRANULARITY
#define DEFAULT_TRIM_THRESHOLD _PDCLIB_MALLOC_TRIM_THRESHOLD
#define DEFAULT_MMAP_THREHOLD _PDCLIB_MALLOC_MMAP_THRESHOLD
#define MAX_RELEASE_CHECK_RATE _PDCLIB_MALLOC_RELEASE_CHECK_RATE

/* C standard says this is so */
#define REALLOC_ZERO_BYTES_FREES 1
#define LACKS_UNISTD_H
#define LACKS_FCNTL_H
#define LACKS_SYS_PARAM_H
#define LACKS_SYS_MMAN_H
#define LACKS_STRINGS_H
#define LACKS_SYS_TYPES_H
#define LACKS_SCHED_H
#include <stdlib.h>
#include <errno.h>
