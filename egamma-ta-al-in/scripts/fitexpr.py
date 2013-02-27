""" 
	Copyright (C) 2009 Sergey Koposov

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
"""
from mpfit import *
import re
import numpy
import scipy
from finout import *
from scipy.optimize import leastsq 
from scipy import special 
import matplotlib.pyplot as PLT #plotting module
from math import *

#---

def call_mpfit(FUNCTION, INIT_PARAM, x, y, error, with_plot = False):
    """
    This method makes fit of function(par,x) to experimental data
    contained in X,Y arrays.
    
    (1)the FUNCTION must be defined as follows:
    
    def func(param,x):
      value = some_formula(param[0],param[1]..., x)
      return value

    (2)INIT_PARAM -- is a list of initial values of parameters
    
    (3) X exp. data
    (4) Y experimental data

    Return: [list of fited parameters], [list of parameters errors],
    Chi2-value
    """
    def mpfitfunc(x,y,err):
        if err == None:
            def f(p,fjac=None): 
                return [0,(y-FUNCTION(p,x))]
        else:
            def f(p,fjac=None): 
                return [0,(y-FUNCTION(p,x))/err]
        return f    
    mpfitparaminfo = generate_mpfit_info(INIT_PARAM)
    mp2 = mpfit(mpfitfunc(x,y,error),
                parinfo=mpfitparaminfo,quiet=0)
    fit_params   = mp2.params
    fit_par_error= mp2.perror
    chi2   = mp2.fnorm
    if len(fit_params)>0:
        print()
        print("MPFIT ALGORITHM RESULT:")
        N_params = len(INIT_PARAM)
        p_cnt=-1
        output_string = ' '
        #for a report about obtained param value into a string:
        for p in fit_params:
            p_cnt+=1
            string = str()
            if fit_par_error!=None:
                string = "PARAM "+str(p_cnt)+":\t"+str(p)+"+/-("+str(fit_par_error[p_cnt])+")\n"
                print(string)
            else:
                string = "PARAM "+str(p_cnt)+":\t"+str(p)+"\n"
                print(string)
            output_string+=string
        #end for
        output_string += 'Chi2: '+str(chi2)
        #write that string to the file:
        param_file = open("params.mpfit.txt", 'w')
        param_file.write(output_string)
        param_file.close()

        #write fited function values at X into output file.
        FUNC_VAL = numpy.zeros(len(x))
        FUNC_VAL = FUNCTION(fit_params, x)
        write_arrays( [x, FUNC_VAL], "output.mpfit.txt")
        print ("Chi2: "+str( chi2))
        if with_plot:
            PLT.plot(x,y,'+', x,FUNC_VAL,'-');
            PLT.legend(['data','formula approx.'],loc='best')
            PLT.show()
        # end if with_plot
    
    if fit_par_error!=None:
        return fit_params,chi2
    else:
        return fit_params, fit_par_error,chi2
    return fit_params


def call_scipy_fit(FUNCTION, INIT_PARAM, X, Y, with_plot = False):
    """
    This method makes fit of function(par,x) to experimental data
    contained in X,Y arrays.
    
    (1)the FUNCTION must be defined as follows:
    
    def func(param,x):
      value = some_formula(param[0],param[1]..., x)
      return value

    (2)INIT_PARAM -- is a list of initial values of parameters
    
    (3) X exp. data
    (4) Y experimental data
    
    Return: [list of fited parameters], [list of parameters errors]
    """
    
    def residuals(INIT_PARAM,x,y):
        err = numpy.zeros(len(y))
        func = FUNCTION(INIT_PARAM,x)
        for i in range(len(y)):
            err[i] = (y[i]-func[i])**2
        return err
    
    #make fit:
    fit_params = [ ]
    fit_par_error = None
    chi2 = -1
    
    out_p = leastsq(residuals, INIT_PARAM, args=(X,Y), Dfun=None, full_output=0,\
                             col_deriv=0, ftol=1.49012e-10, xtol=1.49012e-10,\
                             gtol=0.0, maxfev=100000, epsfcn=0.0, factor=100, diag=None)
    fit_params = out_p[0]
    if len(fit_params)>0:
        print()
        print("SCIPY LEASTSQR RESULT:")
        N_params = len(INIT_PARAM)
        p_cnt=-1
        output_string = ' '
        for p in fit_params:
            p_cnt+=1
            string = str()
            if fit_par_error!=None:
                string = "PARAM "+str(p_cnt)+":\t"+str(p)+"+/-("+str(fit_par_error[p_cnt])+")\n"
                print(string)
            else:
                string = "PARAM "+str(p_cnt)+":\t"+str(p)+"\n"
                print(string)
            output_string+=string
        output_string += 'Chi2: '+str(chi2)
        param_file = open("params.scipy.txt", 'w')
        param_file.write(output_string)
        param_file.close()
        #end for
        #write fited function values at X into output file.
        FUNC_VAL = numpy.zeros(len(X))
        FUNC_VAL = FUNCTION(fit_params, X)
        write_arrays( [X, FUNC_VAL] ,"output.scipy.txt")
        print ("Chi2: "+str( chi2))
        if with_plot :
            PLT.plot(x,y,'+', x,FUNC_VAL,'-');
            PLT.legend(['data','formula approx.'],loc='best')
            PLT.show()
        #end if with_plot

    if fit_par_error!=None:
        return fit_params
    else:
        return fit_params, fit_par_error
    return fit_params



