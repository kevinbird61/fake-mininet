EXEC:=api.out capacity.out path.out augment.out
OBJS:=libfakemn.a
LIBS:=../../lib
CXXFLAGS:= -std=c++11

all: clean $(EXEC)

# executable (using static library)
# need libfakemn.a (compile from the Makefile of project root)
$(EXEC): %.out: %.cc
	g++ -o $@ $< -I$(LIBS) -L. -lfakemn $(CXXFLAGS)

# reset & clean
clean: 
	rm -rf $(EXEC)