import re
import array
import gzip
import string
#import sys
#import os
__DEBUG__ = False
relVec = re.compile(r'(\*(.*?)([0-3ekEK]+)(.*?)\*)') #finds any vector that contains a 0,1,2, or 3

def myOpen(fileN, mode="r"):
    if fileN.endswith('.gz'):
        return gzip.open(fileN,mode)
    return open(fileN,mode)

def main(fileN, inds=None):

    print "processing "+ fileN
    outFile = myOpen(fileN.replace(".evo","_rpl.evo"),'w')
    
    
    for line in myOpen(fileN):
        mat =  relVec.search(line)
        if mat:
            vec = mat.group(1)
            print vec 

            
        outFile.write(line)
    outFile.close()
    return

if __name__ == "__main__":
    import sys
    if len(sys.argv) <2:
        print "Usage : python " + sys.argv[0] + " indices <files>"
        sys.exit()
    inds=[]
    for ii,x in enumerate(sys.argv[1:]):
        try:
            inds.append(int(x))
        except ValueError:
            break
    
    for fileN in sys.argv[ii+1:]:
        main(fileN, inds)
