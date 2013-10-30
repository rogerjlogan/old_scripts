import sys
import re
import pprint
import os
#import string
from string import *
import time

__PROGRAM_NAME__ = "SCAN LABEL REMOVER (From Evos)"
__AUTHOR__ = "AUTHOR: Roger Logan, Anora Solutions, Test Engineer, Houston, TX"
__DATEMODIFIED__ = "LAST MODIFIED: Sept 1, 2011"
__VERSION__ = " v1.0"
__PROGFILE__ = "scanlabel_remover.py"
__INPUTFILE__ = "<pattern.evo>"
__OUTPUTFILE__ = "<pattern.evo>.new"
__PERMISSIONS_ERR__ = "If file was input, check to see if it exists and that read permissions are allowed for you.\n"
__PERMISSIONS_ERR__ += "Also, check that write permissions are allowed for this directory, as this scripts creates a new file (<pattern.evo>.new)."

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __OUTPUTFILE__
    global __CREATION_MSG__
    
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

    newcontentLst=[]
    contentList  = content.split('$ScanFor')
    for sect in contentList:
        if sect.count('* ScanCycle') > 2:
            print "Error!  Found more than two closing '* ScanCycle' for a given '$ScanFor'"
            sys.exit(-1)
        elif not sect.count('* ScanCycle'):
            newcontentLst.append(sect)
            # skip since there are no scan vectors here
            continue
        else:
            regex = re.compile("\*\s*ScanCycle.*")
            sect = regex.sub('',sect,1)
            newcontentLst.append(sect)
        #End if
    #End for
    new_content = '$ScanFor'.join(newcontentLst)

    try:
        ofile = open(__OUTPUTFILE__, "w")
    except:
        err="File Error: "+__OUTPUTFILE__+"\n"
        err+=__PERMISSIONS_ERR__
        print err
        sys.exit(-1)
    ofile.write(new_content)
    ofile.close()
    
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
