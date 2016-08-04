#-------------------------------------------------------------------------------
# Author:       Charles Cross
# Date Created: May 21, 2016
#
# Description:  Makefile for the geomuxpp program
#
# Based on Stephen Brennan's generic makefile.  It comes with several features:
# - Running tests, with Valgrind.
# - Generation of documentation through Doxygen.  You'll need to provide a Doxyfile.
# - Code coverage reports via gcov.
# - Build configurations: debug, release, and coverage.
# - Automatic dependency generation, so you never need to update this file.
#
#-------------------------------------------------------------------------------

# ------------------------------------------------------------------------------------
# CONFIGURATION: Definitely change this stuff!
# ------------------------------------------------------------------------------------

# --- PROJECT CONFIGURATION

#APP - Which "sketch" to build
APP=TridentPower

#CHIP - Which part number to build for, e.g. "SAML21J18B"
CHIP=SAML21J18B

#VARIANT - Which setup to use for the specified chip
VARIANT=0000

# ------------------------------

# Include Setup
LDINCLUDES=-I"include/cmsis/include" \
			-I"include/cmsis/atmel"

LDINCLUDES+=-I"src/cores/$(CHIP)" \
			-I"src/variants/$(CHIP)/$(VARIANT)"

# TODO: Remove this. Must be passed in as "EXTRA_INCLUDES" variable
LDINCLUDES+=-I"src/cores/$(CHIP)/" \
			-I"src/cores/$(CHIP)/config" \
			-I"src/cores/$(CHIP)/hal/include" \
			-I"src/cores/$(CHIP)/hal/utils/include" \
			-I"src/cores/$(CHIP)/hpl/core" \
			-I"src/cores/$(CHIP)/hpl/adc" \
			-I"src/cores/$(CHIP)/hpl/dmac" \
			-I"src/cores/$(CHIP)/hpl/gclk" \
			-I"src/cores/$(CHIP)/hpl/mclk" \
			-I"src/cores/$(CHIP)/hpl/osc32kctrl" \
			-I"src/cores/$(CHIP)/hpl/oscctrl" \
			-I"src/cores/$(CHIP)/hpl/pm" \
			-I"src/cores/$(CHIP)/hpl/port" \
			-I"src/cores/$(CHIP)/hpl/sercom" \
			-I"src/cores/$(CHIP)/hpl/systick" \
			-I"src/cores/$(CHIP)/hpl/tc" \
			-I"src/cores/$(CHIP)/hri"

# LDLIBPATHS - Lib paths for libraries, i.e. '-L/usr/local/lib'
LDLIBPATHS=

# LDFLAGS - Flags to be passed to the linker. Additional options will be added later based on build target
LDFLAGS=$(LDLIBPATHS) \
			-Wl,--no-wchar-size-warning \
			-mthumb \
			-Wl,-Map="$(BINARY_DIR)/$(APP)/$(CFG)/$(APP).map" \
			--specs=nano.specs \
			-Wl,--gc-sections \
			-mcpu=cortex-m0plus \
			-T"linker_scripts/$(CHIP)/flash.ld"

# LDLIBS - Which libs to link to, i.e. '-lm' or 'somelib.a'
LDLIBS=-Wl,--start-group -lm -Wl,--end-group

# --- INCLUDE CONFIGURATION

# EXTRA_INCLUDES - Any additional files you'd like to include i.e. '-I/usr/local/include'
EXTRA_INCLUDES=

# --- DIRECTORY STRUCTURE: This structure is highly recommended, but you can
# change it.  The most important thing is that *none* of these directories are
# subdirectories of each other.  They should be completely disjoint.  Also,
# being too creative with directories could seriously mess up gcov, which is a
# finicky beast.

SOURCE_DIRS=src/apps/$(APP) src/cores/$(CHIP) src/variants/$(CHIP)/$(VARIANT)
BUILD_DIR=build/$(APP)
OBJECT_DIR=$(BUILD_DIR)/obj
BINARY_DIR=$(BUILD_DIR)/bin
DEPENDENCY_DIR=$(BUILD_DIR)/dep

# --- COMPILATION FLAGS

# Compiler to use:
CC=arm-none-eabi-gcc
CXX=arm-none-eabi-g++

# --- C++ compiler flags. We'll add on to these later based on build target.
CXFLAGS=-x c -mthumb -ffunction-sections -mlong-calls -Wall -std=gnu99 -D__$(CHIP)__ -mcpu=cortex-m0plus
CXXFLAGS=-x c++ -mthumb -ffunction-sections -mlong-calls -Wall -std=c++14 -D__$(CHIP)__ -mcpu=cortex-m0plus

# --------------------------------------------------------------------------------------------------

# The options below here should only be changed if you really need to. Most options are configured above

INCLUDES=$(LDINCLUDES) $(EXTRA_INCLUDES)

CFLAGS=$(CXFLAGS) $(INCLUDES) -c
CPPFLAGS=$(CXXFLAGS) $(INCLUDES) -c

