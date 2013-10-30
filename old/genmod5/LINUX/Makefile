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
#-------------------------------------------------------------------------
#local settings
# set DEBUG to 0 or 1
#DEBUG = 1
#-------------------------------------------------------------------------
# nothing to edit after this!!!!!!!!!
CFLAGS = -Wall -ggdb
#need math library:
LDFLAGS =

OBJSggm = ggm_global.o \
gct_gen_mod5.o \
ggm_parse_actable.o \
ggm_process_waveforms.o \
ggm_process_edgeset.o\
ggm_process_edgesetdelay.o \
ggm_find_origin.o \
ggm_process_pins.o \
ggm_wfmtable_optimize.o

OBJSappn = appn_globals.o \
auto_pre_proc_new18.o \
appn_deal_with_functions.o \
appn_expand_vector.o \
appn_out_pats.o \
appn_line_parsing.o

OBJS_VCP = vector_convert_polaris_new17.o

#-------------------------------------------------------------------------
# Main Targets

all:   GCT_GEN_MOD5 PRE_PROC_NEW VCP_NEW

install:GCT_GEN_MOD5 PRE_PROC_NEW
	install -m 755 -o root -g root -s GCT_GEN_MOD5 $(BINDIR)
	install -m 755 -o root -g root -s PRE_PROC_NEW $(BINDIR)
	install -m 755 -o root -g root -s VCP_NEW $(BINDIR)

clean:
	rm -f *.o *core GCT_GEN_MOD5 PRE_PROC_NEW

purge:
	rm -f *.o *core GCT_GEN_MOD5 PRE_PROC_NEW *.bck

#-------------------------------------------------------------------------
# Core Targets

GCT_GEN_MOD5 : $(OBJSggm)
	$(CC) -o $@ $(OBJSggm) $(LDFLAGS) 

PRE_PROC_NEW : $(OBJSappn)
	$(CC) -o $@ $(OBJSappn) $(LDFLAGS) 

VCP_NEW : $(OBJS_VCP)
	$(CC) -o $@ $(OBJS_VCP) $(LDFLAGS) 

$(OBJSggm) : ggm_includes.h
$(OBJSappn) : appn_includes.h

gct_gen_mod5.o : gct_gen_mod5.c
	$(CC) $(CFLAGS) -c $< -o $@
ggm_global.o : ggm_global.c
	$(CC) $(CFLAGS) -c $< -o $@
ggm_parse_actable.o : ggm_parse_actable.c
	$(CC) $(CFLAGS) -c $< -o $@
ggm_process_waveforms.o : ggm_process_waveforms.c
	$(CC) $(CFLAGS) -c $< -o $@
ggm_process_edgeset.o : ggm_process_edgeset.c
	$(CC) $(CFLAGS) -c $< -o $@
ggm_process_edgesetdelay.o : ggm_process_edgesetdelay.c
	$(CC) $(CFLAGS) -c $< -o $@
ggm_find_origin.o : ggm_find_origin.c
	$(CC) $(CFLAGS) -c $< -o $@
ggm_wfmtable_optimize.o : ggm_wfmtable_optimize.c
	$(CC) $(CFLAGS) -c $< -o $@
ggm_process_pins.o : ggm_process_pins.c
	$(CC) $(CFLAGS) -c $< -o $@

appn_globals.o : appn_globals.c
	$(CC) $(CFLAGS) -c $< -o $@
auto_pre_proc_new18.o : auto_pre_proc_new18.c
	$(CC) $(CFLAGS) -c $< -o $@
appn_deal_with_functions.o : appn_deal_with_functions.c
	$(CC) $(CFLAGS) -c $< -o $@
appn_expand_vector.o : appn_expand_vector.c
	$(CC) $(CFLAGS) -c $< -o $@
appn_line_parsing.o : appn_line_parsing.c
	$(CC) $(CFLAGS) -c $< -o $@
appn_out_pats.o : appn_out_pats.c
	$(CC) $(CFLAGS) -c $< -o $@
        
vector_convert_polaris_new18.o : vector_convert_polaris_new17.c
	$(CC) $(CFLAGS) -c $< -o $@
        
##########################################################################
# EOF
##########################################################################
