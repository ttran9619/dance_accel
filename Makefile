SHELL = /bin/sh
CXX = g++

CXXFLAGS = -std=c++14 -Wall -Werror -Wno-unused-result
DEBUGFLAGS = -ggdb -DDEBUG
RELEASEFLAGS = -O2
PROFILEFLAGS = -pg

SRCDIR = src/
INCFLAG = -Iinclude
LIBFLAG = -lncurses

OBJLIST = program_entry.o

EXENAME = program_entry

debug: CXXFLAGS += $(DEBUGFLAGS)
debug: link_stage

release: CXXFLAGS += $(RELEASEFLAGS)
release: link_stage

profile: CXXFLAGS += $(PROFILEFLAGS)
profile: link_stage

link_stage: $(OBJLIST)
	$(CXX) $(CXXFLAGS) -o $(EXENAME) $(OBJLIST) $(LIBFLAG)

%.o: $(SRCDIR)%.cpp
	$(CXX) $(CXXFLAGS) $(INCFLAG) -c $<

clean:
	rm -f -r *.o $(EXENAME) $(EXENAME).dSYM *.out