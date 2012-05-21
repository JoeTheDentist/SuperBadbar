#~ TRACE	:= -DTRACE_DISPLAY=2

EXEC2		:= tp2_q2
EXEC3		:= tp2_q3
EXEC4		:= tp2_q4
EXEC5		:= tp2_q5
EXEC		:= $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)

SRC_REP		:= ../src/
OBJ_REP		:= ../src/

ARCHIVE		:= ../MNA_tp2_IRVM_CIMON_MOREL
CONTENU		:= $(SRC_REP) ../mat/ ../doc/ ../doxy_conf ../Rapport.pdf ../README.txt

FILES		:= vector matLC csr
HDRS_SUPP	:= utile

HDRS		:= $(patsubst %, $(SRC_REP)%.h, $(FILES) $(HDRS_SUPP))
SRCS		:= $(patsubst %, $(SRC_REP)%.cpp, $(FILES))
OBJS		:= $(patsubst %, $(OBJ_REP)%.o, $(FILES))

CC			:= g++ #-pg
CFLAGS		:= $(TRACE) -Wall -Wextra -pedantic -O3 #-g
LDFLAGS		:= #-g -lm

all: $(EXEC)

$(OBJ_REP)%.o: $(SRC_REP)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC2): $(OBJS) $(SRCS) $(HDRS) $(SRC_REP)$(EXEC2).cpp
	$(CC) $(LDFLAGS) $(OBJS) $(SRC_REP)$(EXEC2).cpp -o $@
	
$(EXEC3): $(OBJS) $(SRCS) $(HDRS) $(SRC_REP)$(EXEC3).cpp
	$(CC) $(LDFLAGS) $(OBJS) $(SRC_REP)$(EXEC3).cpp -o $@

$(EXEC4): $(OBJS) $(SRCS) $(HDRS) $(SRC_REP)$(EXEC4).cpp
	$(CC) $(LDFLAGS) $(OBJS) $(SRC_REP)$(EXEC4).cpp -o $@

$(EXEC5): $(OBJS) $(SRCS) $(HDRS) $(SRC_REP)$(EXEC5).cpp
	$(CC) $(LDFLAGS) $(OBJS) $(SRC_REP)$(EXEC5).cpp -o $@

.PHONY: clean propper doc read archive
clean: propper
	@rm -f $(EXEC)
	
propper:
	@rm -f $(wildcard $(OBJ_REP)*.o) gmon.out
	
doc:
	cd ..; doxygen doxy_conf; cd src/

read: doc
	firefox ../doc/html/index.html &

archive:
	@mkdir $(ARCHIVE)
	@cp -rt $(ARCHIVE) $(CONTENU)
	@$(RM) -r `find $(ARCHIVE) -name .svn`
	@tar -czf $(ARCHIVE).tgz $(ARCHIVE)
	@$(RM) -rf $(ARCHIVE)	
