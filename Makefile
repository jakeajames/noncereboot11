ARCHS = arm64

DEBUG = 0

include $(THEOS)/makefiles/common.mk

TOOL_NAME = noncereboot11
$(TOOL_NAME)_FILES = src/debug.c src/finder.c src/ian-find-port.c src/kutils.c src/main.c src/nonce.c src/offsets.c src/unlocknvram.c
$(TOOL_NAME)_CFLAGS += -I$(THEOS_PROJECT_DIR)/headers
$(TOOL_NAME)_FRAMEWORKS = CoreFoundation IOKit
$(TOOL_NAME)_CODESIGN_FLAGS = -Sent.plist

include $(THEOS_MAKE_PATH)/tool.mk
