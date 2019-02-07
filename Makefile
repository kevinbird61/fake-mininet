EXEC:=mn
OBJS:=shell.o switch.o host.o edge.o gplot.o hash.o nm.o path.o
STATIC:=libfakemn.a
CXXFLAGS:= -std=c++11

all: $(EXEC)

# executable
$(EXEC): $(OBJS) main.cc
	g++ $^ -o $@ -Ilib $(CXXFLAGS)

# objectives
shell.o: lib/shell.cc
	g++ -c $^ -o $@ $(CXXFLAGS)
switch.o: lib/switch.cc 
	g++ -c $^ -o $@ $(CXXFLAGS)
host.o: lib/host.cc 
	g++ -c $^ -o $@ $(CXXFLAGS)
hash.o: lib/hash.cc 
	g++ -c $^ -o $@ $(CXXFLAGS)
edge.o: lib/edge.cc 
	g++ -c $^ -o $@ $(CXXFLAGS)
gplot.o: lib/gplot.cc
	g++ -c $^ -o $@ $(CXXFLAGS)
nm.o: lib/network_manager.cc 
	g++ -c $^ -o $@ $(CXXFLAGS)
path.o: lib/path.cc 
	g++ -c $^ -o $@ $(CXXFLAGS)

# static library
lib: $(OBJS)
	ar cr $(STATIC) $(OBJS)
	ranlib $(STATIC)

# reset & clean
clean: 
	rm -rf $(OBJS) $(EXEC) $(STATIC)