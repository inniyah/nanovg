/*
OUI - A minimal semi-immediate GUI handling & layouting library

Copyright (c) 2014 Leonard Ritter <leonard.ritter@duangle.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef _OUI_H_
#define _OUI_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
Revision 2 (2014-07-13)

OUI (short for "Open UI", spoken like the french "oui" for "yes") is a
platform agnostic single-header C library for layouting GUI elements and
handling related user input. Together with a set of widget drawing and logic 
routines it can be used to build complex user interfaces.

OUI is a semi-immediate GUI. Widget declarations are persistent for the duration
of the setup and evaluation, but do not need to be kept around longer than one
frame.

OUI has no widget types; instead, it provides only one kind of element, "Items",
which can be taylored to the application by the user and expanded with custom
buffers and event handlers to behave as containers, buttons, sliders, radio
buttons, and so on.

OUI also does not draw anything; Instead it provides a set of functions to
iterate and query the layouted items in order to allow client code to render
each widget with its current state using a preferred graphics library.

A basic setup for OUI usage looks like this:

void app_main(...) {
    UIcontext *context = uiCreateContext();
    uiMakeCurrent(context);

    while (app_running()) {
        // update position of mouse cursor; the ui can also be updated
        // from received events.
        uiSetCursor(app_get_mouse_x(), app_get_mouse_y());
        // update button state
        for (int i = 0; i < 3; ++i)
            uiSetButton(i, app_get_button_state(i));
        
        // begin new UI declarations
        uiClear();
        
        // - UI setup code goes here -
        app_setup_ui();

        // layout UI
        uiLayout();

        // draw UI
        app_draw_ui(render_context,0,0,0);
        
        // update states and fire handlers
        uiProcess();
    }

    uiDestroyContext(context);
}

Here's an example setup for a checkbox control:

typedef struct CheckBoxData {
    int type;
    const char *label;
    bool *checked;
} CheckBoxData;

// called when the item is clicked (see checkbox())
void app_checkbox_handler(int item, UIevent event) {
    
    // retrieve custom data (see checkbox())
    const CheckBoxData *data = (const CheckBoxData *)uiGetData(item);
    
    // toggle value
    *data->checked = !(*data->checked);
}

// creates a checkbox control for a pointer to a boolean and attaches it to 
// a parent item.
int checkbox(int parent, UIhandle handle, const char *label, bool *checked) {
    
    // create new ui item
    int item = uiItem(); 
    
    // set persistent handle for item that is used
    // to track activity over time
    uiSetHandle(item, handle);
    
    // set size of wiget; horizontal size is dynamic, vertical is fixed
    uiSetSize(item, 0, APP_WIDGET_HEIGHT);
    
    // attach checkbox handler, set to fire as soon as the left button is
    // pressed; UI_BUTTON0_HOT_UP is also a popular alternative.
    uiSetHandler(item, app_checkbox_handler, UI_BUTTON0_DOWN);
    
    // store some custom data with the checkbox that we use for rendering
    // and value changes.
    CheckBoxData *data = (CheckBoxData *)uiAllocData(item, sizeof(CheckBoxData));
    // assign a custom typeid to the data so the renderer knows how to
    // render this control.
    data->type = APP_WIDGET_CHECKBOX;
    data->label = label;
    data->checked = checked;
    
    // append to parent
    uiAppend(parent, item);
    
    return item;
}

A simple recursive drawing routine can look like this:

void app_draw_ui(AppRenderContext *ctx, int item, int x, int y) {
    // retrieve custom data and cast it to an int; we assume the first member
    // of every widget data item to be an "int type" field.
    const int *type = (const int *)uiGetData(item);
    
    // get the widgets relative rectangle and offset by the parents
    // absolute position.
    UIrect rect = uiGetRect(item);
    rect.x += x;
    rect.y += y; 
    
    // if a type is set, this is a specialized widget
    if (type) {
        switch(*type) {
            default: break;
            case APP_WIDGET_LABEL: {
                // ...
            } break;
            case APP_WIDGET_BUTTON: {
                // ...
            } break;
            case APP_WIDGET_CHECKBOX: {
                // cast to the full data type
                const CheckBoxData *data = (CheckBoxData*)type;
                
                // get the widgets current state
                int state = uiGetState(item);
                
                // if the value is set, the state is always active
                if (*data->checked)
                    state = UI_ACTIVE;
                
                // draw the checkbox
                app_draw_checkbox(ctx, rect, state, data->label);
            } break;
        }
    }
    
    // iterate through all children and draw
    int kid = uiFirstChild(item);
    while (kid >= 0) {
        app_draw_ui(ctx, kid, rect.x, rect.y);
        kid = uiNextSibling(kid);
    }
}

See example.cpp in the repository for a full usage example.

*/

// you can override this from the outside to pick
// the export level you need
#ifndef OUI_EXPORT
#define OUI_EXPORT
#endif

// limits

enum {
	// maximum number of items that may be added (must be power of 2)
	UI_MAX_ITEMS = 4096,
	// maximum size in bytes reserved for storage of application dependent data
	// as passed to uiAllocData().
	UI_MAX_BUFFERSIZE = 1048576,
	// maximum size in bytes of a single data buffer passed to uiAllocData().
	UI_MAX_DATASIZE = 4096,
	// maximum depth of nested containers
	UI_MAX_DEPTH = 64,
	// maximum number of buffered input events
	UI_MAX_INPUT_EVENTS = 64,
	// consecutive click threshold in ms
	UI_CLICK_THRESHOLD = 250,
};

typedef unsigned int UIuint;

// opaque UI context
typedef struct UIcontext UIcontext;

// item states as returned by uiGetState()

