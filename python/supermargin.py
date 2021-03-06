#--------------------------------------------------------------------------
#THIS SCRIPT CREATES A SUPERMARGIN ENVISION OBJECT FROM VARIABLES FOUND
#IN EITHER acdata.evo OR dcdata.evo, BUT THE USER MUST PLACE ALL 
#VARIABLES IN A TEXT FILE FOR INPUT
#
#
#Instructions for acdata.evo:
#1) open acdata.evo
#2) select all variables from ParamGlobals and copy into text file
#3) remove all variables that don't have { Type = s; }
#       nedit regex example:
#           SEARCH:\n.*(BOOLEAN|SCALAR|STRING|INTEGER|Type\s*=\s*Ohm).*
#          REPLACE:
#4) make sure all variables remaining have { Type = s; } and then remove leaving ONLY THE VARIABLE NAME
#       nedit regex example:
#           SEARCH:\{.*\}
#          REPLACE:
#5) save text file for input to script
#6) set variables (BELOW) in this script to appropriate values
#   example:
#       TIMING    = 1
#       _tperiod_ = "tperiod"
#7) execute script: python supermargin.py params.txt
#
#
#Instructions for dcdata.evo:
#1) open dcdata.evo
#2) select all variables from ParamGlobals and copy into text file
#3) remove all variables that don't have { Type = V; }
#       nedit regex example:
#           SEARCH:\n.*(BOOLEAN|SCALAR|STRING|INTEGER|Type\s*=\s*A|Type\s*=\s*s|Type\s*=\s*Ohm).*
#          REPLACE:
#4) make sure all variables remaining have { Type = V; } and then remove leaving ONLY THE VARIABLE NAME
#       nedit regex example:
#           SEARCH:\{.*\}
#          REPLACE:
#5) save text file for input to script
#6) set variables (BELOW) in this script to appropriate values
#   example:
#       TIMING   = 0
#       _vddmax_ = "VDDMAX"
#7) execute script: python supermargin.py params.txt
#--------------------------------------------------------------------------

import sys
import re
import pprint
import os
#import string
from string import *
import time

__PROGRAM_NAME__ = "Supermargin Creator"
__AUTHOR__ = "AUTHOR: Roger Logan, Anora Solutions, Test Engineer, Houston, TX"
__DATEMODIFIED__ = "LAST MODIFIED: Aug 12, 2011"
__VERSION__ = " v1.0"
__PROGFILE__ = "supermargin.py"
__INPUTFILE__ = "<params.txt>"
#__OUTPUTFILE__ = "" #not used

_tperiod_ = "period"    #set this variable to your tester period variable
_vddmax_  = "4V" #set this variable to your vdd max variable or to a voltage such as '5V'
TIMING    = 1        #set this to '1' for timing or to '0' for voltage

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 1:
        print "usage: "+__PROGFILE__+" "+__INPUTFILE__
        sys.exit(-1)
    
    infile = open(args[0], 'r')
    content = infile.read()
    infile.close()
    
    localtime = time.asctime(time.localtime(time.time()))
    
    header = "enVision:\"bl8:R15.4.3:S4.1\";\n\n"
    header += "//This file was generated by: "+__PROGFILE__+__VERSION__+".\n//"+__AUTHOR__+"\n//CREATION DATE: "+str(localtime)+"\n\n"
    
    os.system('clear')
    print '\n\n'

    params = []
    rawparams = content.split('\n')
    for param in rawparams:
        if len(param.strip()):params.append(param.strip())
    
    if (TIMING):
        margin_name = "supermargin_timing"
    else:#voltage
        margin_name = "supermargin_voltage"
    outstr  = "Margin "+margin_name+" {\n"
    outstr += "\tMode Scan, Etic, Binary;\n"
    outstr += "\tPinPriority = False;\n"
    
    #build max length of parameters
    maxlen=0
    for param in params:
        if len(param) > maxlen:
            maxlen=len(param)
        #End if
    #End for
    
    for param in params:
        spaces = ' '
        for i in range(maxlen-len(param)):
            spaces+=' '
        #End for
        if (TIMING):
            if param==_tperiod_:#use nominal value to prevent circular dependency
                start_str = "12ns"
                stop_str  = "200ns"
            else:
                start_str = "-0.5*"+_tperiod_
                stop_str  = "2*"+_tperiod_
        else:#voltage
            if param==_vddmax_:#use nominal value to prevent circular dependency
                start_str = "0V"
                stop_str  = "3.6V"
            else:
                start_str = "0V"
                stop_str  = _vddmax_
        outstr += "\tRow = Axis { NumSteps = Expr { String = \"50\"; } ParameterVariance { Param "+param+";"+spaces+"Start = Expr { String = \""+start_str+"\"; } Stop = Expr { String = \""+stop_str+"\"; }}}\n"
    #End for
    
    outstr += "}\n"
    
    outfile = open(margin_name+'.evo', "w")
    outfile.write(header+outstr)
    outfile.close()

    print '\n\n'
    print __PROGRAM_NAME__+" "+__VERSION__
    print __AUTHOR__
    print __DATEMODIFIED__
    print "SUCCESS!!! NEW FILE(S) CREATED:\n"+margin_name+".evo\n\n"

#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
