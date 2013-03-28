#!/usr/bin/python
# -*- coding: utf-8 -*-
help = """
Program name: binner.py
Synopsis:
    python binner.py INPFILE 2000 OUTFILE 102400
    #where numerical values can be any values > 0

# example of running the script:
python binner.py input_file 2000 #prints to stdout
python binner.py input_file 2000 output_file
python binner.py input_file 2000 output_file 102400

input_file -- the file with 1 or more columns of floating point values,
may have any file name, but the content should only contain
ASCII characters with numerals, periods "." and newlines.
Only C-local supported e.g.  3.14157
(and not 3,14 and without thousands separators)

2000 -- is the quantity of bins in histogram, e.g. the program chops
        (max - min) range into 2000 pieces of range and counts
        how much events captured in each range.
        Anything > 0 goes.

output_file -- (optional) name of the filethat shall be produced after program run,
          shall contain 2 columns of values:
	  1st-- the center of each bin;
	  2nd -- count of events for example, count of events when
	         the particle with (col1)-energy value gets into the
		 detector.

102400 -- (optional) is a max number of lines to read from file at one loop. Default is 102400. The functions will read batch of data and process it.
For example if batch_max_size == 1024*1024, 
then we operate on ~8-10 Mbytes in RAM if each line in file has only 1 value, N*8Mbytes if there are multiple values in one line.

#calling binner.py script without output_file will make it print
the results to the stdout.

python binner.py --help # will print these usage notes.

# One more running option is available:
python binner.py input_file 2000 output_file 102400


Copying/modifying conditions:
May be distributed and modified under the terms of the GNU
General Public License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

Bogdan V.Maslovskiy, e-mail: blinkofnight{##doggy##}gmail{##antispam-dot##}com
"""

import sys, os, traceback,numpy

def write_data(xdata, ydata, filename):
    """
    Dump two given lists or numpy arrays into the file.
    \param float values list
    \param filename for output
    """
    count  = len(xdata)
    if count > 0 and len(filename) > 0:
        if filename == 'stdout':
            #print it to stdout
            for i in range(len(ydata)):
                prnt = str(xdata[i]) + '\t' + str(ydata[i])
                print(prnt)
            return 0
        output_file = open(filename, 'w')
        for i in range(count):
            string = str(xdata[i]) + '\t' + str(ydata[i])
            string += '\n'
            output_file.write(string)
        output_file.close()
        return 0
    #end if count > 0
    
    return -1
# write_data(x, y, filename)

def read_lines_batch(fd, n_lines):
    """                                                            
    Read N lines from file.                                        
    \param file_d: file descriptor, should be already open.        
    \param N lines: how much lines to read                         
                                                                   
    \return [ [str1, str2, ...strN], False] in usual situation     
    or [[str1..], True] when EOF reached.                          
    """                                                            
    strlist = []                                                   
    if n_lines <= 0 or fd.closed == True:                          
        return linelist, True                                      
    cnt = 0                                                        
    goon = True                                                    
    while cnt < n_lines:                                           
        line = fd.readline()                                       
        if len(line) < 1:                                          
            return strlist, True                                   
            break                                                  
        strlist.append(line)                                       
        cnt += 1                                                   
    return strlist, False    
#end def read_lines_batch

def get_min_max(filename, batch_max_size = 102400):
    """
Go through all values in the file and calculate min/max value.
Function do not cares how much columns there, it'll push
them all into one array.
    \param filename -- name of hte input file
    \param maximum number of read lines at one time
    \return minval,maxval, True/False -- 2 float values and one boolean.
    If 3rd return value is False, then min/max values had not been calculated.
    """
    file_d = open(filename, 'r')
    minval = -1
    maxval = -0.1
    # got through all file and determine min/max values:
    batch_max_size = 1024
    """
    Calculate minval and maxval.
    First we have to assign min and max values to the ones from data:
    """
    first_run = True
    line_list, got_EOF = read_lines_batch(file_d, batch_max_size)
    while (len(line_list) > 0):
        for line_string in line_list:
            splitted = line_string.split()
            numbers = map(float, splitted)
            if len(numbers) < 1:
                break
            if first_run == True:
                minval = numbers[0]
                maxval = numbers[0]
                first_run = False
            for value in numbers:
                minval = min(minval, value)
                maxval = max(maxval, value)
        if got_EOF == True:
            break
        line_list, got_EOF = read_lines_batch(file_d, batch_max_size)
        #end for line
    #end while
    file_d.close()
    return minval, maxval, True