typedef enum UIitemState {
    // the item is inactive
    UI_COLD = 0,
    // the item is inactive, but the cursor is hovering over this item
    UI_HOT = 1,
    // the item is toggled, activated, focused (depends on item kind)
    UI_ACTIVE = 2,
    // the item is unresponsive
    UI_FROZEN = 3,
} UIitemState;

// layout flags
typedef enum UIlayoutFlags {
    // container flags:

    // flex-direction (bit 0+1)

    // left to right
    UI_ROW = 0x002,
    // top to bottom
    UI_COLUMN = 0x003,

    // model (bit 1)

    // free layout
    UI_LAYOUT = 0x000,
    // flex model
    UI_FLEX = 0x002,

    // flex-wrap (bit 2)

    // single-line
    UI_NOWRAP = 0x000,
    // multi-line, wrap left to right
    UI_WRAP = 0x004,

    // justify-content (start, end, center, space-between)
    // can be implemented by putting flex container in a layout container,
    // then using UI_LEFT, UI_RIGHT, UI_HFILL, UI_HCENTER, etc.

    // align-items
    // can be implemented by putting flex container in a layout container,
    // then using UI_TOP, UI_DOWN, UI_VFILL, UI_VCENTER, etc.
    // FILL is equivalent to stretch/grow

    // align-content (start, end, center, stretch)
    // can be implemented by putting flex container in a layout container,
    // then using UI_TOP, UI_DOWN, UI_VFILL, UI_VCENTER, etc.
    // FILL is equivalent to stretch; space-between is not supported.

    // child item flags:

    // attachments (bit 5-8)
    // fully valid when parent uses UI_LAYOUT model
    // partially valid when in UI_FLEX model

    // anchor to left item or left side of parent
    UI_LEFT = 0x020,
    // anchor to top item or top side of parent
    UI_TOP = 0x040,
    // anchor to right item or right side of parent
    UI_RIGHT = 0x080,
    // anchor to bottom item or bottom side of parent
    UI_DOWN = 0x100,
    // anchor to both left and right item or parent borders
    UI_HFILL = 0x0a0,
    // anchor to both top and bottom item or parent borders
    UI_VFILL = 0x140,
    // center horizontally, with left margin as offset
    UI_HCENTER = 0x000,
    // center vertically, with top margin as offset
    UI_VCENTER = 0x000,
    // center in both directions, with left/top margin as offset
    UI_CENTER = 0x000,
    // anchor to all four directions
    UI_FILL = 0x1e0,

} UIlayoutFlags;

// event flags
typedef enum UIevent {
    // on button 0 down
    UI_BUTTON0_DOWN = 0x0200,
    // on button 0 up
    // when this event has a handler, uiGetState() will return UI_ACTIVE as
    // long as button 0 is down.
    UI_BUTTON0_UP = 0x0400,
    // on button 0 up while item is hovered
    // when this event has a handler, uiGetState() will return UI_ACTIVE
    // when the cursor is hovering the items rectangle; this is the
    // behavior expected for buttons.
    UI_BUTTON0_HOT_UP = 0x0800,
    // item is being captured (button 0 constantly pressed); 
    // when this event has a handler, uiGetState() will return UI_ACTIVE as
    // long as button 0 is down.
    UI_BUTTON0_CAPTURE = 0x1000,
    // on button 2 down (right mouse button, usually triggers context menu)
    UI_BUTTON2_DOWN = 0x2000,
    // item has received a scrollwheel event
    // the accumulated wheel offset can be queried with uiGetScroll()
    UI_SCROLL = 0x4000,
    // item is focused and has received a key-down event
    // the respective key can be queried using uiGetKey() and uiGetModifier()
    UI_KEY_DOWN = 0x8000,
    // item is focused and has received a key-up event
    // the respective key can be queried using uiGetKey() and uiGetModifier()
    UI_KEY_UP = 0x10000,
    // item is focused and has received a character event
    // the respective character can be queried using uiGetKey()
    UI_CHAR = 0x20000,
} UIevent;

// handler callback; event is one of UI_EVENT_*
typedef void (*UIhandler)(int item, UIevent event);

// for cursor positions, mainly
typedef struct UIvec2 {
    union {
        int v[2];
        struct { int x, y; };
    };
} UIvec2;

// layout rectangle
typedef struct UIrect {
    union {
        int v[4];
        struct { int x, y, w, h; };
    };
} UIrect;

// unless declared otherwise, all operations have the complexity O(1).

// Context Management
// ------------------

// create a new UI context; call uiMakeCurrent() to make this context the
// current context. The context is managed by the client and must be released
// using uiDestroyContext()
OUI_EXPORT UIcontext *uiCreateContext();

// select an UI context as the current context; a context must always be 
// selected before using any of the other UI functions
OUI_EXPORT void uiMakeCurrent(UIcontext *ctx);

// release the memory of an UI context created with uiCreateContext(); if the
// context is the current context, the current context will be set to NULL
OUI_EXPORT void uiDestroyContext(UIcontext *ctx);

// Input Control
// -------------

// sets the current cursor position (usually belonging to a mouse) to the
// screen coordinates at (x,y)
OUI_EXPORT void uiSetCursor(int x, int y);

// returns the current cursor position in screen coordinates as set by 
// uiSetCursor()
OUI_EXPORT UIvec2 uiGetCursor();

// returns the offset of the cursor relative to the last call to uiProcess()
OUI_EXPORT UIvec2 uiGetCursorDelta();

// returns the beginning point of a drag operation.
OUI_EXPORT UIvec2 uiGetCursorStart();

// returns the offset of the cursor relative to the beginning point of a drag
// operation.
OUI_EXPORT UIvec2 uiGetCursorStartDelta();

// sets a mouse or gamepad button as pressed/released
// button is in the range 0..63 and maps to an application defined input
// source.
// enabled is 1 for pressed, 0 for released
OUI_EXPORT void uiSetButton(int button, int enabled);

