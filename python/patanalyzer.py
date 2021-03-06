import sys
import re
from pprint import pprint
import os
import time
import inspect

__drvcombos__ = ['lhl','hlh','LHL','HLH']
__strbcombos__ = ['010','101']
__logFile__ = "logfile.txt"
__logStr__ = ""

def getline():
    """Returns the current line number in our program."""
    return inspect.currentframe().f_back.f_lineno
#End lineno()

def secondsToStr(t):
    return "%02dhrs:%02dmins:%02d.%03dsecs" % \
        reduce(lambda ll,b : divmod(ll[0],b) + ll[1:],
            [(t*1000,),1000,60,60])

vectorPat = re.compile("^\s*\*\s*(?P<vector>.*?)\s*\*\s*(?P<sh_wft>.*?)\s*;")
defWFTPat = re.compile("Default\s+WaveformTable\s+(?P<defwft>.*?)\s*;")
defSHPat = re.compile("Default\s+SignalHeader\s+(?P<defsighdr>.*?)\s*;")
patPat = re.compile("^\s*Pattern\s+(?P<patname>\w+?)\s*\{")
def main(ifp,file,fullpath):
    global __logStr__
    pattern=[]
    lineno=0
    v=-1
    thisIsPat,found = False,False
    drvpins,strbpins=[],[]
    drvcombos,strbcombos=[],[]
    sh_wft=''
    all_sh_wft=[]
    for line in ifp:
        lineno+=1
        patObj = patPat.search(line)
        if patObj:
            thisIsPat = True
        if thisIsPat:
            vObj = vectorPat.search(line)
            if vObj:
                v+=1
                vector = vObj.group('vector').replace(' ','').strip()
                sh_wft = vObj.group('sh_wft')
                if len(sh_wft) and sh_wft not in all_sh_wft:
                    all_sh_wft.append(sh_wft)
                pattern.append(vector)
                if v>1:
                    for i,c in enumerate(vector):
                        try:
                            str2chk = pattern[v-2][i]+pattern[v-1][i]+c
                        except:
                            print "\n\nERROR !!!!"
                            print "str2chk assignment broken"
                            print "v:",v
                            print "i:",i
                            print "c:",c
                            print "pattern[v-2]:",pattern[v-2]
                            print "pattern[v-1]:",pattern[v-1]
                            print "vector      :",vector
                            print "len(vector) :",len(vector)
                            print "Index out of range. Line:",getline(),"\n"
                            raise IndexError
                        pin = str(i)
                        if str2chk in __drvcombos__:
                            found = True
                            if pin not in drvpins:
                                drvpins.append(pin)
                            if str2chk not in drvcombos:
                                drvcombos.append(str2chk)
                        if str2chk in __strbcombos__:
                            found = True
                            if pin not in strbpins:
                                strbpins.append(pin)
                            if str2chk not in strbcombos:
                                strbcombos.append(str2chk)
            elif v==-1:
                wftObj = defWFTPat.search(line)
                shObj = defSHPat.search(line)
                if wftObj:
                    all_sh_wft.append(wftObj.group('defwft'))
                elif shObj:
                    all_sh_wft.append(shObj.group('defsighdr'))
    #End for
    if thisIsPat:
        if found:
            __logStr__ += "Transitions found in File: "+fullpath+"\n"
            __logStr__ += "    Drive Pins transitioning     : "+','.join(drvpins)+"\n"
            __logStr__ += "    Drive Combinations found     : "+','.join(drvcombos)+"\n"
            __logStr__ += "    Strobe Pins transitioning    : "+','.join(strbpins)+"\n"
            __logStr__ += "    Strobe Combinations found    : "+','.join(strbcombos)+"\n"
            __logStr__ += "    WaveformTables/SignalHeaders : "+','.join(all_sh_wft)+"\n"
            print "Matches Found ! Check "+__logFile__
        else:
            print "No matches Found."
    else:
        print "Not a pattern. Skipping."
    ifp.close()
#End main()

if __name__ == '__main__':
    start = time.time()
    if len(sys.argv) < 2:
        print("usage: python patanalyzer.py <input directory>")
        exit()
    directory = sys.argv[1]

    #Unzipping all zipped evos since we can't read them with gzip for some reason
    os.system("find "+directory+" -name \"*evo.gz\"|xargs gunzip")

    for root,dirs,files in os.walk(directory):
        for file in files:
            fullpath = os.path.join(root,file)
            if file.endswith('.evo.gz'):
                print "\n\n\nError !!! There's a problem with this script trying to read gzipped files ! Exiting.\n\n\n"
                raise IOError
            elif file.endswith('.evo'):
                print 'Analyzing '+fullpath+' ...'
                ifp = open(fullpath, 'r')
                main(ifp,file,fullpath)
            else:#not a file we are interested in
                continue

    timeStr = "Script took "+secondsToStr(time.time()-start)+"\n\n"
    if len(__logStr__):
        ofp = open(__logFile__,'w')
        ofp.write(timeStr+__logStr__)
        ofp.close()
    print "\n",timeStr
