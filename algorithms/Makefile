# makefile for basic algorithms 
#

$(warning .......... Run Makefile ..........)
$(warning default CXX = $(CXX))
$(warning default CURDIR = $(CURDIR))
$(warning default CXXFLAGS = $(CXXFLAGS))

CXX=g++
CXXFLAGS=-c -g -W -std=c++11 -I. -I./common

#SRCS := $(foreach dir,$(SUBDIRS), $(wildcard $(dir)/*.cpp)) #*/
#LIB_SRCS := $(filter-out test.cpp,$(wildcard *.cpp))

SRCS:= $(wildcard *.cpp)
TARGETS:= $(subst .cpp,, $(SRCS))
TARGETSOBJ:= $(subst cpp,o, $(SRCS))
COMMONSRC:=$(wildcard common/*.cpp)
COMMONOBJ:=$(subst cpp,o,$(COMMONSRC))

$(info SRCS         = $(SRCS))
$(info TARGETS      = $(TARGETS))
$(info TARGETSOBJ   = $(TARGETSOBJ))
$(info COMMONSRC    = $(COMMONSRC))
$(info COMMONOBJ    = $(COMMONOBJ))

$(info ---------------------------------------------------)
.PHONY : all
all : $(COMMONOBJ) $(TARGETS)
	@echo "building default target: [ $^ ] OK."

# 
.PHONY : $(TARGETS)	
$(TARGETS): $(TARGETSOBJ)  
	@echo "buildig the target [$< ===> $@.out ]"
	$(CXX) $(COMMONOBJ) $@.o -o $@.out

	
%.o : %.cpp
	@echo compiling [ $< ==> $@ ]
	$(CXX) $(CXXFLAGS)  $< -o $@
	
$(COMMONOBJ) : $(COMMONSRC)
	@echo compiling common obj [ $< ==> $@ ]
	$(CXX) $(CXXFLAGS)  $< -o $@	
	
.PHONY : clean
clean :
	@echo remove temporal files....     # @ avoid echo the cmd itself
	@-rm -rf *.o  *.out		            # - tell make continue even if rm encounters errors	
	@-rm -rf *~ common/*.o
	@echo clean finished....            # @ avoid echo the cmd itself		
	
