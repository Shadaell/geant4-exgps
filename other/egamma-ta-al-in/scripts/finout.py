#!/usr/bin/python
# -*- coding: utf-8 -*-
"""
Some functions to read/write floating point values from/to file.
Copying/modifying conditions:
May be distributed and modified under the terms of the GNU
General Public License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

Bogdan V.Maslovskiy, e-mail: blinkofnight{##doggy##}gmail{##antispam-dot##}com
"""

import os,numpy
from math import sqrt

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
    n_cols = len(map(float,line.split()));
    #create n_cols quantity of arrays:
    count = 0
    while count < n_cols:
        array = numpy.zeros(lines_count)
        arrays_list.append(array)
        count+=1
    #parse file contents and make arrays from them 
    lines_count=0
    for line in stringList:
        numbers = map(float,line.split())
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
# read_data(n,filename)

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
        numbers = map(float,line.split())
        if len(numbers)>0 :
            n_cols = len(numbers);
    file_d.close()
    return n_cols


def read_user_files(args):
    """
    Depends on how much arguments to program has been given:
    case 1 filename given: assume it has > 1 columns 
            case 2 columns: reads X Y, ERR = sqrt(Y)
            case 3 columns: reads X Y ERR
    case 2 filenames given:
         read X from file1
         read Y from file2, ERR = sqrt(Y)
    case 3 filenames given:
         read X from file1, read Y from file2, read ERR from file 3
    \return Three arrays: X,Y,ERR
    """
    x = numpy.zeros(1)
    y = numpy.zeros(1)
    err = numpy.zeros(1)
    N = 0
    N_args=len(args)
    data = [ ]
    if N_args==2: # 1 input filename given
        data = read_data(args[1]) 
        n_cols = how_much_columns(args[1])
        if n_cols == 2:
            x = data[0];  N = len(x);
            y = data[1]
            err = numpy.zeros(N)
            for i in range(N):
                err[i] = sqrt(y[i])
        if n_cols >= 3:
            x = data[0];  N = len(x);
            y = data[1]
            err = data[2]
        if n_cols == 1:
            print("Sorry! Probably the input file lacks Y-data column!.")
            return 0
    del data; # not needed anymore
    
    if N_args==3:  #2 input files given
        data1 = read_data(args[1]) 
        data2 = read_data(args[2])
        x = data1[0];  N = len(x);
        y = data2[0]
        err = numpy.zeros(N)
        for i in range(N):
            err[i] = sqrt(y[i])
        del data1; del data2;
    if N_args==4:  #3 input files given
        data1 = read_data(args[1]) 
        data2 = read_data(args[2])
        data3 = read_data(args[3])
        x = data1[0];  N = len(x);
        y = data2[0]
        err = data3[0]
        del data1; del data2; del data3;
    return x,y,err

def write_arrays(arr_list,filename):
    """
    Dump given lists or numpy arrays to the file
    \param list of (lists or numpy arrays)
    \param filename for output
    """
    count  = len(arr_list)
    if count >0 and len(filename)>0:
        output_file = open(filename, 'w')
        a_size = len(arr_list[0])
        for i in range(a_size):
            string = ''
            for array in arr_list:
                string += str(array[i])+'\t'
            string += '\n'
            output_file.write(string)
        output_file.close()
    return 0

def dump_2col_data(xdata,ydata, filename):
    """
    Dump given lists or numpy arrays to the file
    \param float values list
    \param filename for output
    """
    count  = len(xdata)
    if count >0 and len(filename)>0:
        output_file = open(filename, 'w')
    for i in range(count):
        string = str(xdata[i])+'\t'+str(ydata[i])
        string += '\n'
        output_file.write(string)
# dump_1col_data(data, filename)

def bin_data(data, n_bins):
    """
    make a histogram from data list with given size of bin.
    \param list of values
    \param quantity of histogramm bin
    \return 2 arrays: numpy array of X values, and histogramm itself
    
    """
    if len(data)> 1:
        minval = 0
        maxval = 0
        for value in data:
            if value < minval:
                minval=value
            if value > maxval:
                maxval=value
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
    return [ ]
