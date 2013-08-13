#define INCL_DOSMEMMGR
#define INCL_DOSERRORS
#define INCL_WINSWITCHLIST

#include <iostream.h>
#include <stdlib.h>
#include <os2.h>

#include "Class_WindowList.hpp"

//------------------------------------------------------------------------

main( int argc, char *argv[] )
{
     // Create an instance of the window list class
     Class_WindowList wl;

     if( argc == 1 || strstr( "/?-?/help-help", argv[1] )  )
     {
          // The user requested help
          cout << "IsRunning v1.0\n";
          cout << "by Stephane Bessette (stephb7@usa.net), 1997\n\n";
          cout << "Syntax:\n";
          cout << "\tIsRunning <name>\n";
          cout << "\tIsRunning -e\n";
          cout << "Where\n";
          cout << "\t<name>\tcorresponds to the name of the program\n";
          cout << "\t-e \tinstructs to enumerate the running tasks\n";
          cout << "\nReturns:\n";
          cout << "\t0. The program is not running\n";
          cout << "\t1. The program is running\n";
          cout << "\t2.  Displayed help or enumerated the running tasks\n";
          cout << "\n\tMessages through standard error\n";
          cout << "\t    to discard output:  IsRunning <name> 2> NUL\n";
          cout << "\nExample:\n";
          cout << "\tIsRunning Desktop\n\n";
     }
     else if( argc == 2 && !strcmp( argv[1], "-e" ) )
     {
          // Enumerate the running tasks
          SWCNTRL sw;
          while( wl.Enumerate( sw ) )
               cout << '"' << sw.szSwtitle << '"' << "\n";
     }
     else
     {
          // The user specified a name
          // If the name contains spaces, then it will span
          // more than one parameter

          // Determine the total length of the parameters
          int nLength = 0;
          for( int x = 1; x < argc; x++ )
               nLength += strlen( argv[x] ) + 1;

          // Then concatenate the parameters
          char *szProgram = new char [ nLength + 1 ];
          if( !szProgram )
               // Memory allocation error
               return 0;

          strcpy( szProgram, "" );
          for( x = 1; x < argc - 1; x++ )
          {
               strcat( szProgram, argv[x] );
               strcat( szProgram, " " );
          }
          strcat( szProgram, argv[argc - 1] );

          // Determine whether the program is running or not
          if( wl.InList( szProgram ) )
          {
               cerr << '"' << szProgram << '"' << " is running\n";
               delete [] szProgram;
               return 1;
          }
          else
          {
               // The parameter is not present in the switch entry
               cerr << '"' << szProgram << '"' << " is not running\n";
               delete [] szProgram;
               return 0;
          }
     }
     return 2;
}

