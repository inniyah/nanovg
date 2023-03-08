# https://wiki.libsdl.org/SDL_Keymod

from types import SimpleNamespace

KMOD = SimpleNamespace(
    NONE               = SDL2.KMOD_NONE,
    LSHIFT             = SDL2.KMOD_LSHIFT,
    RSHIFT             = SDL2.KMOD_RSHIFT,
    LCTRL              = SDL2.KMOD_LCTRL,
    RCTRL              = SDL2.KMOD_RCTRL,
    LALT               = SDL2.KMOD_LALT,
    RALT               = SDL2.KMOD_RALT,
    LGUI               = SDL2.KMOD_LGUI,
    RGUI               = SDL2.KMOD_RGUI,
    NUM                = SDL2.KMOD_NUM,
    CAPS               = SDL2.KMOD_CAPS,
    MODE               = SDL2.KMOD_MODE,
    CTRL               = SDL2.KMOD_CTRL,
    SHIFT              = SDL2.KMOD_SHIFT,
    ALT                = SDL2.KMOD_ALT,
    GUI                = SDL2.KMOD_GUI,
)

# https://wiki.libsdl.org/SDL_Keycode

SDLK = SimpleNamespace(
    N0                  = SDL2.SDLK_0,
    N1                  = SDL2.SDLK_1,
    N2                  = SDL2.SDLK_2,
    N3                  = SDL2.SDLK_3,
    N4                  = SDL2.SDLK_4,
    N5                  = SDL2.SDLK_5,
    N6                  = SDL2.SDLK_6,
    N7                  = SDL2.SDLK_7,
    N8                  = SDL2.SDLK_8,
    N9                  = SDL2.SDLK_9,

    A                  = SDL2.SDLK_a,
    B                  = SDL2.SDLK_b,
    C                  = SDL2.SDLK_c,
    D                  = SDL2.SDLK_d,
    E                  = SDL2.SDLK_e,
    F                  = SDL2.SDLK_f,
    G                  = SDL2.SDLK_g,
    H                  = SDL2.SDLK_h,
    I                  = SDL2.SDLK_i,
    J                  = SDL2.SDLK_j,
    K                  = SDL2.SDLK_k,
    L                  = SDL2.SDLK_l,
    M                  = SDL2.SDLK_m,
    N                  = SDL2.SDLK_n,
    O                  = SDL2.SDLK_o,
    P                  = SDL2.SDLK_p,
    Q                  = SDL2.SDLK_q,
    R                  = SDL2.SDLK_r,
    S                  = SDL2.SDLK_s,
    T                  = SDL2.SDLK_t,
    U                  = SDL2.SDLK_u,
    V                  = SDL2.SDLK_v,
    W                  = SDL2.SDLK_w,
    X                  = SDL2.SDLK_x,
    Y                  = SDL2.SDLK_y,
    Z                  = SDL2.SDLK_z,

    F1                 = SDL2.SDLK_F1,
    F2                 = SDL2.SDLK_F2,
    F3                 = SDL2.SDLK_F3,
    F4                 = SDL2.SDLK_F4,
    F5                 = SDL2.SDLK_F5,
    F6                 = SDL2.SDLK_F6,
    F7                 = SDL2.SDLK_F7,
    F8                 = SDL2.SDLK_F8,
    F9                 = SDL2.SDLK_F9,
    F10                = SDL2.SDLK_F10,
    F11                = SDL2.SDLK_F11,
    F12                = SDL2.SDLK_F12,
    F13                = SDL2.SDLK_F13,
    F14                = SDL2.SDLK_F14,
    F15                = SDL2.SDLK_F15,
    F16                = SDL2.SDLK_F16,
    F17                = SDL2.SDLK_F17,
    F18                = SDL2.SDLK_F18,
    F19                = SDL2.SDLK_F19,
    F20                = SDL2.SDLK_F20,
    F21                = SDL2.SDLK_F21,
    F22                = SDL2.SDLK_F22,
    F23                = SDL2.SDLK_F23,
    F24                = SDL2.SDLK_F24,

    AGAIN              = SDL2.SDLK_AGAIN,
    ALTERASE           = SDL2.SDLK_ALTERASE,
    QUOTE              = SDL2.SDLK_QUOTE,
    APPLICATION        = SDL2.SDLK_APPLICATION,
    AUDIOMUTE          = SDL2.SDLK_AUDIOMUTE,
    AUDIONEXT          = SDL2.SDLK_AUDIONEXT,
    AUDIOPLAY          = SDL2.SDLK_AUDIOPLAY,
    AUDIOPREV          = SDL2.SDLK_AUDIOPREV,
    AUDIOSTOP          = SDL2.SDLK_AUDIOSTOP,
    BACKSLASH          = SDL2.SDLK_BACKSLASH,
    BACKSPACE          = SDL2.SDLK_BACKSPACE,
    BRIGHTNESSDOWN     = SDL2.SDLK_BRIGHTNESSDOWN,
    BRIGHTNESSUP       = SDL2.SDLK_BRIGHTNESSUP,
    CALCULATOR         = SDL2.SDLK_CALCULATOR,
    CANCEL             = SDL2.SDLK_CANCEL,
    CAPSLOCK           = SDL2.SDLK_CAPSLOCK,
    CLEAR              = SDL2.SDLK_CLEAR,
    CLEARAGAIN         = SDL2.SDLK_CLEARAGAIN,
    COMMA              = SDL2.SDLK_COMMA,
    COMPUTER           = SDL2.SDLK_COMPUTER,
    COPY               = SDL2.SDLK_COPY,
    CRSEL              = SDL2.SDLK_CRSEL,
    CURRENCYSUBUNIT    = SDL2.SDLK_CURRENCYSUBUNIT,
    CURRENCYUNIT       = SDL2.SDLK_CURRENCYUNIT,
    CUT                = SDL2.SDLK_CUT,
    DECIMALSEPARATOR   = SDL2.SDLK_DECIMALSEPARATOR,
    DELETE             = SDL2.SDLK_DELETE,
    DISPLAYSWITCH      = SDL2.SDLK_DISPLAYSWITCH,
    DOWN               = SDL2.SDLK_DOWN,
    EJECT              = SDL2.SDLK_EJECT,
    END                = SDL2.SDLK_END,
    EQUALS             = SDL2.SDLK_EQUALS,
    ESCAPE             = SDL2.SDLK_ESCAPE,
    EXECUTE            = SDL2.SDLK_EXECUTE,
    EXSEL              = SDL2.SDLK_EXSEL,
    FIND               = SDL2.SDLK_FIND,
    BACKQUOTE          = SDL2.SDLK_BACKQUOTE,
    HELP               = SDL2.SDLK_HELP,
    HOME               = SDL2.SDLK_HOME,
    INSERT             = SDL2.SDLK_INSERT,
    KBDILLUMDOWN       = SDL2.SDLK_KBDILLUMDOWN,
    KBDILLUMTOGGLE     = SDL2.SDLK_KBDILLUMTOGGLE,
    KBDILLUMUP         = SDL2.SDLK_KBDILLUMUP,
    LALT               = SDL2.SDLK_LALT,
    LCTRL              = SDL2.SDLK_LCTRL,
    LEFT               = SDL2.SDLK_LEFT,
    LEFTBRACKET        = SDL2.SDLK_LEFTBRACKET,
    LGUI               = SDL2.SDLK_LGUI,
    LSHIFT             = SDL2.SDLK_LSHIFT,
    MAIL               = SDL2.SDLK_MAIL,
    MEDIASELECT        = SDL2.SDLK_MEDIASELECT,
    MENU               = SDL2.SDLK_MENU,
    MINUS              = SDL2.SDLK_MINUS,
    MODE               = SDL2.SDLK_MODE,
    MUTE               = SDL2.SDLK_MUTE,
    NUMLOCKCLEAR       = SDL2.SDLK_NUMLOCKCLEAR,
    OPER               = SDL2.SDLK_OPER,
    OUT                = SDL2.SDLK_OUT,
    PAGEDOWN           = SDL2.SDLK_PAGEDOWN,
    PAGEUP             = SDL2.SDLK_PAGEUP,
    PASTE              = SDL2.SDLK_PASTE,
    PAUSE              = SDL2.SDLK_PAUSE,
    PERIOD             = SDL2.SDLK_PERIOD,
    POWER              = SDL2.SDLK_POWER,
    PRINTSCREEN        = SDL2.SDLK_PRINTSCREEN,
    PRIOR              = SDL2.SDLK_PRIOR,
    RALT               = SDL2.SDLK_RALT,
    RCTRL              = SDL2.SDLK_RCTRL,
    RETURN             = SDL2.SDLK_RETURN,
    RETURN2            = SDL2.SDLK_RETURN2,
    RGUI               = SDL2.SDLK_RGUI,
    RIGHT              = SDL2.SDLK_RIGHT,
    RIGHTBRACKET       = SDL2.SDLK_RIGHTBRACKET,
    RSHIFT             = SDL2.SDLK_RSHIFT,
    SCROLLLOCK         = SDL2.SDLK_SCROLLLOCK,
    SELECT             = SDL2.SDLK_SELECT,
    SEMICOLON          = SDL2.SDLK_SEMICOLON,
    SEPARATOR          = SDL2.SDLK_SEPARATOR,
    SLASH              = SDL2.SDLK_SLASH,
    SLEEP              = SDL2.SDLK_SLEEP,
    SPACE              = SDL2.SDLK_SPACE,
    STOP               = SDL2.SDLK_STOP,
    SYSREQ             = SDL2.SDLK_SYSREQ,
    TAB                = SDL2.SDLK_TAB,
    THOUSANDSSEPARATOR = SDL2.SDLK_THOUSANDSSEPARATOR,
    UNDO               = SDL2.SDLK_UNDO,
    UNKNOWN            = SDL2.SDLK_UNKNOWN,
    UP                 = SDL2.SDLK_UP,
    VOLUMEDOWN         = SDL2.SDLK_VOLUMEDOWN,
    VOLUMEUP           = SDL2.SDLK_VOLUMEUP,
    WWW                = SDL2.SDLK_WWW,
    AMPERSAND          = SDL2.SDLK_AMPERSAND,
    ASTERISK           = SDL2.SDLK_ASTERISK,
    AT                 = SDL2.SDLK_AT,
    CARET              = SDL2.SDLK_CARET,
    COLON              = SDL2.SDLK_COLON,
    DOLLAR             = SDL2.SDLK_DOLLAR,
    EXCLAIM            = SDL2.SDLK_EXCLAIM,
    GREATER            = SDL2.SDLK_GREATER,
    HASH               = SDL2.SDLK_HASH,
    LEFTPAREN          = SDL2.SDLK_LEFTPAREN,
    LESS               = SDL2.SDLK_LESS,
    PERCENT            = SDL2.SDLK_PERCENT,
    PLUS               = SDL2.SDLK_PLUS,
    QUESTION           = SDL2.SDLK_QUESTION,
    QUOTEDBL           = SDL2.SDLK_QUOTEDBL,
    RIGHTPAREN         = SDL2.SDLK_RIGHTPAREN,
    UNDERSCORE         = SDL2.SDLK_UNDERSCORE,

    AC_BACK            = SDL2.SDLK_AC_BACK,
    AC_BOOKMARKS       = SDL2.SDLK_AC_BOOKMARKS,
    AC_FORWARD         = SDL2.SDLK_AC_FORWARD,
    AC_HOME            = SDL2.SDLK_AC_HOME,
    AC_REFRESH         = SDL2.SDLK_AC_REFRESH,
    AC_SEARCH          = SDL2.SDLK_AC_SEARCH,
    AC_STOP            = SDL2.SDLK_AC_STOP,

    KP_0               = SDL2.SDLK_KP_0,
    KP_00              = SDL2.SDLK_KP_00,
    KP_000             = SDL2.SDLK_KP_000,
    KP_1               = SDL2.SDLK_KP_1,
    KP_2               = SDL2.SDLK_KP_2,
    KP_3               = SDL2.SDLK_KP_3,
    KP_4               = SDL2.SDLK_KP_4,
    KP_5               = SDL2.SDLK_KP_5,
    KP_6               = SDL2.SDLK_KP_6,
    KP_7               = SDL2.SDLK_KP_7,
    KP_8               = SDL2.SDLK_KP_8,
    KP_9               = SDL2.SDLK_KP_9,
    KP_A               = SDL2.SDLK_KP_A,
    KP_B               = SDL2.SDLK_KP_B,
    KP_C               = SDL2.SDLK_KP_C,
    KP_D               = SDL2.SDLK_KP_D,
    KP_E               = SDL2.SDLK_KP_E,
    KP_F               = SDL2.SDLK_KP_F,

    KP_AMPERSAND       = SDL2.SDLK_KP_AMPERSAND,
    KP_AT              = SDL2.SDLK_KP_AT,
    KP_BACKSPACE       = SDL2.SDLK_KP_BACKSPACE,
    KP_BINARY          = SDL2.SDLK_KP_BINARY,
    KP_CLEAR           = SDL2.SDLK_KP_CLEAR,
    KP_CLEARENTRY      = SDL2.SDLK_KP_CLEARENTRY,
    KP_COLON           = SDL2.SDLK_KP_COLON,
    KP_COMMA           = SDL2.SDLK_KP_COMMA,
    KP_DBLAMPERSAND    = SDL2.SDLK_KP_DBLAMPERSAND,
    KP_DECIMAL         = SDL2.SDLK_KP_DECIMAL,
    KP_DIVIDE          = SDL2.SDLK_KP_DIVIDE,
    KP_ENTER           = SDL2.SDLK_KP_ENTER,
    KP_EQUALS          = SDL2.SDLK_KP_EQUALS,
    KP_EQUALSAS400     = SDL2.SDLK_KP_EQUALSAS400,
    KP_EXCLAM          = SDL2.SDLK_KP_EXCLAM,
    KP_GREATER         = SDL2.SDLK_KP_GREATER,
    KP_HASH            = SDL2.SDLK_KP_HASH,
    KP_HEXADECIMAL     = SDL2.SDLK_KP_HEXADECIMAL,
    KP_LEFTBRACE       = SDL2.SDLK_KP_LEFTBRACE,
    KP_LEFTPAREN       = SDL2.SDLK_KP_LEFTPAREN,
    KP_LESS            = SDL2.SDLK_KP_LESS,
    KP_MEMADD          = SDL2.SDLK_KP_MEMADD,
    KP_MEMCLEAR        = SDL2.SDLK_KP_MEMCLEAR,
    KP_MEMDIVIDE       = SDL2.SDLK_KP_MEMDIVIDE,
    KP_MEMMULTIPLY     = SDL2.SDLK_KP_MEMMULTIPLY,
    KP_MEMRECALL       = SDL2.SDLK_KP_MEMRECALL,
    KP_MEMSTORE        = SDL2.SDLK_KP_MEMSTORE,
    KP_MEMSUBTRACT     = SDL2.SDLK_KP_MEMSUBTRACT,
    KP_MINUS           = SDL2.SDLK_KP_MINUS,
    KP_MULTIPLY        = SDL2.SDLK_KP_MULTIPLY,
    KP_OCTAL           = SDL2.SDLK_KP_OCTAL,
    KP_PERCENT         = SDL2.SDLK_KP_PERCENT,
    KP_PERIOD          = SDL2.SDLK_KP_PERIOD,
    KP_PLUS            = SDL2.SDLK_KP_PLUS,
    KP_PLUSMINUS       = SDL2.SDLK_KP_PLUSMINUS,
    KP_POWER           = SDL2.SDLK_KP_POWER,
    KP_RIGHTBRACE      = SDL2.SDLK_KP_RIGHTBRACE,
    KP_RIGHTPAREN      = SDL2.SDLK_KP_RIGHTPAREN,
    KP_SPACE           = SDL2.SDLK_KP_SPACE,
    KP_TAB             = SDL2.SDLK_KP_TAB,
    KP_VERTICALBAR     = SDL2.SDLK_KP_VERTICALBAR,
    KP_XOR             = SDL2.SDLK_KP_XOR,
)

