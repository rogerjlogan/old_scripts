#!/bin/csh
cksum *vcp*.[ch] >chksum_vcp.ncksum
#  s/([0-9]) ([0-9]) ([^\.])\.([ch])\n/\#define CKS_\3_\4 \1\n#define FS_\3_\4 \2\n/g

sed -i 's/\([0-9]*\) \([0-9]*\) \([^\.]*\)\.\([ch]\)/\#define CKS_\3_\4 \1LL\n#define FS_\3_\4 \2/' chksum_vcp.ncksum
cksum *vcs*.[ch] >chksum_vcs.ncksum
#  s/([0-9]) ([0-9]) ([^\.])\.([ch])\n/\#define CKS_\3_\4 \1\n#define FS_\3_\4 \2\n/g

sed -i 's/\([0-9]*\) \([0-9]*\) \([^\.]*\)\.\([ch]\)/\#define CKS_\3_\4 \1LL\n#define FS_\3_\4 \2/' chksum_vcs.ncksum
cksum *appn*.[ch] >chksum_appn.ncksum
#  s/([0-9]) ([0-9]) ([^\.])\.([ch])\n/\#define CKS_\3_\4 \1\n#define FS_\3_\4 \2\n/g

sed -i 's/\([0-9]*\) \([0-9]*\) \([^\.]*\)\.\([ch]\)/\#define CKS_\3_\4 \1LL\n#define FS_\3_\4 \2/' chksum_appn.ncksum
cksum *ggm*.[ch] >chksum_ggm.ncksum
#  s/([0-9]) ([0-9]) ([^\.])\.([ch])\n/\#define CKS_\3_\4 \1\n#define FS_\3_\4 \2\n/g

sed -i 's/\([0-9]*\) \([0-9]*\) \([^\.]*\)\.\([ch]\)/\#define CKS_\3_\4 \1LL\n#define FS_\3_\4 \2/' chksum_ggm.ncksum
