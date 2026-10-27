MSPM0_SDK_INSTALL_DIR ?= $(abspath ../../../../../..)

include $(MSPM0_SDK_INSTALL_DIR)/tools/imports_mak/imports.mak.linux

CC = "$(TICLANG_ARMCOMPILER)/bin/tiarmclang"
LNK = "$(TICLANG_ARMCOMPILER)/bin/tiarmclang"
OBJCOPY = "$(TICLANG_ARMCOMPILER)/bin/tiarmobjcopy"
BUILDDIR ?= /tmp/build
VPATH = "src"
LINKERFILE = "firmware.ld"

# Simple crypto example (optional); when 1, simple_crypto.c is built (requires USE_AESADV_GCM)
CRYPTO_EXAMPLE = 0

# PIN unwrap (PBKDF2 + GCM) for PIN-based auth (default 1). Uses WolfSSL only for this path.
PIN_UNWRAP ?= 1

# WolfSSL: only for PIN unwrap (PBKDF2 + AES-GCM). Clone: cd firmware && git clone https://github.com/wolfSSL/wolfssl
WOLFSSL_PU_DIR = wolfssl/wolfcrypt/src

OBJECTS = $(BUILDDIR)/HSM.so \
    $(BUILDDIR)/simple_uart.so \
    $(BUILDDIR)/ti_msp_dl_config.so \
    $(BUILDDIR)/startup_mspm0l222x_ticlang.so \
    $(BUILDDIR)/simple_flash.so \
    $(BUILDDIR)/host_messaging.so \
    $(BUILDDIR)/security.so \
    $(BUILDDIR)/filesystem.so \
    $(BUILDDIR)/commands.so \

ifeq ($(CRYPTO_EXAMPLE), 1)
OBJECTS += $(BUILDDIR)/simple_crypto.so
CFLAGS += -DCRYPTO_EXAMPLE=1
endif


ifeq ($(PIN_UNWRAP), 1)
# WolfSSL: include path and flags for PBKDF2 + AES-GCM only
CFLAGS += -I./wolfssl -DWOLFSSL_USER_SETTINGS -DNO_WOLFSSL_DIR -DSINGLE_THREADED
CFLAGS += -DNO_FILESYSTEM -DNO_WRITEV -DTIME_T_NOT_64BIT
CFLAGS += -DHAVE_AESGCM -DWOLFSSL_AESGCM_STREAM
OBJECTS += $(BUILDDIR)/pwdbased.o $(BUILDDIR)/sha256.o $(BUILDDIR)/sha.o $(BUILDDIR)/hmac.o $(BUILDDIR)/hash.o $(BUILDDIR)/md5.o $(BUILDDIR)/aes.o $(BUILDDIR)/curve25519.o $(BUILDDIR)/random.o $(BUILDDIR)/fe_operations.o $(BUILDDIR)/ed25519.o $(BUILDDIR)/sha512.o $(BUILDDIR)/ge_operations.o
ifneq ($(PIN_UNWRAP_USE_AESADV),)
CFLAGS += -DPIN_UNWRAP_USE_AESADV
endif
endif

NAME = hsm

CFLAGS += -I.. \
    -D__MSPM0L2228__ \
    -O2 \
    "-I$(MSPM0_SDK_INSTALL_DIR)/source/third_party/CMSIS/Core/Include" \
    "-I$(MSPM0_SDK_INSTALL_DIR)/source" \
	"-I./inc" \
    -gdwarf-3 \
    -mcpu=cortex-m0plus \
    -march=thumbv6m \
    -mfloat-abi=soft \
    -mthumb

LFLAGS += "-l$(MSPM0_SDK_INSTALL_DIR)/source/ti/drivers/lib/ticlang/m0p/drivers_mspm0l122x_l222x.a" \
    "-l$(MSPM0_SDK_INSTALL_DIR)/kernel/nortos/lib/ticlang/m0p/nortos_mspm0l122x_l222x.a" \
    "-l$(MSPM0_SDK_INSTALL_DIR)/source/ti/driverlib/lib/ticlang/m0p/mspm0l122x_l222x/driverlib.a" \
    "-L$(MSPM0_SDK_INSTALL_DIR)/source" \
    -L.. \
    ./$(LINKERFILE) \
    "-Wl,-m,$(BUILDDIR)/$(NAME).map" \
    -Wl,--rom_model \
    -Wl,--warn_sections \
    "-L$(TICLANG_ARMCOMPILER)/lib" \
    -llibc.a

all: $(BUILDDIR)/$(NAME).elf $(BUILDDIR)/$(NAME).bin

$(BUILDDIR):
	@ mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.so: ./src/%.c | $(BUILDDIR)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

# WolfSSL objects
ifeq ($(PIN_UNWRAP), 1)
$(BUILDDIR)/pwdbased.o: $(WOLFSSL_PU_DIR)/pwdbased.c | $(BUILDDIR)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@
$(BUILDDIR)/sha256.o: $(WOLFSSL_PU_DIR)/sha256.c | $(BUILDDIR)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@
$(BUILDDIR)/sha.o: $(WOLFSSL_PU_DIR)/sha.c | $(BUILDDIR)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@
$(BUILDDIR)/hmac.o: $(WOLFSSL_PU_DIR)/hmac.c | $(BUILDDIR)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@
$(BUILDDIR)/hash.o: $(WOLFSSL_PU_DIR)/hash.c | $(BUILDDIR)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@
$(BUILDDIR)/md5.o: $(WOLFSSL_PU_DIR)/md5.c | $(BUILDDIR)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@
$(BUILDDIR)/aes.o: $(WOLFSSL_PU_DIR)/aes.c | $(BUILDDIR)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@
$(BUILDDIR)/curve25519.o: $(WOLFSSL_PU_DIR)/curve25519.c | $(BUILDDIR)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@
$(BUILDDIR)/random.o: $(WOLFSSL_PU_DIR)/random.c | $(BUILDDIR)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@
$(BUILDDIR)/fe_operations.o: $(WOLFSSL_PU_DIR)/fe_operations.c | $(BUILDDIR)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@
$(BUILDDIR)/ed25519.o: $(WOLFSSL_PU_DIR)/ed25519.c | $(BUILDDIR)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@
$(BUILDDIR)/sha512.o: $(WOLFSSL_PU_DIR)/sha512.c | $(BUILDDIR)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@
$(BUILDDIR)/ge_operations.o: $(WOLFSSL_PU_DIR)/ge_operations.c | $(BUILDDIR)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@
endif

$(BUILDDIR)/$(NAME).elf: $(OBJECTS)
	@ echo linking $@
	@ $(LNK) -Wl,-u,_c_int00 $(OBJECTS)  $(LFLAGS) -o $(BUILDDIR)/$(NAME).elf

$(BUILDDIR)/$(NAME).bin: $(BUILDDIR)/$(NAME).elf
	@ $(OBJCOPY) -O binary $(BUILDDIR)/$(NAME).elf $(BUILDDIR)/$(NAME).bin

clean:
	@ echo Cleaning...
	@ $(RM) $(OBJECTS) > $(DEVNULL) 2>&1
	@ $(RM) $(NAME).elf > $(DEVNULL) 2>&1
	@ $(RM) $(NAME).map > $(DEVNULL) 2>&1
