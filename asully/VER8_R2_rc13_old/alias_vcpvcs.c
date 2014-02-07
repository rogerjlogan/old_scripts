#include <stdio.h>
#include "aliasmap.h"
#include "chksum.cksum"

int alias_vcpvcs(int vect, int vmset, int vdset, int dset0val,int dset1val,int priorstate) {
	int AC;
	AC = FC_BAD;
	if (vdset == 0) {			/* DSET0 */
		if (vmset != 0) {
			switch (dset0val) {	/* mask if 0 */
			case FC_DRIVEOFF:
				AC = (vect == 0 || vect == '0') ? AM_driveoffLOD0 : AM_driveoffHID0;
				break;
			case FC_DRIVEDATA:
				AC = (vect == 0 || vect == '0') ? AM_driveLOD0 : AM_driveHID0;
				break;
			case FC_EDGEDATA:
				AC = (vect == 0 || vect == '0') ? AM_edgestbLOD0 : AM_edgestbHID0;
				break;
			case FC_WINDOWDATA:
			case FC_WINDOWOPEN:
				AC = (vect == 0 || vect == '0') ? AM_windowLOD0 : AM_windowHID0;
				break;
			case FC_EDGEFLOAT:
				AC = (vect == 0 || vect == '0') ? AM_edgefloatD0 : AM_edgefloatD0;
				break;
			case FC_WINDOWFLOAT:
			case FC_WINDOWOPENZ:
				AC = (vect == 0 || vect == '0') ? AM_windowfloatD0 : AM_windowfloatD0;
				break;
			case FC_NULLEDGE:
//				AC = (vect == 0 || vect == '0') ? AM_continueLO : AM_continue;
				if (priorstate == FC_WINDOWOPEN || priorstate == FC_WINDOWOPENZ) {
					if ( vect == 0  || vect == '0')	AC = AM_continueLO;
					else AC = AM_continue;
					}
				else  AC = AM_continueDRV;
				break;			/* Continue */
			case FC_NULLEDGE_DRV:
				AC = AM_continueDRV;
				break;			/* Continue */
			case FC_STROBEOFF:
				if (priorstate == FC_WINDOWOPEN || priorstate == FC_WINDOWOPENZ) 
				   AC = (vect == 0 || vect == '0') ? AM_strobeoffLOD0 : AM_strobeoffHID0;
				else AC = (vect == 0 || vect == '0') ? AM_driveoffLOD0 : AM_driveoffHID0;
				break;
			case FC_DRVSTRBOFF:
				if (priorstate == FC_WINDOWOPEN || priorstate == FC_WINDOWOPENZ)  
					AC = (vect == 0 || vect == '0') ? AM_strobeoffLOD0 : AM_strobeoffHID0;
				else AC = (vect == 0 || vect == '0') ? AM_driveoffLOD0 : AM_driveoffHID0;
				break;
			case FC_NOMUX: AC = AM_NOMUX;break;
// 			case 999 + 'A':
// 				AC = (vect == 0 || vect == '0') ? '2' : '3';
// 				break;			/* 01wW oivV */
// 			case 999 + 'B':
// 				AC = (vect == 0 || vect == '0') ? '6' : '7';
// 				break;			/* zZeE yYkK */
// 			case 999 + 'C':
// 				AC = (vect == 0 || vect == '0') ? '4' : '5';
// 				break;			/* -/p/P  */
// 			case 999 + 'D':
// 				AC = (vect == 0 || vect == '0') ? '8' : '9';
// 				break;			/* fFuU gGtT */
			}
		}
		else {
/* MASK: */
			switch (dset0val) {	/* mask if 0 */
			case FC_DRIVEOFF:
				AC = (vect == 0 || vect == '0') ? AM_driveoffLOD0 : AM_driveoffHID0;
				break;
			case FC_DRIVEDATA:
				AC = (vect == 0 || vect == '0') ? AM_driveLOD0 : AM_driveHID0;
				break;
			case FC_EDGEDATA:
				AC = (vect == 0 || vect == '0') ? AM_maskD0 : AM_maskHID0;
				break;
			case FC_WINDOWDATA:
			case FC_WINDOWOPEN:
				AC = (vect == 0 || vect == '0') ? AM_maskD0 : AM_maskHID0;
				break;
			case FC_EDGEFLOAT:
				AC = (vect == 0 || vect == '0') ? AM_maskD0 : AM_maskHID0;
				break;
			case FC_WINDOWFLOAT:
			case FC_WINDOWOPENZ:
				AC = (vect == 0 || vect == '0') ? AM_maskD0 : AM_maskHID0;
				break;
			case FC_NULLEDGE:
				AC = AM_continueDRV; /* if masked then call it a drive continue */
				break;			/* Continue */
			case FC_NULLEDGE_DRV:
				AC = AM_continueDRV;
				break;			/* Continue */
			case FC_STROBEOFF:
/* was drive off: APS 11/12/09 (driveoff/strobeoff which follows is the correct place for this). */
//				AC = (vect == 0 || vect == '0') ? AM_driveoffLOD0 : AM_driveoffHID0;
/* now masked strobe should be just mask: 11/12/09 */
				AC = (vect == 0 || vect == '0') ? AM_maskD0 : AM_maskHID0;
				break;
			case FC_DRVSTRBOFF:
				AC = (vect == 0 || vect == '0') ? AM_driveoffLOD0 : AM_driveoffHID0;
				break;
			case FC_NOMUX: AC = AM_NOMUX;break;
// 			case 999 + 'A':
// 				AC = (vect == 0 || vect == '0') ? AM_maskD0 : AM_maskHID0;
// 				break;			/* 01wW oivV */
// 			case 999 + 'B':
// 				AC = (vect == 0 || vect == '0') ? AM_maskD0 : AM_maskHID0;
// 				break;			/* zZeE yYkK */
// 			case 999 + 'C':
// 				AC = (vect == 0 || vect == '0') ? AM_maskD0 : AM_maskHID0;
// 				break;			/* -/p/P  */
// 			case 999 + 'D':
// 				AC = (vect == 0 || vect == '0') ? AM_maskD0 : AM_maskHID0;
// 				break;			/* fFuU gGtT */
			}
		}
	}
	else {						/* DSET1 */
		if (vmset != 0) {
			switch (dset1val) {
			case FC_DRIVEOFF:
				AC = (vect == 0 || vect == '0') ? AM_driveoffLOD1 : AM_driveoffHID1;
				break;
			case FC_DRIVEDATA:
				AC = (vect == 0 || vect == '0') ? AM_driveLOD1 : AM_driveHID1;
				break;
			case FC_EDGEDATA:
				AC = (vect == 0 || vect == '0') ? AM_edgestbLOD1 : AM_edgestbHID1;
				break;
			case FC_WINDOWDATA:
			case FC_WINDOWOPEN:
				AC = (vect == 0 || vect == '0') ? AM_windowLOD1 : AM_windowHID1;
				break;
			case FC_EDGEFLOAT:
				AC = (vect == 0 || vect == '0') ? AM_edgefloatD1 : AM_edgefloatD1;
				break;
			case FC_WINDOWFLOAT:
			case FC_WINDOWOPENZ:
				AC = (vect == 0 || vect == '0') ? AM_windowfloatD1 : AM_windowfloatD1;
				break;
			case FC_NULLEDGE:
//				AC = (vect == 0 || vect == '0') ? AM_continueLO : AM_continue;
				if (priorstate == FC_WINDOWOPEN || priorstate == FC_WINDOWOPENZ) {
					if ( vect == 0  || vect == '0') AC = AM_continueLO;
					else AC = AM_continue;
					}
				else  	AC = AM_continueDRV;
				break;			/* Continue */
			case FC_NULLEDGE_DRV:
				AC = AM_continueDRV;
				break;			/* Continue */
			case FC_STROBEOFF:
				if (priorstate == FC_WINDOWOPEN || priorstate == FC_WINDOWOPENZ)  
					AC = (vect == 0 || vect == '0') ? AM_strobeoffLOD1 : AM_strobeoffHID1;
				else AC = (vect == 0 || vect == '0') ? AM_driveoffLOD1 : AM_driveoffHID1;
				break;
			case FC_DRVSTRBOFF:
				if (priorstate == FC_WINDOWOPEN || priorstate == FC_WINDOWOPENZ )  
					AC = (vect == 0 || vect == '0') ? AM_strobeoffLOD1 : AM_strobeoffHID1;
				else AC = (vect == 0 || vect == '0') ? AM_driveoffLOD1 : AM_driveoffHID1;
				break;
			case FC_NOMUX: AC = AM_NOMUX;break;
// 			case 999 + 'A':
// 				AC = (vect == 0 || vect == '0') ? 'a' : 'A';
// 				break;			/*    a/A 01wW oivV */
// 			case 999 + 'B':
// 				AC = (vect == 0 || vect == '0') ? 'b' : 'B';
// 				break;			/*    b/B zZeE yYkK */
// 			case 999 + 'C':
// 				AC = (vect == 0 || vect == '0') ? '4' : '5';
// 				break;			/*        -/p/P  */
// 			case 999 + 'D':
// 				AC = (vect == 0 || vect == '0') ? AM_driveHID0 : AM_driveHID1;
// 				break;			/*    h/H fFuU gGtT */
			}
		}
/* MASK: */
		else {
			switch (dset1val) {
			case FC_DRIVEOFF:
				AC = (vect == 0 || vect == '0') ? AM_driveoffLOD1 : AM_driveoffHID1;
				break;
			case FC_DRIVEDATA:
				AC = (vect == 0 || vect == '0') ? AM_driveLOD1 : AM_driveHID1;
				break;
			case FC_EDGEDATA:
				AC = (vect == 0 || vect == '0') ? AM_maskD1 : AM_maskHID1;
				break;
			case FC_WINDOWDATA:
			case FC_WINDOWOPEN:
				AC = (vect == 0 || vect == '0') ? AM_maskD1 : AM_maskHID1;
				break;
			case FC_EDGEFLOAT:
				AC = (vect == 0 || vect == '0') ? AM_maskD1 : AM_maskHID1;
				break;
			case FC_WINDOWFLOAT:
			case FC_WINDOWOPENZ:
				AC = (vect == 0 || vect == '0') ? AM_maskD1 : AM_maskHID1;
				break;
			case FC_NULLEDGE_DRV:
				AC = AM_continueDRV;
				break;			/* Continue */
			case FC_NULLEDGE:
				AC = AM_continueDRV;
				break;			/* Continue Mask is just drive continue */
			case FC_STROBEOFF:
/* was drive off: APS 11/12/09 (driveoff/strobeoff which follows is the correct place for this). */
//				AC = (vect == 0 || vect == '0') ? AM_driveoffLOD1 : AM_driveoffHID1;
/* now masked strobe should be just mask: 11/12/09 */
				AC = (vect == 0 || vect == '0') ? AM_maskD1 : AM_maskHID1;
				break;
			case FC_DRVSTRBOFF:
				AC = (vect == 0 || vect == '0') ? AM_driveoffLOD1 : AM_driveoffHID1;
				break;
			case FC_NOMUX: AC = AM_NOMUX;break;
// 			case 999 + 'A':
// 				AC = (vect == 0 || vect == '0') ? AM_maskD1 : AM_maskHID1;
// 				break;			/*    a/A 01wW oivV */
// 			case 999 + 'B':
// 				AC = (vect == 0 || vect == '0') ? AM_maskD1 : AM_maskHID1;
// 				break;			/*    b/B zZeE yYkK */
// 			case 999 + 'C':
// 				AC = (vect == 0 || vect == '0') ? AM_maskD1 : AM_maskHID1;
// 				break;			/*        -/p/P  */
// 			case 999 + 'D':
// 				AC = (vect == 0 || vect == '0') ? AM_maskD1 : AM_maskHID1;
// 				break;			/*    h/H fFuU gGtT */
			}
		}
	}
	return (AC);
}

int chksumout(FILE * fpout1, char *open, char *close)
{
	fprintf(fpout1, "%s pre_proc18 %lld %d %s\n", open,
			CKS_pre_proc18_appn_c, FS_pre_proc18_appn_c, close);
	fprintf(fpout1, "%s expand_vector %lld %d %s\n", open,
			CKS_expand_vector_appn_c, FS_expand_vector_appn_c, close);
	fprintf(fpout1, "%s deal_with_functions %lld %d %s\n", open,
			CKS_deal_with_functions_appn_c, FS_deal_with_functions_appn_c,
			close);
	fprintf(fpout1, "%s globals %lld %d %s\n", open, CKS_globals_appn_c,
			FS_globals_appn_c, close);
	fprintf(fpout1, "%s includes %lld %d %s\n", open, CKS_includes_appn_h,
			FS_includes_appn_h, close);
	fprintf(fpout1, "%s line_parsing %lld %d %s\n", open,
			CKS_line_parsing_appn_c, FS_line_parsing_appn_c, close);
	fprintf(fpout1, "%s out_pats %lld %d %s\n", open, CKS_out_pats_appn_c,
			FS_out_pats_appn_c, close);
	return (0);
}
