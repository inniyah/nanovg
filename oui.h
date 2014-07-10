/*
OUI - A minimal immediate GUI handling & layouting library

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

#ifndef _UI_H_
#define _UI_H_

/*

OUI (spoken like the french "oui" for "yes") is a single-header library for
layouting GUI elements and handling their user input.

Together with a set of widget drawing routines it can be used to build flowing
user interfaces; the intended use is for bootstrap situations where only basic
UI services are needed.
*/

// item states as returned by uiGetState()

// the item is inactive
#define UI_COLD   0x0000
// the item is inactive, but the cursor is hovering over this item
#define UI_HOT    0x0001
// the item is toggled or activated (depends on item kind)
#define UI_ACTIVE 0x0002
// the item is unresponsive
#define UI_FROZEN 0x0003
    
// item kinds
    
// this is a reserved kind and only used by the root item 0
#define UI_ROOT   0x0100
// Column container. Arranges child items vertically and adjusts their width to
// the width of the column. Items of fixed width will only be truncated, but not
// expanded.
#define UI_COLUMN 0x0101
// Row container. Arranges items horizontally and distributes their width to
// match the width of the row. Items of fixed width will only be truncated, but
// not expanded. The remaining space will be equally distributed among all items
// of dynamic width.
#define UI_ROW    0x0102

// Label control. The control is non-interactive and will not call any handlers.
#define UI_LABEL  0x0203
// Button control. Will call the buttons handler when activated.
#define UI_BUTTON 0x0204

// maximum number of items that may be added
#define UI_MAX_ITEMS 4096
// maximum size in bytes reserved for storage of application dependent data
// as passed to uiItem().
#define UI_MAX_BUFFERSIZE 1048576
// maximum size in bytes of a single data buffer passed to uiItem().
#define UI_MAX_DATASIZE 4096
// maximum depth of nested containers
#define UI_MAX_DEPTH 64

// opaque UI context
typedef struct UIcontext UIcontext;

// application defined context handle
typedef unsigned long long UIhandle;

// handler callback
typedef void (*UIhandler)(int item);

// layout rectangle
typedef struct UIrect {
    int x, y, w, h;
} UIrect;

// exemplary buffer of variable size to pass to the data argument of uiItem(); 
// see uiItem() for more information.
typedef struct UIdata {
    int size;
    unsigned char content[1];
} UIdata;

// unless declared otherwise, all operations have the complexity O(1).

// create a new UI context; call uiMakeCurrent() to make this context the
// current context.
UIcontext *uiCreateContext();

// select an UI context as the current context; a context must always be 
// selected before using any of the other UI functions
void uiMakeCurrent(UIcontext *ctx);

// release the memory of an UI context created with uiCreateContext(); if the
// context is the current context, the current context will be set to NULL
void uiDestroyContext(UIcontext *ctx);

// sets a mouse or gamepad button as pressed/released
// button is in the range 0..63 and maps to an application defined input
// source.
// enabled is 1 for pressed, 0 for released
void uiSetButton(int button, int enabled);

// returns the current state of an application dependent input button
// as set by uiSetButton().
// the function returns 1 if the button has been set to pressed, 0 for released.
int uiGetButton(int button);

// sets the current cursor position (usually belonging to a mouse) to the
// screen coordinates at (x,y)
void uiSetCursor(int x, int y);

// returns the current cursor position in screen coordinates as set by 
// uiSetCursor()
void uiGetCursor(int *x, int *y);

// clear the item buffer; uiClear() should be called before each UI declaration
// to avoid concatenation of the same UI multiple times.
// After the call, all previously declared item IDs are invalid, and all
// application dependent context data has been freed.
void uiClear();

// add a new UI item with size (w,h) and return the new items ID.
// parent is the item ID of the containing item; an item ID of 0 refers to the
// root item.
// handle is an application defined 64-bit handle. If handle is 0, the item
// will not be interactive.
// kind is one of UI_COLUMN, UI_ROW, UI_LABEL, UI_BUTTON and influences the
// items behavior in layouting and input handling.
// If w or h are 0, the dimension is marked as dynamic and will be rescaled
// accordingly by the containing element.
// if data is not NULL, it points to an application defined buffer conforming
// to the declaration of UIdata; The first element must always be a 32-bit 
// integer denoting the size of the structure in bytes. The contents of data
// will be copied and can be read back later using uiGetData(). The data
// pointer passed to uiItem() is allowed to become invalid right after the call.
int uiItem(int parent, UIhandle handle, int kind, 
    int w, int h, const void *data);

