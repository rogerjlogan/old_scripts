import time
localtime = time.asctime(time.localtime(time.time()))
start_time = time.time()
_file_header_=\
"""
#   Script File Name: wvt_fus2dvc.py
#   Author: Roger Logan
#   Version: 1.0
#   Property of Anora, LLC
#   Script Run Date:"""+localtime+"""
#   Description: Converts multiple WaveformTable's to 93k dvc's (Fusion to 93k)
"""
import re
import gzip
import string
import sys
import getopt
import commands
from pprint import pprint as pprint
import inspect
def lineno():
    """Returns the current line number in our program."""
    return inspect.currentframe().f_back.f_lineno


#this is needs to be dynamic, but this will do for now
_char_switch_={}
_char_switch_['L']='0'
_char_switch_['H']='1'
_char_switch_['0']='L'
_char_switch_['1']='H'
_char_switch_['M']='X'
_char_switch_['Y']='0'

_93k_chars_={}
_93k_chars_['DriveOff']     = 'Z'
_93k_chars_['DriveLow']     = '0'
_93k_chars_['DriveHigh']    = '1'
_93k_chars_['CompareLow']   = 'L'
_93k_chars_['CompareHigh']  = 'H'
_93k_chars_['CompareFloat'] = 'M'
_93k_chars_['NoAction']     = '{}'


_data_key_={}
_data_key_['DriveData']       ={};_data_key_['DriveData']       ['6']='DriveLow'   ;_data_key_['DriveData']       ['7']='DriveHigh'
_data_key_['DriveDataNot']    ={};_data_key_['DriveDataNot']    ['6']='DriveHigh'  ;_data_key_['DriveDataNot']    ['7']='DriveLow'
_data_key_['DriveHighIfOne']  ={};_data_key_['DriveHighIfOne']  ['6']='NoAction'   ;_data_key_['DriveHighIfOne']  ['7']='DriveHigh'
_data_key_['DriveLowIfZero']  ={};_data_key_['DriveLowIfZero']  ['6']='DriveLow'   ;_data_key_['DriveLowIfZero']  ['7']='NoAction'
_data_key_['CompareData']     ={};_data_key_['CompareData']     ['0']='CompareLow' ;_data_key_['CompareData']     ['1']='CompareHigh'
_data_key_['CompareDataNot']  ={};_data_key_['CompareDataNot']  ['0']='CompareHigh';_data_key_['CompareDataNot']  ['1']='CompareLow'
_data_key_['CompareHighIfOne']={};_data_key_['CompareHighIfOne']['0']='NoAction'   ;_data_key_['CompareHighIfOne']['1']='CompareHigh'
_data_key_['CompareLowIfZero']={};_data_key_['CompareLowIfZero']['0']='CompareLow' ;_data_key_['CompareLowIfZero']['1']='NoAction'
_data_key_['CompareOpenData'] ={};_data_key_['CompareOpenData'] ['0']='CompareLow' ;_data_key_['CompareOpenData'] ['1']='CompareHigh'
_data_key_['CompareClose']    ={};_data_key_['CompareClose']    ['0']='NoAction'   ;_data_key_['CompareClose']    ['1']='NoAction'
_valid_edgenames_ = [\
    'NoAction',\
    'DriveData',\
    'DriveDataNot',\
    'DriveHigh',\
    'DriveLow',\
    'DriveOff',\
    'DriveOn',\
    'DriveHighIfOne',\
    'DriveLowIfZero',\
    'CompareData',\
    'CompareDataNot',\
    'CompareFloat',\
    'CompareLow',\
    'CompareHigh',\
    'CompareWindowOpen',\
    'CompareClose',\
    'CompareOpenFloat',\
    'CompareOpenFloatNot',\
    'CompareOpenHigh',\
    'CompareOpenLow',\
    'CompareOpenData',\
    'CompareHighIfOne',\
    'CompareLowIfZero']

_debug_ = False
_pins_         = [] # list of all pins from adapterboard
_pingroups_    = {} # dict of pingroups and their pins (all elements reduced to pins.. not other pingroups)
_defwvt_name_ = '' # name of default waveformtable if found
_defwvt_       = {} # default waveformtable (denoted by double name)
_wvts_        = {} # all nondefault-wavetables to be converted and their elements

pinPtrn = re.compile("Pin\s*\{\s*Name\s*=\s*(?P<pin>\w+)\s*;")
def getPins(content,fileN):
    global _pins_
    _pins_ = list(set(pinPtrn.findall(content))) # make pins unique (in case more than one adapterboard was passed)
    if not len(_pins_):
        sys.exit("ERROR !!! No pins found in "+fileN+" Exiting ! ...")
