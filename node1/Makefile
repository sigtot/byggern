# List all source files to be compiled; separate with space
SOURCE_DIR = src
SOURCE_BUILD_DIR = src
SOURCE_FILES = $(wildcard $(SOURCE_DIR)/*.c)

COMMON_SRC_DIR = ../common/src
COMMON_SRC_BUILD_DIR = common/src
COMMON_SRC_FILES = $(wildcard $(COMMON_SRC_DIR)/*.c)

COMMON_LIB_DIR = ../common/lib
COMMON_LIB_BUILD_DIR = common/lib
COMMON_LIB_FILES = $(wildcard $(COMMON_LIB_DIR)/*.c)

LIB_DIR = lib
LIB_BUILD_DIR = lib
LIB_FILES = $(wildcard $(LIB_DIR)/*.c)
# Set this flag to "yes" (no quotes) to use JTAG; otherwise ISP (SPI) is used
PROGRAM_WITH_JTAG := yes

# Feel free to ignore anything below this line
PROGRAMMER := atmelice_isp
ifeq ($(PROGRAM_WITH_JTAG), yes)
	PROGRAMMER := atmelice
endif

BUILD_DIR := build
TARGET_CPU := atmega162
TARGET_DEVICE := m162

CC := avr-gcc
CFLAGS := -O -std=c11 -mmcu=$(TARGET_CPU)

OBJECT_FILES = $(SOURCE_FILES:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/$(SOURCE_BUILD_DIR)/%.o) $(COMMON_SRC_FILES:$(COMMON_SRC_DIR)/%.c=$(BUILD_DIR)/$(COMMON_SRC_BUILD_DIR)/%.o) $(COMMON_LIB_FILES:$(COMMON_LIB_DIR)/%.c=$(BUILD_DIR)/$(COMMON_LIB_BUILD_DIR)/%.o) $(LIB_FILES:$(LIB_DIR)/%.c=$(BUILD_DIR)/$(LIB_BUILD_DIR)/%.o)

.DEFAULT_GOAL := $(BUILD_DIR)/main.hex

$(BUILD_DIR)/$(SOURCE_BUILD_DIR):
	mkdir $(BUILD_DIR)/$(SOURCE_BUILD_DIR) -p

$(BUILD_DIR)/$(COMMON_SRC_BUILD_DIR):
	mkdir $(BUILD_DIR)/$(COMMON_SRC_BUILD_DIR) -p

$(BUILD_DIR)/$(COMMON_LIB_BUILD_DIR):
	mkdir $(BUILD_DIR)/$(COMMON_LIB_BUILD_DIR) -p

$(BUILD_DIR)/$(LIB_BUILD_DIR):
	mkdir $(BUILD_DIR)/$(LIB_BUILD_DIR) -p

$(BUILD_DIR)/$(LIB_BUILD_DIR)/%.o: $(LIB_DIR)/%.c | $(BUILD_DIR)/$(LIB_BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(COMMON_LIB_BUILD_DIR)/%.o: $(COMMON_LIB_DIR)/%.c | $(BUILD_DIR)/$(COMMON_LIB_BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(SOURCE_BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c | $(BUILD_DIR)/$(SOURCE_BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I../common/src -I../common/lib -Wall

$(BUILD_DIR)/$(COMMON_SRC_BUILD_DIR)/%.o: $(COMMON_SRC_DIR)/%.c | $(BUILD_DIR)/$(COMMON_SRC_BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -Isrc -Ilib -Wall

$(BUILD_DIR)/main.hex: $(OBJECT_FILES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o $(BUILD_DIR)/a.out
	avr-objcopy -j .text -j .data -O ihex $(BUILD_DIR)/a.out $(BUILD_DIR)/main.hex

.PHONY: flash
flash: $(BUILD_DIR)/main.hex
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -U flash:w:$(BUILD_DIR)/main.hex:i

.PHONY: fuse
fuse:
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -U efuse:w:0xff:m
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -U hfuse:w:0x19:m
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -U lfuse:w:0xfd:m

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: erase
erase:
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -e
