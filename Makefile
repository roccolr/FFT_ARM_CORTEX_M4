# Toolchain
CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar
SIZE = arm-none-eabi-size

# MCU flags STM32F303 Cortex-M4F
CFLAGS  = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS += -Wall -O2 -ffunction-sections -fdata-sections
CFLAGS += -std=gnu11
CFLAGS += -I./src

# Source and build directories
SRC_DIR = src
BUILD_DIR = build

SRCS = $(SRC_DIR)/fft_math.c $(SRC_DIR)/arm_fft.c
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Output static library
LIBNAME = armfft.a

.PHONY: all clean # .PHONY -> questo target non rappresenta un file 

all: $(BUILD_DIR) $(LIBNAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBNAME): $(OBJS)
	$(AR) rcs $@ $(OBJS)
	$(SIZE) $@

clean:
	rm -rf $(LIBNAME)
