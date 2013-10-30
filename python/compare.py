import sys
import re
import pprint
import os
#import string
from string import *
import time

__PROGRAM_NAME__ = "Compare 2 files"
__AUTHOR__ = "AUTHOR: Roger Logan, Anora Solutions, Test Engineer, Dallas, TX"
__DATEMODIFIED__ = "LAST MODIFIED: March 14, 2011"
__VERSION__ = " v1.0"
__PROGFILE__ = "compare.py"
__INPUTFILE1__ = "<inputfile.txt>"
__INPUTFILE2__ = "<inputfile.txt>"
__OUTPUTFILE__ = "output.txt"

__EVO_HEADER__ = "enVision:\"bl8:R10.3.2.WW0104:S3.0\"; /* 5.7 */\n\n"


#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 2:
        print "usage: "+__PROGFILE__+" "+__INPUTFILE1__+" "+__INPUTFILE2__
        print len(args)
        sys.exit(-1)
    
    os.system('clear')
    print '\n\n'

    infile1 = open(args[0], 'r')
    content1 = infile1.read()
    infile1.close()

    infile2 = open(args[1], 'r')
    content2 = infile2.read()
    infile2.close()

    
    content1=content1.split('\n')
    content2=content2.split('\n')
    
    
    for i in content1:
        for n in content2:
            if n not in content1:
                print n
    
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
