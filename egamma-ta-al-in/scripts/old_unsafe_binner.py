#!/usr/bin/python
# -*- coding: utf-8 -*-
"""
#running the script:
python binner.py input_file.raw 2000 output_file

input_file.raw -- the file with 1 column of floating point values,
may have any file name, but the content should only contain
ASCII characters with numerals, periods "." and newlines.
Only C-local supported e.g.  3.14157
(and not 3,14 and without thousands separators)

2000 -- is the quantity of bins in histogram, e.g. the program chops
        (Emax-Emin) range into 2000 pieces of range and counts
        how much events captured in each range

output_file -- that shall be produced after program run,
          shall contain 2 columns of values:

	  1st-- the center of small binned range;

	  2nd -- count of events[for example, count of events when
	         the particle with (col1)-energy value gets into the
		 detector[DetectorSD class in code].

#calling binner.py script without output_fil will make it print
the results to the stdout.

python binner.py --help # will print small usage notes.


Copying/modifying conditions:
May be distributed and modified under the terms of the GNU
General Public License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

Bogdan V.Maslovskiy, e-mail: blinkofnight{##doggy##}gmail{##antispam-dot##}com
"""
import sys, os, traceback,numpy


def read_data(filename):
    """
    Determine how much columns is in the file and
    read them the to Numpy arrays.
    
    \return list of float values of size N, N is equal to 
    the quantity of file's columns. 
    The array's size is determined by how much new lines is 
    in the input file.
    """
    file_d = open(filename, 'r')
    stringList = file_d.readlines()
    lines_count  = len(stringList)
    if lines_count < 1:
        return [ ]
    arrays_list = []
    line = stringList[0]
    n_cols = len(map(float, line.split()));
    #create n_cols quantity of arrays:
    count = 0
    while count < n_cols:
        array = numpy.zeros(lines_count)
        arrays_list.append(array)
        count+=1
    #parse file contents and make arrays from them 
    lines_count=0
    for line in stringList:
        numbers = map(float, line.split())
        column = 0
        #--parse line into string with float values
        #-- k-th string value goes to k-th array in arrays_list at index
        # which is equal to number of current line
        for value in numbers:
            if column < n_cols:
                (arrays_list[column])[lines_count]=value
                column+=1
        #--
        lines_count+=1
    file_d.close()
    del line
    del stringList
    return arrays_list
# end read_data(n, filename)

def how_much_columns(filename):
    """
    Determine how much columns is in the file and
    return that value
    
    \return integer value, how much data columns in file.
    """
    file_d = open(filename, 'r');
    line = file_d.readline();
    n_cols=0
    if len(line)>0:
        numbers = map(float, line.split())
        if len(numbers)>0 :
            n_cols = len(numbers);
    file_d.close()
    return n_cols

def dump_2col_data(xdata, ydata, filename):
    """
    Dump give list or numpy array to the file
    \param float values list
    \param filename for output
    """
    count  = len(xdata)
    if count > 0 and len(filename) > 0:
        if filename == 'stdout':
            #print it to stdout
            for i in range(len(y)):
                prnt = str(x[i]) + '\t' + str(y[i])
                print(prnt)
            return 0
        output_file = open(filename, 'w')
        for i in range(count):
            string = str(xdata[i]) + '\t' + str(ydata[i])
            string += '\n'
            output_file.write(string)
        output_file.close()
        return 0
    #end if coutn > 0
# dump_1col_data(data, filename)

def bin_data(data, n_bins):
    """
    make a histogram from data list with given size of bin.
    \param list of values
    \param quantity of histogramm bin
    \return 2 arrays: numpy array of X values, and histogramm itself
    
    """
    if len(data) > 1:
        minval = 0
        maxval = 0
        N = len(data)
        print ("Data: ")
        print (data)
        minval = numpy.amin(data)
        maxval = numpy.amax(data)
        if (maxval-minval)!=0 and n_bins!=0:
            X_values = numpy.zeros(n_bins+1)
            h=(maxval-minval)/n_bins
            hist = numpy.zeros(n_bins+1)
            for x in data:
                index = int((x - minval)/h)
                hist[index]+=1
            for i in range(n_bins):
                X_values[i]= (i+0.5)*h
            return X_values,hist
    return [ ],[ ]

