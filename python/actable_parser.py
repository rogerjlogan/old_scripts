"""
    Requirements:
         - Python2.3 or higher
    Function:
        Used to generate the following files:
            - actable.proc          - Required by GCT_GEN_MOD6 (or later version)
"""
__progfile__ = "actable_parser.py"
__version__ = "v1.0"
__author__ = "AUTHOR: Roger Logan, Anora Solutions, Test Engineer, Houston, TX"
__date__ = "LAST MODIFIED: July 13, 2011"

#{format function             :num of polaris args}
__all_waveform_formats__ = \
{\
'WaveSetSBC'                  :4,\
'WaveSetNR'                   :2,\
'WaveSetRTO'                  :3,\
'WaveSetRTZ'                  :3,\
'WaveSetStrobe'               :4,\
'WaveSetEdgeStrobe'           :4,\
'WaveSetStrobeZ'              :4,\
'WaveSetEdgeStrobeZ'          :4,\
'WaveSetStrobeValid'          :4,\
'WaveSetEdgeStrobeValid'      :4,\
'WaveSetClk'                  :3,\
'WaveSetDoubleClk'            :5,\
'WaveSetTripleClk'            :7,\
'WaveSetQuadClk'              :9,\
'WaveSetPentaClk'             :11,\
'WaveSetHexClk'               :13,\
'WaveSetOff'                  :3,\
'WaveSetContinue'             :1,\
'WaveSetDelaySBC'             :7,\
'WaveSetDelayNR'              :3,\
'WaveSetDelayRTO'             :5,\
'WaveSetDelayRTZ'             :5,\
'WaveSetDelayStrobe'          :7,\
'WaveSetDelayEdgeStrobe'      :7,\
'WaveSetDelayStrobeZ'         :7,\
'WaveSetDelayEdgeStrobeZ'     :7,\
'WaveSetDelayStrobeValid'     :7,\
'WaveSetDelayEdgeStrobeValid' :7,\
'WaveSetDelayClk'             :5,\
'WaveSetDelayDoubleClk'       :9,\
'WaveSetDelayTripleClk'       :13,\
'WaveSetDelayQuadClk'         :17,\
'WaveSetDelayPentaClk'        :21,\
'WaveSetDelayHexClk'          :25,\
'WaveSetDelayOff'             :5,\
}

import sys
import re
import pprint
import time
import string
import pprint

#from global_defs import *

__ACTABLE_IFILE__ = "<actable.p>"
__ACTABLEMOD_OFILE__ = "actable.proc"
__EVHDR__ = "enVision:\"bl8:R11.1.0.WW1111:S3.5\"; /* 5.7 */\n\n"
__VERBOSE__ = True

__SAVED_HEADER__ = ""
__SAVED_FOOTER__ = ""

#Error Messages
__PERMISSIONS_ERR__ = "If file was input, check to see if it exists and that read permissions are allowed for you.\n"
__PERMISSIONS_ERR__ += "Also, check that write permissions are allowed for this directory, as this scripts creates certain files."
__ACTABLECONTENT_ERR__ = "'ACTableOpen' not found in "+__ACTABLE_IFILE__


class TextException(Exception): pass

class Ddict(dict):
    def __init__(self, default=None):
        self.default = default
    def __getitem__(self, key):
        if not self.has_key(key):
            self[key] = self.default()
        return dict.__getitem__(self, key)
#End Ddict()