# end def get_min_max

def make_histogramm_file(minval, maxval, n_bins, str_ifname, batch_max_size = 102400):
    """
    Make a histogram from data file with given size of bin.
    It will calculate min and max value, divide range into bins
    and calculate occurance of values in range of 1 bin.
    This function is OK to use on big files, it'll read them by blocks.
    
    \param precalculated min. value of data
    \param precalculated max. value of data
    \param quantity of histogram bins
    \param input file with data

    \param batch_max_size(optional) -- limit of max read lines at once,
        the function will read batch of data and process it.
        For example if batch_max_size == 1024*1024, 
        then we operate on ~8-10 Mbytes in RAM if each line in file has only 1 value, N*8Mbytes if there are multiple values in one line.
    
    \return values_arr, occurance_arr, True -- 
    returns 2 numpy arrays and True if everything is fine or
    2 empty lists and False: [], [], False if something is wrong.
    """
    if (maxval > minval) and (n_bins > 0):
        file_d = open(str_ifname, 'r')
        
        h = (maxval - minval) / n_bins # step of histo
        values = numpy.zeros(n_bins+1)    # array of bins
        occurance = numpy.zeros(n_bins + 1) # array for event's quantity
        
        for i in range(n_bins):
            values [i] = (i+0.5)*h
        
        def book(values):
            "book value into hist."
            for one in values:
                index = int((one - minval)/h)
                occurance [index] += 1
        #end def book
        
        #the we have to book it:
        line_list, got_EOF = read_lines_batch(file_d, batch_max_size)
        while (len(line_list) > 0):
            for line_string in line_list:
                splitted = line_string.split()
                numbers = map(float, splitted)
                if len(numbers) < 1:
                    break
                book(numbers)
            if got_EOF == True:
                break
            line_list, got_EOF = read_lines_batch(file_d, batch_max_size)
        #end while
        
        file_d.close()
        return values, occurance, True
    else:
        # if get to here, then something is wrong:
        return [],[], False
    # end if/else
# end def

def bin_datafile(str_ifname, str_ofname, n_bins,  batch_max_size = 102400):
    """
    Make a histogram from data list with given size of bin.
    It will calculate min and max value, divide range into bins
    and calculate occurance of values in range of 1 bin.
    This function is OK to use on big files, it'll read them by blocks.
    
    \param input file name
    \param output file name
    \param quantity of histogram bin

    \param batch_max_size(optional) -- limit of max read lines at once,
        the function will read batch of data and process it.
        For example if batch_max_size == 1024*1024, 
        then we operate on ~8-10 Mbytes in RAM if each line in file has only 1 value, N*8Mbytes if there are multiple values in one line.
    
    \return 0 on success
    """
    # rewind to start of the file:
    minval, maxval, mnmx_ok = get_min_max(str_ifname, batch_max_size)
    if mnmx_ok == False:
        return -1, \
"""
def bin_datafile(str_ifname, str_ofname, n_bins) says:
    Failed to calculate min and max values from file.
    Maybe you've got something else there, except numerical data?
"""
    if (maxval-minval) > 0 and n_bins > 0:
        values, occurance, success = make_histogramm_file(minval, maxval, n_bins, str_ifname, batch_max_size)
        write_data(values, occurance, str_ofname)
        if success == True:
            return 0, "success"
        else:
            return -1, "wrong min/max values or maybe file?"
    return -1, "Wrong min, max or n_bins values!"
# end def

def main(args):
    if (len(args)>1):
        if '-help' in args[1]:
            print(help)
            return 0
    #input
    in_filename = args[1]
    out_filename = 'stdout'
    n_bins = 2000
    if (len(args) > 2):
        n_bins = int(args[2])
    if (len(args) > 3):
        out_filename = args[3]
    #
    #make histograms from sequence of values 0.1 0.2 .. 0.87
    batch_max_size = 1024*300
    if(len(args) > 4):
        batch_max_size = argv[4]
    status, msg = bin_datafile( in_filename, out_filename, n_bins, batch_max_size)
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

