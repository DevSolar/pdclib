// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

double atof( const char * s ) { /* TODO */ };
int atoi( const char * s ) { /* TODO */ };
long atol( const char * s ) { /* TODO */ };
long long atoll( const char * s) { /* TODO */ };

double strtod( const char * restrict s, char * * restrict endptr ) { /* TODO */ };
float strtof( const char * restrict s, char * * restrict endptr ) { /* TODO */ };
long double strtold( const char * restrict s, char * * restrict endptr ) { /* TODO */ };

long long strtoll( const char * restrict s, char * * restrict endptr, int base ) { /* TODO */ };
unsigned long long strtoull( const char * restrict s, char * * restrict endptr, int base) { /* TODO */ };

long strtol( const char * restrict s, char * * restrict endptr, int base ) { /* TODO */ };
unsigned long strtoul( const char * restrict s, char * * restrict endptr, int base) { /* TODO */ };

/* PDPC code - unreviewed, verbatim
double atof(const char *nptr)
{
    return (strtod(nptr, (char **)NULL));
}

double strtod(const char *nptr, char **endptr)
{
    double x = 0.0;
    
    while (1)
    {
        if (isdigit(*nptr))
        {
            x = x * 10 + (*nptr - '0');
        }
        else
        {
            if (endptr != NULL)
            {
                *endptr = (char *)nptr;
            }
            break;
        }
        nptr++;
    }
    return (x);
}

int atoi(const char *nptr)
{
    return ((int)strtol(nptr, (char **)NULL, 10));
}

long int atol(const char *nptr)
{
    return (strtol(nptr, (char **)NULL, 10));
}

long int strtol(const char *nptr, char **endptr, int base)
{
    long x = 0;
    int undecided = 0;
    
    if (base == 0)
    {
        undecided = 1;
    }
    while (1)
    {
        if (isdigit(*nptr))
        {
            if (base == 0)
            {
                if (*nptr == '0')
                {
                    base = 8;
                }
                else
                {
                    base = 10;
                    undecided = 0;
                }
            }
            x = x * base + (*nptr - '0');
            nptr++;
        }
        else if (isalpha(*nptr))
        {
            if ((*nptr == 'X') || (*nptr == 'x'))
            {
                if ((base == 0) || ((base == 8) && undecided))
                {
                    base = 16;
                    undecided = 0;
                }
                else
                {
                    break;
                }
            }
            else
            {
                x = x * base + (toupper((unsigned char)*nptr) - 'A') + 10;
                nptr++;
            }
        }
        else
        {
            break;
        }
    }
    if (endptr != NULL)
    {
        *endptr = (char *)nptr;
    }
    return (x);
}

unsigned long int strtoul(const char *nptr, char **endptr, int base)
{
    unsigned long x = 0;
    
    while (1)
    {
        if (isdigit(*nptr))
        {
            x = x * base + (*nptr - '0');
            nptr++;
        }
        else if (isalpha(*nptr) && (base > 10))
        {
            x = x * base + (toupper((unsigned char)*nptr) - 'A') + 10;
            nptr++;
        }
        else
        {
            break;
        }
    }
    if (endptr != NULL)
    {
        *endptr = (char *)nptr;
    }
    return (x);
}
*/
