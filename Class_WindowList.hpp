/*************************************************************************

                     Queries the switch list entries
                     -------------------------------


                 by Stephane Bessette (stephb7@usa.net)
                             Freeware @1997



Class_WindowList


                                 Example
                                 -------

-Create an instance where the search is complete and case sensitive
     Class_WindowList wl;
     or
     Class_WindowList wl( TRUE );
     or
     Class_WindowList wl( TRUE, TRUE );

-Create an instance where the search is complete and case insensitive
     Class_WindowList wl( TRUE, FALSE );

-Create an instance where the search is partial and case sensitive
     Class_WindowList wl( FALSE );
     or
     Class_WindowList wl( FALSE, TRUE );

-Create an instance where the search is partial and case insensitive
     Class_WindowList wl( FALSE, FALSE );

-Obtain the number of entries in the switch list
     int nCount = wl.Get_Count();

-Determine if a program is in the list
     PSZ pszName = "Desktop";
     if( wl.InList( pszName ) )
          // The program is running
     else
          // The program is not running, or does not have the same name

-Query information about a program
     PSZ pszName = "Desktop";
     SWCNTRL swcntrl;
     swcntrl = Get_swcntrl( pszName );
     if( swcntrl.hwnd )
          // We have a valid switch list structure

-Enumerate all the switch list entries
     SWCNTRL swcntrl;
     while( Enumerate( swcntrl  )
     {
          // Process the information
          // But do not exit the loop:  it MUST iterate to termination
     }

-Tip
     If IsRunning reports that a program is not running and you know
     otherwise enumerate the list of running programs with:  IsRunning -e
     and check whether the program you're looking for is listed

*************************************************************************/

#ifndef CLASS_WINDOWLIST_HPP
#define CLASS_WINDOWLIST_HPP

class Class_WindowList {
public:
     Class_WindowList( BOOL _bCompareFullString = TRUE, BOOL _bCaseSensitive = TRUE );
     ~Class_WindowList();
     //-------------------------------------------------------------------
     int Get_Count();
     BOOL InList( PSZ pszName );
     SWCNTRL Get_swcntrl( PSZ pszName );
     BOOL Enumerate( SWCNTRL &swcntrl );
//************************************************************************
private:
     PSWBLOCK pswblk;// Pointer to information returned
     SWCNTRL swcntrl;// Temporary switch control structure
     BOOL bCaseSensitive;// Should the name comparison be case sensitive?
     BOOL bCompareFullString;// Compare all the characters in the string?
};

#endif // CLASS_WINDOWLIST_HPP
