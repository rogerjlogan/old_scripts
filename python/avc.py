import os
import re
import gzip
import string
import sys
import inspect
from pprint import pprint

_outdir_ = "avc_out"

def lineno():
    """Returns the current line number in our program."""
    return inspect.currentframe().f_back.f_lineno
#End lineno()

_RD_ERROR_ = "Make sure you have permissions to READ files in this directory."
_WR_ERROR_ = "Make sure you have permissions to WRITE files in this directory."

_pats_created_=[]
_pincombos_=[]
fmtPtrn = re.compile(r'\bFORMAT\b\s+(?P<pins>.*?)\s*;',re.DOTALL)
vecPtrn = re.compile(r'^\s*R(?P<rpt>\d+?)\s*(?P<wvt>\w+?)\s+(?P<vec>\w+?)\s+(?:%.*?)?\s*;\s*$')
def main(inpathfn):
    in_path, fn = os.path.split(inpathfn)
    patname = os.path.splitext(fn)[0]
    print "Processing",fn,"..."
    global _pats_created_,_pincombos_
    if not os.path.exists(_outdir_):
        try:
            os.makedirs(_outdir_)
        except:exit("Directory WRITE/CREATE Error !!!: "+_outdir_+"\n"+_WR_ERROR_+"\nLine: "+str(lineno())+"\n\n")
    try:
        pathfn = os.path.join(_outdir_,patname+'.avc')
        ofile = open(pathfn, "w")
    except:exit("Directory WRITE/CREATE Error !!!: "+patname+".evo\n"+_WR_ERROR_+"\nLine: "+str(lineno())+"\n\n")
    _pats_created_.append(pathfn)
    prev_vec=''
    content=open(inpathfn).read()
    fmtObj=fmtPtrn.search(content)
    if not fmtObj:
        sys.exit("\n\nERROR !!! No FORMAT found in avc file: "+fn+" Exiting ...\n\n")
    for pin in fmtObj.group('pins').split():
        if pin not in _pincombos_:
            _pincombos_[pin]=''
    cyc_cnt=0
    vec_cnt=0
    for line in content.split('\n'):
        vecObj=vecPtrn.search(line)
        if not vecObj:
            ofile.write(line+'\n')
        else:
            vec_vnt+=1
            rpt = vecObj.group('rpt')
            wvt = vecObj.group('wvt')
            vec = vecObj.group('vec')
            if len(vec) != len(_pincombos_):
                sys.exit("\n\nERROR !!! Length of vector does not match length of format: "+fn+" Exiting ...\n\n")
            if rpt>1:
                
            
            
            
            cyc_cnt+=rpt
            prev_vec=vec
    ofile.close()
    return

if __name__ == "__main__":
    if len(sys.argv) <2:
        print "Usage : python " + sys.argv[0] + " <files>"
        sys.exit()
    for pathfn in sys.argv[1:]:
        main(pathfn)