# https://wiki.libsdl.org/SDL_Scancode

SCANCODE = SimpleNamespace(
    N0                 = SDL2.SDL_SCANCODE_0,
    N1                 = SDL2.SDL_SCANCODE_1,
    N2                 = SDL2.SDL_SCANCODE_2,
    N3                 = SDL2.SDL_SCANCODE_3,
    N4                 = SDL2.SDL_SCANCODE_4,
    N5                 = SDL2.SDL_SCANCODE_5,
    N6                 = SDL2.SDL_SCANCODE_6,
    N7                 = SDL2.SDL_SCANCODE_7,
    N8                 = SDL2.SDL_SCANCODE_8,
    N9                 = SDL2.SDL_SCANCODE_9,
    A                  = SDL2.SDL_SCANCODE_A,
    AC_BACK            = SDL2.SDL_SCANCODE_AC_BACK,
    AC_BOOKMARKS       = SDL2.SDL_SCANCODE_AC_BOOKMARKS,
    AC_FORWARD         = SDL2.SDL_SCANCODE_AC_FORWARD,
    AC_HOME            = SDL2.SDL_SCANCODE_AC_HOME,
    AC_REFRESH         = SDL2.SDL_SCANCODE_AC_REFRESH,
    AC_SEARCH          = SDL2.SDL_SCANCODE_AC_SEARCH,
    AC_STOP            = SDL2.SDL_SCANCODE_AC_STOP,
    AGAIN              = SDL2.SDL_SCANCODE_AGAIN,
    ALTERASE           = SDL2.SDL_SCANCODE_ALTERASE,
    APOSTROPHE         = SDL2.SDL_SCANCODE_APOSTROPHE,
    APPLICATION        = SDL2.SDL_SCANCODE_APPLICATION,
    AUDIOMUTE          = SDL2.SDL_SCANCODE_AUDIOMUTE,
    AUDIONEXT          = SDL2.SDL_SCANCODE_AUDIONEXT,
    AUDIOPLAY          = SDL2.SDL_SCANCODE_AUDIOPLAY,
    AUDIOPREV          = SDL2.SDL_SCANCODE_AUDIOPREV,
    AUDIOSTOP          = SDL2.SDL_SCANCODE_AUDIOSTOP,
    B                  = SDL2.SDL_SCANCODE_B,
    BACKSLASH          = SDL2.SDL_SCANCODE_BACKSLASH,
    BACKSPACE          = SDL2.SDL_SCANCODE_BACKSPACE,
    BRIGHTNESSDOWN     = SDL2.SDL_SCANCODE_BRIGHTNESSDOWN,
    BRIGHTNESSUP       = SDL2.SDL_SCANCODE_BRIGHTNESSUP,
    C                  = SDL2.SDL_SCANCODE_C,
    CALCULATOR         = SDL2.SDL_SCANCODE_CALCULATOR,
    CANCEL             = SDL2.SDL_SCANCODE_CANCEL,
    CAPSLOCK           = SDL2.SDL_SCANCODE_CAPSLOCK,
    CLEAR              = SDL2.SDL_SCANCODE_CLEAR,
    CLEARAGAIN         = SDL2.SDL_SCANCODE_CLEARAGAIN,
    COMMA              = SDL2.SDL_SCANCODE_COMMA,
    COMPUTER           = SDL2.SDL_SCANCODE_COMPUTER,
    COPY               = SDL2.SDL_SCANCODE_COPY,
    CRSEL              = SDL2.SDL_SCANCODE_CRSEL,
    CURRENCYSUBUNIT    = SDL2.SDL_SCANCODE_CURRENCYSUBUNIT,
    CURRENCYUNIT       = SDL2.SDL_SCANCODE_CURRENCYUNIT,
    CUT                = SDL2.SDL_SCANCODE_CUT,
    D                  = SDL2.SDL_SCANCODE_D,
    DECIMALSEPARATOR   = SDL2.SDL_SCANCODE_DECIMALSEPARATOR,
    DELETE             = SDL2.SDL_SCANCODE_DELETE,
    DISPLAYSWITCH      = SDL2.SDL_SCANCODE_DISPLAYSWITCH,
    DOWN               = SDL2.SDL_SCANCODE_DOWN,
    E                  = SDL2.SDL_SCANCODE_E,
    EJECT              = SDL2.SDL_SCANCODE_EJECT,
    END                = SDL2.SDL_SCANCODE_END,
    EQUALS             = SDL2.SDL_SCANCODE_EQUALS,
    ESCAPE             = SDL2.SDL_SCANCODE_ESCAPE,
    EXECUTE            = SDL2.SDL_SCANCODE_EXECUTE,
    EXSEL              = SDL2.SDL_SCANCODE_EXSEL,
    F                  = SDL2.SDL_SCANCODE_F,
    F1                 = SDL2.SDL_SCANCODE_F1,
    F10                = SDL2.SDL_SCANCODE_F10,
    F11                = SDL2.SDL_SCANCODE_F11,
    F12                = SDL2.SDL_SCANCODE_F12,
    F13                = SDL2.SDL_SCANCODE_F13,
    F14                = SDL2.SDL_SCANCODE_F14,
    F15                = SDL2.SDL_SCANCODE_F15,
    F16                = SDL2.SDL_SCANCODE_F16,
    F17                = SDL2.SDL_SCANCODE_F17,
    F18                = SDL2.SDL_SCANCODE_F18,
    F19                = SDL2.SDL_SCANCODE_F19,
    F2                 = SDL2.SDL_SCANCODE_F2,
    F20                = SDL2.SDL_SCANCODE_F20,
    F21                = SDL2.SDL_SCANCODE_F21,
    F22                = SDL2.SDL_SCANCODE_F22,
    F23                = SDL2.SDL_SCANCODE_F23,
    F24                = SDL2.SDL_SCANCODE_F24,
    F3                 = SDL2.SDL_SCANCODE_F3,
    F4                 = SDL2.SDL_SCANCODE_F4,
    F5                 = SDL2.SDL_SCANCODE_F5,
    F6                 = SDL2.SDL_SCANCODE_F6,
    F7                 = SDL2.SDL_SCANCODE_F7,
    F8                 = SDL2.SDL_SCANCODE_F8,
    F9                 = SDL2.SDL_SCANCODE_F9,
    FIND               = SDL2.SDL_SCANCODE_FIND,
    G                  = SDL2.SDL_SCANCODE_G,
    GRAVE              = SDL2.SDL_SCANCODE_GRAVE,
    H                  = SDL2.SDL_SCANCODE_H,
    HELP               = SDL2.SDL_SCANCODE_HELP,
    HOME               = SDL2.SDL_SCANCODE_HOME,
    I                  = SDL2.SDL_SCANCODE_I,
    INSERT             = SDL2.SDL_SCANCODE_INSERT,
    J                  = SDL2.SDL_SCANCODE_J,
    K                  = SDL2.SDL_SCANCODE_K,
    KBDILLUMDOWN       = SDL2.SDL_SCANCODE_KBDILLUMDOWN,
    KBDILLUMTOGGLE     = SDL2.SDL_SCANCODE_KBDILLUMTOGGLE,
    KBDILLUMUP         = SDL2.SDL_SCANCODE_KBDILLUMUP,
    KP_0               = SDL2.SDL_SCANCODE_KP_0,
    KP_00              = SDL2.SDL_SCANCODE_KP_00,
    KP_000             = SDL2.SDL_SCANCODE_KP_000,
    KP_1               = SDL2.SDL_SCANCODE_KP_1,
    KP_2               = SDL2.SDL_SCANCODE_KP_2,
    KP_3               = SDL2.SDL_SCANCODE_KP_3,
    KP_4               = SDL2.SDL_SCANCODE_KP_4,
    KP_5               = SDL2.SDL_SCANCODE_KP_5,
    KP_6               = SDL2.SDL_SCANCODE_KP_6,
    KP_7               = SDL2.SDL_SCANCODE_KP_7,
    KP_8               = SDL2.SDL_SCANCODE_KP_8,
    KP_9               = SDL2.SDL_SCANCODE_KP_9,
    KP_A               = SDL2.SDL_SCANCODE_KP_A,
    KP_AMPERSAND       = SDL2.SDL_SCANCODE_KP_AMPERSAND,
    KP_AT              = SDL2.SDL_SCANCODE_KP_AT,
    KP_B               = SDL2.SDL_SCANCODE_KP_B,
    KP_BACKSPACE       = SDL2.SDL_SCANCODE_KP_BACKSPACE,
    KP_BINARY          = SDL2.SDL_SCANCODE_KP_BINARY,
    KP_C               = SDL2.SDL_SCANCODE_KP_C,
    KP_CLEAR           = SDL2.SDL_SCANCODE_KP_CLEAR,
    KP_CLEARENTRY      = SDL2.SDL_SCANCODE_KP_CLEARENTRY,
    KP_COLON           = SDL2.SDL_SCANCODE_KP_COLON,
    KP_COMMA           = SDL2.SDL_SCANCODE_KP_COMMA,
    KP_D               = SDL2.SDL_SCANCODE_KP_D,
    KP_DBLAMPERSAND    = SDL2.SDL_SCANCODE_KP_DBLAMPERSAND,
    KP_DECIMAL         = SDL2.SDL_SCANCODE_KP_DECIMAL,
    KP_DIVIDE          = SDL2.SDL_SCANCODE_KP_DIVIDE,
    KP_E               = SDL2.SDL_SCANCODE_KP_E,
    KP_ENTER           = SDL2.SDL_SCANCODE_KP_ENTER,
    KP_EQUALS          = SDL2.SDL_SCANCODE_KP_EQUALS,
    KP_EQUALSAS400     = SDL2.SDL_SCANCODE_KP_EQUALSAS400,
    KP_EXCLAM          = SDL2.SDL_SCANCODE_KP_EXCLAM,
    KP_F               = SDL2.SDL_SCANCODE_KP_F,
    KP_GREATER         = SDL2.SDL_SCANCODE_KP_GREATER,
    KP_HASH            = SDL2.SDL_SCANCODE_KP_HASH,
    KP_HEXADECIMAL     = SDL2.SDL_SCANCODE_KP_HEXADECIMAL,
    KP_LEFTBRACE       = SDL2.SDL_SCANCODE_KP_LEFTBRACE,
    KP_LEFTPAREN       = SDL2.SDL_SCANCODE_KP_LEFTPAREN,
    KP_LESS            = SDL2.SDL_SCANCODE_KP_LESS,
    KP_MEMADD          = SDL2.SDL_SCANCODE_KP_MEMADD,
    KP_MEMCLEAR        = SDL2.SDL_SCANCODE_KP_MEMCLEAR,
    KP_MEMDIVIDE       = SDL2.SDL_SCANCODE_KP_MEMDIVIDE,
    KP_MEMMULTIPLY     = SDL2.SDL_SCANCODE_KP_MEMMULTIPLY,
    KP_MEMRECALL       = SDL2.SDL_SCANCODE_KP_MEMRECALL,
    KP_MEMSTORE        = SDL2.SDL_SCANCODE_KP_MEMSTORE,
    KP_MEMSUBTRACT     = SDL2.SDL_SCANCODE_KP_MEMSUBTRACT,
    KP_MINUS           = SDL2.SDL_SCANCODE_KP_MINUS,
    KP_MULTIPLY        = SDL2.SDL_SCANCODE_KP_MULTIPLY,
    KP_OCTAL           = SDL2.SDL_SCANCODE_KP_OCTAL,
    KP_PERCENT         = SDL2.SDL_SCANCODE_KP_PERCENT,
    KP_PERIOD          = SDL2.SDL_SCANCODE_KP_PERIOD,
    KP_PLUS            = SDL2.SDL_SCANCODE_KP_PLUS,
    KP_PLUSMINUS       = SDL2.SDL_SCANCODE_KP_PLUSMINUS,
    KP_POWER           = SDL2.SDL_SCANCODE_KP_POWER,
    KP_RIGHTBRACE      = SDL2.SDL_SCANCODE_KP_RIGHTBRACE,
    KP_RIGHTPAREN      = SDL2.SDL_SCANCODE_KP_RIGHTPAREN,
    KP_SPACE           = SDL2.SDL_SCANCODE_KP_SPACE,
    KP_TAB             = SDL2.SDL_SCANCODE_KP_TAB,
    KP_VERTICALBAR     = SDL2.SDL_SCANCODE_KP_VERTICALBAR,
    KP_XOR             = SDL2.SDL_SCANCODE_KP_XOR,
    L                  = SDL2.SDL_SCANCODE_L,
    LALT               = SDL2.SDL_SCANCODE_LALT,
    LCTRL              = SDL2.SDL_SCANCODE_LCTRL,
    LEFT               = SDL2.SDL_SCANCODE_LEFT,
    LEFTBRACKET        = SDL2.SDL_SCANCODE_LEFTBRACKET,
    LGUI               = SDL2.SDL_SCANCODE_LGUI,
    LSHIFT             = SDL2.SDL_SCANCODE_LSHIFT,
    M                  = SDL2.SDL_SCANCODE_M,
    MAIL               = SDL2.SDL_SCANCODE_MAIL,
    MEDIASELECT        = SDL2.SDL_SCANCODE_MEDIASELECT,
    MENU               = SDL2.SDL_SCANCODE_MENU,
    MINUS              = SDL2.SDL_SCANCODE_MINUS,
    MODE               = SDL2.SDL_SCANCODE_MODE,
    MUTE               = SDL2.SDL_SCANCODE_MUTE,
    N                  = SDL2.SDL_SCANCODE_N,
    NUMLOCKCLEAR       = SDL2.SDL_SCANCODE_NUMLOCKCLEAR,
    O                  = SDL2.SDL_SCANCODE_O,
    OPER               = SDL2.SDL_SCANCODE_OPER,
    OUT                = SDL2.SDL_SCANCODE_OUT,
    P                  = SDL2.SDL_SCANCODE_P,
    PAGEDOWN           = SDL2.SDL_SCANCODE_PAGEDOWN,
    PAGEUP             = SDL2.SDL_SCANCODE_PAGEUP,
    PASTE              = SDL2.SDL_SCANCODE_PASTE,
    PAUSE              = SDL2.SDL_SCANCODE_PAUSE,
    PERIOD             = SDL2.SDL_SCANCODE_PERIOD,
    POWER              = SDL2.SDL_SCANCODE_POWER,
    PRINTSCREEN        = SDL2.SDL_SCANCODE_PRINTSCREEN,
    PRIOR              = SDL2.SDL_SCANCODE_PRIOR,
    Q                  = SDL2.SDL_SCANCODE_Q,
    R                  = SDL2.SDL_SCANCODE_R,
    RALT               = SDL2.SDL_SCANCODE_RALT,
    RCTRL              = SDL2.SDL_SCANCODE_RCTRL,
    RETURN             = SDL2.SDL_SCANCODE_RETURN,
    RETURN2            = SDL2.SDL_SCANCODE_RETURN2,
    RGUI               = SDL2.SDL_SCANCODE_RGUI,
    RIGHT              = SDL2.SDL_SCANCODE_RIGHT,
    RIGHTBRACKET       = SDL2.SDL_SCANCODE_RIGHTBRACKET,
    RSHIFT             = SDL2.SDL_SCANCODE_RSHIFT,
    S                  = SDL2.SDL_SCANCODE_S,
    SCROLLLOCK         = SDL2.SDL_SCANCODE_SCROLLLOCK,
    SELECT             = SDL2.SDL_SCANCODE_SELECT,
    SEMICOLON          = SDL2.SDL_SCANCODE_SEMICOLON,
    SEPARATOR          = SDL2.SDL_SCANCODE_SEPARATOR,
    SLASH              = SDL2.SDL_SCANCODE_SLASH,
    SLEEP              = SDL2.SDL_SCANCODE_SLEEP,
    SPACE              = SDL2.SDL_SCANCODE_SPACE,
    STOP               = SDL2.SDL_SCANCODE_STOP,
    SYSREQ             = SDL2.SDL_SCANCODE_SYSREQ,
    T                  = SDL2.SDL_SCANCODE_T,
    TAB                = SDL2.SDL_SCANCODE_TAB,
    THOUSANDSSEPARATOR = SDL2.SDL_SCANCODE_THOUSANDSSEPARATOR,
    U                  = SDL2.SDL_SCANCODE_U,
    UNDO               = SDL2.SDL_SCANCODE_UNDO,
    UNKNOWN            = SDL2.SDL_SCANCODE_UNKNOWN,
    UP                 = SDL2.SDL_SCANCODE_UP,
    V                  = SDL2.SDL_SCANCODE_V,
    VOLUMEDOWN         = SDL2.SDL_SCANCODE_VOLUMEDOWN,
    VOLUMEUP           = SDL2.SDL_SCANCODE_VOLUMEUP,
    W                  = SDL2.SDL_SCANCODE_W,
    WWW                = SDL2.SDL_SCANCODE_WWW,
    X                  = SDL2.SDL_SCANCODE_X,
    Y                  = SDL2.SDL_SCANCODE_Y,
    Z                  = SDL2.SDL_SCANCODE_Z,
    INTERNATIONAL1     = SDL2.SDL_SCANCODE_INTERNATIONAL1,
    INTERNATIONAL2     = SDL2.SDL_SCANCODE_INTERNATIONAL2,
    INTERNATIONAL3     = SDL2.SDL_SCANCODE_INTERNATIONAL3,
    INTERNATIONAL4     = SDL2.SDL_SCANCODE_INTERNATIONAL4,
    INTERNATIONAL5     = SDL2.SDL_SCANCODE_INTERNATIONAL5,
    INTERNATIONAL6     = SDL2.SDL_SCANCODE_INTERNATIONAL6,
    INTERNATIONAL7     = SDL2.SDL_SCANCODE_INTERNATIONAL7,
    INTERNATIONAL8     = SDL2.SDL_SCANCODE_INTERNATIONAL8,
    INTERNATIONAL9     = SDL2.SDL_SCANCODE_INTERNATIONAL9,
    LANG1              = SDL2.SDL_SCANCODE_LANG1,
    LANG2              = SDL2.SDL_SCANCODE_LANG2,
    LANG3              = SDL2.SDL_SCANCODE_LANG3,
    LANG4              = SDL2.SDL_SCANCODE_LANG4,
    LANG5              = SDL2.SDL_SCANCODE_LANG5,
    LANG6              = SDL2.SDL_SCANCODE_LANG6,
    LANG7              = SDL2.SDL_SCANCODE_LANG7,
    LANG8              = SDL2.SDL_SCANCODE_LANG8,
    LANG9              = SDL2.SDL_SCANCODE_LANG9,
    NONUSBACKSLASH     = SDL2.SDL_SCANCODE_NONUSBACKSLASH,
    NONUSHASH          = SDL2.SDL_SCANCODE_NONUSHASH,
)

