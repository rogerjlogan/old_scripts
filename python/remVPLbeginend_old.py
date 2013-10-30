import sys
import re
import pprint
import os
import fileinput
import bisect

class Ddict(dict):
    def __init__(self, default=None):
        self.default = default
    def __getitem__(self, key):
#        if not self.has_key(key):
        if key not in self.keys():
            self[key] = self.default()
        return dict.__getitem__(self, key)
#End Ddict()
def find_all(a_str, sub):
    start = 0
    while True:
        start = a_str.find(sub, start)
        if start == -1: return
        yield start
        start += len(sub)
#End find_all()
def main():
    args = sys.argv[1:]
    if len(args) != 1:
    	print("usage: python beginend.py <inputfile>")
    	sys.exit(-1)
    try:
        with open(args[0]) as f:content = f.read()
    except FileNotFoundError:
        print(args[0]+" file is missing")
    except PermissionError:
    	print("You are not allowed to read "+args[0])
                                                 
#    infile = file(args[0], 'r')
#    content = infile.read()
#    infile.close()

    begin_index = list(find_all(content,'begin'))
    end_index = list(find_all(content,'end;'))
    nl_index = list(find_all(content,'\n'))
    nl_index.sort()
    if len(begin_index) != len(end_index):
        print ("FATAL ERROR:Unbalanced begin/end;")
        print ("# of begin => "+str(len(begin_index)))
        print ("# of end;  => "+str(len(end_index)))
        exit()
    #End if

    begins_ends = Ddict( dict )
    prevLines = Ddict( dict )
    for i,be in enumerate(zip(begin_index,end_index)):
        b,e=be[0],be[1]
        begins_ends[b]='begin'
        begins_ends[e]='end;'
        temp = bisect.bisect(nl_index,b-2)
        if temp==0:
            prevLines[b]=0
        else:
            prevLines[b]=nl_index[temp-1]
    #End for
#    keylist = begins_ends.keys()
#    keylist.sort()
    grps,begins=[],[]
    for k in sorted(begins_ends.keys()):
        v = begins_ends[k]
        if v=='begin':
            begins.append(k)
        elif v=='end;':
            grps.append((begins.pop(),k))
    #End for

    #finalize groups of begin/end; pointers (sort by 1st pointer)
    grps.sort(key=lambda tup:tup[0])

    i,l=0,0
    repeatlines = Ddict( dict )
    for line in content.splitlines(True): #using splitlines() instead of split() to preserve '\n' for file pointer
        l+=1          #increment line count
        i+=len(line)  #increment file pointer
        if 'repeat' in line:
            repeatlines[l]=(i-len(line),i) #record start and stop of file pointer for line with 'repeat'
    #End for
    repeats_with_beginend = []
    for k in sorted(repeatlines.keys()):
        #looking for repeats followed by begin (basically if 2nd ptr in repeat lines == 1st ptr in grps)
        repeats_with_beginend += ([item for item in grps if item[0] == repeatlines[k][1]])
#        repeats_with_beginend = filter(None,repeats_with_beginend) #delete blanks (python 2.X and below)


    print(grps)
    print(repeats_with_beginend)
    exit()

    newcontent=content
#this is too much of a memory hog
#    for x,y in iter(grps):
#       if not len([(a,b) for a,b in repeats_with_beginend if x==a or y==b]):
#           newcontent=newcontent[:x]+'     '+newcontent[x+5:y]+'    '+newcontent[y+4:]

#much more efficient
#first we save begins/ends that we want to keep
    for x,y in iter(repeats_with_beginend):
        newcontent=newcontent[:x]+'BBBBB'+newcontent[x+5:y]+'EEEE'+newcontent[y+4:]
#delete all begin/end that remain (the vast majority)
    newcontent=newcontent.replace('begin','     ')
    newcontent=newcontent.replace('end;','    ')
#now let's put back the begin/end we wanted to keep
    newcontent=newcontent.replace('BBBBB','begin')
    newcontent=newcontent.replace('EEEE','end;')
    
    ofileArray = args[0].split('.')
    ofile = ofileArray[0]+'_mod.'+ofileArray[1]
    outfile = open(ofile, "w")
    outfile.write(newcontent)
    outfile.close()

    print ("SUCCESS!!! NEW FILE CREATED: "+ofile)
    print ("WARNING!!! Check file to replace 'begin' and 'end;' where you still need them")
    print ("           such as the top and bottom of file.")


#End main()

if __name__ == '__main__':
    main()
