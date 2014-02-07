import sys
import re
import pprint

__PROGRAM_NAME__ = "ACTABLE OPTIMIZER"
__AUTHOR__ = "AUTHOR: Roger Logan, LTXCredence Apps Engineer, Houston, TX"
__DATEMODIFIED__ = "LAST MODIFIED: October 22, 2008"
__VERSION__ = "VERSION: 1.0"
__FILENAME__ = "pol2fus.py"
__INPUT_FILENAME__ = "<actable.evo>"
__PINLISTFILENAME__ = "pinlist.txt"
__OUTPUT_FILENAME__ = "<actable.evo>.new"

__EVO_HEADER__ = "enVision:\"bl8:R11.1.0.WW1111:S3.5\"; /* 5.7 */\n\n"
__DEBUG__ = True
__VERBOSE__ = False

__stripcomments__ = True

__psblcats__ = []

class TextException(Exception): pass

class Ddict(dict):
    def __init__(self, default=None):
        self.default = default
    def __getitem__(self, key):
        if not self.has_key(key):
            self[key] = self.default()
        return dict.__getitem__(self, key)
#End Ddict()

def lineno():
    """Returns the current line number in our program."""
    return inspect.currentframe().f_back.f_lineno
#End lineno()

def sortWFTkeys(WFTs):
    WFTs=WFTs.keys()
    
    srtdkeys=[]
    num=0
    for key in WFTs:
        if 'WFT_' in key:
            num+=1
        else:
            srtdkeys.append(key)
    srtdkeys.sort()
    for i in range(num):
        srtdkeys.append('WFT_'+str(i))
    return srtdkeys
#End sortWFTkeys()

def build_actable(WFTs):
    
    WFTkeys=sortWFTkeys(WFTs)
    
    ostr=''
    for WFT in WFTkeys:
        per=WFTs[WFT]['per'].strip()
        com=WFTs[WFT]['com'].strip()
        cells=WFTs[WFT]['cells']
        inhrt_str=''
        for inhrt in WFTs[WFT]['inhrts']:
            inhrt_str+='\n\tInherit '+inhrt.strip()+';'

        ostr+="WaveformTable "+WFT+" {\n\tPeriod \""+per+"\";\n\tComment = \""+com+"\";"+inhrt_str+"\n"
        
        for cell in cells:
            cellpinlist=cell['cellpinlist'].strip()
            cellalias=cell['cellalias'].strip()
            cellname=cell['cellname'].strip()
            cellcontents=cell['cellcontents']
            
            cellcontents=cellcontents.replace('{','{ ')
            cellcontents=cellcontents.replace('@',' @ ')
            cellcontents=cellcontents.replace('Drive{','\n\t\tDrive {')
            cellcontents=cellcontents.replace('}}Compare','}\n\t\t}\n\t\tCompare')
            cellcontents=cellcontents.replace('Waveform{','\n\t\t\tWaveform {')
            cellcontents=cellcontents.replace('}}}','}\n\t\t}\n\t}')
            
            cellcontents=cellcontents.replace('Data','Data ')
            cellcontents=cellcontents.replace('  @',' @')
            
            #lazy fixes - prob should rework this
            cellcontents=cellcontents.replace('Drive','Drive ')
            cellcontents=cellcontents.replace('Drive Data','DriveData')
            cellcontents=cellcontents.replace('Drive Low','DriveLow')
            cellcontents=cellcontents.replace('Drive High','DriveHigh')
            cellcontents=cellcontents.replace('Drive On','DriveOn')
            cellcontents=cellcontents.replace('Drive Off','DriveOff')
            cellcontents=cellcontents.replace('Data Not','DataNot')
            cellcontents=cellcontents.replace('Other',' Other')
            cellcontents=cellcontents.replace('EntryState','EntryState ')

            ostr+="\tCell \""+cellpinlist+"\" "+cellalias+" "+cellname+" {\n\t\t"+cellcontents+"\n"
        #End for
        
        ostr+='}\n\n'
    #End for    
    return ostr
#End build_actable()

#-----------------------------------------------------------------------
#   strip
#-----------------------------------------------------------------------
def strip(string,delim_st,delim_sp='\n',ignore_st=None,ignore_sp=None):
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

