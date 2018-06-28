/* text utilities

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef TEXT_UTILITIES_H
#define TEXT_UTILITIES_H TEXT_UTILITIES_H

#include <inttypes.h>
#include <stdio.h>

/* Trim leading and trailing whitespace from a given string.
   Will return a pointer beyond leading whitespace, and overwrite trailing
   whitespace with null bytes.
*/
char * trim( char * s );

/* A function similar to strtok(), that returns the next token in a string,
   up to the next separator character (which is replaced with a null byte)
   or up to end-of-string.
   As opposed to strtok(), which treats consecutive separators as one, this
   function will work "correctly" for those as well, returning a (pointer
   to an) empty string in those cases.
   Pass the string as first parameter IN THE FIRST CALL ONLY, and NULL in
   subsequent calls. The function holds an internal, static pointer to the
   string being processed. This, of course, means the function is not thread-
   safe.
*/
char * next_token( char * s, char delim );

/* When processing a file with delimited-values, there are a couple of things
   you want to be sure about before parsing it:
   - the number of lines (data records) in the file;
   - that all lines of the file will fit the intended line buffer size;
   - that all records in the file indeed have the expected number of fields;
   - that none of the fields for which you are assuming a given size exceeds
     that size.
   (For line buffer size, consider that the buffer must be large enough for
   the line contents, the newline (to check that the line was actually read
   in full), and the null terminator.)
   This function does all that for you in a single pass. The parameters are:
   - FILE handle to the file (function will rewind the file before checking,
     and rewind again when it is done);
   - the intended line buffer size;
   - the field delimiter;
   - the expected number of fields;
   - a pointer to an array holding the expected maximum width for each field,
     with a negative value indicating that this field's width need not be
     checked.
   The function will return the number of lines in the file, or (size_t)-1
   if one of the checks failed. The reason for the failed check will be
   written to stderr. (The file will not be rewound in this case.)
   This requires reading and tokenizing the file twice, but removes lots of
   error checking from the actual parsing, making for cleaner code.
*/
size_t check_file( FILE * fh, size_t max_line_length, char delim, size_t fields, int const * widths );

#endif