// add a new UI item of type UI_COLUMN.
// this is a shorthand of the equivalent call
// int id = uiItem(parent,0,UI_COLUMN,0,0,NULL); uiSetSpacing(id, spacing);
int uiColumn(int parent, int spacing);

// this is a shorthand of the equivalent call
// int id = uiItem(parent,0,UI_ROW,0,0,NULL); uiSetSpacing(id, spacing);
int uiRow(int parent, int spacing);

// layout all added items and update the internal state according to the
// current cursor position and button states.
// It is safe to immediately draw the items after a call to uiProcess().
// this is an O(N) operation for N = number of declared items.
void uiProcess();

// returns the number of child items a container item contains. If the item 
// is not a container or does not contain any items, 0 is returned.
// if item is 0, the child item count of the root item will be returned.
int uiGetChildCount(int item);

// returns the first child item of a container item. If the item is not
// a container or does not contain any items, -1 is returned.
// if item is 0, the first child item of the root item will be returned.
int uiFirstChild(int item);

// returns the last child item of a container item. If the item is not
// a container or does not contain any items, -1 is returned.
// if item is 0, the last child item of the root item will be returned.
int uiLastChild(int item);

// returns an items parent container item.
// if item is 0, -1 will be returned.
int uiParent(int item);

// returns an items child index relative to its parent. If the item is the
// first item, the return value is 0; If the item is the last item, the return
// value is equivalent to uiGetChildCount(uiParent(item))-1.
// if item is 0, 0 will be returned.
int uiGetChildId(int item);

// returns an items next sibling in the list of the parent containers children.
// if item is 0 or the item is the last child item, -1 will be returned.
int uiNextSibling(int item);

// assign a spacing value by which child items of a container items will be
// separated. If item is not a container type, the call has no effect.
void uiSetSpacing(int item, int spacing);

// returns the current spacing value assigned to item by uiSetSpacing()
int uiGetSpacing(int item);

// returns the kind of the item as passed to uiItem().
// The returned value is one of UI_COLUMN, UI_ROW, UI_LABEL, UI_BUTTON.
int uiGetKind(int item);

// returns the items layout rectangle relative to its parent. If uiGetRect()
// is called before uiProcess(), the values of the returned rectangle are
// undefined.
UIrect uiGetRect(int item);

// returns the items layout rectangle in absolute coordinates. If 
// uiGetAbsoluteRect() is called before uiProcess(), the values of the returned
// rectangle are undefined.
UIrect uiGetScreenRect(int item);

// explicitly assign a layout rectangle to an item; If uiSetRect() is called
// after uiProcess(), behavior is undefined.
// This function is primarily used to position the root element.
void uiSetRect(int item, int x, int y, int w, int h);

// return the application-dependent context data for an item as passed to
// uiItem(). The memory of the pointer is managed by the UI context.
const void *uiGetData(int item);

// return the application-dependent handle of the item as passed to uiItem().
UIhandle uiGetHandle(int item);

// return the current state of the item.
// The returned value is one of UI_COLD, UI_HOT, UI_ACTIVE.
int uiGetState(int item);

// set the handler callback for an interactive item. The meaning of the
// callback is dependent on the item kind.
void uiSetHandler(int item, UIhandler handler);

// return the handler callback for an item as passed to uiSetHandler()
UIhandler uiGetHandler(int item);

// set the state of a toggleable item to active. If set, uiGetState() will
// always return UI_ACTIVE.
// enabled is 1 for active, 0 for default behavior
void uiSetActive(int item, int enabled);

// returns the active state of a toggleable item;
// the function returns 1 if the item is always active, 0 for default behavior.
int uiGetActive(int item);

// set an interactive item to activate on button-down. The default behavior
// is to call the handler callback when the button is released; if set, 
// the handler will already be called if the button is pressed.
void uiSetEarlyHandler(int item, int enabled);

// returns the setting passed to uiSetEarlyHandler();
// the function returns 1 if the setting is active, 0 for default behavior.
int uiGetEarlyHandler(int item);

#endif // _UI_H_

