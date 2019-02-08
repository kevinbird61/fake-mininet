EXEC:=mn
OBJS:=shell.o switch.o host.o edge.o gplot.o hash.o network_manager.o path.o
STATIC:=libfakemn.a
CXXFLAGS:= -std=c++11

all: $(EXEC)

# executable
$(EXEC): $(OBJS) main.cc
	g++ $^ -o $@ -Ilib $(CXXFLAGS)

# objectives (libraries)
$(OBJS): %.o: lib/%.cc 
	g++ -c $^ -o $@ $(CXXFLAGS)

# static library
lib: $(OBJS)
	ar cr $(STATIC) $(OBJS)
	ranlib $(STATIC)

# reset & clean
clean: 
	rm -rf $(OBJS) $(EXEC) $(STATIC)