import re
import pprint

def union(a,b):
    intsct=filter(lambda x:x in a,b)
    diff1=filter(lambda x:x not in b,a)
    diff2=filter(lambda x:x not in a,b)
    return intsct+diff1+diff2
#End union()

# s = "a{{ a } { b \
#  { { { c } } {another level {and one more}}}} }"
# regex=re.compile(r'({(?:[^{}]*)})',re.DOTALL)
# matches = [m.start() for m in regex.finditer(s)]
# print matches
# print regex.findall(s)
# 
# ss = "a(*( a *)d (** b *) (* (* (* \
# x *)d*) *) *) *)"
# 
# regex=re.compile(r'(\(\*[^\*]*\*\))',re.DOTALL)
# Lindeces = [m.start() for m in regex.finditer(ss)]
# Lstrings = regex.findall(ss)
# 
# regex=re.compile(r'(\(\*[^\(\)]*\*\))',re.DOTALL)
# Rindeces = [m.start() for m in regex.finditer(ss)]
# Rstrings = regex.findall(ss)
# 
# 
# print union(Lindeces,Rindeces)
# print union(Lstrings,Rstrings)

def getLowest(s,l,r=0):
    
    if r:
        if len(l) != len(r):
            raise ValueError("Delimiters do not match!")
        elif len(l) > 2:
            raise ValueError("Delimiters out of range! (max length should be two)")
        elif len(l) == 2:

            l1 = re.escape(l[0])
            l2 = re.escape(l[1])
            r1 = re.escape(r[0])
            r2 = re.escape(r[1])

            regexStr = "("+l1+l2+"[^"+l2+r1+"]*"+r1+r2+")"
            regex=re.compile(regexStr,re.DOTALL)
            innerI = [m.start() for m in regex.finditer(s)]
            innerS = regex.findall(s)

            regexStr = "("+l1+l2+"[^"+l1+r2+"]*"+r1+r2+")"
            regex=re.compile(regexStr,re.DOTALL)
            outerI = [m.start() for m in regex.finditer(s)]
            outerS = regex.findall(s)
            
            print union(innerI,outerI)
            print union(innerS,outerS)
        else:#len(l)=1
            l1 = re.escape(l)
            r1 = re.escape(r)
            regexStr = "("+l1+"(?:[^"+l1+r1+"]*)"+r1+")"
            regex=re.compile(regexStr,re.DOTALL)
            print [m.start() for m in regex.finditer(s)]
            print regex.findall(s)
            
            
            
        
        

#def stripComments(s,l,r=0):
#    lowest = getLowest(s,l,r=0)
#    for ss in lowest:
    
        
def main():

    s = "a{{ a } { b \
     { { { c } } {another level {and one more}}}} }"
    regex=re.compile(r'({(?:[^{}]*)})',re.DOTALL)
    matches = [m.start() for m in regex.finditer(s)]
#    print matches
#    print regex.findall(s)

    ss = "a(*( a *)d (** b *) (* (* (* \
 x *)d*) *) *) *)"

#     regex=re.compile(r'(\(\*[^\*]*\*\))',re.DOTALL)
#     Lindeces = [m.start() for m in regex.finditer(ss)]
#     Lstrings = regex.findall(ss)
# 
#     regex=re.compile(r'(\(\*[^\(\)]*\*\))',re.DOTALL)
#     Rindeces = [m.start() for m in regex.finditer(ss)]
#     Rstrings = regex.findall(ss)

    getLowest(s,"{","}")
    getLowest(ss,"(*","*)")


if __name__ == '__main__':
    main()
