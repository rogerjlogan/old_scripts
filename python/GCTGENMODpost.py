"""
    Requirements:
        - Python2.3 or higher
        - Must have global_defs.py in current directory
        - Run GCTGENMODsetup.py
            - globalvars.proc must be present from GCTGENMODsetup.py output
        - Run GCT_GEN_MOD6 (or later version)
            - waveform table input file <Waveforms_GCTGENMOD6.evo> must come from GCT_GEN_MOD6 (or later version)
    Function:
        Creates <Waveforms_GCTGENMOD6.evo>.new from input file: <Waveforms_GCTGENMOD6.evo>
        Compacts cells and creates duplicate waveform tables that use inheritance.
        Each newly created waveform table ends with ..._cat_AAAAAAA where 'AAAAAAA'
        is a string of capital letters indicating the category in the ACSpec (acdata.evo)
        that should be used with the given waveform table.
"""
__progfile__ = "GCTGENMODpost.py"
__version__ = "v1.0"
__author__ = "AUTHOR: Roger Logan, LTXCredence Apps Engineer, Houston, TX"
__date__ = "LAST MODIFIED: December 18, 2008"

import sys
import re
import pprint

from global_defs import *

__ACTABLE_IFILE__ = "<Waveforms_GCTGENMOD6.evo>"
__ACTABLE_OFILE__ = "<Waveforms_GCTGENMOD6.evo>.new"

__STAGE1_FILE__ = "GCTGENMODsetup.py"
__GLOBALVARS_IFILE__ = "globalvars.proc"
__GLOBALVARS_ERROR__ = "'"+__GLOBALVARS_IFILE__+"' is corrupted, unreadable, or not present.\n"
__GLOBALVARS_ERROR__ += "You must run "+__STAGE1_FILE__+" and/or change permissions to read for "+__GLOBALVARS_IFILE__

__EVHDR__ = "enVision:\"bl8:R11.1.0.WW1111:S3.5\"; /* 5.7 */\n\n"
__VERBOSE__ = False
__STRIP_COMMENTS__ = True
__USE_GROUPS__ = True

def build_actable(WFTs):
    
    WFTkeys=sortDictkeys(WFTs)
    
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

def createWFTables(wftarray,psblcats):
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
        for cell in cells:
            catObj=cat_patrn.search(cell['cellname'])
            if catObj:
                for pc in psblcats:
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
    #End for
    return finalWFTs
#End createWFTables()

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __ACTABLE_OFILE__
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 1:
        err="\nusage: python "+__progfile__+" "+__ACTABLE_IFILE__+"\n"
        sys.exit(err)
    
    if __VERBOSE__:
        print '\n\n'
        print __progfile__,__version__
        print __author__
        print __date__
    print '\n'
    
    # Open the file for read only.
    infile = file(args[0], 'r')
    contents = infile.read()
    infile.close()
    try:
        apex = Ddict( dict )
        glblvarsfile = file(__GLOBALVARS_IFILE__, 'r')
        glblvars = glblvarsfile.read()
        glblvarsfile.close()
        #get pins from input file
        pins_patrn = re.compile("PINS:(?P<pins>.*)")
        pinObj=pins_patrn.search(glblvars)
        apex['pins']=eval(pinObj.group('pins'))
        #get muxpins from input file
        muxpins_patrn = re.compile("MUXPINS:(?P<muxpins>.*)")
        muxpinObj=muxpins_patrn.search(glblvars)
        apex['muxpins']=eval(muxpinObj.group('muxpins'))
        #get groups from input file
        grps_patrn = re.compile("GROUPS:(?P<groups>.*)")
        grpObj=grps_patrn.search(glblvars)
        apex['groups']=eval(grpObj.group('groups'))
        #get excluded groups from input file
        xgrps_patrn = re.compile("XGROUPS:(?P<xgroups>.*)")
        xgrpObj=xgrps_patrn.search(glblvars)
        apex['xgroups']=eval(xgrpObj.group('xgroups'))
        #get sorted group list from input file
        srtdgrps_patrn = re.compile("SRTDGRPS:(?P<srtdgrps>.*)")
        srtdgrpsObj=srtdgrps_patrn.search(glblvars)
        apex['srtdgrps']=eval(srtdgrpsObj.group('srtdgrps'))
    except:
        sys.exit(stop(__GLOBALVARS_ERROR__))

    #REPLACE ALL INSTANCES OF 'MUXPIN' WITH 'MUXPIN','MUXPINm'
    apex_str=str(apex)
    for muxpin in apex['muxpins']:
        apex_str=apex_str.replace("\'"+muxpin+"\'","\'"+muxpin+"\',"+" \'"+muxpin+"m\'")
    apex=eval(apex_str)

    __ACTABLE_OFILE__=args[0]+'.new'
    actofile = open(__ACTABLE_OFILE__, "w")

    #get pins from input file
    psblcats_patrn = re.compile("//(.*):CAT")
    psblcats=psblcats_patrn.findall(contents)

    if __STRIP_COMMENTS__:
        contents=stripcom(contents,'//')

    #define regex patterns for later use in script
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

