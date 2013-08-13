/************************************************************/
/* This Rexx script demonstrates how to determine whether a */
/* program is running or not                                */
/*                                                          */
/* Freeware, Stephane Bessette, 1997                        */
/************************************************************/

/* Name of the program */
Program = 'Desktop'

/* Call IsRunning and discard its messages */
'@call IsRunning.exe' Program '2> NUL'

/* IsRunning returns 1 if the specified program is running */
if rc == 1 then say '"' || Program || '"' || " is running"
else say '"' || Program || '"' || " is not running"

