import sys
import shutil
__DEBUG__ = False

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
    stack=[]
    rs_found=False
    firstbeginfound=False
    for line in ifp:
        if 'Shutdown' in line or 'repeat' in line:
            rs_found=True
            ofp.write(line)
            continue
        if 'begin' in line:
            if not firstbeginfound and not rs_found:
                firstbeginfound=True
                stack.append(firstbeginfound)
                ofp.write(line)
                continue
            stack.append(rs_found)
            if rs_found:
                ofp.write(line)
                rs_found=False
            elif __DEBUG__:
                ofp.write(line[:-1]+' DELETED\n')
        elif 'end;' in line:
            rs_found=False
            if stack.pop():
                ofp.write(line)
            elif __DEBUG__:
                ofp.write(line[:-1]+' DELETED\n')
        else:
            rs_found=False
            ofp.write(line)
        #End if
    #End for
    ifp.close()
    ofp.close()
#End main()

if __name__ == '__main__':
    if len(sys.argv) < 2:
    	print("usage: python remVPLbeginend.py <inputfile(s)>")
        sys.exit()
    for fn in sys.argv[1:]:
        print 'Processing '+fn
        main(fn)