// returns the current state of an application dependent input button
// as set by uiSetButton().
// the function returns 1 if the button has been set to pressed, 0 for released.
OUI_EXPORT int uiGetButton(int button);

// returns the number of chained clicks; 1 is a single click,
// 2 is a double click, etc.
OUI_EXPORT int uiGetClicks();

// sets a key as down/up; the key can be any application defined keycode
// mod is an application defined set of flags for modifier keys
// enabled is 1 for key down, 0 for key up
// all key events are being buffered until the next call to uiProcess()
OUI_EXPORT void uiSetKey(unsigned int key, unsigned int mod, int enabled);

// sends a single character for text input; the character is usually in the
// unicode range, but can be application defined.
// all char events are being buffered until the next call to uiProcess()
OUI_EXPORT void uiSetChar(unsigned int value);

// accumulates scroll wheel offsets for the current frame
// all offsets are being accumulated until the next call to uiProcess()
OUI_EXPORT void uiSetScroll(int x, int y);

// returns the currently accumulated scroll wheel offsets for this frame
OUI_EXPORT UIvec2 uiGetScroll();





// Stages
// ------

// clear the item buffer; uiClear() should be called before the first 
// UI declaration for this frame to avoid concatenation of the same UI multiple 
// times.
// After the call, all previously declared item IDs are invalid, and all
// application dependent context data has been freed.
OUI_EXPORT void uiClear();

// layout all added items starting from the root item 0.
// after calling uiLayout(), no further modifications to the item tree should
// be done until the next call to uiClear().
// It is safe to immediately draw the items after a call to uiLayout().
// this is an O(N) operation for N = number of declared items.
OUI_EXPORT void uiLayout();

// update the current hot item; this only needs to be called if items are kept
// for more than one frame and uiLayout() is not called
OUI_EXPORT void uiUpdateHotItem();

// update the internal state according to the current cursor position and 
// button states, and call all registered handlers.
// timestamp is the time in milliseconds relative to the last call to uiProcess()
// and is used to estimate the threshold for double-clicks
// after calling uiProcess(), no further modifications to the item tree should
// be done until the next call to uiClear().
// Items should be drawn before a call to uiProcess()
// this is an O(N) operation for N = number of declared items.
OUI_EXPORT void uiProcess(int timestamp);

// reset the currently stored hot/active etc. handles; this should be called when
// a re-declaration of the UI changes the item indices, to avoid state
// related glitches because item identities have changed.
OUI_EXPORT void uiClearState();

// UI Declaration
// --------------

// create a new UI item and return the new items ID.
OUI_EXPORT int uiItem();

// set an items state to frozen; the UI will not recurse into frozen items
// when searching for hot or active items; subsequently, frozen items and
// their child items will not cause mouse event notifications.
// The frozen state is not applied recursively; uiGetState() will report
// UI_COLD for child items. Upon encountering a frozen item, the drawing
// routine needs to handle rendering of child items appropriately.
// see example.cpp for a demonstration.
OUI_EXPORT void uiSetFrozen(int item, int enable);

// set the application-dependent handle of an item.
// handle is an application defined 64-bit handle. If handle is NULL, the item
// will not be interactive.
OUI_EXPORT void uiSetHandle(int item, void *handle);

// allocate space for application-dependent context data and assign it
// as the handle to the item.
// The memory of the pointer is managed by the UI context and released
// upon the next call to uiClear()
OUI_EXPORT void *uiAllocHandle(int item, int size);

// set the global handler callback for interactive items.
// the handler will be called for each item whose event flags are set using
// uiSetEvents.
OUI_EXPORT void uiSetHandler(UIhandler handler);

// flags is a combination of UI_EVENT_* and designates for which events the 
// handler should be called. 
OUI_EXPORT void uiSetEvents(int item, int flags);

// assign an item to a container.
// an item ID of 0 refers to the root item.
// if child is already assigned to a parent, an assertion will be thrown.
// the function returns the child item ID
OUI_EXPORT int uiAppend(int item, int child);

// set the size of the item; a size of 0 indicates the dimension to be 
// dynamic; if the size is set, the item can not expand beyond that size.
OUI_EXPORT void uiSetSize(int item, int w, int h);

// set the anchoring behavior of the item to one or multiple UIlayoutFlags
OUI_EXPORT void uiSetLayout(int item, int flags);

// set the left, top, right and bottom margins of an item; when the item is
// anchored to the parent or another item, the margin controls the distance
// from the neighboring element.
OUI_EXPORT void uiSetMargins(int item, short l, short t, short r, short b);

// set item as recipient of all keyboard events; the item must have a handle
// assigned; if item is -1, no item will be focused.
OUI_EXPORT void uiFocus(int item);

// Iteration
// ---------

// returns the first child item of a container item. If the item is not
// a container or does not contain any items, -1 is returned.
// if item is 0, the first child item of the root item will be returned.
OUI_EXPORT int uiFirstChild(int item);

// returns the last child item of a container item. If the item is not
// a container or does not contain any items, -1 is returned.
// if item is 0, the last child item of the root item will be returned.
OUI_EXPORT int uiLastChild(int item);

// returns an items parent container item.
// if item is 0, -1 will be returned.
OUI_EXPORT int uiParent(int item);

// returns an items next sibling in the list of the parent containers children.
// if item is 0 or the item is the last child item, -1 will be returned.
OUI_EXPORT int uiNextSibling(int item);
// returns an items previous sibling in the list of the parent containers
// children.
// if item is 0 or the item is the first child item, -1 will be returned.
OUI_EXPORT int uiPrevSibling(int item);

// Querying
// --------

// return the total number of allocated items
OUI_EXPORT int uiGetItemCount();

// return the current state of the item. This state is only valid after
// a call to uiProcess().
// The returned value is one of UI_COLD, UI_HOT, UI_ACTIVE, UI_FROZEN.
OUI_EXPORT UIitemState uiGetState(int item);

