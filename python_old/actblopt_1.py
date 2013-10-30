import sys
import re
#import os
#import inspect
#import string
import pprint

__PROGRAM_NAME__ = "ACTABLE OPTIMIZER"
__AUTHOR__ = "AUTHOR: Roger Logan, LTXCredence Apps Engineer, Houston, TX"
__DATEMODIFIED__ = "LAST MODIFIED: October 22, 2008"
__VERSION__ = "VERSION: 1.0"
__FILENAME__ = "pol2fus.py"
__INPUT_FILENAME__ = "<infile.evo>"
__OUTPUT_FILENAME__ = "<infile.evo>.new"

__EVO_HEADER__ = "enVision:\"bl8:R11.1.0.WW1111:S3.5\"; /* 5.7 */\n\n"
__DEBUG__ = True
__VERBOSE__ = True

__stripcomments__ = False

class TextException(Exception): pass

def lineno():
    """Returns the current line number in our program."""
    return inspect.currentframe().f_back.f_lineno
#End lineno()

def build_actable(wftarray):

    ostr=''
    for wft in wftarray:
        wftn=wft['wftn'].strip()
        per=wft['per'].strip()
        com=wft['com'].strip()
        inhrt_str=''
        for inhrt in wft['inhrts']:
            inhrt_str+='\n\tInherit '+inhrt+';'

        ostr+="WaveformTable "+wftn+" {\n\tPeriod \""+per+"\";\n\tComment = \""+com+"\";"+inhrt_str+"\n"
        
        for cell in wft['cells']:
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
  else:
    # THIS IS A SINGLELINE STRING - NO NEED TO CHECK BEYOND NEWLINE
    patrn = re.compile("("+es_delim_st+"(?:.*))")
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
  return string
#End strip()

def modifyInherits(wftarray):

    for wft in wftarray:
        print wft
        sys.exit(-1)


#End modifyInherits()

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __OUTPUT_FILENAME__
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 1:
        print "usage: "+__FILENAME__+" "+__INPUT_FILENAME__
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
    
    __OUTPUT_FILENAME__=args[0]+'.new'
    if __DEBUG__:print '__OUTPUT_FILENAME__ : ',__OUTPUT_FILENAME__
    outfile = open(__OUTPUT_FILENAME__, "w")

    if __stripcomments__:
        contents=strip(contents,'//')
        contents=strip(contents,'/*','*/')

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
                        newname=name_name+name_cat
                    else:
                        newname=name

                    UN=set.union(set(pinlist), set(npl))
                    combo={'cellpinlist' :'+'.join(UN),\
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
    
        wftarray.append({'wftn':wftn,'inhrts':inhrts,'per':per,'com':com,'cells':cellarray})

    #End for
    wftarray=modifyInherits(wftarray)
    ostr=build_actable(wftarray)

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
