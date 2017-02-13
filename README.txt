Instructions for using command line text editor:

1. Opening a file
Upon running the program, one can:
a) supply a text file name which exists, which is read into buffer
b) supply a non existent file name, which creates an empty buffer with entered filename
c) not supply a file name, which creates an empty buffer named “?”

Any changes made to the buffer will only be written to the file using the command ‘w’

2. Command and input mode
The colon character ‘:’ will appear to indicate the user is in command mode.  This mode will accept commands and line ranges.

The two input modes are append and input.  To append after line y enter ‘y a’, and to insert before line y enter ‘y i’.  Enter as many lines as needed.  To end input mode, enter ‘.’ alone at the beginning of a line.

3. Enter Line Range

Line range symbols:
.	current line address in buffer
$	last line in buffer
n	a sequence of digits 1 <= n <= $
,	separates a pair (if any) of line address symbols

Line range interpretation where ‘z’ is the command entered:
,.z  .z  z  ,z  .,z  are all interpreted as .,. z
y z is interpreted as y,y z
,yz is interpreted as .,y z
x,z is interpreted as x,. z

4. Commands where ‘y’ is line or ‘x,y’ is line range
y a	appends after line y
y i	inserts before line y
x,y r  removes lines x through y
x.y    prints lines x through y
x, y n prints lines x though y preceded by the line number
x.y c  prompts for and reads text to be changed, then prompts for and reads replacement text. Searches each addressed line for occurrence of specified string and changes all matched strings to replacement text.
y u     moves current line address up by y lines (but never beyond first line)
y d  moves current line address down by y lines (never beyond last line)
x, y  same as x, y p
w     writes buffer to file
n      same as n,n p
.       same as .,. p
$      same as $,$ p
,       same as 1,$ p
=      prints current line address
return: same as 1d

5. Notes
All letter commands are lowercase
Any tab and space characters entered into command line are ignored
If a line range is specified where none is expected, the range is ignored
If a line range x,y is specified where only a single line range address is expected, x is ignored and y is used 