// return the application-dependent handle of the item as passed to uiSetHandle()
// or uiAllocHandle().
OUI_EXPORT void *uiGetHandle(int item);

// return the item that is currently under the cursor or -1 for none
OUI_EXPORT int uiGetHotItem();

// return the item that is currently focused or -1 for none
OUI_EXPORT int uiGetFocusedItem();

// return the handler callback as passed to uiSetHandler()
OUI_EXPORT UIhandler uiGetHandler();
// return the event flags for an item as passed to uiSetEvents()
OUI_EXPORT int uiGetEvents(int item);
// when handling a KEY_DOWN/KEY_UP event: the key that triggered this event
OUI_EXPORT unsigned int uiGetKey();
// when handling a KEY_DOWN/KEY_UP event: the key that triggered this event
OUI_EXPORT unsigned int uiGetModifier();

// returns the items layout rectangle relative to the parent. If uiGetRect()
// is called before uiLayout(), the values of the returned rectangle are
// undefined.
OUI_EXPORT UIrect uiGetRect(int item);

// returns the items layout rectangle in absolute coordinates. If 
// uiGetAbsoluteRect() is called before uiLayout(), the values of the returned
// rectangle are undefined.
// This function has complexity O(N) for N parents
OUI_EXPORT UIrect uiGetAbsoluteRect(int item);

// returns 1 if an items absolute rectangle contains a given coordinate
// otherwise 0
OUI_EXPORT int uiContains(int item, int x, int y);

// when called from an input event handler, returns the active items absolute
// layout rectangle. If uiGetActiveRect() is called outside of a handler,
// the values of the returned rectangle are undefined.
OUI_EXPORT UIrect uiGetActiveRect();

// return the width of the item as set by uiSetSize()
OUI_EXPORT int uiGetWidth(int item);
// return the height of the item as set by uiSetSize()
OUI_EXPORT int uiGetHeight(int item);

// return the anchoring behavior as set by uiSetLayout()
OUI_EXPORT int uiGetLayout(int item);

// return the left margin of the item as set with uiSetMargins()
OUI_EXPORT short uiGetMarginLeft(int item);
// return the top margin of the item as set with uiSetMargins()
OUI_EXPORT short uiGetMarginTop(int item);
// return the right margin of the item as set with uiSetMargins()
OUI_EXPORT short uiGetMarginRight(int item);
// return the bottom margin of the item as set with uiSetMargins()
OUI_EXPORT short uiGetMarginDown(int item);

#ifdef __cplusplus
};
#endif

#endif // _OUI_H_

#ifdef OUI_IMPLEMENTATION

#include <assert.h>

#ifdef _MSC_VER
	#pragma warning (disable: 4996) // Switch off security warnings
	#pragma warning (disable: 4100) // Switch off unreferenced formal parameter warnings
	#ifdef __cplusplus
	#define UI_INLINE inline
	#else
	#define UI_INLINE
	#endif
#else
	#define UI_INLINE inline
#endif

#define UI_MAX_KIND 16

#define UI_ANY_BUTTON0_INPUT (UI_BUTTON0_DOWN \
    |UI_BUTTON0_UP \
    |UI_BUTTON0_HOT_UP \
    |UI_BUTTON0_CAPTURE)

#define UI_ANY_BUTTON2_INPUT (UI_BUTTON2_DOWN)

#define UI_ANY_MOUSE_INPUT (UI_ANY_BUTTON0_INPUT \
    |UI_ANY_BUTTON2_INPUT)

#define UI_ANY_KEY_INPUT (UI_KEY_DOWN \
    |UI_KEY_UP \
    |UI_CHAR)

#define UI_ANY_INPUT (UI_ANY_MOUSE_INPUT \
    |UI_ANY_KEY_INPUT)

// extra item flags
enum {
	// bit 0-8
    UI_ITEM_LAYOUT_MASK = 0x0001FF,
    // bit 9-18
    UI_ITEM_EVENT_MASK  = 0x07FE00,
    // item is frozen (bit 19)
	UI_ITEM_FROZEN      = 0x080000,
	// item handle is pointer to data (bit 20)
	UI_ITEM_DATA	    = 0x100000,
};

typedef struct UIitem {
    // declaration independent unique handle (for persistence)
    void *handle;

    unsigned int flags;

    // container structure
    
    // index of first kid
    int firstkid;
    // index of last kid
    int lastkid;
    
    // child structure
    
    // parent item
    int parent;
    // index of next sibling with same parent
    int nextitem;
    // index of previous sibling with same parent
    int previtem;
    
    // margin offsets, interpretation depends on flags
    // after layouting, the first two components are absolute coordinates
    short margins[4];
    // size
    short size[2];
} UIitem;

typedef enum UIstate {
    UI_STATE_IDLE = 0,
    UI_STATE_CAPTURE,
} UIstate;

typedef struct UIhandleEntry {
    unsigned int key;
    int item;
} UIhandleEntry;

typedef struct UIinputEvent {
    unsigned int key;
    unsigned int mod;
    UIevent event;
} UIinputEvent;

struct UIcontext {
    // handler
    UIhandler handler;

    // button state in this frame
    unsigned long long buttons;
    // button state in the previous frame
    unsigned long long last_buttons;
    
    // where the cursor was at the beginning of the active state
    UIvec2 start_cursor;
    // where the cursor was last frame
    UIvec2 last_cursor;
    // where the cursor is currently
    UIvec2 cursor;
    // accumulated scroll wheel offsets
    UIvec2 scroll;
    
    int active_item;
    int focus_item;
    int last_hot_item;
    int last_click_item;
    int hot_item;

    UIrect hot_rect;
    UIrect active_rect;
    UIstate state;
    unsigned int active_key;
    unsigned int active_modifier;
    int event_item;
    int last_timestamp;
    int last_click_timestamp;
    int clicks;
    
