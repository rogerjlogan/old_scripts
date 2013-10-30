# Use this script to do a regex global append
# in one file of multiple variables
# INSTRUCTIONS:  Create a txt file with a list of the vars you want to have in appended
#This will read in all vars from varlist.txt and search for them in searchfile.txt
#The output.txt file will be a copy of searchfile.txt with vars append with __APPEND_STRING__

__APPEND_STRING__ = "_PZ"

import sys
import re
import pprint
import os
#import string
from string import *
import time
import gzip

__PROGRAM_NAME__ = "Multivariable Append"
__AUTHOR__ = "AUTHOR: Roger Logan, Anora, Test Engineer, Dallas, TX"
__DATEMODIFIED__ = "LAST MODIFIED: March 14, 2011"
__VERSION__ = " v1.0"
__PROGFILE__ = "multivar_append.py"
__INPUTFILE1__ = "<varlist.txt>"
__INPUTFILE2__ = "<searchfile.txt>"
__OUTPUTFILE__ = "output.txt"

#this will return a list of strings passed with all white space removed and empty strings deleted from list
def striplist(l):
    return (filter(None,[x.strip() for x in l]))

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __OUTPUTFILE__,__INPUTFILE1__,__INPUTFILE2__
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 2:
        print "usage: "+__PROGFILE__+" "+__INPUTFILE1__+" "+__INPUTFILE2__
        sys.exit(-1)
    
    os.system('clear')
    print '\n\n'

    varfile = open(args[0], 'r')
    __INPUTFILE1__=args[0]
    rawvarslst = varfile.read()
    varfile.close()

    searchfile = open(args[1], 'r')
    __INPUTFILE2__=args[1]
    content = searchfile.read()
    searchfile.close()

    varslst=striplist(rawvarslst.split('\n'))
   
    for var in varslst:
        content = re.sub(var+"(?![a-z|A-Z|\d|"+__APPEND_STRING__+"])",var+__APPEND_STRING__,content)
    __OUTPUTFILE__ = __INPUTFILE2__+"_mod"
    
    f = open(__OUTPUTFILE__, 'w')
    f.write(content)
    f.close()

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
