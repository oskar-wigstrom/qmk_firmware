COMBO_ENABLE = yes
RGBLIGHT_ENABLE = no        # Keyboard RGB underglow
#RGB_MATRIX_ENABLE = yes      # Per key RGB

# Easy definition of combos
VPATH +=  keyboards/gboards/

# Keylogging
CONSOLE_ENABLE = yes

# Extra features that are nice but takes space
WPM_ENABLE = no
EXTRAKEY_ENABLE = no        # For volume keys and similar
MOUSEKEY_ENABLE = no        # Them mouse keys yo
KEY_OVERRIDE_ENABLE = no
TAP_DANCE_ENABLE = no
AUDIO_ENABLE = no

# Saves a bunch of memory
EXTRAFLAGS += -flto
VERBOSE = no
DEBUG_MATRIX_SCAN_RATE  = no
DEBUG_MATRIX = no
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no

# Features
CAPS_WORD_ENABLE = yes
LEADER_ENABLE = yes

# Homerow mods (with sm_td)
DEFERRED_EXEC_ENABLE = yes

SRC += keycodes.c
SRC += features/custom_shift_keys.c
