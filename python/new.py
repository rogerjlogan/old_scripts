import re
import gzip
import string
import sys

def main(fileN):
    print "processing "+ fileN
    for line in open(fileN):
        print "put some code here";break
    return

if __name__ == "__main__":
    if len(sys.argv) <2:
        print "Usage : python " + sys.argv[0] + " <files>"
        sys.exit()
    for fileN in sys.argv[1:]:
        main(fileN)