#-----------------------------------------------------------------------
#   strip
#-----------------------------------------------------------------------
def stripcom(string,delim_st,delim_sp='\n',ignore_st=None,ignore_sp=None):
  """This will return 'string' stripped of anything between (and including) 'delim_st' and 'delim_sp'\
  (except when 'delim_sp' is newline) EVEN IF THEY ARE NESTED.  Delimiters can be any string or character\
  (alphanumerics as well as non-alphanumerics).\
  'ignore_st' and 'ignore _sp' allow removal of substrings from string before parsing for nested strings."""
  
  if ignore_st and ignore_sp:
    string=strip(string,ignore_st,ignore_sp)
  
  es_delim_st=re.escape(delim_st) # returns non-alphanumerics backslashed for regex
  es_delim_sp=re.escape(delim_sp) # returns non-alphanumerics backslashed for regex
  
  if delim_sp!='\n':
    # THIS IS A MULTILINE STRING SO WE NEED TO CHECK FOR NESTING
    patrn = re.compile(
      # This is a regex WITHIN a regex
      "("+es_delim_st+      # outer regex start
      "(?:.*?)"+                # inner regex  ?: prevents backreference of inner regex
                                #              .* searches for any char except '\n'(any # of times)
                                #              ? before closing makes this 'lazy' (it will grab FIRST occurance of 'delim_sp')
      es_delim_sp+")",      # outer regex end
      re.DOTALL|            # re.DOTALL overrides '.*' limitation of '\n' described above
      re.VERBOSE)           # re.VERBOSE allows these comments (ignores whitespace including newlines)
    while 1:
      strObj = patrn.search(string) # search for 1st occurance of backreferenced pattern (from outer regex defined above)
      if not strObj:break  # no more, we're done
      # found a substring
      substring=strObj.group() # get string from RE object
      if substring.count(delim_st) and delim_st!= delim_sp>1:
        if delim_sp!='\n':
          # remove nested substring (two 'delim_st' and one 'delim_sp')
          strObj = patrn.search(substring,1) # ignore 1st delim_st
        else:
          strObj = patrn.search(substring)
        if strObj:
          substring = strObj.group() # get string from RE object
      string=string.replace(substring,'',1) # only remove that one instance
  else:
    # THIS IS A SINGLELINE STRING - NO NEED TO CHECK BEYOND NEWLINE
    patrn = re.compile("("+es_delim_st+"(?:.*))")
    string = re.sub(patrn,'',string)
  return string
#End strip()


def getACTABLEcontents(actblfile):
    """
        Get ACTable and structures it for easy parsing
    """
    global __SAVED_HEADER__
    global __SAVED_FOOTER__
    try:
        infile = file(actblfile, 'r')
        actblallcont = infile.read()
        infile.close()
    except:
        err="File Error: "+actblfile+"\n"
        err+=__PERMISSIONS_ERR__
        sys.exit(stop(err))
    patrn=re.compile("(?P<header>.*)ACTableOpen(?P<actable>.*)ACTableClose;(?P<footer>.*)",re.DOTALL)
    
    if string.find(actblallcont,"ACTableOpen") < 0:
        sys.exit(stop(__ACTABLECONTENT_ERR__))
    actblcontObj=patrn.search(actblallcont)
    actblcont='ACTableOpen'+actblcontObj.group('actable')+'ACTableClose;'
    __SAVED_HEADER__ = actblcontObj.group('header')
    __SAVED_FOOTER__ = actblcontObj.group('footer')

    actblcont=stripcom(actblcont,'(*','*)')
    actblcont=stripcom(actblcont,'{','}')

    #remove spaces next to symbols
    symbls=[',',':',';','\+','-','\*','/','=','\[','\]','\(','\)']
    for s in symbls:
        patrn=re.compile("(?:\s*)"+s+"(?:\s*)",re.DOTALL)
        actblcont=re.sub(patrn,s,actblcont)
        
    actblcont=actblcont.replace('\[','[')
    actblcont=actblcont.replace('\]',']')
    actblcont=actblcont.replace('\(','(')
    actblcont=actblcont.replace('\)',')')
    actblcont=actblcont.replace('\+','+')
    actblcont=actblcont.replace('\*','*')
    actblcont=actblcont.replace('\n',' ')
    actblcont=actblcont.replace(';',';\n')

    patrn=re.compile("begin(?:\s*)")
    actblcont=re.sub(patrn,"\nbegin\n",actblcont)
    patrn=re.compile("then(?:\s*)")
    actblcont=re.sub(patrn,"then\n",actblcont)
    patrn=re.compile("else(?:\s*)")
    actblcont=re.sub(patrn,"else\n",actblcont)
    
    return actblcont
#End parseACTable()

