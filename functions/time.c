// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

char * asctime( const struct tm * tptr ) { /* TODO */ };
clock_t clock( void ) { /* TODO */ };
char * ctime( const time_t * tod ) { /* TODO */ };
double difftime( time_t t1, time_t t0 ) { /* TODO */ };
struct tm * gmtime( const time_t * tod ) { /* TODO */ };
struct tm * localtime( const time_t * tod ) { /* TODO */ };
time_t mktime( struct tm * tptr ) { /* TODO */ };
size_t strftime( char * restrict s, size_t n, const char * restrict format,
 const struct tm * restrict tptr ) { /* TODO */ };
time_t time( time_t * tod ) { /* TODO */ };

/* PDPC code - unreviewed, verbatim
/* scalar date routines    --    public domain by Ray Gardner
** These will work over the range 1-01-01 thru 14699-12-31
** The functions written by Ray are isleap, months_to_days, 
** years_to_days, ymd_to_scalar, scalar_to_ymd.
** modified slightly by Paul Edwards
*/

static int isleap(unsigned yr)
{
   return yr % 400 == 0 || (yr % 4 == 0 && yr % 100 != 0);
}

static unsigned months_to_days(unsigned month)
{
   return (month * 3057 - 3007) / 100;
}

static long years_to_days (unsigned yr)
{
   return yr * 365L + yr / 4 - yr / 100 + yr / 400;
}

static long ymd_to_scalar(unsigned yr, unsigned mo, unsigned day)
{
   long scalar;
   
   scalar = day + months_to_days(mo);
   if ( mo > 2 )                         /* adjust if past February */
      scalar -= isleap(yr) ? 1 : 2;
   yr--;
   scalar += years_to_days(yr);
   return (scalar);
}

static void scalar_to_ymd(long scalar, 
                          unsigned *pyr, 
                          unsigned *pmo, 
                          unsigned *pday)
{
   unsigned n;                /* compute inverse of years_to_days() */

   n = (unsigned)((scalar * 400L) / 146097L); 
   while (years_to_days(n) < scalar)
   {
      n++;                         
   }
   for ( n = (unsigned)((scalar * 400L) / 146097L); years_to_days(n) < scalar; )
      n++;                          /* 146097 == years_to_days(400) */
   *pyr = n;
   n = (unsigned)(scalar - years_to_days(n-1));
   if ( n > 59 ) {                       /* adjust if past February */
      n += 2;
      if ( isleap(*pyr) )
         n -= n > 62 ? 1 : 2;
   }
   *pmo = (n * 100 + 3007) / 3057;  /* inverse of months_to_days() */
   *pday = n - months_to_days(*pmo);
   return;
}

time_t time(time_t *timer)
{
    time_t tt;
#ifdef __OS2__    
    DATETIME dt;
    APIRET rc;
#endif    
#if (defined(__MSDOS__) || defined(__MVS__))
    struct {
        int year;
        int month;
        int day;
        int hours;
        int minutes;
        int seconds;
        int hundredths;
    } dt;
#endif
#ifdef __MVS__
    unsigned int clk[2];
#endif    

#ifdef __OS2__
    rc = DosGetDateTime(&dt);
    if (rc != 0)
    {
        tt = (time_t)-1;
    }
    else
#endif    
#ifdef __MSDOS__
    __datetime(&dt);
#endif
#ifdef __MVS__
    tt = __getclk(clk);
#else

    {
        tt = ymd_to_scalar(dt.year, dt.month, dt.day) 
             - ymd_to_scalar(1970, 1, 1);
        tt = tt * 24 + dt.hours;
        tt = tt * 60 + dt.minutes;
        tt = tt * 60 + dt.seconds;
    }
#endif    
    if (timer != NULL)
    {
        *timer = tt;
    }
    return (tt);
}

clock_t clock(void)
{
    return ((clock_t)-1);
}

double difftime(time_t time1, time_t time0)
{
    return ((double)(time1 - time0));
}

time_t mktime(struct tm *timeptr)
{
    time_t tt;
    
    if ((timeptr->tm_year < 70) || (timeptr->tm_year > 120))
    {
        tt = (time_t)-1;
    }
    else
    {
        tt = ymd_to_scalar(timeptr->tm_year + 1900, 
                           timeptr->tm_mon, 
                           timeptr->tm_mday)
             - ymd_to_scalar(1970, 1, 1);
        tt = tt * 24 + timeptr->tm_hour;
        tt = tt * 60 + timeptr->tm_min;
        tt = tt * 60 + timeptr->tm_sec;
    }
    return (tt);
}

