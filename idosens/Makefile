#
# (c) 2021-2022, Université Grenoble Alpes, LIG, FabMSTIC
#

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1 


# name of the application
APPLICATION = qrcode_display

EXTERNAL_BOARD_DIRS ?= ../../boards

# If no BOARD is found in the environment, use this default:
BOARD ?= idosens_base

INCLUDES += -I$(CURDIR)/include
INCLUDES += -I$(CURDIR)/bitmap
INCLUDES += -I$(CURDIR)/fonts


# This has to be the absolute path to the RIOT base directory:
# RIOTBASE ?= $(CURDIR)/../../RIOT/

# required modules
#USEMODULE +=  shell
#USEMODULE +=  shell_commands
USEMODULE += xtimer
USEMODULE += crypto_aes_128

USEMODULE += sx1276
LORA_REGION ?= EU868

USEPKG += semtech-loramac
USEPKG += cayenne-lpp
# use package add qrcode
USEPKG += qr-code-generator

USEMODULE += epd_driver
EXTERNAL_MODULE_DIRS += ../../modules/

USEMODULE += $(DRIVER)
USEMODULE += fmt
USEMODULE += printf_float


# required features
#FEATURES_REQUIRED +=  periph_adc
FEATURES_REQUIRED +=  periph_rtc
FEATURES_REQUIRED +=  periph_uart
FEATURES_REQUIRED += periph_spi

# LoRaWAN id and keys
DEVEUI ?= A9C19E521B55E28B 
APPEUI ?= 6B99D2A40E8F0E6699038DB3C22D6768
APPKEY ?= 989D287F1F0970F8AFBF1DCF5B1B04F3 

# Time in seconds between two transmits : default is 5 minutes
TXPERIOD ?= (300U)

# Pass these enviroment variables to docker
DOCKER_ENV_VARS += DEVEUI
DOCKER_ENV_VARS += APPEUI
DOCKER_ENV_VARS += APPKEY
CFLAGS += -Wno-format-nonliteral

include $(RIOTBASE)/Makefile.include


ifndef CONFIG_KCONFIG_USEMODULE_LORAWAN
  # OTAA compile time configuration keys
  CFLAGS += -DCONFIG_LORAMAC_APP_KEY_DEFAULT=\"$(APPKEY)\"
  CFLAGS += -DCONFIG_LORAMAC_APP_EUI_DEFAULT=\"$(APPEUI)\"
  CFLAGS += -DCONFIG_LORAMAC_DEV_EUI_DEFAULT=\"$(DEVEUI)\"
endif