def mkACTableModFile(actcont):
    try:
        ofile = open(__ACTABLEMOD_OFILE__, "w")
    except:
        err="File Error: "+__ACTABLEMOD_OFILE__+"\n"
        err+=__PERMISSIONS_ERR__
        sys.exit(stop(err))
    ofile.write(mkHeader(__progfile__,__version__,__author__))
    ofile.write(actcont)
    ofile.close()
#End mkACTableModFile()

def mkHeader (prog,ver,auth):
    localtime = time.asctime(time.localtime(time.time()))
    header  = "(* This file was generated by: "+prog+ver+" from actable.p *)\n"
    header += "(* "+auth+" *)\n"
    header += "(* CREATION DATE: "+str(localtime)+" *)\n\n"
    return header
#End mkHeader()

def parseLines(actcont):

    TopPtn    = re.compile("(?P<top>.*)GROUP_START_0",re.DOTALL)
    BottomPtn = re.compile("GROUP_END_"+str(actcont.count('GROUP_START')-1)+"(?P<bottom>.*)",re.DOTALL)

    TopObj    = TopPtn.search(actcont)
    BottomObj = BottomPtn.search(actcont)

    if not TopObj or not BottomObj:
        print "ERROR!  No Labels Found!\nAdd GROUP_START_0,GROUP_END_0, GROUP_START_1, GROUP_END_1, ETC...."
        print "This script is designed to consolidate actable.p"
        print "Without labels, it is assumed that this file is already consolidated!!!"
        sys.exit(-1)
    #End if

    formats = []
    waves = Ddict(dict)
    org   = Ddict(dict)
    for i in range(actcont.count('GROUP_START')):
        sectPtn=re.compile("GROUP_START_"+str(i)+"(?P<section>.*)GROUP_END_"+str(i),re.DOTALL)
        sectObj = sectPtn.search(actcont)
        sectStr = sectObj.group('section')
        
        WaveFormPtn = re.compile("WaveSet(?P<type>.*?)\((?P<waveform>.*?)\)")
        OrgPtn      = re.compile("EdgeSetOrigin\((?P<origin>.*?)\)")
        
        lines = sectStr.split('\n')
        
        for line in lines:
            WaveFormObj=WaveFormPtn.search(line)
            OrgObj=OrgPtn.search(line)
            
            if WaveFormObj:
                format = 'WaveSet'+WaveFormObj.group('type')
                raw_wf = WaveFormObj.group('waveform')
                wfLst  = raw_wf.split(',')
                if format not in __all_waveform_formats__.keys():
                    print 'ERROR !!!  UNKNOW WAVEFORM !'
                    sys.exit(-1)
                else:
                    wfparam=wfLst[0]
                    args = __all_waveform_formats__[format]
                    argLst = []
                    if args == 1:continue
                    for n in range(args):
                        if n==0:continue
                        argLst.append(wfLst[n])
                    #End for
                    if waves[wfparam] and waves[wfparam] != argLst:
                        print "GROUP_START_0"
                        print 'waves[wf]:'+str(waves[wfparam])
                        print "GROUP_START_"+str(i)
                        print 'argLst   :'+str(argLst)
                        print line+'\n\n'
                    else:
                        waves[wfparam]=argLst
                    #End if

            if OrgObj:
                raw_org  = OrgObj.group('origin')
                orgLst   = raw_org.split(',')
                orgparam = orgLst[0]
                edge     = orgLst[1]
                org_name = 'EdgeSetOrigin'
                args = 2
                argLst = []

                if orgparam not in org.keys() or edge not in org[orgparam].keys():
                    org[orgparam][edge] = orgLst[2]
                elif org[orgparam][edge] != orgLst[2]:
                    print "GROUP_START_"+str(i)
                    print 'orgparam:            '+orgparam
                    print 'edge:                '+edge
                    print 'org[param][edge]:    '+str(org[orgparam][edge])
                    print 'orgLst[2]:           '+orgLst[2]
                    print line+'\n\n'
                #End if
            #End if
        #End for
    #End for
        


    sys.exit(-1)
        
        
        
        
        