#define UI_IMPLEMENTATION
#ifdef UI_IMPLEMENTATION

#include <assert.h>

#define UI_MAX_KIND 16

typedef enum UIflags {
    // if true, item is always active
    UI_FLAG_ALWAYS_ACTIVE = (1<<0),
    // if true, activate on mousedown, not mouseup
    UI_FLAG_EARLY_HANDLER = (1<<1),
} UIflags;

typedef struct UIitem {
    // declaration independent unique handle (for persistence)
    UIhandle handle;
    // handler
    UIhandler handler;
    
    // container structure
    
    // number of kids
    int numkids;
    // index of first kid
    int firstkid;
    // index of last kid
    int lastkid;
    
    // child structure
    
    // parent item
    int parent;
    // index of kid relative to parent
    int kidid;
    // index of next sibling with same parent
    int nextitem;
    
    // attributes
    
    // layout rectangle
    UIrect rect;
    // absolute position
    int absx,absy;
    // widget type
    int kind;
    // index of data or -1 for none
    int data;
    // layouting containers: spacing between items
    int spacing;
    // a combination of UIflags
    int flags;
} UIitem;

struct UIcontext {
    unsigned long long buttons;
    int cx, cy;
    
    UIhandle hot;
    UIhandle active;
    int handle_item;
    
    int count;    
    UIitem items[UI_MAX_ITEMS];
    int datasize;
    unsigned char data[UI_MAX_BUFFERSIZE];
};

static UIcontext *ui_context = NULL;

UIcontext *uiCreateContext() {
    UIcontext *ctx = (UIcontext *)malloc(sizeof(UIcontext));
    memset(ctx, 0, sizeof(UIcontext));
    return ctx;
}

void uiMakeCurrent(UIcontext *ctx) {
    ui_context = ctx;
    if (ui_context)
        uiClear();
}

void uiDestroyContext(UIcontext *ctx) {
    if (ui_context == ctx)
        uiMakeCurrent(NULL);
    free(ctx);
}

void uiSetButton(int button, int enabled) {
    assert(ui_context);
    unsigned long long mask = 1ull<<button;
    ui_context->buttons = (enabled)?
        (ui_context->buttons | mask):
        (ui_context->buttons & ~mask);
}

int uiGetButton(int button) {
    assert(ui_context);
    return (ui_context->buttons & (1ull<<button))?1:0;
}

void uiSetCursor(int x, int y) {
    assert(ui_context);
    ui_context->cx = x;
    ui_context->cy = y;
}

void uiGetCursor(int *x, int *y) {
    assert(ui_context);
    *x = ui_context->cx;
    *y = ui_context->cy;
}

UIitem *uiItemPtr(int item) {
    assert(ui_context && (item >= 0) && (item < ui_context->count));
    return ui_context->items + item;
}

void uiClear() {
    assert(ui_context);
    ui_context->count = 1;
    ui_context->datasize = 0;
    ui_context->hot = 0;

    // init root object    
    UIitem *item = ui_context->items;
    memset(item, 0, sizeof(UIitem));
    item->parent = -1;
    item->firstkid = -1;
    item->lastkid = -1;
    item->nextitem = -1;
    item->kind = UI_ROOT;
    item->data = -1;
}

int uiAllocItem(int parent, UIhandle handle, int kind, const void *data) {
    assert(ui_context && (ui_context->count < UI_MAX_ITEMS));
    assert(parent >= 0);
    int idx = ui_context->count++;
    UIitem *item = uiItemPtr(idx);
    memset(item, 0, sizeof(UIitem));
    item->parent = parent;
    item->handle = handle;
    item->firstkid = -1;
    item->lastkid = -1;
    item->nextitem = -1;
    item->kidid = ui_context->items[parent].numkids++;
    if (ui_context->items[parent].lastkid < 0) {
        ui_context->items[parent].firstkid = idx;
        ui_context->items[parent].lastkid = idx;
    } else {
        ui_context->items[ui_context->items[parent].lastkid].nextitem = idx;
        ui_context->items[parent].lastkid = idx;
    }
    item->kind = kind;
    item->data = -1;
    if (data) {
        UIdata *pdata = (UIdata *)data;        
        assert((pdata->size > 0) && (pdata->size < UI_MAX_DATASIZE));
        assert((ui_context->datasize+pdata->size) <= UI_MAX_BUFFERSIZE);
        item->data = ui_context->datasize;
        ui_context->datasize += pdata->size;
        memcpy(ui_context->data + item->data, data, pdata->size);
    }
    return idx;
}