# --- BUILD CONFIGURATIONS: 
CFG=release

# Add optimization
ifeq ($(CFG),release)
CFLAGS += -O1
CPPFLAGS += -O1
endif

# Add debugging symbols
ifeq ($(CFG),debug)
CFLAGS += -O1 -g -DDEBUG
CPPFLAGS += -O1 -g -DDEBUG
endif

ifneq ($(CFG),debug)
ifneq ($(CFG),release)
$(error Bad build configuration.  Choices are debug, release)
endif
endif

$(warning hey)

# --- FILENAME LISTS: (and other internal variables)
DIR_GUARD=@mkdir -p $(@D)

# Generate object and dependency lists
COBJECTS=$(foreach sdir,$(SOURCE_DIRS),$(patsubst $(sdir)/%.c,$(OBJECT_DIR)/$(APP)/$(CFG)/$(sdir)/%.o,$(shell find $(sdir) -type f -name "*.c")))
CPPOBJECTS=$(foreach sdir,$(SOURCE_DIRS),$(patsubst $(sdir)/%.cpp,$(OBJECT_DIR)/$(APP)/$(CFG)/$(sdir)/%.o,$(shell find $(sdir) -type f -name "*.cpp")))
OBJECTS=$(COBJECTS) $(CPPOBJECTS)

CDEPENDENCIES=$(foreach sdir,$(SOURCE_DIRS),$(patsubst $(sdir)/%.c,$(DEPENDENCY_DIR)/$(SOURCE_DIR)/%.d,$(shell find $(sdir) -type f -name "*.c")))
CPPDEPENDENCIES=$(foreach sdir,$(SOURCE_DIRS),$(patsubst $(sdir)/%.cpp,$(DEPENDENCY_DIR)/$(SOURCE_DIR)/%.d,$(shell find $(sdir) -type f -name "*.cpp")))
DEPENDENCIES=$(CDEPENDENCIES) $(CPPDEPENDENCIES)

# --- GLOBAL TARGETS: You can probably adjust and augment these if you'd like.
.PHONY: all clean

all: $(BINARY_DIR)/$(APP)/$(CFG)/$(APP).elf

clean:
	rm -rf $(BUILD_DIR)

# RULE TO BUILD YOUR MAIN TARGET HERE: (you may have to edit this, but it is configurable).
$(BINARY_DIR)/$(APP)/$(CFG)/$(APP).elf: $(OBJECTS)
	$(DIR_GUARD)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)
	@echo Finished building target: $@
	"arm-none-eabi-objcopy" -O binary "$(BINARY_DIR)/$(APP)/$(CFG)/$(APP).elf" "$(BINARY_DIR)/$(APP)/$(CFG)/$(APP).bin"
	"arm-none-eabi-objcopy" -O ihex -R .eeprom -R .fuse -R .lock -R .signature "$(BINARY_DIR)/$(APP)/$(CFG)/$(APP).elf" "$(BINARY_DIR)/$(APP)/$(CFG)/$(APP).hex"
	"arm-none-eabi-objcopy" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma \
		.eeprom=0 --no-change-warnings -O binary "$(BINARY_DIR)/$(APP)/$(CFG)/$(APP).elf" "$(BINARY_DIR)/$(APP)/$(CFG)/$(APP).eep" || exit 0
	"arm-none-eabi-objdump" -h -S -l "$(BINARY_DIR)/$(APP)/$(CFG)/$(APP).elf" > "$(BINARY_DIR)/$(APP)/$(CFG)/$(APP).lss"
	"arm-none-eabi-size" -A "$(BINARY_DIR)/$(APP)/$(CFG)/$(APP).elf"

# --- Generic Compilation Command

# C Files
$(OBJECT_DIR)/$(APP)/$(CFG)/%.o: %.c
	$(DIR_GUARD)
	$(CC) $(CFLAGS) $< -o $@

# CPP files
$(OBJECT_DIR)/$(APP)/$(CFG)/%.o: %.cpp
	$(DIR_GUARD)
	$(CXX) $(CPPFLAGS) $< -o $@

# --- Automatic Dependency Generation
$(DEPENDENCY_DIR)/%.d: %.c
	$(DIR_GUARD)
	$(CC) $(CFLAGS) -MM $< | sed -e 's!\(.*\)\.o:!$@ $(OBJECT_DIR)/$$(CFG)/$(<D)/\1.o:!' > $@

$(DEPENDENCY_DIR)/%.d: %.cpp
	$(DIR_GUARD)
	$(CXX) $(CPPFLAGS) -MM $< | sed -e 's!\(.*\)\.o:!$@ $(OBJECT_DIR)/$$(CFG)/$(<D)/\1.o:!' > $@

# --- Include Generated Dependencies
ifneq "$(MAKECMDGOALS)" "clean_all"
-include $(DEPENDENCIES)
endif
