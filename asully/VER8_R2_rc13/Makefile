#Makefile for POLARIS SCRIPTS
# modeled this after the irmp3 Makefile
# TABS should not be emulated!!!!
#-------------------------------------------------------------------------
# Install destination paths
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
SRCDIR = ../src
OBJDIR = ./obj
#-------------------------------------------------------------------------
# Compiler/linker settings
CC = gcc
rmdel = /bin/rm
#-------------------------------------------------------------------------
#local settings
# set DEBUG to 0 or 1
#DEBUG = 1
#-------------------------------------------------------------------------
# nothing to edit after this!!!!!!!!!
# this still didn't allow large files.... so don't include
#CFLAGS = -Wall -ggdb -DUSE_LARGEFILE
CFLAGS = -Wall -ggdb
#need math library:
LDFLAGS =

# gct gen mod
OBJSggm = global_ggm.o \
gct_gen_mod8_ggm.o \
read_cycletbl_ggm.o \
make_hexmuxlist_ggm.o \
make_scan_headers_ggm.o \
compact_cycletbl_ggm.o \
parse_cyctbl_ggm.o \
parse_actable_ggm.o \
process_waveforms_ggm.o \
modify_waveforms_ggm.o \
process_all_edgesets_ggm.o \
edgeset_make_wfms_ggm.o \
chk_problem_type_ggm.o \
find_origin_ggm.o \
resolve_list_ggm.o \
separate_actable_ggm.o \
purge_actable_ggm.o \
get_pins_ggm.o \

#BUILD_INHERIT_MENU
OBJSBIM = build_inherit_menu.o \
read_ggm_build.o \
globals_build.o \
read_patref_build.o \
write_params_build.o

# auto pre proc
OBJSappn = globals_appn.o \
pre_proc18_appn.o \
deal_with_functions_appn.o \
expand_vector_appn.o \
out_pats_appn.o \
line_parsing_appn.o \
alias_vcpvcs.o

# vector convert polaris
OBJS_VCP = global_vcp.o \
main_vcp.o \
alias_vcpvcs.o \
outvector_vcp.o \
outvector_evX2_vcp.o \
convert_vcp.o \
cpmopt_vcp.o \
smallfunc_vcp.o \
comments_shutdown_vcp.o

# vector convert scan autogen
OBJS_VCS = global_vcs.o \
autogen8_vcs.o \
alias_vcpvcs.o \
parse_mod_vcs.o \
outputvector_vcs.o

#SUBROUTINE REPLACE
OBJS_DESUB = desub.o

#-------------------------------------------------------------------------
# Main Targets

all:MAKESUM GCT_GEN_MOD8 PRE_PROC_NEW VCP_NEW VCS_AUTOGEN8 BUILD_INHERIT_MENU DESUB

install:GCT_GEN_MOD8 PRE_PROC_NEW VCP_NEW VCS_AUTOGEN8 BUILD_INHERIT_MENU
	install -m 755 -o root -g root -s GCT_GEN_MOD8 $(BINDIR)
	install -m 755 -o root -g root -s PRE_PROC_NEW $(BINDIR)
	install -m 755 -o root -g root -s VCP_NEW $(BINDIR)
	install -m 755 -o root -g root -s VCS_AUTOGEN8 $(BINDIR)
	install -m 755 -o root -g root -s BUILD_INHERIT_MENU $(BINDIR)

clean:
	$(rmdel) -f *.o *core GCT_GEN_MOD8 PRE_PROC_NEW VCS_AUTOGEN8 VCP_NEW BUILD_INHERIT_MENU DESUB *.bck chksum.cksum

#-------------------------------------------------------------------------
# Core Targets

#MAKESUM : chksum.cksum
#	MakeChkSum.sh
MAKESUM :
	MakeChkSum.sh

GCT_GEN_MOD8 : $(OBJSggm)
	$(CC) -o $@ $(OBJSggm) $(LDFLAGS) 

BUILD_INHERIT_MENU : $(OBJSBIM)
	$(CC) -o $@ $(OBJSBIM) $(LDFLAGS) 

PRE_PROC_NEW : $(OBJSappn)
	$(CC) -o $@ $(OBJSappn) $(LDFLAGS) 
	$(rmdel) -f PRE_PROC_CPM
	ln -s PRE_PROC_NEW PRE_PROC_CPM

VCP_NEW : $(OBJS_VCP)
	$(CC) -o $@ $(OBJS_VCP) $(LDFLAGS) 

VCS_AUTOGEN8 : $(OBJS_VCS)
	$(CC) -o $@ $(OBJS_VCS) $(LDFLAGS) 

