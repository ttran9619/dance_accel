SHELL = /bin/sh
CXX = g++

CXXFLAGS = -std=c++14 -Wall -Werror -Wno-unused-result -Wno-sign-compare -Wno-unused-variable
DEBUGFLAGS = -ggdb -DDEBUG
RELEASEFLAGS = -O2
PROFILEFLAGS = -pg

SRCDIR = src/
INCFLAG = -Iinclude
LIBFLAG = 

OBJLIST = data_collection.o signal_processing.o \
		  AudioFile.o audio_driver.o

EXENAME = program_entry

debug: CXXFLAGS += $(DEBUGFLAGS)
debug: link_stage

release: CXXFLAGS += $(RELEASEFLAGS)
release: link_stage

profile: CXXFLAGS += $(PROFILEFLAGS)
profile: link_stage

tests: CXXFLAGS += $(DEBUGFLAGS)
tests: test_link_stage

test_link_stage: $(OBJLIST) tests.o
	$(CXX) $(CXXFLAGS) $^ -o test_entry $(LIBFLAG)

link_stage: $(OBJLIST) program_entry.o
	$(CXX) $(CXXFLAGS) $^ -o $(EXENAME) $(LIBFLAG)

-include $(OBJS:.o=.d)

%.o: $(SRCDIR)%.c
	$(CXX) $(CXXFLAGS) $(INCFLAG) -MMD -MF $*.d -c $<

%.o: $(SRCDIR)%.cpp
	$(CXX) $(CXXFLAGS) $(INCFLAG) -MMD -MF $*.d -c $<

clean:
	rm -f -r *.o *.d $(EXENAME) $(EXENAME).dSYM *.out
