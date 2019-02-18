EXEC:=api.out capacity.out find-path.out max-flow.out \
	plot.out dfs.out bfs.out sssp.out file.out
OBJS:=libfakemn.a
LIBS:=../../lib
CXXFLAGS:= -std=c++11

all: clean $(EXEC)

# executable (using static library)
# need libfakemn.a (compile from the Makefile of project root)
$(EXEC): %.out: %/main.cc
	g++ -o $@ $< -I$(LIBS) -g3 -L. -lfakemn $(CXXFLAGS)

# reset & clean
clean: 
	rm -rf $(EXEC)