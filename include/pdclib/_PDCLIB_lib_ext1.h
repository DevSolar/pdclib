/* __STDC_WANT_LIB_EXT1__ redefinition guard

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef __STDC_WANT_LIB_EXT1__
  #ifdef __STDC_WANT_LIB_EXT1_PREVIOUS__
    #if __STDC_WANT_LIB_EXT1_PREVIOUS__ != -1
      #error __STDC_WANT_LIB_EXT1__ undefined when it was defined earlier.
    #endif
  #else
    #define __STDC_WANT_LIB_EXT1_PREVIOUS__ -1
  #endif
#else
  #if ( __STDC_WANT_LIB_EXT1__ + 0 ) == 0 && ( 0 - __STDC_WANT_LIB_EXT1__ - 1 ) == 1
    #error __STDC_WANT_LIB_EXT1__ defined but empty. Should be an integer value.
  #endif
  #ifdef __STDC_WANT_LIB_EXT1_PREVIOUS__
    #if ( __STDC_WANT_LIB_EXT1__ + 0 ) != __STDC_WANT_LIB_EXT1_PREVIOUS__
      #error __STDC_WANT_LIB_EXT1__ redefined from previous value.
    #endif
  #else
    #if ( __STDC_WANT_LIB_EXT1__ + 0 ) == 0
      #define __STDC_WANT_LIB_EXT1_PREVIOUS__ 0
    #elif ( __STDC_WANT_LIB_EXT1__ + 0 ) == 1
      #define __STDC_WANT_LIB_EXT1_PREVIOUS__ 1
    #else
      #error __STDC_WANT_LIB_EXT1__ set to value other than 0,1 -- undefined behavior
    #endif
  #endif
#endif