def createWFTables(wftarray):
    """
        Creates someWFT_nnnnnn with inherited cells from someWFT
    """
    cat_patrn=re.compile("_cat_(?P<cat>.*)")
    #re-arrange for indexing by waveform table name (wftn)
    newWFTs=Ddict(dict)
    for w in wftarray:
        wftn=w['wftn']
        per=w['per']
        inhrts=w['inhrts']
        com=w['com']
        cells=w['cells']
        
        newWFTs[wftn]={'per':per,'com':com,'inhrts':inhrts,'cells':cells}
    #End for

    finalWFTs=Ddict(dict)
    WFT_nn=Ddict(dict)
    #go thru each waveform table
    for WFT in newWFTs:
        per    = newWFTs[WFT]['per']
        com    = newWFTs[WFT]['com']
        inhrts = newWFTs[WFT]['inhrts']
        cells  = newWFTs[WFT]['cells']
        #index wft from inherit and go thru each cell
        for cell in newWFTs[WFT]['cells']:
            catObj=cat_patrn.search(cell['cellname'])
            if catObj:
                for pc in __psblcats__:
                    if filter(lambda x:x in list(pc),list(catObj.group('cat'))):
                        if WFT+'_'+pc not in finalWFTs.keys():
                            finalWFTs[WFT+'_'+pc]={'per':per,'com':com,'inhrts':[],'cells':[]}
                        if WFT+'.'+cell['cellname'] not in finalWFTs[WFT+'_'+pc]['inhrts']:
                            finalWFTs[WFT+'_'+pc]['inhrts'].append(WFT+'.'+cell['cellname'])
                #End for
        #End for

        if not newWFTs[WFT]['inhrts']:
            WFT_nn[WFT]=newWFTs[WFT]
    #End for
    
    for k in WFT_nn.keys():
        if finalWFTs.has_key(k): continue
        else: finalWFTs[k] = WFT_nn[k]
    
#    pprint.pprint(finalWFTs)
    
    return finalWFTs

#End createWFTables()

class PinGroupConverter(object):
    def getPins(self,item):
        pinlist=[]
        for v in self._extract(item):
            pinlist.append(v)
        #End for
        return pinlist
    #End getPins
    def _extract(self,item2chk):
        if item2chk.strip() not in __allpingroups__:
            yield item2chk
        else:
            for item in __allpingroups__[item2chk.strip()]:
                for v in self._extract(item):
                    yield v
                #End for
            #End for
    #End _extract()
    def getGroups(self,item,srtd_grps):
        plst=item.split(',')
        for g in srtd_grps:
            if g in __xgrps__:continue
            intsct=filter(lambda x:x in plst,__allpingroups__[g])
            diff=filter(lambda x:x not in __allpingroups__[g],plst)
            if intsct and len(intsct)==len(__allpingroups__[g]):
                diff.append(g)
                item=(',').join(diff)
                plst=diff
        #End for
        return item
    #End getGroups()
#End PinGroupConverter()

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __OUTPUT_FILENAME__,__psblcats__
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 2:
        print "usage:",__FILENAME__,__INPUT_FILENAME__,__PINLISTFILENAME__
        sys.exit(-1)
    
    #os.system('clear')
    if __VERBOSE__:
        print '\n\n'
        print __PROGRAM_NAME__
        print __AUTHOR__
        print __DATEMODIFIED__
        print __VERSION__
    print '\n\n'
    
    # Open the file for read only.
    infile = file(args[0], 'r')
    contents = infile.read()
    infile.close()

    pingrpfile = file(args[1], 'r')
    pingrps = pingrpfile.read()
    pingrpfile.close()
    
    __OUTPUT_FILENAME__=args[0]+'.new'
    outfile = open(__OUTPUT_FILENAME__, "w")

    #get pins from input file
    psblcats_patrn = re.compile("//(.*):CAT")
    __psblcats__=psblcats_patrn.findall(contents)

    if __stripcomments__:
        contents=strip(contents,'//')
