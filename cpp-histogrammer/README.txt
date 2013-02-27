Program name: histogrammer
Synopsis:
    histogrammer INPFILE OUTFILE 2000

INPFILE -- the file with 1 or more columns of floating point values,
may have any file name, but the content should only contain
ASCII characters with numerals, periods "." and newlines.
Only C-local supported e.g.  3.14157
(and not 3,14 and without thousands separators)

OUTFILE -- (optional) name of the filethat shall be produced after program run,
          shall contain 2 columns of values:
	  1st-- the center of each bin;
	  2nd -- count of events for example, count of events when
	         the particle with (col1)-energy value gets into the
		 detector.

2000 -- is the quantity of bins in histogram, e.g. the program chops
        (max - min) range into 2000 pieces of range and counts
        how much events captured in each range.
        Anything > 0 goes.

Compilation:
	One may need CMake and make to compile the program:
	#change directory to program's sources: .. 
	mkdir build
	cd build
	cmake ..
	make
    You will find an executable named "histogrammer" in directory "build", that's it.


Copying/modifying conditions:
May be distributed and modified under the terms of the GNU
General Public License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.
See http://gnu.org

Author:
Bogdan V.Maslovskiy, e-mail: blinkofnight{##doggy##}gmail{##antispam-dot##}com
April, 25-th, 2012

