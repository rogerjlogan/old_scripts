import sys
import re
import pprint
import os
#import string
from string import *
import time

__PROGRAM_NAME__ = "ACTABLE PERIOD SET"
__AUTHOR__ = "AUTHOR: Roger Logan, Anora Solutions, Test Engineer, Houston, TX"
__DATEMODIFIED__ = "LAST MODIFIED: July 27, 2011"
__VERSION__ = " v1.0"
__PROGFILE__ = "actable_periodset.py"
__INPUTFILE__ = "<acdata.evo>"
__OUTPUTFILE__ = "<acdata.evo>.new"

__EVO_HEADER__ = "enVision:\"bl8:R10.3.2.WW0104:S3.0\"; /* 5.7 */\n\n"

class Ddict(dict):
    def __init__(self, default=None):
        self.default = default
    def __getitem__(self, key):
        if not self.has_key(key):
            self[key] = self.default()
        return dict.__getitem__(self, key)
#End Ddict()

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

    contents = split(content,'***')

    cat_patrn = re.compile("Category\s*(.*?)\s*\{")
    cats=cat_patrn.findall(contents[0])
    
    for cat in cats:
        per_patrn = re.compile("\t"+cat+" = (?P<period>.*)")
        perObj = per_patrn.search(contents[1])
        if perObj:
            period = perObj.group('period')
            subpat = re.compile("Category\s*"+cat+"\s*\{\s*\n*",re.DOTALL)
            contents[0]=subpat.sub("Category "+cat+" { tperiod = \""+period+"\"; ",contents[0])
    
    print contents[0]
    
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