#End getPins()

pgPtrn = re.compile("PinGroup\s+(?P<pgname>\w+)\s*\{\s*Group\s*=\s*Expr\s*\{\s*String\s*=\s*\"\s*(?P<pins>.*?)\s*\";\s*\}\s*\}",re.DOTALL)
def getPinGroups(content,fileN):
    global _pingroups_
    groupLst=pgPtrn.findall(content)
    if not len(groupLst):
        sys.exit("ERROR !!! No pingroups found in "+fileN+" Exiting ! ...")
    rawgroups = {}
    for pg,rawpins in groupLst:
        rawgroups[pg]=rawpins
    _pingroups_=dict.fromkeys(rawgroups, '')
    for pg in rawgroups:
        _pingroups_[pg]=[]
        elems = re.sub(r'\s*([\+-])\s*',r',\1',rawgroups[pg].strip()).split(',')
        for n,elem in enumerate(elems):
            elem = elem.strip()
            if not len(elem):continue
            if elem[0]=='-':
                print "\nWARNING !!! Subtraction found in pingroup:",pg,"! You should convert this group by hand !"
                continue
            elif elem[0]=='+':
                _pingroups_[pg].append(elem[1:])
            else:
                _pingroups_[pg].append(elem)
#End getPinGroups()

def getPinsFromGroups(pg):
    """
    this is pretty rudimentary... need a recursive algorithm here
    """
    if pg in _pingroups_:
        return ' '.join(_pingroups_[pg])
    else:
        return pg
#End getPinsFromGroups()

cellhdrPtrn = re.compile(r'\"\s*(?P<pins>\S+)\s*"\s+(?P<chars>\S+)\s+(?P<cellname>\w+)')
cellPtrn = re.compile(r'\bCell\b')
drivePtrn = re.compile(r'\bDrive\b')
commPtrn = re.compile(r'\bComment\b\s*=\s*\"(?P<comment>.*?)\"\s*;',re.DOTALL)
drvcmpPtrn = re.compile(r'(?P<edgetype>Drive|Compare)\s*\{\s*Waveform\s*\{(?P<edgedata>.*?)\}',re.DOTALL)
edgePtrn = re.compile(r'(?P<edgename>\w+)\s*@\s*\"\s*(?P<edgetime>.*?)\s*\"',re.DOTALL)
perPtrn = re.compile(r'\bPeriod\b\s+\"(?P<period>.*?)\"\s*;',re.DOTALL)
dataPtrn = re.compile(r'\bData\b\s+(?P<data>\S+)\s*;')
inheritPtrn = re.compile(r'\bInherit\b\s+(?P<inherit>\S+)\s*;')
celldataPtrn = re.compile(r'(?P<cellname>\S+)\s*\{\s*Data\s*(?P<data>\S+)\s*;',re.DOTALL)
def getWaves(content,fileN):
    global _wvts_
    def getDelimContents(string,st_delim='{',sp_delim='}'):
        """Get contents of delimiters even if nested"""
        stack = []
        start,started = 0,False
        itemname=''
        for i, c in enumerate(string):
            if not started and c != st_delim:
                itemname+=c
            elif c == st_delim:
                if not started:
                    start=i
                    started = True
                stack.append(i)
            elif c == sp_delim and stack:
                stack.pop()
            elif not stack: # we must be done
                break
        return itemname.strip(),i,string.strip()[start-1:i] # let's include delims in return
    #End getDelimContents()
    def getAll(objname,string,named=True):
        global _defwvt_name_
        _string=string
        items={}
        while True:
            i = _string.find(objname)
            if i==-1:break
            str2chk = _string[i+len(objname):]
            itemname,stopi,itemcontent = getDelimContents(str2chk)
            if not len(itemname) and named:break
            elif not named:itemname=objname
            if objname == 'WaveformTable' and ' ' in itemname:
                name1,name2 = itemname.split()
                name1,name2 = name1.strip(),name2.strip()
                if name1 == name2:
                    _defwvt_name_ = name1+'__'+name2
                    itemname = _defwvt_name_
                else:
                    sys.exit("\n\nERROR !!! Bad WaveformTable name found ! \""+itemname+"\" Exiting ...")
            items[itemname]=itemcontent
            _string=_string[stopi:]
        return items
    #End getAll()
    def getData(celltop):
        data = ''
        dataObj = dataPtrn.search(celltop)
        inheritObj = inheritPtrn.search(celltop)
        if dataObj:
            data = dataObj.group('data')
        elif inheritObj and len(_defwvt_name_):
            name,cell = inheritObj.group('inherit').split('.')
            if name != _defwvt_name_:
                sys.exit("\n\nERRROR !!! Unknown inherit statement ! Currently only supports inherits of Default WaveformTable ! Exiting ...")
            data = _defwvt_[cell]
        return data
    #End getData()
    def parseWaveTop(wavetop):
        comment,period = '',''
        commObj = commPtrn.search(wavetop)
        if commObj:
            comment = commObj.group('comment')
        perObj = perPtrn.search(wavetop)
        if perObj:
            period = perObj.group('period')
        return comment,period.strip()
    #End parseWaveTop()
    def parseDefWvt(wvt):
        global _defwvt_
        dataObj = celldataPtrn.findall(wvt)
        for name,data in dataObj:
            _defwvt_[name] = data
    #End parseDefWvt()
    def getEdges(string):
        edges={}
        drvcmpObj = drvcmpPtrn.findall(string)
        for edgetype,edgecontent in drvcmpObj:
            edges[edgetype]=[]
            for edge in edgecontent.split(';'):
                edgeObj = edgePtrn.search(edge)
                if edgeObj:
                    edgename = edgeObj.group('edgename').strip()
                    edgetime = edgeObj.group('edgetime').strip()
                    if edgename not in _valid_edgenames_:
                        sys.exit("\n\nERROR !!! Unknown edgetype found:"+edgetype+" ! Exiting ...")
                    elif edgename == 'DriveOn':continue
                    edges[edgetype].append((edgename,edgetime))
        return edges
    #Emd getEdges()
    
    ######################
    #   getWaves() START
    ######################
    
    waves = getAll('WaveformTable',content)
    if len(_defwvt_name_):
        parseDefWvt(waves[_defwvt_name_])
    for wvt in waves:
        if wvt == _defwvt_name_:continue
        _wvts_[wvt]={}
        wavebody=waves[wvt]
        wavetopObj = cellPtrn.search(wavebody)
        wavetop=wavebody[1:wavetopObj.start()].strip()
        comment,period = parseWaveTop(wavetop)
        _wvts_[wvt]['comment']=comment
        _wvts_[wvt]['period']=period
        _wvts_[wvt]['cells']={}
        if not len(period) and wvt != _defwvt_name_:
            sys.exit("\n\nERROR !!! No \"Period\" found in WaveformTable: "+wvt+" ! Exiting ...")
        cells = getAll('Cell',waves[wvt])
        for cellhdr in cells:
            cellbody = cells[cellhdr]
            celltopObj = drivePtrn.search(cellbody)
            cellhdrObj = cellhdrPtrn.search(cellhdr)
            if not cellhdrObj:
                sys.exit("\n\nERROR !!! Unknown syntax in WaveformTable: "+wvt+" ! Exiting ...")
            celltop=cellbody[1:celltopObj.start()].strip()
            data = getData(celltop)