SDL_WINDOW = SimpleNamespace(
    FULLSCREEN         = SDL2.SDL_WINDOW_FULLSCREEN,
    OPENGL             = SDL2.SDL_WINDOW_OPENGL,
    SHOWN              = SDL2.SDL_WINDOW_SHOWN,
    HIDDEN             = SDL2.SDL_WINDOW_HIDDEN,
    BORDERLESS         = SDL2.SDL_WINDOW_BORDERLESS,
    RESIZABLE          = SDL2.SDL_WINDOW_RESIZABLE,
    MINIMIZED          = SDL2.SDL_WINDOW_MINIMIZED,
    MAXIMIZED          = SDL2.SDL_WINDOW_MAXIMIZED,
    INPUT_GRABBED      = SDL2.SDL_WINDOW_INPUT_GRABBED,
    INPUT_FOCUS        = SDL2.SDL_WINDOW_INPUT_FOCUS,
    MOUSE_FOCUS        = SDL2.SDL_WINDOW_MOUSE_FOCUS,
    FULLSCREEN_DESKTOP = SDL2.SDL_WINDOW_FULLSCREEN_DESKTOP,
    FOREIGN            = SDL2.SDL_WINDOW_FOREIGN,
    ALLOW_HIGHDPI      = SDL2.SDL_WINDOW_ALLOW_HIGHDPI,

    EVENT_NONE         = SDL2.SDL_WINDOWEVENT_NONE,
    EVENT_SHOWN        = SDL2.SDL_WINDOWEVENT_SHOWN,
    EVENT_HIDDEN       = SDL2.SDL_WINDOWEVENT_HIDDEN,
    EVENT_EXPOSED      = SDL2.SDL_WINDOWEVENT_EXPOSED,
    EVENT_MOVED        = SDL2.SDL_WINDOWEVENT_MOVED,
    EVENT_RESIZED      = SDL2.SDL_WINDOWEVENT_RESIZED,
    EVENT_SIZE_CHANGED = SDL2.SDL_WINDOWEVENT_SIZE_CHANGED,
    EVENT_MINIMIZED    = SDL2.SDL_WINDOWEVENT_MINIMIZED,
    EVENT_MAXIMIZED    = SDL2.SDL_WINDOWEVENT_MAXIMIZED,
    EVENT_RESTORED     = SDL2.SDL_WINDOWEVENT_RESTORED,
    EVENT_ENTER        = SDL2.SDL_WINDOWEVENT_ENTER,
    EVENT_LEAVE        = SDL2.SDL_WINDOWEVENT_LEAVE,
    EVENT_FOCUS_GAINED = SDL2.SDL_WINDOWEVENT_FOCUS_GAINED,
    EVENT_FOCUS_LOST   = SDL2.SDL_WINDOWEVENT_FOCUS_LOST,
    EVENT_CLOSE        = SDL2.SDL_WINDOWEVENT_CLOSE,
)

