EXEC:=mn
OBJS:=libfakemn.a
LIBS:=../../lib
CXXFLAGS:= -std=c++11

all: $(EXEC)

# executable (using static library)
$(EXEC): api.cc
	# need libfakemn.a (compile from the Makefile of project root)
	g++ $^ -o $@ -I$(LIBS) -L. -lfakemn $(CXXFLAGS)

# reset & clean
clean: 
	rm -rf $(EXEC)