    int count;    
    int datasize;
    int eventcount;
    
    UIitem items[UI_MAX_ITEMS];    
    unsigned char data[UI_MAX_BUFFERSIZE];
    UIinputEvent events[UI_MAX_INPUT_EVENTS];
};

UI_INLINE int ui_max(int a, int b) {
    return (a>b)?a:b;
}

UI_INLINE int ui_min(int a, int b) {
    return (a<b)?a:b;
}

static UIcontext *ui_context = NULL;

UIcontext *uiCreateContext() {
    UIcontext *ctx = (UIcontext *)malloc(sizeof(UIcontext));
    memset(ctx, 0, sizeof(UIcontext));
    UIcontext *oldctx = ui_context;
    uiMakeCurrent(ctx);
    uiClear();
    uiClearState();
    uiMakeCurrent(oldctx);
    return ctx;
}

void uiMakeCurrent(UIcontext *ctx) {
    ui_context = ctx;
}

void uiDestroyContext(UIcontext *ctx) {
    if (ui_context == ctx)
        uiMakeCurrent(NULL);
    free(ctx);
}

void uiSetButton(int button, int enabled) {
    assert(ui_context);
    unsigned long long mask = 1ull<<button;
    // set new bit
    ui_context->buttons = (enabled)?
        (ui_context->buttons | mask):
        (ui_context->buttons & ~mask);
}

static void uiAddInputEvent(UIinputEvent event) {
    assert(ui_context);
    if (ui_context->eventcount == UI_MAX_INPUT_EVENTS) return;
    ui_context->events[ui_context->eventcount++] = event;
}

static void uiClearInputEvents() {
    assert(ui_context);
    ui_context->eventcount = 0;
    ui_context->scroll.x = 0;
    ui_context->scroll.y = 0;
}

void uiSetKey(unsigned int key, unsigned int mod, int enabled) {
    assert(ui_context);
    UIinputEvent event = { key, mod, enabled?UI_KEY_DOWN:UI_KEY_UP };
    uiAddInputEvent(event);
}

void uiSetChar(unsigned int value) {
    assert(ui_context);
    UIinputEvent event = { value, 0, UI_CHAR };
    uiAddInputEvent(event);
}

void uiSetScroll(int x, int y) {
    assert(ui_context);
    ui_context->scroll.x += x;
    ui_context->scroll.y += y;
}

UIvec2 uiGetScroll() {
    assert(ui_context);
    return ui_context->scroll;
}

int uiGetLastButton(int button) {
    assert(ui_context);
    return (ui_context->last_buttons & (1ull<<button))?1:0;
}

int uiGetButton(int button) {
    assert(ui_context);
    return (ui_context->buttons & (1ull<<button))?1:0;
}

int uiButtonPressed(int button) {
    assert(ui_context);
    return !uiGetLastButton(button) && uiGetButton(button);
}

int uiButtonReleased(int button) {
    assert(ui_context);
    return uiGetLastButton(button) && !uiGetButton(button);
}

void uiSetCursor(int x, int y) {
    assert(ui_context);
    ui_context->cursor.x = x;
    ui_context->cursor.y = y;
}

UIvec2 uiGetCursor() {
    assert(ui_context);
    return ui_context->cursor;
}

UIvec2 uiGetCursorStart() {
    assert(ui_context);
    return ui_context->start_cursor;
}

UIvec2 uiGetCursorDelta() {
    assert(ui_context);
    UIvec2 result = {{{
        ui_context->cursor.x - ui_context->last_cursor.x,
        ui_context->cursor.y - ui_context->last_cursor.y
    }}};
    return result;
}

UIvec2 uiGetCursorStartDelta() {
    assert(ui_context);
    UIvec2 result = {{{
        ui_context->cursor.x - ui_context->start_cursor.x,
        ui_context->cursor.y - ui_context->start_cursor.y
    }}};
    return result;
}

unsigned int uiGetKey() {
    assert(ui_context);
    return ui_context->active_key;
}

unsigned int uiGetModifier() {
    assert(ui_context);
    return ui_context->active_modifier;
}

// return the total number of allocated items
OUI_EXPORT int uiGetItemCount() {
    assert(ui_context);
    return ui_context->count;
}

UIitem *uiItemPtr(int item) {
    assert(ui_context && (item >= 0) && (item < ui_context->count));
    return ui_context->items + item;
}

int uiGetHotItem() {
    assert(ui_context);
    return ui_context->hot_item;
}

void uiFocus(int item) {
    assert(ui_context && (item >= -1) && (item < ui_context->count));
    ui_context->focus_item = item;
}

static void uiValidateStateItems() {
    assert(ui_context);
	if (ui_context->last_hot_item >= ui_context->count)
		ui_context->last_hot_item = -1;
	if (ui_context->active_item >= ui_context->count)
		ui_context->active_item = -1;
	if (ui_context->focus_item >= ui_context->count)
		ui_context->focus_item = -1;
	if (ui_context->last_click_item >= ui_context->count)
		ui_context->last_click_item = -1;
}

int uiGetFocusedItem() {
    assert(ui_context);
    return ui_context->focus_item;
}

void uiClear() {
    assert(ui_context);
    ui_context->count = 0;
    ui_context->datasize = 0;
    ui_context->hot_item = -1;
}

void uiClearState() {
    assert(ui_context);
	ui_context->last_hot_item = -1;
	ui_context->active_item = -1;
	ui_context->focus_item = -1;
	ui_context->last_click_item = -1;
}

int uiItem() {
    assert(ui_context);
    assert(ui_context->count < UI_MAX_ITEMS);
    int idx = ui_context->count++;
    UIitem *item = uiItemPtr(idx);
    memset(item, 0, sizeof(UIitem));
    item->parent = -1;
    item->firstkid = -1;
    item->lastkid = -1;
    item->nextitem = -1;
    item->previtem = -1;
    return idx;
}

