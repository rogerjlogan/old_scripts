import sys
import re
import gzip

def modFileName(fileName):
    name, suffix=fileName.rsplit(".",1)
    return name+"_mod."+suffix

def proc(inp):
    vector_patrn = re.compile("(\[\w+,\w+,\w+,\w+,\w+,\w+,\w+,\w+,?)(\w+,?)(\w+,?)(\w+,?)(\w+,\w+,\w+,\w+\]?)")
    out_file = ""
    for eachline in inp:
        out_file_line = eachline
        vector = vector_patrn.search(eachline)
        if (vector):
            oldv = vector.group(1)+vector.group(2)+vector.group(3)+vector.group(4)+vector.group(5)
            newv = vector.group(1)+vector.group(3)+vector.group(5)
            out_file_line = out_file_line.replace(oldv,newv)
        out_file += out_file_line
    return out_file

if __name__ == '__main__':
    for fn in sys.argv[1:]:
        print "Processing " + fn
        fnOut = modFileName(fn)
        if fn[-3:] == '.gz':
            gzip.open(fnOut,"wb").write("".join(proc(gzip.open(fn,'rb'))))
        else:
            open(fnOut,"w").write("".join(proc(open(fn))))

# #THIS CODE IS MEMORY INTENSIVE AND SHOULD NOT BE USED
# #     vector_patrn = re.compile("(\[\w+,\w+,\w+,\w+,\w+,\w+,\w+,\w+,)(\w+,)(\w+,)(\w+,)(\w+,\w+,\w+,\w+\])")
# #     vectors=vector_patrn.findall(open(sys.argv[1:][0],'r').read())
# #     
# #     for vector in vectors:
# #         oldv=''
# #         for v in vector:oldv=oldv+v
# #         newv=vector[0]+vector[2]+vector[4]
# #         content=content.sub(oldv,newv)
#     
#     __OUTPUTFILE__=sys.argv[1:][0]+'.mod'
#     out_fp = open(__OUTPUTFILE__,'w')
#     out_fp.write(out_file)
# 