#            drivebody = getAll('Drive',cellbody,False)
#            comparebody = getAll('Compare',cellbody,False)
            edges = getEdges(cellbody)
            pins = cellhdrObj.group('pins').strip()
            chars = cellhdrObj.group('chars').strip()
            
            if pins not in _wvts_[wvt]['cells']:
                _wvts_[wvt]['cells'][pins]={}
            
            for i,char in enumerate(chars.split('/')):
                char=char.strip()
                if char not in _wvts_[wvt]['cells'][pins]:
                    _wvts_[wvt]['cells'][pins][char]={}
                thisdata=data.split('/')[i]
                _wvts_[wvt]['cells'][pins][char]['data']=thisdata
                assert 'Drive' in edges
                _wvts_[wvt]['cells'][pins][char]['action']={}
                newedge={}
                for d,edge in enumerate(edges['Drive']):
                    numdrives=d+1
                    newedge={}
                    if edge[0] in _data_key_:
                        newedge=(_data_key_[edge[0]][thisdata],edge[1])
                    else:
                        newedge=edge
                    _wvts_[wvt]['cells'][pins][char]['action'][d]=newedge
                if 'Compare' in edges:
                    if numdrives != 1:
                        sys.exit("\n\nERROR !!! Unknown syntax in WaveformTable: "+wvt+" ! Exiting ...")
                    for r,edge in enumerate(edges['Compare']):
                        if edge[0] in _data_key_:
                            newedge=(_data_key_[edge[0]][thisdata],edge[1])
                        else:
                            newedge=edge
                        _wvts_[wvt]['cells'][pins][char]['action'][r+numdrives]=newedge
                        #data_that_needs_convert
    if _debug_:pprint(_wvts_)
#End getWaves()

