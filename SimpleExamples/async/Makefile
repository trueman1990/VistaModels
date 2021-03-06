TARGET_ARCH = linux

CC     = vista_c++ -gcc43 -sc23 -tsv 
OPT    = -O3
DEBUG  = -g -DMB_DEBUG
OTHER  = -Wall +model_builder
CFLAGS = $(DEBUG) $(OTHER)

VISTAVER = $(strip $(patsubst Vista,,$(shell vista -version)))
PAPOULISDIR = vista_work/papoulis_project$(VISTAVER)

MODELS = models
LOCAL  = local
MODULE = run
Project = Project

VISTA_HOME = $(dir $(dir $(shell which vista)))
MODEL_BUILDER_HOME = $(VISTA_HOME)papoulis

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

MBSRCS = $(wildcard $(MODELS)/*.cpp)
MBOBJS = $(MBSRCS:.cpp=.o)
MBARCHIVE = lib$(MODELS).a

INCDIR = -I. -Iinclude -I$(LOCAL) -I$(MODELS)

LIBS   = $(EXTRA_LIBS) -L. -l$(MODELS) 
EXE    = $(MODULE).x
DFILES = $(OBJS:.o=.d) $(MBOBJS:.o=.d)

S ?= sim
P ?= parameters.txt
T ?= traces.tcl

.SUFFIXES: .cpp .cc .o .x .h

$(EXE): $(PAPOULISDIR) $(OBJS) $(MBARCHIVE) writer
	$(CC) $(CFLAGS) $(INCDIR) -o $@ $(OBJS) $(LIBS) 2>&1 | c++filt
	if [ ! -n "$$V2_HOME" ] ; \
	then vista_build_project $(Project); fi

writer: src/writer.c
	gcc src/writer.c -o writer

vistagui:

$(MBARCHIVE): $(MBOBJS)
	ar rcs $@ $(MBOBJS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $*.o
	@$(CC) -MM $(CFLAGS) $(INCDIR) -c $< > $*.d
	@sed -e 's|.*:|$*.o:|' < $*.d > $*.d.tmp
	@mv $*.d.tmp $*.d


.cc.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $*.o
	@$(CC) -MM $(CFLAGS) $(INCDIR) -c $< > $*.d
	@sed -e 's|.*:|$*.o:|' < $*.d > $*.d.tmp
	@mv $*.d.tmp $*.d

clean:
	rm -rf vista_work Project Source Object sim work papoulis_project
	rm -rf writer src/reader
	find . -name "*~" -exec rm {} \;
	find . -name "*.d" -exec rm {} \;
	rm -f $(OBJS) $(MBOBJS) $(MBARCHIVE) $(EXE)

vista: $(EXE) $T
	vista -sc22 -trace-delta-cycles -tsv -memory-profiling \
		-event-debugging -with-cause -trace-all-sockets \
		-params $P -simdir $S -memory-profiling \
		-exec $(EXE) -simscript $T

batch: $(EXE) $T
	vista -sc22 -tsv -simscript $T -params $P -simdir $S \
		-batch -exec $(EXE)

$T:
	echo "#trace_transactions -name * -tree" > $T
	echo "#trace -name * -tree" >> $T
	echo "#trace -kind sc_object_attribute -name * -tree -unlimited" >> $T

COMMAND = "if {![does_tlm_library_exist $(MODELS)]} \
	      {create_tlm_library $(MODELS) $(MODELS)}; \
	   reload_tlm_library $(MODELS);\
	   foreach n [glob -directory $(MODELS) -tails *.mb] { \
	     save_model -g TLM/$(MODELS)/[lindex [split \$$n .] 0] }"

mb $(PAPOULISDIR):
	@if [ -e $(MODELS) ]; then vista_model_builder -c $(COMMAND); fi

pa: $(EXE)
	vista_analysis sim
	
-include $(DFILES)