SDL_GL = SimpleNamespace(
    RED_SIZE                   = SDL2.SDL_GL_RED_SIZE,
    GREEN_SIZE                 = SDL2.SDL_GL_GREEN_SIZE,
    BLUE_SIZE                  = SDL2.SDL_GL_BLUE_SIZE,
    ALPHA_SIZE                 = SDL2.SDL_GL_ALPHA_SIZE,
    BUFFER_SIZE                = SDL2.SDL_GL_BUFFER_SIZE,
    DOUBLEBUFFER               = SDL2.SDL_GL_DOUBLEBUFFER,
    DEPTH_SIZE                 = SDL2.SDL_GL_DEPTH_SIZE,
    STENCIL_SIZE               = SDL2.SDL_GL_STENCIL_SIZE,
    ACCUM_RED_SIZE             = SDL2.SDL_GL_ACCUM_RED_SIZE,
    ACCUM_GREEN_SIZE           = SDL2.SDL_GL_ACCUM_GREEN_SIZE,
    ACCUM_BLUE_SIZE            = SDL2.SDL_GL_ACCUM_BLUE_SIZE,
    ACCUM_ALPHA_SIZE           = SDL2.SDL_GL_ACCUM_ALPHA_SIZE,
    STEREO                     = SDL2.SDL_GL_STEREO,
    MULTISAMPLEBUFFERS         = SDL2.SDL_GL_MULTISAMPLEBUFFERS,
    MULTISAMPLESAMPLES         = SDL2.SDL_GL_MULTISAMPLESAMPLES,
    ACCELERATED_VISUAL         = SDL2.SDL_GL_ACCELERATED_VISUAL,
    RETAINED_BACKING           = SDL2.SDL_GL_RETAINED_BACKING,
    CONTEXT_MAJOR_VERSION      = SDL2.SDL_GL_CONTEXT_MAJOR_VERSION,
    CONTEXT_MINOR_VERSION      = SDL2.SDL_GL_CONTEXT_MINOR_VERSION,
    CONTEXT_EGL                = SDL2.SDL_GL_CONTEXT_EGL,
    CONTEXT_FLAGS              = SDL2.SDL_GL_CONTEXT_FLAGS,
    CONTEXT_PROFILE_MASK       = SDL2.SDL_GL_CONTEXT_PROFILE_MASK,
    SHARE_WITH_CURRENT_CONTEXT = SDL2.SDL_GL_SHARE_WITH_CURRENT_CONTEXT,
    FRAMEBUFFER_SRGB_CAPABLE   = SDL2.SDL_GL_FRAMEBUFFER_SRGB_CAPABLE,

    CONTEXT_DEBUG_FLAG              = SDL2.SDL_GL_CONTEXT_DEBUG_FLAG,
    CONTEXT_FORWARD_COMPATIBLE_FLAG = SDL2.SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG,
    CONTEXT_ROBUST_ACCESS_FLAG      = SDL2.SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG,
    CONTEXT_RESET_ISOLATION_FLAG    = SDL2.SDL_GL_CONTEXT_RESET_ISOLATION_FLAG,

    CONTEXT_PROFILE_CORE            = SDL2.SDL_GL_CONTEXT_PROFILE_CORE,
    CONTEXT_PROFILE_COMPATIBILITY   = SDL2.SDL_GL_CONTEXT_PROFILE_COMPATIBILITY,
    CONTEXT_PROFILE_ES              = SDL2.SDL_GL_CONTEXT_PROFILE_ES,
)