#this one needs the zlib...
DESUB : $(OBJS_DESUB)
	$(CC) -o $@ $(OBJS_DESUB) $(LDFLAGS) -l z

$(OBJSggm) : common_includes.h includes_ggm.h aliasmap.h chksum.cksum
$(OBJSBIM) : common_includes.h includes_ggm.h chksum.cksum
$(OBJSappn) : common_includes.h includes_appn.h chksum.cksum
$(OBJS_VCP) : common_includes.h include_vcp.h aliasmap.h chksum.cksum
$(OBJS_VCS) : common_includes.h include_vcs.h aliasmap.h chksum.cksum
$(OBJS_BUILD) : common_includes.h include_build.h chksum.cksum
$(OBJS_DESUB) : chksum.cksum

gct_gen_mod8_ggm.o : gct_gen_mod8_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@
global_ggm.o : global_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@
read_cycletbl_ggm.o : read_cycletbl_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@
make_hexmuxlist_ggm.o : make_hexmuxlist_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@
make_scan_headers_ggm.o : make_scan_headers_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@
compact_cycletbl_ggm.o : compact_cycletbl_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@
parse_cyctbl_ggm.o : parse_cyctbl_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@
parse_actable_ggm.o : parse_actable_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@
modify_waveforms_ggm.o : modify_waveforms_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@
process_waveforms_ggm.o : process_waveforms_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@
process_all_edgesets_ggm.o : process_all_edgesets_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@
edgeset_make_wfms_ggm.o : edgeset_make_wfms_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@
chk_problem_type_ggm.o : chk_problem_type_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@
find_origin_ggm.o : find_origin_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@
resolve_list_ggm.o : resolve_list_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@
get_pins_ggm.o : get_pins_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@
separate_actable_ggm.o : separate_actable_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@
purge_actable_ggm.o : purge_actable_ggm.c
	$(CC) $(CFLAGS) -c $< -o $@

build_inherit_menu.o : build_inherit_menu.c
	$(CC) $(CFLAGS) -c $< -o $@
globals_build.o : globals_build.c
	$(CC) $(CFLAGS) -c $< -o $@
read_ggm_build.o : read_ggm_build.c
	$(CC) $(CFLAGS) -c $< -o $@
write_params_build.o : write_params_build.c
	$(CC) $(CFLAGS) -c $< -o $@
read_patref_build.o : read_patref_build.c
	$(CC) $(CFLAGS) -c $< -o $@

globals_appn.o : globals_appn.c
	$(CC) $(CFLAGS) -c $< -o $@
pre_proc18_appn.o : pre_proc18_appn.c
	$(CC) $(CFLAGS) -c $< -o $@
deal_with_functions_appn.o : deal_with_functions_appn.c
	$(CC) $(CFLAGS) -c $< -o $@
expand_vector_appn.o : expand_vector_appn.c
	$(CC) $(CFLAGS) -c $< -o $@
line_parsing_appn.o : line_parsing_appn.c
	$(CC) $(CFLAGS) -c $< -o $@
out_pats_appn.o : out_pats_appn.c
	$(CC) $(CFLAGS) -c $< -o $@
        
main_vcp.o : main_vcp.c
	$(CC) $(CFLAGS) -c $< -o $@
outvector_vcp.o : outvector_vcp.c
	$(CC) $(CFLAGS) -c $< -o $@
outvector_evX2_vcp.o : outvector_evX2_vcp.c
	$(CC) $(CFLAGS) -c $< -o $@
convert_vcp.o : convert_vcp.c
	$(CC) $(CFLAGS) -c $< -o $@
cpmopt_vcp.o : cpmopt_vcp.c
	$(CC) $(CFLAGS) -c $< -o $@
smallfunc_vcp.o : smallfunc_vcp.c
	$(CC) $(CFLAGS) -c $< -o $@
comments_shutdown_vcp.o : comments_shutdown_vcp.c
	$(CC) $(CFLAGS) -c $< -o $@

alias_vcpvcs.o : alias_vcpvcs.c
	$(CC) $(CFLAGS) -c $< -o $@
        
autogen8_vcs.o : autogen8_vcs.c
	$(CC) $(CFLAGS) -c $< -o $@
global_vcs.o : global_vcs.c
	$(CC) $(CFLAGS) -c $< -o $@
outputvector_vcs.o : outputvector_vcs.c
	$(CC) $(CFLAGS) -c $< -o $@
parse_mod_vcs.o : parse_mod_vcs.c
	$(CC) $(CFLAGS) -c $< -o $@

desub.o : desub.c
	$(CC) $(CFLAGS) -c $< -o $@

##########################################################################
# EOF
##########################################################################