#---
def generate_mpfit_info(ParamValues, minvalue = None, maxvalue = None, parnames = None ):
    """
    Generates a dictionary with keywords of
    parameters information for the MPFIT class routines,
    it inserts parameters values into this structures.
    the generated list is returned
    """
    mpfitParamInfo = [ ]
    
    for i in range(len(ParamValues)):
        if (minvalue == None) or (maxvalue ==None):#min/max values are not assigned
            if parnames == None:
                mpfitParamInfo.append({'n':i, 'value':ParamValues[i],
                                       'limits':[0, 1e06],
                                       'limited':[True,True],
                                       'fixed':False,
                                       'parname':"P-"+str(i),
                                       'error':0})
            else:  #parnames non nones
                mpfitParamInfo.append({'n':i, 'value':ParamValues[i],
                                       'limits':[0, 1e06],
                                       'limited':[True,True],
                                       'fixed':False,
                                       'parname':parnames[i],
                                       'error':0})
        else: #if minvalue and maxvalue are affigned
            if parnames == None:
                mpfitParamInfo.append({'n':i, 'value':ParamValues[i],
                                       'limits':[minvalue, maxvalue],
                                       'limited':[True,True],
                                       'fixed':False,
                                       'parname':"P-"+str(i),
                                       'error':0})
            else: #parnames non nones
                mpfitParamInfo.append({'n':i, 'value':ParamValues[i],
                                       'limits':[minvalue, maxvalue],
                                       'limited':[True,True],
                                       'fixed':False,
                                       'parname':parnames[i],
                                       'error':0})
                
    return mpfitParamInfo


def mpfitexpr(func, x, y, err , start_params, check=True, full_output=False, **kw):
	"""Fit the used defined expression to the data
	Input:
	- func: string with the function definition 
	- x: x vector
	- y: y vector
	- err: vector with the errors of y
	- start_params: the starting parameters for the fit
	Output:
	- The tuple (params, yfit) with best-fit params and the values of func evaluated at x
	Keywords:
	- check: boolean parameter. If true(default) the function will be checked for sanity
	- full_output: boolean parameter. If True(default is False) then instead of best-fit parameters the mpfit object is returned
	Example:
	params,yfit=mpfitexpr('p[0]+p[2]*(x-p[1])',x,y,err,[0,10,1])
	
	If you need to use numpy and scipy functions in your function, then
		you must to use the full names of these functions, e.g.:
		numpy.sin, numpy.cos etc.
	
	This function is motivated by mpfitexpr() from wonderful MPFIT IDL package
		written by Craig Markwardt	
	
	"""

	def myfunc(p,fjac=None,x=None, y=None, err=None):
		return [0, eval('(y-(%s))/err'%func)]

	myre = "[^a-zA-Z]p\[(\d+)\]"
	r = re.compile(myre)
	maxp = -1
	for m in re.finditer(r,func):
		curp = int(m.group(1))
		maxp = curp if curp > maxp else maxp	
	if check:
		if maxp == -1: 
			raise Exception("wrong function format")
		if maxp + 1 != len(start_params):
			raise Exception("the length of the start_params != the length of the parameter verctor of the function")
	fa={'x' : x, 'y' : y,'err' : err}
	res = mpfit.mpfit(myfunc,start_params,functkw=fa,**kw)
	yfit = eval(func, globals(), {'x':x, 'p': res.params})
	if full_output:
		return (res, yfit)
	else:
		return (res.params, yfit)

