COMBO_ENABLE = yes
RGBLIGHT_ENABLE = no        # Keyboard RGB underglow
RGB_MATRIX_ENABLE = yes      # Per key RGB

# Easy definition of combos
VPATH +=  keyboards/gboards/

# Keylogging
CONSOLE_ENABLE = yes


AUDIO_ENABLE = yes

# Extra features that are nice but takes space
WPM_ENABLE = no
EXTRAKEY_ENABLE = no        # For volume keys and similar
MOUSEKEY_ENABLE = no        # Them mouse keys yo
KEY_OVERRIDE_ENABLE = no
LEADER_ENABLE = no
TAP_DANCE_ENABLE = no

# Saves a bunch of memory
EXTRAFLAGS += -flto
VERBOSE = no
DEBUG_MATRIX_SCAN_RATE  = no
DEBUG_MATRIX = no
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no

# Homerow mods
DEFERRED_EXEC_ENABLE = yes

SRC += oneshot.c
SRC += oneshot_user.c
SRC += layermodes.c
SRC += leader.c
SRC += leader_user.c
SRC += casemodes.c
SRC += casemodes_user.c
SRC += tap_hold.c
SRC += tap_hold_user.c
SRC += utils.c