#        contents=strip(contents,'/*','*/')

    #get pins from input file
    pins_patrn = re.compile("PINS:(?P<pins>.*)")
    pinObj=pins_patrn.search(pingrps)
    pins=eval(pinObj.group('pins'))

    #get groups from input file
    grps_patrn = re.compile("GROUPS:(?P<groups>.*)")
    grpObj=grps_patrn.search(pingrps)
    groups=eval(grpObj.group('groups'))

    ws_patrn = re.compile("(\s*)")
    per_patrn = re.compile("Period(\s*?)\"(?P<per>.*?)\"")
    com_patrn = re.compile("Comment(\s*?)=(\s*?)(.*);")
    inherit_patrn = re.compile("Inherit(?:\s*)(.*?);")
    cell_patrn = re.compile("\nCell(.*)")
    lastbr1_patrn = re.compile("\}(\s*)WaveformTable")
    
    cells_patrn = re.compile("Cell(?P<cell>.*)")
    cellalias_patrn = re.compile("(\s*?)\"(.*?)\" (?P<alias>.*?) ")
    cellname_patrn = re.compile("(\s*?)\"(.*?)\" (.*?) (?P<name>.*?)\{")
    cellcontents_patrn = re.compile("(\s*?)\"(.*?)\" (.*?) (.*?)\{(?P<contents>.*)")
    lastbrace_patrn = re.compile("(\s*?)}(\s*?)}(\s*?)}(\s*?)}")
    qts_patrn = re.compile("\"(?P<quotes>.*?)\"")
    cat_patrn = re.compile("(?P<name>.*?)_cat_(?P<cat>.*)")
    #THIS SHOULD BE UNNECESSARY
    cat2_patrn = re.compile("(?P<name>.*)DSET([01])(?P<cat>.*)")
    inherit_patrn = re.compile("Inherit(?:\s*)(.*?);")

    wftn_patrn = re.compile("([^\{]*)")
    per_patrn = re.compile("Period(\s*?)\"(?P<per>.*?)\"")
    com_patrn = re.compile("Comment(\s*?)=(\s*?)\"(?P<com>.*?)\"")

    contents=contents.replace('\r','')
    contents=contents.replace('\t','')
    contents=contents.replace('\f','')
    contents=contents.replace('\n','')

    wfts=contents.split('WaveformTable')
    #skip everything before 1st 'WaveformTable'
    wfts=wfts[1:]
    
    wftarray=[]
    for wft in wfts:
        wft=wft.strip()
        wft=wft[:-1]
        inhrts=inherit_patrn.findall(wft)
        wft=wft.replace('Cell \"','\nCell\"')
        cells=cell_patrn.findall(wft)
        
        cellarray=[]
        newcellarray=[]
        i=-1
        for cell in cells:
            i+=1
            combo={}

            cellpinlistObj=qts_patrn.search(cell)
            cellpinlist=cellpinlistObj.group('quotes')

            cellaliasObj=cellalias_patrn.search(cell)
            cellalias=cellaliasObj.group('alias')

            cellnameObj=cellname_patrn.search(cell)
            cellname=cellnameObj.group('name')

            cellcontentsObj=cellcontents_patrn.search(cell)
            cellcontents=cellcontentsObj.group('contents')
            #REMOVING WHITESPACE
            cellcontents=re.sub(ws_patrn,'',cellcontents)

            thiscell = {'cellpinlist' :cellpinlist,\
                        'cellalias'   :cellalias,\
                        'cellname'    :cellname,\
                        'cellcontents':cellcontents}
            cellarray.append(thiscell)

            pinlist  = thiscell['cellpinlist'].split('+')
            alias    = thiscell['cellalias']
            name     = thiscell['cellname']
            contents = thiscell['cellcontents']

            ii=-1
            for newcell in cellarray:
                ii+=1
                
                npl = newcell['cellpinlist'].split('+')
                nas = newcell['cellalias']
                nnm = newcell['cellname']
                ncn = newcell['cellcontents']
                if alias==nas and contents==ncn and ii!=i:

                    cat1Obj=cat_patrn.search(name)
                    cat2Obj=cat_patrn.search(nnm)
                    if cat1Obj and cat2Obj:
                        name_name=cat1Obj.group('name').strip()
                        name_cat=cat1Obj.group('cat').strip()
                        nnm_name=cat2Obj.group('name').strip()
                        nnm_cat=cat2Obj.group('cat').strip()
                        name_cat_lst=name_cat.split()
                        if nnm_cat not in name_cat_lst:
                            name_cat='_cat_'+nnm_cat+name_cat
                        else:
                            name_cat='_cat_'+name_cat
                        newname=name_name+name_cat
                    else:
                        newname=name
                    
                    #python2.4 or higher
#                    UNION=set.union(set(pinlist), set(npl))

                    #python2.3 or higher
                    intsct=filter(lambda x:x in pinlist,npl)
                    diff1=filter(lambda x:x not in npl,pinlist)
                    diff2=filter(lambda x:x not in pinlist,npl)
                    UNION=intsct+diff1+diff2
                    
                    combo={'cellpinlist' :'+'.join(UNION),\
                           'cellalias'   :alias,\
                           'cellname'    :newname,\
                           'cellcontents':contents}
                    cellarray[ii]=combo
                    del cellarray[i]
                    i-=1
                #End if
            #End for
        #End for

        wftnObj=wftn_patrn.search(wft)
        perObj=per_patrn.search(wft)
        comObj=com_patrn.search(wft)

        if wftnObj:wftn=wftnObj.group()
        else:wftn=''
        if perObj:per=perObj.group('per')
        else:per=''
        if comObj:com=comObj.group('com')
        else:com=''

        wftarray.append({'wftn':wftn.strip(),'inhrts':inhrts,'per':per.strip(),'com':com.strip(),'cells':cellarray})

    #End for

    mod_wftarray=createWFTables(wftarray)
    ostr=build_actable(mod_wftarray)
    if __VERBOSE__:
        print "SUCCESS!!! NEW FILE CREATED: "+__OUTPUT_FILENAME__
    outfile.write(__EVO_HEADER__)
    outfile.write(ostr)
    outfile.close()
#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