void uiNotifyItem(int item, UIevent event) {
    assert(ui_context);
    if (!ui_context->handler)
    	return;
    assert((event & UI_ITEM_EVENT_MASK) == event);
    ui_context->event_item = item;
	UIitem *pitem = uiItemPtr(item);
	if (pitem->flags & event) {
		ui_context->handler(item, event);
	}
}

int uiAppend(int item, int child) {
    assert(child > 0);
    assert(uiParent(child) == -1);
    UIitem *pitem = uiItemPtr(child);
    UIitem *pparent = uiItemPtr(item);
    pitem->parent = item;
    if (pparent->lastkid < 0) {
        pparent->firstkid = child;
        pparent->lastkid = child;
    } else {
        pitem->previtem = pparent->lastkid;
        uiItemPtr(pparent->lastkid)->nextitem = child;
        pparent->lastkid = child;
    }
    return child;
}

void uiSetFrozen(int item, int enable) {
    UIitem *pitem = uiItemPtr(item);
    if (enable)
    	pitem->flags |= UI_ITEM_FROZEN;
    else
    	pitem->flags &= ~UI_ITEM_FROZEN;
}

void uiSetSize(int item, int w, int h) {
    UIitem *pitem = uiItemPtr(item);
    pitem->size[0] = w;
    pitem->size[1] = h;
}

int uiGetWidth(int item) {
    return uiItemPtr(item)->size[0];
}

int uiGetHeight(int item) {
    return uiItemPtr(item)->size[1];
}

void uiSetLayout(int item, int flags) {
    uiItemPtr(item)->flags |= flags & UI_ITEM_LAYOUT_MASK;
}

int uiGetLayout(int item) {
    return uiItemPtr(item)->flags & UI_ITEM_LAYOUT_MASK;
}

void uiSetMargins(int item, short l, short t, short r, short b) {
    UIitem *pitem = uiItemPtr(item);
    pitem->margins[0] = l;
    pitem->margins[1] = t;
    pitem->margins[2] = r;
    pitem->margins[3] = b;
}

short uiGetMarginLeft(int item) {
    return uiItemPtr(item)->margins[0];
}
short uiGetMarginTop(int item) {
    return uiItemPtr(item)->margins[1];
}
short uiGetMarginRight(int item) {
    return uiItemPtr(item)->margins[2];
}
short uiGetMarginDown(int item) {
    return uiItemPtr(item)->margins[3];
}

// compute bounding box of all items super-imposed
UI_INLINE void uiComputeImposedSizeDim(UIitem *pitem, int dim) {
    int wdim = dim+2;
	if (pitem->size[dim])
		return;
	// largest size is required size
	short need_size = 0;
	int kid = pitem->firstkid;
	while (kid >= 0) {
		UIitem *pkid = uiItemPtr(kid);
		// width = start margin + calculated width + end margin
		int kidsize = pkid->margins[dim] + pkid->size[dim] + pkid->margins[wdim];
		need_size = ui_max(need_size, kidsize);
		kid = uiNextSibling(kid);
	}
	pitem->size[dim] = need_size;
}

// compute bounding box of all items stacked
UI_INLINE void uiComputeStackedSizeDim(UIitem *pitem, int dim) {
    int wdim = dim+2;
	if (pitem->size[dim])
		return;
	short need_size = 0;
	int kid = pitem->firstkid;
	while (kid >= 0) {
		UIitem *pkid = uiItemPtr(kid);
		// width += start margin + calculated width + end margin
		need_size += pkid->margins[dim] + pkid->size[dim] + pkid->margins[wdim];
		kid = uiNextSibling(kid);
	}
    pitem->size[dim] = need_size;
}

static void uiComputeBestSize(int item, int dim) {
    UIitem *pitem = uiItemPtr(item);

    // children expand the size
    int kid = uiFirstChild(item);
    while (kid >= 0) {
        uiComputeBestSize(kid, dim);
        kid = uiNextSibling(kid);
    }
    
    if(pitem->flags & UI_FLEX) {
    	// flex model
    	if ((pitem->flags & 1) == (unsigned int)dim) // direction
    		uiComputeStackedSizeDim(pitem, dim);
    	else
    		uiComputeImposedSizeDim(pitem, dim);
    } else {
    	// layout model
    	uiComputeImposedSizeDim(pitem, dim);
    }
}

// stack all items according to their alignment
UI_INLINE void uiLayoutStackedItemDim(UIitem *pitem, int dim) {
    int wdim = dim+2;

    short space = pitem->size[dim];
    short used = 0;

	int count = 0;
	// first pass: count items that need to be expanded,
	// and the space that is used
	int kid = pitem->firstkid;
	while (kid >= 0) {
		UIitem *pkid = uiItemPtr(kid);
		int flags = (pkid->flags & UI_ITEM_LAYOUT_MASK) >> dim;
		if ((flags & UI_HFILL) == UI_HFILL) { // grow
			count++;
			used += pkid->margins[dim] + pkid->margins[wdim];
		} else {
			used += pkid->margins[dim] + pkid->size[dim] + pkid->margins[wdim];
		}
		kid = uiNextSibling(kid);
	}

    int extra_space = ui_max(space - used,0);

    if (extra_space && count) {
		// distribute width among items
		float width = (float)extra_space / (float)count;
		float x = 0.0f;
		float x1;
		// second pass: distribute and rescale
		kid = pitem->firstkid;
		while (kid >= 0) {
			short ix0,ix1;
			UIitem *pkid = uiItemPtr(kid);
			int flags = (pkid->flags & UI_ITEM_LAYOUT_MASK) >> dim;

			x += (float)pkid->margins[dim];
			if ((flags & UI_HFILL) == UI_HFILL) { // grow
				x1 = x+width;
			} else {
				x1 = x+(float)pkid->size[dim];
			}
			ix0 = (short)x;
			ix1 = (short)x1;
			pkid->margins[dim] = ix0;
			pkid->size[dim] = ix1-ix0;
			x = x1 + (float)pkid->margins[wdim];

			kid = uiNextSibling(kid);
		}
    } else {
		// single pass: just distribute
		short x = 0;
		int kid = pitem->firstkid;
		while (kid >= 0) {
			UIitem *pkid = uiItemPtr(kid);

			x += pkid->margins[dim];
			pkid->margins[dim] = x;
			x += pkid->size[dim] + pkid->margins[wdim];

			kid = uiNextSibling(kid);
		}
    }
}