def bin_datafile_simple(str_ifname, str_ofname, n_bins):
    """
    Make a histogram from data list with given size of bin.
    It will calculate min and max value, divide range into bins
    and calculate occurance of values in range of 1 bin.
    This function is DUMB, DO NOT to use on big files, it'll kill your RAM!
    
    \param input file name
    \param output file name
    \param quantity of histogram bin
    \return 0 on success
    """
    data = read_data(str_ifname)
    if len(data)>0:
        x,y = bin_data(data[0], n_bins)
        dump_2col_data(x,y, str_ofname) #write to file
    return 0, "success"
# end def

def bin_datafile(str_ifname, str_ofname, n_bins):
    """
    Make a histogram from data list with given size of bin.
    It will calculate min and max value, divide range into bins
    and calculate occurance of values in range of 1 bin.
    This function is OK to use on big files, it'll read them by blocks.
    
    \param input file name
    \param output file name
    \param quantity of histogram bin
    \return 0 on success
    """
    n_cols = 0 # N columns
    file_d = open(str_ifname, 'r')
    line_string = file_d.readline()
    # find out N columns:
    if len(line_string)>0:
        numbers = map(float, line_string.split())
        if len(numbers)>0 :
            n_cols = len(numbers);
    if n_cols <= 0:
        msg = "Error! Cant determine how much columns in the data file, maybe you've comma-separated data? Try using space/tab instead."
        print(msg)
        return -1, msg
    minval = 0
    maxval = 1
    # got through all file and determine min/max values:
    while len(line_string) > 0:
        numbers = map(float, line_string.split())
        for item in numbers:
            minval = min(minval, item)
            maxval = max(maxval, item)
        line_string = file_d.readline()
    print("min: " + str(minval))
    print("max: " + str(maxval))
    # rewind to start of the file:
    file_d.seek(0, os.SEEK_SET)
    line_string = file_d.readline()
    # make a histogramm:
    if (maxval-minval) > 0 and n_bins > 0:
        h = (maxval-minval)/n_bins # step of histo
        values = numpy.zeros(n_bins+1)    # array of bins
        for i in range(n_bins):
            values [i] = (i+0.5)*h
        occurance = numpy.zeros(n_bins+1) # array for event's quantity
        def book(values):
            "book value into hist."
            for one in values:
                index = int((one - minval)/h)
                occurance [index] += 1
        #end def book
        
        #since we already read 1 value into line_string after file_d.seek
        #the we have to book it:
        book(map(float, line_string.split()))
        """
        Read batch of data and process it: we'll operate limited in size batch
        """
        batch_max_size = 1024
        nomore = False
        while nomore == False:
            count = 0
            #read a batch of text lines:
            while len(line_string) > 0 and count < batch_max_size:
                line_string = file_d.readline()
                numbers = map(float, line_string.split())
                book(numbers)
                count += 1
            # end while len
            if len(line_string) < 1:
                nomore = True
                break
        # end while
        dump_2col_data(values, occurance, str_ofname)
    # end if
    file_d.close()
    return 0, "success"
# end def

def main(args):
    usage="This program will take data from input\
 file and make a histogram from it with given binning.\nUsage:\npython "
    usage += args[0]
    usage += " input_filename n_bins output_filename\n\
\nWhere (n_bins) must be an unsinged integer.\n The last argument\
 is optional. \n\nWarning! The input file has to contain sequence of floating point numbers,\
 separated by anything like space, tabulation or new line.\n\n\
example: python binner.py 1000 input.txt output.txt\n"

    if (len(args)>1):
        if '-help' in args[1]:
            print(usage)
            return 0
    #input
    in_filename = args[1]
    out_filename = 'stdout'
    n_bins = 2000
    if (len(args) > 2):
        n_bins = int(args[2])
    else:
        print("Sorry, failed to parse number of bins, please try gain.\n")
        print("Usage:")
        print(usage)
        return 0
    if (len(args) > 3):
        out_filename = args[3]
    #
    #make histograms from sequence of values 0.1 0.2 .. 0.87
    status, msg = bin_datafile_simple( in_filename, out_filename, n_bins)
    #status, msg = bin_datafile( in_filename, out_filename, n_bins)
    print(msg)
    #done
    return 0
# main()

if __name__ =='__main__':
    try:
        main(sys.argv)
    except: #catch all exceptions here
        e = sys.exc_info()[1]
        exc_type, exc_value, exc_traceback = sys.exc_info()
        print( "ERROR! An exception occured:")
        print( e)
        print( "-------------")
        print( "*** traceback:")
        print (repr(traceback.extract_tb(exc_traceback)))