char *asctime(const struct tm *timeptr)
{
    static const char wday_name[7][3] = {
          "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };
    static const char mon_name[12][3] = {
          "Jan", "Feb", "Mar", "Apr", "May", "Jun",
          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    static char result[26];

    sprintf(result, "%.3s %.3s%3d %.2d:%.2d:%.2d %d\n",
          wday_name[timeptr->tm_wday],
          mon_name[timeptr->tm_mon],
          timeptr->tm_mday, timeptr->tm_hour,
          timeptr->tm_min, timeptr->tm_sec,
          1900 + timeptr->tm_year);
    return result;
}

char *ctime(const time_t *timer)
{
    return (asctime(localtime(timer)));
}

struct tm *gmtime(const time_t *timer)
{
    return (localtime(timer));
}

/* dow - written by Paul Edwards, 1993-01-31 */
/* Released to the Public Domain */
/* This routine will work over the range 1-01-01 to 32767-12-31.
   It assumes the current calendar system has always been in
   place in that time.  If you pass 0 or negative years, then
   it produces results on the assumption that there is a year
   0.  It should always produce a value in the range of 0..6
   if a valid month and day have been passed, no matter what
   the year is.  However, it has not been tested for negative
   years, because the results are meaningless anyway.  It is
   mainly to stop people playing silly buggers and causing
   the macro to crash on negative years. */
 
/* Modified 1994-08-26 by Paul Edwards to make it return
   0..6 for Sunday..Saturday instead of Monday..Sunday */
/* change the "(d) + 1" to "(d) + 0" to get it back to Monday
   to Sunday if you want */   

#define dow(y,m,d) \
  ((((((m)+9)%12+1)<<4)%27 + (d) + 1 + \
  ((y)%400+400) + ((y)%400+400)/4 - ((y)%400+400)/100 + \
  (((m)<=2) ? ( \
  (((((y)%4)==0) && (((y)%100)!=0)) || (((y)%400)==0)) \
  ? 5 : 6) : 0)) % 7)

static struct tm tms;

struct tm *localtime(const time_t *timer)
{
    unsigned yr, mo, da;
    unsigned long secs;
    unsigned long days;

    days = *timer / (60L*60*24);
    secs = *timer % (60L*60*24);
    scalar_to_ymd(days + ymd_to_scalar(1970, 1, 1), &yr, &mo, &da);
    tms.tm_year = yr - 1900;
    tms.tm_mon = mo - 1;
    tms.tm_mday = da;
    tms.tm_yday = (int)(ymd_to_scalar(tms.tm_year + 1900, 1, 1)
                  - ymd_to_scalar(tms.tm_year + 1900, mo, da));
    tms.tm_wday = dow(tms.tm_year + 1900, mo, da);
    tms.tm_isdst = -1;
    tms.tm_sec = (int)(secs % 60);
    secs /= 60;
    tms.tm_min = (int)(secs % 60);
    secs /= 60;
    tms.tm_hour = (int)secs;
    return (&tms);
}

/*
 * strftime.c
 *
 * implements the iso c function strftime()
 *
 * written 1989-09-06 by jim nutt
 * released into the public domain by jim nutt
 *
 * modified 1989-10-21 by Rob Duff
 *
 * modified 1994-08-26 by Paul Edwards
 */

static char *aday[] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

static char *day[] = {
    "Sunday", "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday"
};

static char *amonth[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

static char *month[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

static char *__tzname[2] = { "" "" };
static char buf[26];

static void strfmt(char *str, const char *fmt, ...);

/**
 *
 * size_t strftime(char *str,
 *                 size_t maxs,
 *                 const char *fmt,
 *                 const struct tm *t)
 *
 *      this functions acts much like a sprintf for time/date output.
 *      given a pointer to an output buffer, a format string and a
 *      time, it copies the time to the output buffer formatted in
 *      accordance with the format string.  the parameters are used
 *      as follows:
 *
 *          str is a pointer to the output buffer, there should
 *          be at least maxs characters available at the address
 *          pointed to by str.
 *
 *          maxs is the maximum number of characters to be copied
 *          into the output buffer, included the '\0' terminator
 *
 *          fmt is the format string.  a percent sign (%) is used
 *          to indicate that the following character is a special
 *          format character.  the following are valid format
 *          characters:
 *
 *              %A      full weekday name (Monday)
 *              %a      abbreviated weekday name (Mon)
 *              %B      full month name (January)
 *              %b      abbreviated month name (Jan)
 *              %c      standard date and time representation
 *              %d      day-of-month (01-31)
 *              %H      hour (24 hour clock) (00-23)
 *              %I      hour (12 hour clock) (01-12)
 *              %j      day-of-year (001-366)
 *              %M      minute (00-59)
 *              %m      month (01-12)
 *              %p      local equivalent of AM or PM
 *              %S      second (00-59)
 *              %U      week-of-year, first day sunday (00-53)
 *              %W      week-of-year, first day monday (00-53)
 *              %w      weekday (0-6, sunday is 0)
 *              %X      standard time representation
 *              %x      standard date representation
 *              %Y      year with century
 *              %y      year without century (00-99)
 *              %Z      timezone name
 *              %%      percent sign
 *
 *      the standard date string is equivalent to:
 *
 *          %a %b %d %Y
 *
 *      the standard time string is equivalent to:
 *
 *          %H:%M:%S
 *
 *      the standard date and time string is equivalent to:
 *
 *          %a %b %d %H:%M:%S %Y
 *
 *      strftime returns the number of characters placed in the
 *      buffer, not including the terminating \0, or zero if more
 *      than maxs characters were produced.
 *
**/

size_t strftime(char *s, size_t maxs, const char *f, const struct tm *t)
{
      int w;
      char *p, *q, *r;

      p = s;
      q = s + maxs - 1;
      while ((*f != '\0'))
      {
            if (*f++ == '%')
            {
                  r = buf;
                  switch (*f++)
                  {
                  case '%' :
                        r = "%";
                        break;

                  case 'a' :
                        r = aday[t->tm_wday];
                        break;

                  case 'A' :
                        r = day[t->tm_wday];
                        break;

                  case 'b' :
                        r = amonth[t->tm_mon];
                        break;

                  case 'B' :
                        r = month[t->tm_mon];
                        break;

                  case 'c' :
                        strfmt(r, "%0 %0 %2 %2:%2:%2 %4",
                              aday[t->tm_wday], amonth[t->tm_mon],
                              t->tm_mday,t->tm_hour, t->tm_min,
                              t->tm_sec, t->tm_year+1900);
                        break;

                  case 'd' :
                        strfmt(r,"%2",t->tm_mday);
                        break;

                  case 'H' :
                        strfmt(r,"%2",t->tm_hour);
                        break;

                  case 'I' :
                        strfmt(r,"%2",(t->tm_hour%12)?t->tm_hour%12:12);
                        break;

                  case 'j' :
                        strfmt(r,"%3",t->tm_yday+1);
                        break;

                  case 'm' :
                        strfmt(r,"%2",t->tm_mon+1);
                        break;

                  case 'M' :
                        strfmt(r,"%2",t->tm_min);
                        break;

                  case 'p' :
                        r = (t->tm_hour>11)?"PM":"AM";
                        break;

                  case 'S' :
                        strfmt(r,"%2",t->tm_sec);
                        break;

                  case 'U' :
                        w = t->tm_yday/7;
                        if (t->tm_yday%7 > t->tm_wday)
                              w++;
                        strfmt(r, "%2", w);
                        break;

                  case 'W' :
                        w = t->tm_yday/7;
                        if (t->tm_yday%7 > (t->tm_wday+6)%7)
                              w++;
                        strfmt(r, "%2", w);
                        break;

                  case 'w' :
                        strfmt(r,"%1",t->tm_wday);
                        break;

                  case 'x' :
                        strfmt(r, "%3s %3s %2 %4", aday[t->tm_wday],
                              amonth[t->tm_mon], t->tm_mday, t->tm_year+1900);
                        break;

                  case 'X' :
                        strfmt(r, "%2:%2:%2", t->tm_hour,
                              t->tm_min, t->tm_sec);
                        break;

                  case 'y' :
                        strfmt(r,"%2",t->tm_year%100);
                        break;

                  case 'Y' :
                        strfmt(r,"%4",t->tm_year+1900);
                        break;

                  case 'Z' :
                        r = (t->tm_isdst) ? __tzname[1] : __tzname[0];
                        break;

                  default:
                        buf[0] = '%';     /* reconstruct the format */
                        buf[1] = f[-1];
                        buf[2] = '\0';
                        if (buf[1] == 0)
                              f--;        /* back up if at end of string */
                  }
                  while (*r)
                  {
                        if (p == q)
                        {
                              *q = '\0';
                              return 0;
                        }
                        *p++ = *r++;
                  }
            }
            else
            {
                  if (p == q)
                  {
                        *q = '\0';
                        return 0;
                  }
                  *p++ = f[-1];
            }
      }
      *p = '\0';
      return (size_t)(p - s);
}

static int pow[5] = { 1, 10, 100, 1000, 10000 };

/**
 * static void strfmt(char *str, char *fmt);
 *
 * simple sprintf for strftime
 *
 * each format descriptor is of the form %n
 * where n goes from zero to four
 *
 * 0    -- string %s
 * 1..4 -- int %?.?d
 *
**/

static void strfmt(char *str, const char *fmt, ...)
{
      int ival, ilen;
      char *sval;
      va_list vp;

      va_start(vp, fmt);
      while (*fmt)
      {
            if (*fmt++ == '%')
            {
                  ilen = *fmt++ - '0';
                  if (ilen == 0)                /* zero means string arg */
                  {
                        sval = va_arg(vp, char*);
                        while (*sval)
                              *str++ = *sval++;
                  }
                  else                          /* always leading zeros */
                  {
                        ival = va_arg(vp, int);
                        while (ilen)
                        {
                              ival %= pow[ilen--];
                              *str++ = (char)('0' + ival / pow[ilen]);
                        }
                  }
            }
            else  *str++ = fmt[-1];
      }
      *str = '\0';
      va_end(vp);
}
*/