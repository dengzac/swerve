# Makefile for FRC4159-2017

-include sources.mk

RM := rm -rf
MKDIR := mkdir -p
OUTPUT_DIRS := $(sort $(foreach obj,$(OBJS),$(dir $(obj))))

CPP_PREFIX := arm-frc-linux-gnueabi-
CPP := $(CPP_PREFIX)g++
CFLAGS := -std=c++1y -O0 -Og -g3 -Wall -c -fmessage-length=0

LINK_FLAGS := -Wl,-rpath,/opt/GenICam_v3_0_NI/bin/Linux32_ARM

INCLUDE_FLAGS := $(foreach dir,$(INCLUDE_DIRS),-I"$(dir)")
LIB_FLAGS := $(foreach dir,$(LIB_DIRS),-L"$(dir)")

.PHONY: all
# all target
all: $(BUILD_DIR)/FRCUserProgram

-include $(OBJS:.o=.d)

deploy: $(BUILD_DIR)/FRCUserProgram
	ant

# linting
lint:
	astyle --recursive --suffix=none --options=.astylerc "./src/*.cpp" "./src/*.h"

# Create all output directories
output-dir: $(OUTPUT_DIRS)

# Create directory
$(OUTPUT_DIRS):
	$(MKDIR) $@

# frc-build to build full project
$(BUILD_DIR)/FRCUserProgram: output-dir $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	$(CPP) $(LINK_FLAGS) $(LIB_FLAGS) -o "$(BUILD_DIR)/FRCUserProgram" $(OBJS) -lwpi -lnavx_frc_cpp
	@echo 'Finished building target: $@'
	@echo ' '

# Object files
$(BUILD_DIR)/%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(CPP) $(CFLAGS) $(INCLUDE_FLAGS) -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Clean stuff
clean:
	-$(RM) $(BUILD_DIR)
	-@echo ' '

# Dep files
$(BUILD_DIR)/%.d: $(OUTPUT_DIRS)
	@$(CPP) -MM -MT $(@:.d=.o) $(CFLAGS) $(INCLUDE_FLAGS) $(@:build/%.d=%.cpp) > $@;
