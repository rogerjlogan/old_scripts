# Use this script to do a regex global replace
# across multiple files.
# INSTRUCTIONS:  Create a txt file with a list of the files you want to open
# with each file name separated by a newline..
# Example:
# 
# file1
# file2
# file3
# ...
# file10

__FIND_STRING__ = "(@)"
__REPL_STRING__ = "(pALL)"

import sys
import re
import pprint
import os
#import string
from string import *
import time
import gzip

__PROGRAM_NAME__ = "Multifile Replace"
__AUTHOR__ = "AUTHOR: Roger Logan, Anora Solutions, Test Engineer, Houston, TX"
__DATEMODIFIED__ = "LAST MODIFIED: March 14, 2011"
__VERSION__ = " v2.0"
__PROGFILE__ = "multifile_replace.py"
__INPUTFILE__ = "<inputfile.txt>"
__OUTPUTFILE__ = "output.txt"

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 1:
        print "usage: "+__PROGFILE__+" "+__INPUTFILE__
        sys.exit(-1)
    
    os.system('clear')
    print '\n\n'

    infile = open(args[0], 'r')
    content = infile.read()
    infile.close()

    files=content.split('\n')
    for thisfile in  files:
        if not len(thisfile): continue
        if thisfile[-3:] == '.gz':
            f = gzip.open(thisfile, 'rb')
        else:
            f = open(thisfile, 'r')
        file_content = f.read()
        f.close()
        newcontent = file_content.replace(__FIND_STRING__,__REPL_STRING__)
        if thisfile[-3:] == '.gz':
            f = gzip.open(thisfile, 'wb')
        else:
            f = open(thisfile, 'w')
        f.write(newcontent)
        f.close()
    #End for
            
    print '\n\n'
    print __PROGRAM_NAME__+" "+__VERSION__
    print __AUTHOR__
    print __DATEMODIFIED__


#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
