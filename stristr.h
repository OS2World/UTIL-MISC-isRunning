/*************************************************************************

                  Case insensitive version of strstr
                  ----------------------------------


                 by Stephane Bessette (stephb7@usa.net)
                             Freeware @1997



BOOL stristr( char *string, char *substring)


                                 Example
                                 -------

char string[] = "This is a string";
char substring[] = "IS a";

if( stristr( string, substring ) )
     // The substring is contained in the string
else
     // The substring is not contained in the string

*************************************************************************/

#ifndef STRISTR_H
#define STRISTR_H

#include <ctype.h>

BOOL stristr( char *string, char *substring )
{
     // A case insensitive version of strstr

     while( *string && tolower( *substring ) != tolower( *string ) )
     {
          string++;
     }
     if( *string )
     {
          // The beginning of the substring was found in the string
          while( *string && *substring && tolower( *substring ) == tolower( *string ) )
          {
               string++;
               substring++;
          }
          if( !*substring )
               // The whole substring was located
               return TRUE;
     }
     return FALSE;
}

#endif // STRISTR_H
