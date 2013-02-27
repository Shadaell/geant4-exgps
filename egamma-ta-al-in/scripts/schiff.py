#!/usr/bin/python
# -*- coding: utf-8 -*-
"""
Copying/modifying conditions:
May be distributed and modified under the terms of the GNU
General Public License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

Bogdan V.Maslovskiy, e-mail: blinkofnight{##doggy##}gmail{##antispam-dot##}com
"""
import sys,traceback
from numpy import *
from math import *
from mpmath import *
from finout import *
from fitexpr import *
from scipy import integrate
from scipy.optimize import curve_fit
from scipy.optimize import newton
import matplotlib.pyplot as PLT

#diameter of exposed to e- radiation target's round:
D_tget = 0.9;                    # cm

#thickness of target:
L_tget = 0.105;                  # cm

#square of exposed target surface
S_tget = pi * (D_tget / 2.0)**2      # cm^2

#volume:
V = mpf(S_tget*L_tget);          # cm^3
N_Avogadro = mpf(6.022e23)       # mole^(-1)


rho  = 16.654 #g/cm^3
M_Tn = 180.9  #g/mole

#quantity of Tn-nucleus
Q_Tn= mpf(V*rho/M_Tn*N_Avogadro);

#Z of Tantan
Z_Tn= 73;

#Z of Thalium
Z_Tl= 81;

#quantity of e- radiated into target
Q_e = mpf(30e06)

# N=j*M*sigma, N - number of reaction, j[1/cm^2],
# M -- quantity of target nucleus, sigma [cm^(-2)] -- cross section
print("Q_Tn: "+str(Q_Tn))
coeff = S_tget*Q_Tn/Q_e
print("coeff: "+str(coeff))

Z = 81
r = mpf(2.81794e-15)
#Initial e- energy, keV:
Ee = 44
mu = 0.511
E0 = mpf(Ee + mu)
deltaEg = 0.008
C = 111
init_parameters = [1.55e26*4.4*2.8*(1.0/deltaEg)]

def M0(Eg):
    #if abs(Eg - E0) < 1e-16:
    #    return -15
    frag = mpf((mu*Eg/(2.0*E0*(E0-Eg)))**2 + (Z**(1.0/3.0)/C)**2)
    #if abs(frag) < 1e-16:
    #    return -15
    return 1.0/frag

def schiff_func(parameters, Eg):
    if Eg > Ee :
        return 0
    if len(parameters) < 1 :
        return -100
    
    coefflist = [1/(2*pi)*4, Z**2/137.0, r**2, parameters[0],
                 (mpf(E0/mu))**2, deltaEg/Eg]
    A = mpf(1)
    #
    for item in coefflist:
        A = A * mpf(item)
    #
    m0eg = mpf(M0(Eg))
    if m0eg < -10:
        return -10
    a1 = (E0**2 + (E0 - Eg)**2)/E0**2 * ln(m0eg)
    a2 = (E0 + (E0 - Eg))**2/E0**2
    value =  A*mpf(a1 - a2)
    return value

def Schiff_arrays(parameters,x):
    """
    Schiff-function
    \param initial energy of e-
    \param delta_Egamma, numpy array
    """
    result = numpy.zeros(len(x))
    for i in range(len(x)):
        result[i] = schiff_func(parameters, x[i])
    return result

def find_zero(function, init_parameters, near_zero):
    """
    \param function -- def function(param_list, X) ...
    \param list of initial parameters
    \param initial value for zero search.
    """
    print("Looking for the function root:")
    def func0(arg):
        return schiff_func(init_parameters, arg)
    x_zero = newton(func0, 44.0)
    print("The function(par, x) root is at x0 = " + str(x_zero))
    return x_zero

def make_schiff_calc(string_filename):
    """
    \param filename of input file with 2 columns of numerical data: 1 column is energy in keV, second is number of spectra counts. 
    \return integer and sting, [0, "success"] if everything is good,
    [-1,"error msg"] if not.
    """
    X = numpy.zeros(10);
    data = read_data(string_filename)
    # << get a list of numpy arrays from file:
    # data = [numpy_arr1, numpy_arr2]
    
    if len(data) < 2:
        return -1, "FAIL: make_schiff_calc(filename): 1 or less data columns has been read, we need 2."
    X = data[0]
    Y = data[1]
    if len(X) < 2:
        del X, Y, data
        return -1, "FAIL: make_schiff_calc(filename): The read arrays has length less than 2 numbers."
    FVAL = numpy.zeros(len(X))
    X_MEV = (X)/1000.0
    for i in range(len(FVAL)):
        FVAL[i] = schiff_func(init_parameters, X_MEV[i])
    #dump function values to the file:
    write_arrays([X, Y, FVAL], "func_values_output.txt")
    string = "Value at 44MeV: " + str( schiff_func(init_parameters, 44.0))
    print(string)
    string = "Value at E0MeV: " + str( schiff_func(init_parameters, E0))
    print(string)
    find_zero(schiff_func, init_parameters, 44.0)
    #
    # lets look at what is in the end of the spectra separately:
    PLT.plot(X, Y, '+', X, FVAL, '-');
    PLT.legend(['simulation','Schiff function, no fit.'],loc='best')
    PLT.show()
    # #make a fit with 1 parameter:
    #error = numpy.sqrt(Y)
    #fitted_param, fitted_par_error, chi2 = call_mpfit(Schiff_arrays, init_parameters, X_MEV, Y, error, True)
    # # look where is zero now:
    #find_zero(schiff_func, fitted_param, 44.0)
    return 0, "make_schiff_calc(filename): success."

def main(args):
    usage = """USAGE: python script.py input.txt 
This program will take data from input file with 2 columns of numbers and plots a Schiff's function on it."""
    if '-help' in args:
        print(usage)
        return 0
    #input
    if len(args)>1:
        int_code, mesg = make_schiff_calc(args[1])
        print(str(int_code) + mesg)
    # end if len(args)>1:
    # done
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
        print( "*** functions call traceback:")
        for string in (traceback.extract_tb(exc_traceback)):
            print(string )
    