#############################################################################
#       'cells' is now a list of strings:
#           cells = [
#                '"cellpinlist" cellalias cellname cellcontents',
#                '"cellpinlist" cellalias cellname cellcontents',
#                ....
#                ....
#                '"cellpinlist" cellalias cellname cellcontents'
#           ]
#       Example:
#           cells = [
#               '"ALLPINS" d CPM_CALLING_DPM {Data 3 Other;Drive {EntryState DriveOn;}}',
#               '"ALLPINS" - HOLD_STATE {Data 6;Drive {EntryState DriveOn;}}',
#               ...
#               ...
#               '"NMI_" y/Y ALLoffWF_DSET0yY_cat_DJQRSTUVW {Data 2/3;Drive {Waveform {DriveOff @"  tref ";}}}'
#           ]
#############################################################################
        conv=PinGroupConverter()
        cellarray,newcellarray,i=[],[],-1
        cellnames=[]
        for cell in cells:
            i+=1
            combinedcells={}

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
            
            #ADD CURRENT ALIAS TO NAME (BEFORE '_cat_')
            cnameObj=cat_patrn.search(cellname)
            if cnameObj:
                cname=cnameObj.group('name')
                cat=cnameObj.group('cat')
                aliaschars=cellalias.replace('/','')
                aliaschars=aliaschars.replace('.','dot')
                aliaschars=aliaschars.replace(',','comma')
                aliaschars=aliaschars.replace('-','dash')
                cellname=cname+'_alias_'+aliaschars+'_cat_'+cat

            thiscell = {'cellpinlist' :cellpinlist,\
                        'cellalias'   :cellalias,\
                        'cellname'    :cellname,\
                        'cellcontents':cellcontents}
            cellarray.append(thiscell)


            pinlist  = thiscell['cellpinlist'].split('+')
            alias    = thiscell['cellalias']
            name     = thiscell['cellname']
            contents = thiscell['cellcontents']

#############################################################################
#           'cellarray' is now a list of dictionaries
#           Example:
#               cellarray = [
#                   {   'cellalias' : 'd',
#                    'cellcontents' : 'Data3Other;Drive{EntryStateDriveOn;}}',
#                        'cellname' : 'CPM_CALLING_DPM ',
#                     'cellpinlist' : 'ALLPINS' },
#                   {   'cellalias' : '-',
#                    'cellcontents' : 'Data6;Drive{EntryStateDriveOn;}}',
#                        'cellname' : 'HOLD_STATE ',
#                     'cellpinlist' : 'ALLPINS' },
#                    ...
#                    ...
#                   {   'cellalias' : 'y/Y',
#                    'cellcontents' : 'Data2/3;Drive{Waveform{DriveOff@"tref";}}}',
#                        'cellname' : 'ALLoffWF_DSET0yY_cat_DJQRSTUVW ',
#                     'cellpinlist' : 'X2CLKIN' }
#               ]
#############################################################################
            ii=-1
            for newcell in cellarray:
                ii+=1
#############################################################################
#               Comparing cells to cells for compaction.
#               OUTER LOOP VARS-------INNER LOOP VARS
#               pinlist---------------npl
#               alias-----------------nas
#               name------------------nnm
#               contents--------------ncn
#############################################################################
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
                        
                        CATUNION=getUnion(name_cat,nnm_cat)

                         #convert to list for sorting, then re-combine into str, and uniqify
                        CATUNION=unique(''.join([x for x in sorted(list(CATUNION))]))
                        
                        newname=name_name+'_cat_'+CATUNION
                    #End if

                    PLUNION=getUnion(pinlist,npl)
                    PLUNION=unique(PLUNION)

                    combinedcells={'cellpinlist' :'+'.join(PLUNION),\
                           'cellalias'   :alias,\
                           'cellname'    :newname,\
                           'cellcontents':contents}
                    cellarray[ii]=combinedcells
                    #remove and decrement
                    del cellarray[i];i-=1
                #End if
            #End for
        #End for
        
        if __USE_GROUPS__:
            i=-1
            for cell in cellarray:
                i+=1
                plst=conv.getGroups(cell['cellpinlist'].split('+'),apex)
                cellarray[i]['cellpinlist']='+'.join(plst)
            #End for

        #get the wft name,period, and comments from wft string 
        # (see regex patterns defined above loops)
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

    mod_wftarray=createWFTables(wftarray,psblcats)
    ostr=build_actable(mod_wftarray)
    if __VERBOSE__:
        print "SUCCESS!!! NEW FILE CREATED: "+__ACTABLE_OFILE__
    actofile.write(__EVHDR__)
    actofile.write(mkHeader(__progfile__,__version__,__author__,'//'))
    actofile.write(ostr)
    actofile.close()
#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