// superimpose all items according to their alignment
UI_INLINE void uiLayoutImposedItemDim(UIitem *pitem, int dim) {
    int wdim = dim+2;

    short space = pitem->size[dim];

    int kid = pitem->firstkid;
    while (kid >= 0) {
        UIitem *pkid = uiItemPtr(kid);

        int flags = (pkid->flags & UI_ITEM_LAYOUT_MASK) >> dim;

        switch(flags & UI_HFILL) {
        default: break;
        case UI_HCENTER: {
            pkid->margins[dim] += (space-pkid->size[dim])/2;
        } break;
        case UI_RIGHT: {
            pkid->margins[dim] = space-pkid->size[dim]-pkid->margins[wdim];
        } break;
        case UI_HFILL: {
        	pkid->size[dim] = ui_max(0,space-pkid->margins[dim]-pkid->margins[wdim]);
        } break;
        }

        kid = uiNextSibling(kid);
    }
}

static void uiLayoutItem(int item, int dim) {
    UIitem *pitem = uiItemPtr(item);
    
    if(pitem->flags & UI_FLEX) {
    	// flex model
    	if ((pitem->flags & 1) == (unsigned int)dim) // direction
    		uiLayoutStackedItemDim(pitem, dim);
    	else
    		uiLayoutImposedItemDim(pitem, dim);
    } else {
    	// layout model
    	uiLayoutImposedItemDim(pitem, dim);
    }
    
    int kid = uiFirstChild(item);
    while (kid >= 0) {
        uiLayoutItem(kid, dim);
        kid = uiNextSibling(kid);
    }
}

UIrect uiGetRect(int item) {
	UIitem *pitem = uiItemPtr(item);
	UIrect rc = {{{
		pitem->margins[0], pitem->margins[1],
		pitem->size[0], pitem->size[1]
	}}};
    return rc;
}

UIrect uiGetActiveRect() {
    assert(ui_context);
    return ui_context->active_rect;
}

int uiFirstChild(int item) {
    return uiItemPtr(item)->firstkid;
}

int uiLastChild(int item) {
    return uiItemPtr(item)->lastkid;
}

int uiNextSibling(int item) {
    return uiItemPtr(item)->nextitem;
}

int uiPrevSibling(int item) {
    return uiItemPtr(item)->previtem;
}

int uiParent(int item) {
    return uiItemPtr(item)->parent;
}

void *uiAllocHandle(int item, int size) {
    assert((size > 0) && (size < UI_MAX_DATASIZE));
    UIitem *pitem = uiItemPtr(item);
    assert(pitem->handle == NULL);
    assert((ui_context->datasize+size) <= UI_MAX_BUFFERSIZE);
    pitem->handle = ui_context->data + ui_context->datasize;
    pitem->flags |= UI_ITEM_DATA;
    ui_context->datasize += size;
    return pitem->handle;
}

void uiSetHandle(int item, void *handle) {
    UIitem *pitem = uiItemPtr(item);
    assert(pitem->handle == NULL);
    pitem->handle = handle;
}

void *uiGetHandle(int item) {
    return uiItemPtr(item)->handle;
}

void uiSetHandler(UIhandler handler) {
	assert(ui_context);
	ui_context->handler = handler;
}

UIhandler uiGetHandler() {
	assert(ui_context);
    return ui_context->handler;
}

void uiSetEvents(int item, int flags) {
    UIitem *pitem = uiItemPtr(item);
    pitem->flags &= ~UI_ITEM_EVENT_MASK;
    pitem->flags |= flags & UI_ITEM_EVENT_MASK;
}

int uiGetEvents(int item) {
    return uiItemPtr(item)->flags & UI_ITEM_EVENT_MASK;
}

UIrect uiGetAbsoluteRect(int item) {
    UIrect rect = uiGetRect(item);
    item = uiParent(item);
    while (item >= 0) {
        rect.x += uiItemPtr(item)->margins[0];
        rect.y += uiItemPtr(item)->margins[1];
        item = uiParent(item);
    }    
    return rect;
}

int uiContains(int item, int x, int y) {
    UIrect rect = uiGetAbsoluteRect(item);
    x -= rect.x;
    y -= rect.y;
    if ((x>=0)
     && (y>=0)
     && (x<rect.w)
     && (y<rect.h)) return 1;
    return 0;
}

int uiFindItemForEvent(int item, UIevent event,
		UIrect *hot_rect,
		int x, int y, int ox, int oy) {
    UIitem *pitem = uiItemPtr(item);
    if (pitem->flags & UI_ITEM_FROZEN) return -1;
    UIrect rect = {{{ pitem->margins[0], pitem->margins[1],
    				  pitem->size[0], pitem->size[1] }}};
    x -= rect.x;
    y -= rect.y;
    ox += rect.x;
    oy += rect.y;
    if ((x>=0)
     && (y>=0)
     && (x<rect.w)
     && (y<rect.h)) {
        int kid = uiLastChild(item);
        while (kid >= 0) {
            int best_hit = uiFindItemForEvent(kid,
            		event,hot_rect,x,y,ox,oy);
            if (best_hit >= 0) return best_hit;
            kid = uiPrevSibling(kid);
        }
        // click-through if the item has no handler for this event
        if (pitem->flags & event) {
            rect.x = ox;
            rect.y = oy;
            if (hot_rect)
            	*hot_rect = rect;
            return item;
        }
    }
    return -1;
}