#     for itm in item.items():
#         pprint.pprint(itm)
# 
# 
#     sys.exit(-1)
#     
#     
#     
#     wave = Ddict(dict)
#     org = Ddict(dict)
# 
#     newlines = []
#     found = []
# 
#     WaveFormPtn=re.compile("WaveSet(?P<name>.*?)\((?P<rawcontent>.*?)\)")
#     OrgPtn=re.compile("EdgeSetOrigin(?P<name>.*?)\((?P<rawcontent>.*?)\)")
#     for line in lines:
# 
#         WaveFormObj=WaveFormPtn.search(line)
#         OrgObj=OrgPtn.search(line)
#         if WaveFormObj or OrgObj:
#             if line in found:
#                 duplicates.append(line)
#             else:
#                 found.append(line)
#         
#         continue
#         
#         if WaveFormObj:
#             WaveFormStr = WaveFormObj.group('rawcontent')
#             WaveFormLst = WaveFormStr.split(',')
#             param = WaveFormLst[0]
#             if not len(WaveFormStr):break
#             if param not in wave.keys():
#                 wave[param] = WaveFormStr
#             elif wave[param] != WaveFormStr:
#                 print 'wave[param]:  '+str(wave[param])
#                 print 'WaveFormStr: '+WaveFormStr
#                 print line+'\n'
#         elif OrgObj:
#             OrgStr = OrgObj.group('rawcontent')
#             OrgLst = OrgStr.split(',')
#             param = OrgLst[0]
#             edge = OrgLst[1]
#             if param not in org.keys() or edge not in org[param].keys():
#                 org[param][edge] = OrgLst[2]
#             elif org[param][edge] != OrgLst[2]:
#                 print 'param:               '+param
#                 print 'edge:                '+edge
#                 print 'org[param][edge]:    '+str(org[param][edge])
#                 print 'OrgLst[2]:           '+OrgLst[2]
#                 print line+'\n\n'
#     #End for
#     
#     print '\n'.join(duplicates)
#     sys.exit(-1)
        
#         org_cnt = 0
#         for element in elements:
#             if element == elements[0]:
#                 WaveFormObj=WaveFormPtn.search(element)
#                 newlines.append(line)
#                 format_type = 'WaveSet'+WaveFormObj.group('name')
#                 WaveFormStr = WaveFormObj.group('WSrawcontent')
#                 WaveFormLst = WaveFormStr.split(',')
#                 parameter = WaveFormLst[0]
# 
#                 if parameter not in wave.keys() or format_type not in wave[parameter].keys():
#                     wave[parameter][format_type]=WaveFormStr
#                     print wave
#                 elif wave[parameter][format_type] != WaveFormStr:
#                     print parameter+'\t'
#                     print format_type+'\t\t'
#                     print WaveFormStr
#                     print wave[parameter][format_type]+'\n'
# 
# 
# 
#             elif:
#                 if string.find(element,"EdgeSetOrigin") < 0:
#                     continue
#                 org_cnt += 1
#                 if parameter not in wave.keys() or format_type not in wave[parameter].keys():
#                     wave[parameter][format_type]=WaveFormStr
#                 elif wave[parameter][format_type] != WaveFormStr:
#                     print parameter+'\t'
#                     print format_type+'\t\t'
#                     print WaveFormStr
#                     print wave[parameter][format_type]+'\n'
    

    
    return '\n'.join(newlines)

#End parseLines()

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __ACTABLE_IFILE__
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 1:
        err="\nusage: python "+__progfile__+" "+__ACTABLE_IFILE__+"\n"
        sys.exit(err)

    __ACTABLE_IFILE__=args[0]

    if __VERBOSE__:
        print '\n\n'
        print __progfile__,__version__
        print __author__
        print __date__
    print '\n'

    actcont=getACTABLEcontents(__ACTABLE_IFILE__)

    actcont=parseLines(actcont)
    
    mkACTableModFile(actcont)
    
    ostr="SUCCESS!!! NEW FILES CREATED:\n"
    ostr+=__ACTABLEMOD_OFILE__+"\n"
    print ostr

#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
