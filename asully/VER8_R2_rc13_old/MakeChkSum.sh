#!/bin/csh
cksum *.[ch] >chksum.cksum
#  s/([0-9]) ([0-9]) ([^\.])\.([ch])\n/\#define CKS_\3_\4 \1\n#define FS_\3_\4 \2\n/g

sed -i 's/\([0-9]*\) \([0-9]*\) \([^\.]*\)\.\([ch]\)/\#define CKS_\3_\4 \1LL\n#define FS_\3_\4 \2/' chksum.cksum
