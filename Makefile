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

# PROJECT_NAME - not actually used.  but what's your project's name?
PROJECT_NAME="saml21"

# PROJECT_TYPE - staticlib, dynamiclib, executable
PROJECT_TYPE=executable

# PROJECT_MAIN - filename within your source directory that contains main() 
PROJECT_MAIN=main.c

# TARGET - the name you want your target to have (bin/release/[whatgoeshere])
TARGET=saml21

# LDINCLUDES - Include paths for libraries, i.e. '-I/usr/local/include'
LDINCLUDES=-I"src/" \
			-I"src/config" \
			-I"src/hal/include" \
			-I"src/hal/utils/include" \
			-I"src/hpl/core" \
			-I"src/hpl/adc" \
			-I"src/hpl/dmac" \
			-I"src/hpl/gclk" \
			-I"src/hpl/mclk" \
			-I"src/hpl/osc32kctrl" \
			-I"src/hpl/oscctrl" \
			-I"src/hpl/pm" \
			-I"src/hpl/port" \
			-I"src/hpl/sercom" \
			-I"src/hpl/systick" \
			-I"src/hpl/tc" \
			-I"src/hri" \
			-I"src/CMSIS/Include" \
			-I"src/saml21b/include"	\
			-I"src/adp" \
			-I"src/sleep_manager"

# LDLIBPATHS - Lib paths for libraries, i.e. '-L/usr/local/lib'
LDLIBPATHS=-L"../saml21b/gcc/gcc"

# LDFLAGS - Flags to be passed to the linker. Additional options will be added later based on build target
LDFLAGS=$(LDLIBPATHS) \
			-Wl,--no-wchar-size-warning \
			-mthumb \
			-Wl,-Map="$(BINARY_DIR)/$(CFG)/$(TARGET).map" \
			--specs=nano.specs \
			-Wl,--gc-sections \
			-mcpu=cortex-m0plus \
			-T"linker_scripts/saml21j18b_flash.ld"

# LDLIBS - Which libs to link to, i.e. '-lm' or 'somelib.a'
#
#LDLIBS=-lzmq -lmxcam -lmxuvc -lavformat -lavcodec -lavutil -lswresample -lswscale -lx264 -lmxcam -lmxuvc -lpthread 
LDLIBS=-Wl,--start-group -lm -Wl,--end-group

# --- INCLUDE CONFIGURATION

# EXTRA_INCLUDES - Any additional files you'd like to include i.e. '-I/usr/local/include'
EXTRA_INCLUDES=

# --- DIRECTORY STRUCTURE: This structure is highly recommended, but you can
# change it.  The most important thing is that *none* of these directories are
# subdirectories of each other.  They should be completely disjoint.  Also,
# being too creative with directories could seriously mess up gcov, which is a
# finicky beast.
SOURCE_DIR=src
BUILD_DIR=build
OBJECT_DIR=$(BUILD_DIR)/obj
BINARY_DIR=$(BUILD_DIR)/bin
DEPENDENCY_DIR=$(BUILD_DIR)/dep

# --- COMPILATION FLAGS

# Compiler to use:
CC=arm-none-eabi-gcc
CXX=arm-none-eabi-g++

# --- C++ compiler flags. We'll add on to these later based on build target.
CXFLAGS=-x c -mthumb -ffunction-sections -mlong-calls -Wall -std=gnu99 -D__SAML21J18B__ -mcpu=cortex-m0plus
CXXFLAGS=-x c++ -mthumb -ffunction-sections -mlong-calls -Wall -std=c++14 -D__SAML21J18B__ -mcpu=cortex-m0plus

# --------------------------------------------------------------------------------------------------

# The options below here should only be changed if you really need to. Most options are configured above

INCLUDES=-I$(INCLUDE_DIR) -I$(SOURCE_DIR) $(LDINCLUDES) $(EXTRA_INCLUDES)

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

# --- FILENAME LISTS: (and other internal variables)
DIR_GUARD=@mkdir -p $(@D)
OBJECT_MAIN=$(OBJECT_DIR)/$(CFG)/$(SOURCE_DIR)/$(patsubst %.c,%.o,$(PROJECT_MAIN))

# Find all C and C++ source files
SOURCES=$(shell find $(SOURCE_DIR) -type f -name "*.c*")

# Setup both C and C++ objects
COBJECTS=$(patsubst $(SOURCE_DIR)/%.c,$(OBJECT_DIR)/$(CFG)/$(SOURCE_DIR)/%.o,$(SOURCES))
OBJECTS=$(patsubst $(SOURCE_DIR)/%.cpp,$(OBJECT_DIR)/$(CFG)/$(SOURCE_DIR)/%.o,$(COBJECTS))

# Setup both C and C++ dependencies
CDEPENDENCIES=$(patsubst $(SOURCE_DIR)/%.c,$(DEPENDENCY_DIR)/$(SOURCE_DIR)/%.d,$(SOURCES))
DEPENDENCIES=$(patsubst $(SOURCE_DIR)/%.cpp,$(DEPENDENCY_DIR)/$(SOURCE_DIR)/%.d,$(CDEPENDENCIES))

# --- GLOBAL TARGETS: You can probably adjust and augment these if you'd like.
.PHONY: all clean clean_all

all: $(BINARY_DIR)/$(CFG)/$(TARGET).elf

clean:
	rm -rf $(OBJECT_DIR)/$(CFG)/* $(BINARY_DIR)/$(CFG)/* $(SOURCE_DIR)/*.gch

clean_all:
	rm -rf $(BUILD_DIR) $(SOURCE_DIR)/*.gch

# RULE TO BUILD YOUR MAIN TARGET HERE: (you may have to edit this, but it is configurable).
$(BINARY_DIR)/$(CFG)/$(TARGET).elf: $(OBJECTS)
	$(DIR_GUARD)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)
	@echo Finished building target: $@
	"arm-none-eabi-objcopy" -O binary "$(BINARY_DIR)/$(CFG)/$(TARGET).elf" "$(BINARY_DIR)/$(CFG)/$(TARGET).bin"
	"arm-none-eabi-objcopy" -O ihex -R .eeprom -R .fuse -R .lock -R .signature "$(BINARY_DIR)/$(CFG)/$(TARGET).elf" "$(BINARY_DIR)/$(CFG)/$(TARGET).hex"
	"arm-none-eabi-objcopy" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma \
		.eeprom=0 --no-change-warnings -O binary "$(BINARY_DIR)/$(CFG)/$(TARGET).elf" "$(BINARY_DIR)/$(CFG)/$(TARGET).eep" || exit 0
	"arm-none-eabi-objdump" -h -S -l "$(BINARY_DIR)/$(CFG)/$(TARGET).elf" > "$(BINARY_DIR)/$(CFG)/$(TARGET).lss"
	"arm-none-eabi-size" -A "$(BINARY_DIR)/$(CFG)/$(TARGET).elf"

# --- Generic Compilation Command

# C Files
$(OBJECT_DIR)/$(CFG)/%.o: %.c
	$(DIR_GUARD)
	$(CC) $(CFLAGS) $< -o $@

# CPP files
$(OBJECT_DIR)/$(CFG)/%.o: %.cpp
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
