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

#define UI_COLD   0x0000
#define UI_HOT    0x0001
#define UI_ACTIVE 0x0002
    
// containers
#define UI_ROOT   0x0100
#define UI_COLUMN 0x0101
#define UI_ROW    0x0102

// controls
#define UI_LABEL  0x0203
#define UI_BUTTON 0x0204
#define UI_RADIO  0x0205

#define UI_MAX_ITEMS 4096
#define UI_MAX_BUFFERSIZE 1048576
#define UI_MAX_DATASIZE 4096
#define UI_MAX_DEPTH 64

typedef struct UIcontext UIcontext;
typedef unsigned long long UIhandle;

typedef struct UIrect {
    int x, y, w, h;
} UIrect;

typedef struct UIdata {
    int size;
    unsigned char content[1];
} UIdata;

UIcontext *uiCreateContext();
void uiMakeCurrent(UIcontext *ctx);
void uiDestroyContext(UIcontext *ctx);

void uiSetButton(int button, int enabled);
int uiGetButton(int button);

void uiSetCursor(int x, int y);
void uiGetCursor(int *x, int *y);

void uiClear();

int uiItem(int parent, UIhandle handle, int kind, 
    int w, int h, void *data);
int uiColumn(int parent, int spacing);
int uiRow(int parent, int spacing);

void uiLayout();

int uiFirstChild(int item);
int uiLastChild(int item);
int uiNextSibling(int item);
int uiParent(int item);

void uiSetSpacing(int item, int spacing);
int uiGetSpacing(int item);

int uiGetKind(int item);
UIrect uiGetRect(int item);
UIrect uiGetScreenRect(int item);
void uiSetRect(int item, int x, int y, int w, int h);
void *uiGetData(int item);
int uiGetChildId(int item);
int uiGetChildCount(int item);
int uiGetHandle(int item);
int uiGetState(int item);

#endif // _UI_H_

#ifdef UI_IMPLEMENTATION

#include <assert.h>

#define UI_MAX_KIND 16

typedef struct UIitem {
    UIhandle handle;
    int parent;
    // number of kids
    int numkids;
    // index of kid relative to parent
    int kidid;
    UIrect rect;
    int absx,absy;
    int kind;
    int data;
    int spacing;
    // index of first kid
    int firstkid;
    // index of last kid
    int lastkid;
    // index of next sibling with same parent
    int nextitem;
} UIitem;

struct UIcontext {
    unsigned long long buttons;
    int cx, cy;
    
    UIhandle hot;
    UIhandle active;
    
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
    uiClear();
}

void uiDestroyContext(UIcontext *ctx) {
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

int uiAllocItem(int parent, UIhandle handle, int kind, void *data) {
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

int uiItem(int parent, UIhandle handle, int kind, int w, int h, void *data) {
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

void *uiGetData(int item) {
    UIitem *pitem = uiItemPtr(item);
    if (pitem->data < 0) return NULL;
    return ui_context->data + pitem->data;
}

int uiGetHandle(int item) {
    return uiItemPtr(item)->handle;
}

int uiGetChildId(int item) {
    return uiItemPtr(item)->kidid;
}

int uiGetChildCount(int item) {
    return uiItemPtr(item)->numkids;
}

void uiLayoutItem(int item, int x, int y);
void uiLayoutChildren(int item, int x, int y) {
    int kid = uiFirstChild(item);
    while (kid > 0) {
        uiLayoutItem(kid, x, y);
        kid = uiNextSibling(kid);
    }
}

void uiLayoutItem(int item, int x, int y) {
    UIrect rect = uiGetRect(item);
    rect.x += x;
    rect.y += y;
    
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
            
            uiLayoutChildren(item, rect.x, rect.y);
            
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
            
            uiLayoutChildren(item, rect.x, rect.y);

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
            
            if (!ui_context->active && uiGetButton(0)) {
                ui_context->active = pitem->handle;
            }
        }
    }
    
    int kid = uiFirstChild(item);
    while (kid > 0) {
        uiUpdateItemState(kid, pitem->absx, pitem->absy);
        kid = uiNextSibling(kid);
    }

}

void uiLayout() {
    uiLayoutItem(0, 0, 0);
    uiUpdateItemState(0, 0, 0);
    if (!uiGetButton(0)) {
        ui_context->active = 0;
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
    return (!uiIsHot(item))?UI_COLD:(uiIsActive(item))?UI_ACTIVE:UI_HOT;

}

#endif // UI_IMPLEMENTATION
