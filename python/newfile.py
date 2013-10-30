import sys
import re
import pprint
import os
#import string
from string import *
import time

__PROGRAM_NAME__ = "VECTOR GENERATOR"
__AUTHOR__ = "AUTHOR: Roger Logan, Anora Solutions, Test Engineer, Houston, TX"
__DATEMODIFIED__ = "LAST MODIFIED: March 14, 2011"
__VERSION__ = " v2.0"
__PROGFILE__ = "newfile.py"
__INPUTFILE__ = "<inputfile.txt>"
__OUTPUTFILE__ = "output.txt"

__EVO_HEADER__ = "enVision:\"bl8:R10.3.2.WW0104:S3.0\"; /* 5.7 */\n\n"


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
    __OUTPUTFILE__=args[0]+'.vectors'
    content = infile.read()
    infile.close()

    
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
