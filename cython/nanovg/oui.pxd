cdef extern from "oui.h":

    cpdef enum:
        UI_MAX_DATASIZE
        UI_MAX_DEPTH
        UI_MAX_INPUT_EVENTS
        UI_CLICK_THRESHOLD

    ctypedef unsigned int UIuint

    cpdef enum UIitemState:
        UI_COLD
        UI_HOT
        UI_ACTIVE
        UI_FROZEN

    cpdef enum UIboxFlags:
        UI_ROW
        UI_COLUMN
        UI_LAYOUT
        UI_FLEX
        UI_NOWRAP
        UI_WRAP
        UI_START
        UI_MIDDLE
        UI_END
        UI_JUSTIFY

    cpdef enum UIlayoutFlags:
        UI_LEFT
        UI_TOP
        UI_RIGHT
        UI_DOWN
        UI_HFILL
        UI_VFILL
        UI_HCENTER
        UI_VCENTER
        UI_CENTER
        UI_FILL
        UI_BREAK

    cpdef enum UIevent:
        UI_BUTTON0_DOWN
        UI_BUTTON0_UP
        UI_BUTTON0_HOT_UP
        UI_BUTTON0_CAPTURE
        UI_BUTTON2_DOWN
        UI_SCROLL
        UI_KEY_DOWN
        UI_KEY_UP
        UI_CHAR

    cpdef enum:
        UI_USERMASK
        UI_ANY

    ctypedef void (*UIhandler)(UIcontext* ui_context, int item, UIevent event)

    cdef struct UIvec2:
        int v[2]
        int x
        int y

    cdef struct UIrect:
        int v[4]
        int x
        int y
        int w
        int h

    UIcontext* uiCreateContext(unsigned int item_capacity, unsigned int buffer_capacity)

    void uiDestroyContext(UIcontext* ctx)

    void uiSetContextHandle(UIcontext* ui_context, void* handle)

    void* uiGetContextHandle(UIcontext* ui_context)

    void uiSetCursor(UIcontext* ui_context, int x, int y)

    UIvec2 uiGetCursor(UIcontext* ui_context)

    UIvec2 uiGetCursorDelta(UIcontext* ui_context)

    UIvec2 uiGetCursorStart(UIcontext* ui_context)

    UIvec2 uiGetCursorStartDelta(UIcontext* ui_context)

    void uiSetButton(UIcontext* ui_context, unsigned int button, unsigned int mod, bool enabled)

    int uiGetButton(UIcontext* ui_context, unsigned int button)

    int uiGetClicks(UIcontext* ui_context)

    void uiSetKey(UIcontext* ui_context, unsigned int key, unsigned int mod, bool enabled)

    void uiSetChar(UIcontext* ui_context, unsigned int value)

    void uiSetScroll(UIcontext* ui_context, int x, int y)

    UIvec2 uiGetScroll(UIcontext* ui_context)

    void uiBeginLayout(UIcontext* ui_context)

    void uiEndLayout(UIcontext* ui_context)

    void uiUpdateHotItem(UIcontext* ui_context)

    void uiProcess(UIcontext* ui_context, int timestamp)

    void uiClearState(UIcontext* ui_context)

    int uiItem(UIcontext* ui_context)

    void uiSetFrozen(UIcontext* ui_context, int item, bool enable)

    void uiSetHandle(UIcontext* ui_context, int item, void* handle)

    void* uiAllocHandle(UIcontext* ui_context, int item, unsigned int size)

    void uiSetHandler(UIcontext* ui_context, UIhandler handler)

    void uiSetEvents(UIcontext* ui_context, int item, unsigned int flags)

    void uiSetFlags(UIcontext* ui_context, int item, unsigned int flags)

    int uiInsert(UIcontext* ui_context, int item, int child)

    int uiAppend(UIcontext* ui_context, int item, int sibling)

    int uiInsertBack(UIcontext* ui_context, int item, int child)

    int uiInsertFront(UIcontext* ui_context, int item, int child)

    void uiSetSize(UIcontext* ui_context, int item, int w, int h)

    void uiSetLayout(UIcontext* ui_context, int item, unsigned int flags)

    void uiSetBox(UIcontext* ui_context, int item, unsigned int flags)

    void uiSetMargins(UIcontext* ui_context, int item, short l, short t, short r, short b)

    void uiFocus(UIcontext* ui_context, int item)

    int uiFirstChild(UIcontext* ui_context, int item)

    int uiNextSibling(UIcontext* ui_context, int item)

    int uiGetItemCount(UIcontext* ui_context)

    unsigned int uiGetAllocSize(UIcontext* ui_context)

    UIitemState uiGetState(UIcontext* ui_context, int item)

    void* uiGetHandle(UIcontext* ui_context, int item)

    int uiGetHotItem(UIcontext* ui_context)

    int uiGetFocusedItem(UIcontext* ui_context)

    int uiFindItem(UIcontext* ui_context, int item, int x, int y, unsigned int flags, unsigned int mask)

    UIhandler uiGetHandler(UIcontext* ui_context)

    unsigned int uiGetEvents(UIcontext* ui_context, int item)

    unsigned int uiGetFlags(UIcontext* ui_context, int item)

    unsigned int uiGetKey(UIcontext* ui_context)

    unsigned int uiGetModifier(UIcontext* ui_context)

    UIrect uiGetRect(UIcontext* ui_context, int item)

    int uiContains(UIcontext* ui_context, int item, int x, int y)

    int uiGetWidth(UIcontext* ui_context, int item)

    int uiGetHeight(UIcontext* ui_context, int item)

    unsigned int uiGetLayout(UIcontext* ui_context, int item)

    unsigned int uiGetBox(UIcontext* ui_context, int item)

    short uiGetMarginLeft(UIcontext* ui_context, int item)

    short uiGetMarginTop(UIcontext* ui_context, int item)

    short uiGetMarginRight(UIcontext* ui_context, int item)

    short uiGetMarginDown(UIcontext* ui_context, int item)

    int uiRecoverItem(UIcontext* ui_context, int olditem)

    void uiRemapItem(UIcontext* ui_context, int olditem, int newitem)

    int uiGetLastItemCount(UIcontext* ui_context)

    cpdef enum:
        UI_ITEM_BOX_MODEL_MASK
        UI_ITEM_BOX_MASK
        UI_ITEM_LAYOUT_MASK
        UI_ITEM_EVENT_MASK
        UI_ITEM_FROZEN
        UI_ITEM_DATA
        UI_ITEM_INSERTED
        UI_ITEM_HFIXED
        UI_ITEM_VFIXED
        UI_ITEM_FIXED_MASK
        UI_ITEM_COMPARE_MASK

    cdef struct UIitem:
        void* handle
        unsigned int flags
        int firstkid
        int nextitem
        short margins[4]
        short size[2]

    cpdef enum UIstate:
        UI_STATE_IDLE
        UI_STATE_CAPTURE

    cpdef enum UIstage:
        UI_STAGE_LAYOUT
        UI_STAGE_POST_LAYOUT
        UI_STAGE_PROCESS

    cdef struct UIhandleEntry:
        unsigned int key
        int item

    cdef struct UIinputEvent:
        unsigned int key
        unsigned int mod
        UIevent event

    cdef struct UIcontext:
        unsigned int item_capacity
        unsigned int buffer_capacity
        UIhandler handler
        void* handle
        unsigned long long buttons
        unsigned long long last_buttons
        UIvec2 start_cursor
        UIvec2 last_cursor
        UIvec2 cursor
        UIvec2 scroll
        int active_item
        int focus_item
        int last_hot_item
        int last_click_item
        int hot_item
        UIstate state
        UIstage stage
        unsigned int active_key
        unsigned int active_modifier
        unsigned int active_button_modifier
        int last_timestamp
        int last_click_timestamp
        int clicks
        int count
        int last_count
        int eventcount
        unsigned int datasize
        UIitem* items
        unsigned char* data
        UIitem* last_items
        int* item_map
        UIinputEvent events[64]
