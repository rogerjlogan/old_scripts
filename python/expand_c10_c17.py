import sys
import re
import pprint
import os
#import string
from string import *
import time

__PROGRAM_NAME__ = "EXPAND REPEATS (repeat 100 and match repeat 50 until pass)"
__AUTHOR__ = "AUTHOR: Roger Logan, Anora Solutions, Test Engineer, Houston, TX"
__DATEMODIFIED__ = "LAST MODIFIED: Oct 20, 2011"
__VERSION__ = " v1.0"
__PROGFILE__ = "expand_c10_c17.py"
__INPUTFILE__ = "<inputfile.txt>"
__OUTPUTFILE__ = "output.txt"


#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __OUTPUTFILE__
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 1:
        print "usage: "+__PROGFILE__+" "+__INPUTFILE__
        sys.exit(-1)
    
    os.system('clear')
    print '\n\n'

    infile = open(args[0], 'r')
    __OUTPUTFILE__=args[0]+'.new'
    content = infile.read()
    infile.close()

    rpt100_patrn = re.compile("repeat(?:\s*)100(?:\s*\n*\s*?)begin(?:\n?)(.*?)(?:\n?)end(?:\s*\n*\s*?);",re.DOTALL)
    foundrpts=rpt100_patrn.finditer(content)
    for rpts in foundrpts:
        print "vectors:"
        print rpts.group()
        print "\n\n"
    
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
