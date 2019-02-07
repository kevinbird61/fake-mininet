EXEC:=api.out path.out
OBJS:=libfakemn.a
LIBS:=../../lib
CXXFLAGS:= -std=c++11

all: clean $(EXEC)

# executable (using static library)
api.out: api.cc
	# need libfakemn.a (compile from the Makefile of project root)
	g++ $^ -o $@ -I$(LIBS) -L. -lfakemn $(CXXFLAGS)
path.out: path.cc
	# need libfakemn.a (compile from the Makefile of project root)
	g++ $^ -o $@ -I$(LIBS) -L. -lfakemn $(CXXFLAGS)

# reset & clean
clean: 
	rm -rf $(EXEC)