#define INCL_DOSMEMMGR
#define INCL_DOSERRORS
#define INCL_WINSWITCHLIST

#include <iostream.h>
#include <os2.h>

#include "stristr.h"
#include "Class_WindowList.hpp"

//------------------------------------------------------------------------

Class_WindowList::Class_WindowList( BOOL _bCompareFullString, BOOL _bCaseSensitive )
{
     bCaseSensitive = _bCaseSensitive;
     bCompareFullString = _bCompareFullString;

     // Determine the number of items in the list,
     // calculate the size of the buffer needed,
     // and finally query the items in the switch list

     ULONG cbItems;// Number of items in list
     HAB hab;
     cbItems = WinQuerySwitchList( hab, NULL, 0 );

     ULONG ulBufSize;// Size of the buffer
     ulBufSize = ( cbItems * sizeof( SWENTRY ) ) + sizeof( HSWITCH );

     // Allocate the buffer
     pswblk = new SWBLOCK [ cbItems ];

    // Call WinQuerySwitchList again to fill our buffer with information
     cbItems = WinQuerySwitchList( hab, pswblk, ulBufSize );
}

//------------------------------------------------------------------------

Class_WindowList::~Class_WindowList()
{
     // Deallocate dynamic memory
     delete [] pswblk;
}

//------------------------------------------------------------------------

BOOL Class_WindowList::InList( PSZ pszName )
{
     // Determines if pszName is present in the switch list
     int y;
     for( int x = 0; x < pswblk->cswentry; x++ )
     {
          // Replace hidden characters with a space
          // Necessary when the name of an object is on
          // multiple lines
          for( y = 0; y < strlen( pswblk->aswentry[x].swctl.szSwtitle ); y++ )
               if( pswblk->aswentry[x].swctl.szSwtitle[y] < ' ' )
                    pswblk->aswentry[x].swctl.szSwtitle[y] = ' ';

          if( bCaseSensitive )
          {
               // Case sensitive search
               if( bCompareFullString )
               {
                    // Compare all the characters in the string
                    if( !strcmp( pswblk->aswentry[x].swctl.szSwtitle, pszName ) )
                         return TRUE;
               }
               else
               {
                    // Find the string in the task entry
                    if( strstr( pswblk->aswentry[x].swctl.szSwtitle, pszName ) )
                         return TRUE;
               }
          }
          else
          {
               // Case insensitive search
               if( bCompareFullString )
               {
                    // Compare all the characters in the string
                    if( !stricmp( pswblk->aswentry[x].swctl.szSwtitle, pszName ) )
                         return TRUE;
               }
               else
               {
                    // Find the string in the task entry
                    if( stristr( pswblk->aswentry[x].swctl.szSwtitle, pszName ) )
                         return TRUE;
               }
          }
     }
     return FALSE;
}

//------------------------------------------------------------------------

SWCNTRL Class_WindowList::Get_swcntrl( PSZ pszName )
{
     // Retrieve the switch-list control block structure of pszName
     for( int x = 0; x < pswblk->cswentry; x++ )
     {
          if( !strcmp( pswblk->aswentry[x].swctl.szSwtitle, pszName ) )
               return pswblk->aswentry[x].swctl;
     }
     // The entry is not found; return nothing
     swcntrl.hwnd = NULL;
     swcntrl.hwndIcon = NULL;
     swcntrl.hprog = NULL;
     swcntrl.idProcess = 0;
     swcntrl.idSession = 0;
     swcntrl.uchVisibility = 0;
     swcntrl.fbJump = SWL_NOTJUMPABLE;
     *swcntrl.szSwtitle = '\0';
     swcntrl.bProgType = 0;
     return swcntrl;
}

//------------------------------------------------------------------------

BOOL Class_WindowList::Enumerate( SWCNTRL &swcntrl )
{
     // Enumerate all the switch control entries
     // In order for this to work properly, all the items must be retrieved
     // i.e. the function must return FALSE
     static int nPosition = 0;
     if( nPosition < pswblk->cswentry )
     {
          // Return the current item
          swcntrl = pswblk->aswentry[nPosition].swctl;
          strcpy( swcntrl.szSwtitle, pswblk->aswentry[nPosition].swctl.szSwtitle );
          nPosition++;
          return TRUE;
     }
     else
     {
          // We've enumerated all the items
          nPosition = 0;
          return FALSE;
     }
}

//------------------------------------------------------------------------

int Class_WindowList::Get_Count()
{
     // Return the number of items in the switch list
     return pswblk->cswentry;
}

/*

//------------------------------------------------------------------------

Class_WindowList::
{
     //
}

*/

