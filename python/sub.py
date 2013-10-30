# Use this script to replace a list of variables with their values
# INSTRUCTIONS:  Create a list file such that each line contains
# two values separated by a comma where the first value is to be replaced by the second value
# Example:
# 
# val1,true
# val2,false 
# val3,false
# ...

import sys
import re
import pprint
#import string
from string import *
import time

import csv

__PROGRAM_NAME__ = "Substitution"
__AUTHOR__ = "AUTHOR: Roger Logan, Anora Solutions, Test Engineer, Houston, TX"
__DATEMODIFIED__ = "LAST MODIFIED: Feb 15, 2013"
__VERSION__ = " v2.0"
__PROGFILE__ = "sub.py"
__LISTFILE__ = "<list.csv>"
__INPUTFILE__ = "<inputfile>"
__OUTPUTFILE__ = "<inputfile>_mod"

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __LISTFILE__,__OUTPUTFILE__
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 2:
        print "usage: "+__PROGFILE__+" "+__LISTFILE__+" "+__INPUTFILE__
        exit()
    
    print '\n\n'

    infile = open(args[1], 'r')
    __OUTPUTFILE__=args[1]+'_mod'
    content = infile.read()
    infile.close()

    newcontent=content
    with open(args[0], 'rb') as f:
        reader = csv.reader(f)
        for row in reader:
            newcontent = re.sub(r'\b%s\b' % strip(row[0]), strip(row[1]), newcontent)
    f = open(__OUTPUTFILE__, 'w')
    f.write(newcontent)
    f.close()
    #End for
            
    print '\n\n'
    print __PROGRAM_NAME__+" "+__VERSION__
    print __AUTHOR__
    print __DATEMODIFIED__
    print "SUCCESS!!! NEW FILE CREATED: "+__OUTPUTFILE__+"\n\n"


#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
