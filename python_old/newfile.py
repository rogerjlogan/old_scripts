import sys
import re
import pprint
import os
#import string
from string import *
import time

# This program generates vectors starting with the last vector of a pattern.
# It requires a signal header, the last vector of the pattern to appended, and a 
# modified execution log from Polaris.
# Each vector must be delimited by 3 asterisks (***)

__PROGRAM_NAME__ = "VECTOR GENERATOR"
__AUTHOR__ = "AUTHOR: Roger Logan, Anora Solutions, Test Engineer, Houston, TX"
__DATEMODIFIED__ = "LAST MODIFIED: March 14, 2011"
__VERSION__ = " v2.0"
__PROGFILE__ = "vectorgen.py"
__INPUTFILE__ = "<execution_mod.log>" #modify to deliminate vectors with 3 asterisks (***), must contain a valid envision signal header
__OUTPUTFILE__ = "new_vectors.txt"  #copy these into your pattern.evo

__EVO_HEADER__ = "enVision:\"bl8:R10.3.2.WW0104:S3.0\"; /* 5.7 */\n\n"
__CREATION_MSG__ = ""#written in main time.time()

__DEBUG__ = 0
__CLEARSTROBES__ = 1 # USE THIS TO MASK STROBES DURING DRIVE VECTORS

__pins__ = [] #all pins from signal header
__startvctr__ = [] #last vector of init pattern
__addvectors__ = [] #these are the vectors to be added to init pattern
__strobetype__ = 0

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __OUTPUTFILE__
    global __CREATION_MSG__
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
#     if len(args) != 1:
#         print "usage: "+__PROGFILE__+" "+__INPUTFILE__
#         sys.exit(-1)
    
    os.system('clear')
    print '\n\n'
    value =  1
    if value: value=2
    else: value=3
    print "value: "
    print value

#     infile = open(args[0], 'r')
#     __OUTPUTFILE__=args[0]+'.vectors'
#     content = infile.read()
#     infile.close()

    
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
