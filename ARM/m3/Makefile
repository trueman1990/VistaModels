TARGET_ARCH = linux

CC     = vista_c++ 
OPT    = 
OPT    = -O9 
DEBUG  = -DMB_DEBUG -tsv -pg -fprofile-arcs -ftest-coverage
DEBUG  = -g -DMB_DEBUG -tsv
OTHER  = -Wall +model_builder -DARM +models_catalogue
OTHER  = +model_builder +models_catalogue
CFLAGS = $(DEBUG) $(OTHER)

MODELS = Models
LOCAL  = blocks_lib
MODULE = arm
Project = M3

VISTA_HOME = $(dir $(dir $(shell which vista)))
MODEL_BUILDER_HOME = $(VISTA_HOME)papoulis
VISTA_HOME = /home/tools/vista
MODEL_BUILDER_HOME = $(VISTA_HOME)/papoulis

ifeq ($(VISTA_ROOT),)
    # try to find Vista if its not set
    VISTA_ROOT         = $(patsubst %/bin/,%, $(dir $(shell which vista)))
    export VISTA_ROOT
endif

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

MBSRCS = $(wildcard $(MODELS)/*.cpp)
MBOBJS = $(MBSRCS:.cpp=.o)
MBARCHIVE = lib$(MODELS).a

INCDIR = -I. -I./$(LOCAL) -I./$(MODELS) -I/usr/include/i386-linux-gnu

LIBS   = $(EXTRA_LIBS) -L. -l$(MODELS) -L/usr/lib/i386-linux-gnu
EXE    = $(MODULE).x
DFILES = $(OBJS:.o=.d) $(MBOBJS:.o=.d)

S ?= sim
P ?= parameters.txt
T ?= traces.tcl
N ?= top

.SUFFIXES: .cpp .cc .o .x .h


$(EXE): $(OBJS) $(MBARCHIVE) AES.dgn AEShw.dgn
	$(CC) $(CFLAGS) $(INCDIR) -o $@ $(OBJS) $(LIBS) 2>&1 | c++filt
#	if [ ! -n "$$V2_HOME" ] ; \
#	then vista_build_project $(Project); fi

vistagui: $(EXE)

$(MBARCHIVE): $(MBOBJS)
	ar rcs $@ $(MBOBJS)

run:
	./arm.x

AES.cov:
	vista_sw_tool -c "use_coverage; load_design AES.dgn; load_test AES.tst; dump_report -output ./AES_cov.html -full -source-dir CBwork/AES"

AEShw.cov:
	vista_sw_tool -c "use_coverage; load_design AEShw.dgn; load_test AEShw.tst; dump_report -output ./AEShw_cov.html -full -source-dir CBwork/AEShw"

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
	rm -rf vista_work $(Project) Source Object sim papoulis_project work
	find . -name "*~" -exec rm {} \;
	find . -name "*.d" -exec rm {} \;
	find . -name "*.gcno" -exec rm {} \;
	find . -name "*.gcda" -exec rm {} \;
	find . -name "*.gcov" -exec rm {} \;
	rm -rf app.info index* vista_* gcov* gmon* transcript *.png cbarm.log
	rm -f $(OBJS) $(MBOBJS) $(MBARCHIVE) $(EXE)

codeblocks: 
	codeblocks codeblocks.cbp 

vista: $(EXE) $T
	vista -trace-delta-cycles -tsv -memory-profiling \
		-event-debugging -with-cause -trace-all-sockets \
		-params $P -simdir $S -memory-profiling \
		-exec $(EXE) -simscript $T

batch: $(EXE) $T
	vista -tsv -simscript $T -params $P -simdir $S \
		-trace-all-sockets -vp-plus -batch -exec $(EXE)
#		-batch -exec $(EXE)

events: $S
	vista_dump_events $S -kind initiator_socket -name $N > events2
	diff events*

$T:
	echo "#trace_transactions -name * -tree" > $T
	echo "#trace -name * -tree" >> $T
	echo "#trace -kind sc_object_attribute -name * -tree -unlimited" >> $T

COMMAND = "if {![does_tlm_library_exist $(MODELS)]} \
	      {create_tlm_library $(MODELS) $(MODELS)}; \
	   reload_tlm_library $(MODELS);\
	   foreach n [glob -directory $(MODELS) -tails *.mb] { \
	     save_model -g TLM/$(MODELS)/[lindex [split \$$n .] 0] }"

mb:
	@if [ -e $(MODELS) ]; then vista_model_builder -c $(COMMAND); fi

papoulis_project:
	if [ -e $(HOME)/include/custom_models.tcl ]; then \
		vista_mb -c "source $(HOME)/include/custom_models.tcl"; fi
	@if [ -e $(MODELS) ]; then vista_model_builder -c $(COMMAND); fi

pa: $(EXE)
	vista_analysis sim

dgn: AES.dgn AEShw.dgn

AES.dgn AEShw.dgn: CBwork/AES/Debug/AES CBwork/AEShw/Debug/AEShw
	vista_sw_tool -c "use_coverage; create_design CBwork/AEShw/Debug/AEShw -output AEShw.dgn -limit 100; create_design CBwork/AES/Debug/AES -output AES.dgn -limit 100"

-include $(DFILES)