int uiFindItem(int item, int x, int y, int ox, int oy) {
	return uiFindItemForEvent(item, (UIevent)UI_ANY_MOUSE_INPUT,
			&ui_context->hot_rect, x, y, ox, oy);
}

void uiLayout() {
    assert(ui_context);
    if (!ui_context->count) return;

    // compute widths
    uiComputeBestSize(0,0);
    uiLayoutItem(0,0);

    // compute heights
    uiComputeBestSize(0,1);
    uiLayoutItem(0,1);

    uiValidateStateItems();
    // drawing routines may require this to be set already
    uiUpdateHotItem();
}

void uiUpdateHotItem() {
    assert(ui_context);
    if (!ui_context->count) return;
    ui_context->hot_item = uiFindItem(0,
        ui_context->cursor.x, ui_context->cursor.y, 0, 0);
}

int uiGetClicks() {
	return ui_context->clicks;
}

void uiProcess(int timestamp) {
    assert(ui_context);
    if (!ui_context->count) {
        uiClearInputEvents();
        return;
    }
    
    int hot_item = ui_context->last_hot_item;
    int active_item = ui_context->active_item;
    int focus_item = ui_context->focus_item;

    // send all keyboard events
    if (focus_item >= 0) {
        for (int i = 0; i < ui_context->eventcount; ++i) {
            ui_context->active_key = ui_context->events[i].key;
            ui_context->active_modifier = ui_context->events[i].mod;
            uiNotifyItem(focus_item, 
                ui_context->events[i].event);
        }
    } else {
        ui_context->focus_item = -1;
    }
    if (ui_context->scroll.x || ui_context->scroll.y) {
    	int scroll_item = uiFindItemForEvent(0, UI_SCROLL, NULL,
    			ui_context->cursor.x, ui_context->cursor.y, 0, 0);
    	if (scroll_item >= 0) {
            uiNotifyItem(scroll_item, UI_SCROLL);
    	}
    }

    uiClearInputEvents();

    int hot = ui_context->hot_item;

    switch(ui_context->state) {
    default:
    case UI_STATE_IDLE: {
        ui_context->start_cursor = ui_context->cursor;
        if (uiGetButton(0)) {
            hot_item = -1;
            active_item = hot;
            ui_context->active_rect = ui_context->hot_rect;
            
            if (active_item != focus_item) {
                focus_item = -1;
                ui_context->focus_item = -1;
            }
            
            if (active_item >= 0) {
            	if (
            		((timestamp - ui_context->last_click_timestamp) > UI_CLICK_THRESHOLD)
            	 || (ui_context->last_click_item != active_item)) {
            		ui_context->clicks = 0;
            	}
            	ui_context->clicks++;

                ui_context->last_click_timestamp = timestamp;
                ui_context->last_click_item = active_item;
                uiNotifyItem(active_item, UI_BUTTON0_DOWN);
            }            
            ui_context->state = UI_STATE_CAPTURE;            
        } else if (uiGetButton(2) && !uiGetLastButton(2)) {
            hot_item = -1;
        	hot = uiFindItemForEvent(0, UI_BUTTON2_DOWN,
        			&ui_context->active_rect,
        			ui_context->cursor.x, ui_context->cursor.y, 0, 0);
        	if (hot >= 0) {
        		uiNotifyItem(hot, UI_BUTTON2_DOWN);
        	}
        } else {
            hot_item = hot;
        }
    } break;
    case UI_STATE_CAPTURE: {
        if (!uiGetButton(0)) {
            if (active_item >= 0) {
                uiNotifyItem(active_item, UI_BUTTON0_UP);
                if (active_item == hot) {
                    uiNotifyItem(active_item, UI_BUTTON0_HOT_UP);
                }
            }
            active_item = -1;
            ui_context->state = UI_STATE_IDLE;
        } else {
            if (active_item >= 0) {
                uiNotifyItem(active_item, UI_BUTTON0_CAPTURE);
            }            
            if (hot == active_item)
                hot_item = hot;
            else
                hot_item = -1;
        }
    } break;
    }
    
    ui_context->last_cursor = ui_context->cursor;
    ui_context->last_hot_item = hot_item;
    ui_context->active_item = active_item;

    ui_context->last_timestamp = timestamp;
    ui_context->last_buttons = ui_context->buttons;
}

static int uiIsActive(int item) {
    assert(ui_context);
    return ui_context->active_item == item;
}

static int uiIsHot(int item) {
    assert(ui_context);
    return ui_context->last_hot_item == item;
}

static int uiIsFocused(int item) {
    assert(ui_context);
    return ui_context->focus_item == item;
}

UIitemState uiGetState(int item) {
    UIitem *pitem = uiItemPtr(item);
    if (pitem->flags & UI_ITEM_FROZEN) return UI_FROZEN;
    if (uiIsFocused(item)) {
        if (pitem->flags & (UI_KEY_DOWN|UI_CHAR|UI_KEY_UP)) return UI_ACTIVE;
    }
    if (uiIsActive(item)) {
        if (pitem->flags & (UI_BUTTON0_CAPTURE|UI_BUTTON0_UP)) return UI_ACTIVE;
        if ((pitem->flags & UI_BUTTON0_HOT_UP)
            && uiIsHot(item)) return UI_ACTIVE;
        return UI_COLD;
    } else if (uiIsHot(item)) {
        return UI_HOT;
    }
    return UI_COLD;
}

#endif // OUI_IMPLEMENTATION