def createDVCs():
    for wvt in _wvts_:
        dvcfile = open(wvt+'.dvc','w')
        dvcfile.write('SPECS \"spec_'+wvt+'\"\n')
        dvcfile.write('per    '+_wvts_[wvt]['period']+'\n')
        dvcfile.write('########################################################\n')
        dvcfile.write('DVC wvt_'+wvt+'\n')
        dvcfile.write('########################################################\n')
        dvcfile.write('#'+_wvts_[wvt]['comment'].replace('\n','\n#')+'\n')
        dvcfile.write('period = per\n')
        for pins in _wvts_[wvt]['cells']:
             dvcfile.write('\n# '+pins+'\n')
             dvcfile.write('PINS '+getPinsFromGroups(pins)+'\n')
             for char in _wvts_[wvt]['cells'][pins]:
                comment = ' # '+char
                if char in _char_switch_:
                    string='    '+_char_switch_[char]+' '
                else:
                    string='    '+char+' '
                for i in _wvts_[wvt]['cells'][pins][char]['action']:
                    event = _wvts_[wvt]['cells'][pins][char]['action'][i][0]
                    time = _wvts_[wvt]['cells'][pins][char]['action'][i][1]
                    comment+=' '+event+':'+time
                    string+=_93k_chars_[event]+':'+time+' '
                dvcfile.write(string+comment+'\n')
        dvcfile.close()
#End createDVCs()

def main(argv):
    global _debug_
    def usage():
        usgstr = """\
        \n\n\tMake sure each file only contains objects that you need.
                Note 1:Comments will be auto-stripped from each file.
                Note 2: if wavetables in separate files, then concatenate all wavetables to be converted into one file
                    Example: cat ./wavetables/*evo > wavetables.evo
                Note 3: if Default WaveformTable (denoted by double name) is needed, include it in actable.evo.
                        Often, this object is located in cycletbl.evo.
                        The double name is changed to name__name when used in Inherit statements in other WaveformTable's.
                
                Usages: (order doesn't matter - just keep paired items together .. ie: -d device.evo)
                   python """+sys.argv[0]+""" [opt_opt] [req_opt1] arg1 [req_opt2] arg2 [req_opt3] arg3
                Optional Options [opt_opt]:
                    -h, --help                                  show this help message and exit
                    --debug                                     make lots of noise (default is off)
                Required Options [req_optX]:
                    -d device.evo,  --device=device.evo         looking for at least one "Adapterboard" object to get list of all the pins
                    -p pinlist.evo, --pinlist=pinlist.evo       looking for all "PinGroup" objects and their pins
                    -a actable.evo, --actable=actable.evo       looking for all "WaveformTable" objects to be converted
                Examples:
                   python """+sys.argv[0]+""" -h
                   python """+sys.argv[0]+""" -d device.evo -p pinlist.evo -a actable.evo
                   python """+sys.argv[0]+""" --pinlist=pinlist.evo --device=device.evo --actable=actable.evo
                   python """+sys.argv[0]+""" -a actable.evo -p pinlist.evo -d device.evo --debug
        \n\n"""
        print usgstr
        sys.exit(2)
    #End usage()
    def getContents(fileN,strip_comments=True):
        """
        returns contents of file stripped of C type comments (default) or without being stripped
        """
        if strip_comments:# pass file through C compiler to strip comments
            contents = commands.getoutput("sed 's/a/aA/g;s/__/aB/g;s/#/aC/g' "+fileN+" |\
                                           gcc -P -E - | \
                                           sed 's/aC/#/g; s/aB/__/g;s/aA/a/g'");
        else:
            infile = open(fileN)
            contents = infile.read()
            infile.close()
        return contents
    #End getContents()
    try:
        opts, args = getopt.getopt(argv, 'hd:p:a:', ['help', 'device=', 'pinlist=', 'actable=', 'debug'])
        if not opts or len(opts)<3:usage()
    except getopt.GetoptError:usage()
    for opt, arg in opts:
        if opt in ('-h', '--help'):usage()
        elif opt == '--debug':
            _debug_ = True
    for opt, arg in opts:
        if opt in ('-d', '--device'):
            getPins(getContents(arg),arg)       # populate _pins_
        elif opt in ('-p', '--pinlist'):
            getPinGroups(getContents(arg),arg)  # populate _pingroups_
        elif opt in ('-a', '--actable'):
            getWaves(getContents(arg),arg)      # populate _wvts_ and _defwvt_/_defwvt_name_  if found
    createDVCs()
#End main()

if __name__ == "__main__":
    print _file_header_
    main(sys.argv[1:])
    print "\nScript took",time.time() - start_time, "seconds"

