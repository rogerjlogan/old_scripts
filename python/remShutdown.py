import sys
import shutil

def main(inFile):
#    outFile = inFile.replace('.vpl', '_mod.vpl')
    shutil.copyfile(inFile, inFile+".bak")
    outFile = inFile
    inFile = inFile+".bak"
    if inFile.endswith('.gz'):
        ifp = gzip.open(inFile)
        ofp = gzip.open(outFile,'w')
    else:
        ifp = open(inFile)
        ofp = open(outFile,'w')
    found=False
    for line in ifp:
        if 'Shutdown' in line: #set flag, don't write to line
            found=True
            continue
        elif 'end;' in line:
            if found: #end of Shutdown, reset flag and continue, don't write
                found=False
                continue
            else: #this isn't the end we're looking for, write and continue
                ofp.write(line)
        elif found: #still part of shutdown, don't write
            continue
        else: #not part of shutdown, write line and continue
            ofp.write(line)
        #End if
    #End for
    ifp.close()
    ofp.close()
#End main()

if __name__ == '__main__':
    if len(sys.argv) < 2:
    	print("usage: python remShutdown.py <inputfile(s)>")
        sys.exit()
    for fn in sys.argv[1:]:
        print 'Processing '+fn
        main(fn)

