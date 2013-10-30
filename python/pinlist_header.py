import sys
import re
import pprint
import os
#import string
from string import *
import time

__pins__ = [] #raw pinlist
__pinhdr__ = "" #vertical pinlist string

def buildPinlistHeader():
    global __pinhdr__
    offset=3
    maxlen=len(max(__pins__,key=len))
    padpins=[]
    for pin in __pins__:
        padpins.append(pin.ljust(maxlen))
    hdr = []
    for c in range(1,maxlen):
        row = "\" "
        for p in padpins:
            row += p[c-1]
        row += " \""
        hdr.append(row)
    __pinhdr__ = join(hdr,"\n")

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __pins__
    __pins__ = ['CLK1','DIN0','DIN1','D_ZK0','D_ZK1','D_ZK2','E0','E1','E2','E3','ID0','ID1','ID2','ID3','K0','K1','K2','K3','K4','RESET_N','TEST_N','CLK2','DOUT','ERROR_N','A0','A1','A2','A3']
    buildPinlistHeader()
    print __pinhdr__

#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