int uiItem(int parent, UIhandle handle, int kind, int w, int h, const void *data) {
    int idx = uiAllocItem(parent, handle, kind, data);
    UIitem *item = uiItemPtr(idx);
    item->rect.w = w;
    item->rect.h = h;
    return idx;
}

void uiSetSpacing(int item, int spacing) {
    uiItemPtr(item)->spacing = spacing;
}

int uiGetSpacing(int item) {
    return uiItemPtr(item)->spacing;
}

int uiColumn(int parent, int spacing) {
    int idx = uiItem(parent, 0, UI_COLUMN, 0, 0, NULL);
    uiSetSpacing(idx, spacing);
    return idx;
}

int uiRow(int parent, int spacing) {
    int idx = uiItem(parent, 0, UI_ROW, 0, 0, NULL);
    uiSetSpacing(idx, spacing);
    return idx;
}

UIrect uiGetRect(int item) {
    return uiItemPtr(item)->rect;
}

UIrect uiGetScreenRect(int item) {
    UIitem *pitem = uiItemPtr(item);
    UIrect rect = pitem->rect;
    rect.x = pitem->absx;
    rect.y = pitem->absy;
    return rect;
}

void uiSetRect(int item, int x, int y, int w, int h) {
    UIitem *pitem = uiItemPtr(item);
    pitem->rect.w = w;
    pitem->rect.h = h;
    pitem->rect.x = x;
    pitem->rect.y = y;
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

int uiParent(int item) {
    return uiItemPtr(item)->parent;
}

int uiGetKind(int item) {
    return uiItemPtr(item)->kind;
}

static void uiSetFlag(int item, int flag, int enabled) {
    if (enabled)
        uiItemPtr(item)->flags |= flag;
    else
        uiItemPtr(item)->flags &= ~flag;
}

static int uiGetFlag(int item, int flag) {
    return (uiItemPtr(item)->flags & flag)?1:0;
}

void uiSetActive(int item, int enabled) {
    uiSetFlag(item, UI_FLAG_ALWAYS_ACTIVE, enabled);
}

int uiGetActive(int item) {
    return uiGetFlag(item, UI_FLAG_ALWAYS_ACTIVE);
}

void uiSetEarlyHandler(int item, int enabled) {
    uiSetFlag(item, UI_FLAG_EARLY_HANDLER, enabled);
}

int uiGetEarlyHandler(int item) {
    return uiGetFlag(item, UI_FLAG_EARLY_HANDLER);
}

const void *uiGetData(int item) {
    UIitem *pitem = uiItemPtr(item);
    if (pitem->data < 0) return NULL;
    return ui_context->data + pitem->data;
}

UIhandle uiGetHandle(int item) {
    return uiItemPtr(item)->handle;
}

void uiSetHandler(int item, UIhandler handler) {
    uiItemPtr(item)->handler = handler;
}

UIhandler uiGetHandler(int item) {
    return uiItemPtr(item)->handler;
}

int uiGetChildId(int item) {
    return uiItemPtr(item)->kidid;
}

int uiGetChildCount(int item) {
    return uiItemPtr(item)->numkids;
}

void uiLayoutItem(int item);
void uiLayoutChildren(int item) {
    int kid = uiFirstChild(item);
    while (kid > 0) {
        uiLayoutItem(kid);
        kid = uiNextSibling(kid);
    }
}

void uiLayoutItem(int item) {
    UIrect rect = uiGetRect(item);
    
    switch(uiGetKind(item)) {
        case UI_COLUMN:
        case UI_ROOT: {
            int kid = uiFirstChild(item);
            while (kid > 0) {
                UIitem *pitem = uiItemPtr(kid);
                if (!pitem->rect.w || (pitem->rect.w > rect.w)) {
                    pitem->rect.w = rect.w;
                }
                kid = uiNextSibling(kid);
            }
            
            uiLayoutChildren(item);
            
            int spacing = uiItemPtr(item)->spacing;
            int h = -spacing;
            // stack kids vertically
            kid = uiFirstChild(item);
            while (kid > 0) {
                UIitem *pitem = uiItemPtr(kid);
                h += spacing;
                pitem->rect.y = h;
                h += pitem->rect.h;
                kid = uiNextSibling(kid);
            }
            
            if (h > rect.h) {
                uiItemPtr(item)->rect.h = h;
            }
            
        } break;
        case UI_ROW: {
            int spacing = uiItemPtr(item)->spacing;
            // figure out height of row
            // also see how much horizontal space is used
            int lastkidid = uiGetChildCount(item)-1;
            lastkidid = (lastkidid<0)?0:lastkidid;
            int w = spacing*lastkidid;
            // how many children have no explicit width?
            int numdynkids = 0;
            int kid = uiFirstChild(item);
            while (kid > 0) {
                UIitem *pitem = uiItemPtr(kid);
                if (!pitem->rect.w)
                    numdynkids++;
                else
                    w += pitem->rect.w;
                kid = uiNextSibling(kid);
            }
            
            int space = rect.w - w;
            // distribute remaining width across children
            int dw = numdynkids?(space / numdynkids):0;
            dw = (dw<0)?0:dw;
            // rounding error
            space -= numdynkids*dw;

            w = -spacing;
            // stack kids horizontally
            kid = uiFirstChild(item);
            while (kid > 0) {
                UIitem *pitem = uiItemPtr(kid);
                w += spacing;
                pitem->rect.x = w;
                if (!pitem->rect.w) {
                    --numdynkids;
                    // round last kid
                    if (!numdynkids)
                        dw += space;
                    pitem->rect.w = dw;
                }
                w += pitem->rect.w;
                kid = uiNextSibling(kid);
            }
            
            uiLayoutChildren(item);

            // adjust row height to tallest child
            kid = uiFirstChild(item);
            while (kid > 0) {
                UIitem *pitem = uiItemPtr(kid);
                if (pitem->rect.h > rect.h)
                    rect.h = pitem->rect.h;
                kid = uiNextSibling(kid);
            }
            uiItemPtr(item)->rect.h = rect.h;
        } break;
        default: break;
    }
}

void uiUpdateItemState(int item, int x, int y) {
    UIitem *pitem = uiItemPtr(item);
    pitem->absx = pitem->rect.x+x;
    pitem->absy = pitem->rect.y+y;
    
    if (pitem->handle) {
        int cx = ui_context->cx - pitem->absx;
        int cy = ui_context->cy - pitem->absy;
        if ((cx>=0)
            && (cy>=0)
            && (cx<pitem->rect.w)
            && (cy<pitem->rect.h)) {
            ui_context->hot = pitem->handle;
            
            // button down, no widget activated
            if (!ui_context->active && uiGetButton(0)) {
                ui_context->active = pitem->handle;
                if (pitem->flags & UI_FLAG_EARLY_HANDLER) {
                    ui_context->handle_item = item;
                }
            } else if ( // button up, this widget is active
                (ui_context->active == pitem->handle) && !uiGetButton(0)) {
                ui_context->handle_item = item;
            }
        }
    }
    
    int kid = uiFirstChild(item);
    while (kid > 0) {
        uiUpdateItemState(kid, pitem->absx, pitem->absy);
        kid = uiNextSibling(kid);
    }

}

void uiProcess() {
    ui_context->handle_item = -1;
    uiLayoutItem(0);
    uiUpdateItemState(0, 0, 0);
    if (!uiGetButton(0)) {
        ui_context->active = 0;
    }
    if (ui_context->handle_item >= 0) {
        UIhandler handler = uiGetHandler(ui_context->handle_item);
        if (handler) {
            handler(ui_context->handle_item);
        }
    }
}

int uiIsActive(int item) {
    assert(ui_context);
    return (ui_context->active == uiItemPtr(item)->handle)?1:0;
}

int uiIsHot(int item) {
    assert(ui_context);
    return (ui_context->hot == uiItemPtr(item)->handle)?1:0;
}

int uiGetState(int item) {
    UIitem *pitem = uiItemPtr(item);
    if (pitem->flags & UI_FLAG_ALWAYS_ACTIVE) return UI_ACTIVE;
    return (!uiIsHot(item))?UI_COLD:(uiIsActive(item))?UI_ACTIVE:UI_HOT;

}

#endif // UI_IMPLEMENTATION
