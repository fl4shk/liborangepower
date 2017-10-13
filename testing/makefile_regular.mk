# These directories specify where source code files are located.
# Edit these variables if more directories are needed.  
# Separate each entry by spaces.
SHARED_SRC_DIRS:=$(CURDIR) src
CXX_DIRS:=$(SHARED_SRC_DIRS)

# End of source directories


# Comment out or un-comment out the next line to enable debugging stuff to
# be generated
#DEBUG:=yeah do debug

DEBUG_OPTIMIZATION_LEVEL:=-O0
REGULAR_OPTIMIZATION_LEVEL:=-O2

ALWAYS_DEBUG_SUFFIX:=_debug
ifdef DEBUG
	DEBUG_SUFFIX:=$(ALWAYS_DEBUG_SUFFIX)
endif

# This is the name of the output file.  Change this if needed!
PROJ:=$(shell basename $(CURDIR))$(DEBUG_SUFFIX)



# Compilers and initial compiler flags
CXX:=$(PREFIX)g++
CXX_FLAGS:=$(CXX_FLAGS) -std=c++17 -Wall

LD:=$(CXX)

# Initial linker flags
LD_FLAGS:=$(LD_FLAGS) -lm



ifdef DEBUG
	EXTRA_DEBUG_FLAGS:=-g
	DEBUG_FLAGS:=-gdwarf-3 $(EXTRA_DEBUG_FLAGS)
	EXTRA_LD_FLAGS:=$(DEBUG_FLAGS)
	OPTIMIZATION_LEVEL:=$(DEBUG_OPTIMIZATION_LEVEL)
else
	OPTIMIZATION_LEVEL:=$(REGULAR_OPTIMIZATION_LEVEL)
endif






FINAL_BASE_FLAGS:=$(OPTIMIZATION_LEVEL) \
	$(EXTRA_BASE_FLAGS) $(EXTRA_DEBUG_FLAGS)

# Final compiler and linker flags
CXX_FLAGS:=$(CXX_FLAGS) $(FINAL_BASE_FLAGS)
LD_FLAGS:=$(LD_FLAGS) $(EXTRA_LD_FLAGS) $(COMMON_LD_FLAGS)




# Generated directories
OBJDIR:=objs$(DEBUG_SUFFIX)
DEPDIR:=deps$(DEBUG_SUFFIX)

# Directories to search, specified at the top of this file
export VPATH	:=	\
	$(foreach DIR,$(CXX_DIRS),$(CURDIR)/$(DIR)) \


CXX_SOURCES:=$(foreach DIR,$(CXX_DIRS),$(notdir $(wildcard $(DIR)/*.cpp)))
CXX_OFILES:=$(CXX_SOURCES:%.cpp=$(OBJDIR)/%.o) 
CXX_PFILES:=$(CXX_SOURCES:%.cpp=$(DEPDIR)/%.P) 
 


# Compiler-generated files
# OFILES are object code files (extension .o)
OFILES:=$(CXX_OFILES) 
# PFILES are used for automatic dependency generation
PFILES:=$(CXX_PFILES) 



all : all_pre $(OFILES)
	$(LD) $(OBJDIR)/*.o -o $(PROJ) $(LD_FLAGS)

# all_objs is ENTIRELY optional.
all_objs : all_pre $(OFILES)
	@#


all_pre :
	mkdir -p $(OBJDIR) $(DEPDIR)





# Here's where things get really messy.

$(CXX_OFILES) : $(OBJDIR)/%.o : %.cpp 
	@#echo "Generating dependency information for "$@"...." 
	@echo $@" was updated or has no object file.  (Re)Compiling...." 
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@ 
	@cp $(OBJDIR)/$*.d $(DEPDIR)/$*.P 
	@#$(sed_script) < $(OBJDIR)/$*.d >> $(DEPDIR)/$*.P 
	@rm -f $(OBJDIR)/$*.d


-include $(PFILES)

#¯\(°_o)/¯

.PHONY : clean
clean :
	rm -rfv $(OBJDIR) $(DEPDIR) $(ASMOUTDIR) $(PREPROCDIR) $(PROJ) tags *.taghl gmon.out

