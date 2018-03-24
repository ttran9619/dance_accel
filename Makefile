SHELL = /bin/sh
CXX = g++

CXXFLAGS = -std=c++14 -Wall -Werror -Wno-unused-result -Wno-sign-compare
DEBUGFLAGS = -ggdb -DDEBUG
RELEASEFLAGS = -O2
PROFILEFLAGS = -pg

SRCDIR = src/
INCFLAG = -Iinclude
LIBFLAG =

OBJLIST = program_entry.o data_collection.o signal_processing.o \
		  AudioFile.o

EXENAME = program_entry

debug: CXXFLAGS += $(DEBUGFLAGS)
debug: link_stage

release: CXXFLAGS += $(RELEASEFLAGS)
release: link_stage

profile: CXXFLAGS += $(PROFILEFLAGS)
profile: link_stage

link_stage: $(OBJLIST)
	$(CXX) $(CXXFLAGS) $^ -o $(EXENAME) $(LIBFLAG)

-include $(OBJS:.o=.d)

%.o: $(SRCDIR)%.c
	$(CXX) $(CXXFLAGS) $(INCFLAG) -MMD -MF $*.d -c $<

%.o: $(SRCDIR)%.cpp
	$(CXX) $(CXXFLAGS) $(INCFLAG) -MMD -MF $*.d -c $<

clean:
	rm -f -r *.o *.d $(EXENAME) $(EXENAME).dSYM *.out
