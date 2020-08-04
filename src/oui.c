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

#include "oui.h"

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "android.h"

#ifdef _MSC_VER
    #pragma warning (disable: 4996) // Switch off security warnings
    #pragma warning (disable: 4100) // Switch off unreferenced formal parameter warnings
    #pragma warning (disable: 4244)
    #pragma warning (disable: 4305)
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

static int ui_max(int a, int b) {
    return (a>b)?a:b;
}

static int ui_min(int a, int b) {
    return (a<b)?a:b;
}

static float ui_maxf(float a, float b) {
    return (a>b)?a:b;
}

static float ui_minf(float a, float b) {
    return (a<b)?a:b;
}

static UIcontext *ui_context = NULL;

void uiClear() {
    ui_context->last_count = ui_context->count;
    ui_context->count = 0;
    ui_context->datasize = 0;
    ui_context->hot_item = -1;
    // swap buffers
    UIitem *items = ui_context->items;
    ui_context->items = ui_context->last_items;
    ui_context->last_items = items;
    for (int i = 0; i < ui_context->last_count; ++i) {
        ui_context->item_map[i] = -1;
    }
}

UIcontext *uiCreateContext(
        unsigned int item_capacity,
        unsigned int buffer_capacity) {
    assert(item_capacity);
    UIcontext *ctx = (UIcontext *)malloc(sizeof(UIcontext));
    memset(ctx, 0, sizeof(UIcontext));
    ctx->item_capacity = item_capacity;
    ctx->buffer_capacity = buffer_capacity;
    ctx->stage = UI_STAGE_PROCESS;
    ctx->items = (UIitem *)malloc(sizeof(UIitem) * item_capacity);
    ctx->last_items = (UIitem *)malloc(sizeof(UIitem) * item_capacity);
    ctx->item_map = (int *)malloc(sizeof(int) * item_capacity);
    if (buffer_capacity) {
        ctx->data = (unsigned char *)malloc(buffer_capacity);
    }

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
    free(ctx->items);
    free(ctx->last_items);
    free(ctx->item_map);
    free(ctx->data);
    free(ctx);
}

OUI_EXPORT UIcontext *uiGetContext() {
    return ui_context;
}

void uiSetButton(unsigned int button, unsigned int mod, int enabled) {
    assert(ui_context);
    unsigned long long mask = 1ull<<button;
    // set new bit
    ui_context->buttons = (enabled)?
            (ui_context->buttons | mask):
            (ui_context->buttons & ~mask);
    ui_context->active_button_modifier = mod;
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

int uiGetLastButton(unsigned int button) {
    assert(ui_context);
    return (ui_context->last_buttons & (1ull<<button))?1:0;
}

int uiGetButton(unsigned int button) {
    assert(ui_context);
    return (ui_context->buttons & (1ull<<button))?1:0;
}

int uiButtonPressed(unsigned int button) {
    assert(ui_context);
    return !uiGetLastButton(button) && uiGetButton(button);
}

int uiButtonReleased(unsigned int button) {
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

int uiGetItemCount() {
    assert(ui_context);
    return ui_context->count;
}

int uiGetLastItemCount() {
    assert(ui_context);
    return ui_context->last_count;
}

unsigned int uiGetAllocSize() {
    assert(ui_context);
    return ui_context->datasize;
}

UIitem *uiItemPtr(int item) {
    assert(ui_context && (item >= 0) && (item < ui_context->count));
    return ui_context->items + item;
}

UIitem *uiLastItemPtr(int item) {
    assert(ui_context && (item >= 0) && (item < ui_context->last_count));
    return ui_context->last_items + item;
}

int uiGetHotItem() {
    assert(ui_context);
    return ui_context->hot_item;
}

void uiFocus(int item) {
    assert(ui_context && (item >= -1) && (item < ui_context->count));
    assert(ui_context->stage != UI_STAGE_LAYOUT);
    ui_context->focus_item = item;
}

static void uiValidateStateItems() {
    assert(ui_context);
    ui_context->last_hot_item = uiRecoverItem(ui_context->last_hot_item);
    ui_context->active_item = uiRecoverItem(ui_context->active_item);
    ui_context->focus_item = uiRecoverItem(ui_context->focus_item);
    ui_context->last_click_item = uiRecoverItem(ui_context->last_click_item);
}

int uiGetFocusedItem() {
    assert(ui_context);
    return ui_context->focus_item;
}


void uiBeginLayout() {
    assert(ui_context);
    assert(ui_context->stage == UI_STAGE_PROCESS); // must run uiEndLayout(), uiProcess() first
    uiClear();
    ui_context->stage = UI_STAGE_LAYOUT;
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
    assert(ui_context->stage == UI_STAGE_LAYOUT); // must run between uiBeginLayout() and uiEndLayout()
    assert(ui_context->count < (int)ui_context->item_capacity);
    int idx = ui_context->count++;
    UIitem *item = uiItemPtr(idx);
    memset(item, 0, sizeof(UIitem));
    item->firstkid = -1;
    item->nextitem = -1;
    return idx;
}

void uiNotifyItem(int item, UIevent event) {
    assert(ui_context);
    if (!ui_context->handler)
        return;
    assert((event & UI_ITEM_EVENT_MASK) == event);
    UIitem *pitem = uiItemPtr(item);
    if (pitem->flags & event) {
        ui_context->handler(item, event);
    }
}

int uiLastChild(int item) {
    item = uiFirstChild(item);
    if (item < 0)
        return -1;
    while (true) {
        int nextitem = uiNextSibling(item);
        if (nextitem < 0)
            return item;
        item = nextitem;
    }
}

int uiAppend(int item, int sibling) {
    assert(sibling > 0);
    UIitem *pitem = uiItemPtr(item);
    UIitem *psibling = uiItemPtr(sibling);
    assert(!(psibling->flags & UI_ITEM_INSERTED));
    psibling->nextitem = pitem->nextitem;
    psibling->flags |= UI_ITEM_INSERTED;
    pitem->nextitem = sibling;
    return sibling;
}

int uiInsert(int item, int child) {
    assert(child > 0);
    UIitem *pparent = uiItemPtr(item);
    UIitem *pchild = uiItemPtr(child);
    assert(!(pchild->flags & UI_ITEM_INSERTED));
    if (pparent->firstkid < 0) {
        pparent->firstkid = child;
        pchild->flags |= UI_ITEM_INSERTED;
    } else {
        uiAppend(uiLastChild(item), child);
    }
    return child;
}

int uiInsertFront(int item, int child) {
    return uiInsert(item, child);
}

int uiInsertBack(int item, int child) {
    assert(child > 0);
    UIitem *pparent = uiItemPtr(item);
    UIitem *pchild = uiItemPtr(child);
    assert(!(pchild->flags & UI_ITEM_INSERTED));
    pchild->nextitem = pparent->firstkid;
    pparent->firstkid = child;
    pchild->flags |= UI_ITEM_INSERTED;
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
    if (!w)
        pitem->flags &= ~UI_ITEM_HFIXED;
    else
        pitem->flags |= UI_ITEM_HFIXED;
    if (!h)
        pitem->flags &= ~UI_ITEM_VFIXED;
    else
        pitem->flags |= UI_ITEM_VFIXED;
}

int uiGetWidth(int item) {
    return uiItemPtr(item)->size[0];
}

int uiGetHeight(int item) {
    return uiItemPtr(item)->size[1];
}

void uiSetLayout(int item, unsigned int flags) {
    UIitem *pitem = uiItemPtr(item);
    assert((flags & UI_ITEM_LAYOUT_MASK) == (unsigned int)flags);
    pitem->flags &= ~UI_ITEM_LAYOUT_MASK;
    pitem->flags |= flags & UI_ITEM_LAYOUT_MASK;
}

unsigned int uiGetLayout(int item) {
    return uiItemPtr(item)->flags & UI_ITEM_LAYOUT_MASK;
}

void uiSetBox(int item, unsigned int flags) {
    UIitem *pitem = uiItemPtr(item);
    assert((flags & UI_ITEM_BOX_MASK) == (unsigned int)flags);
    pitem->flags &= ~UI_ITEM_BOX_MASK;
    pitem->flags |= flags & UI_ITEM_BOX_MASK;
}

unsigned int uiGetBox(int item) {
    return uiItemPtr(item)->flags & UI_ITEM_BOX_MASK;
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
void uiComputeImposedSize(UIitem *pitem, int dim) {
    int wdim = dim+2;
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
void uiComputeStackedSize(UIitem *pitem, int dim) {
    int wdim = dim+2;
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

// compute bounding box of all items stacked, repeating when breaking
void uiComputeWrappedStackedSize(UIitem *pitem, int dim) {
    int wdim = dim+2;

    short need_size = 0;
    short need_size2 = 0;
    int kid = pitem->firstkid;
    while (kid >= 0) {
        UIitem *pkid = uiItemPtr(kid);

        // if next position moved back, we assume a new line
        if (pkid->flags & UI_BREAK) {
            need_size2 = ui_max(need_size2, need_size);
            // newline
            need_size = 0;
        }

        // width = start margin + calculated width + end margin
        need_size += pkid->margins[dim] + pkid->size[dim] + pkid->margins[wdim];
        kid = uiNextSibling(kid);
    }
    pitem->size[dim] = ui_max(need_size2, need_size);
}

// compute bounding box of all items stacked + wrapped
void uiComputeWrappedSize(UIitem *pitem, int dim) {
    int wdim = dim+2;

    short need_size = 0;
    short need_size2 = 0;
    int kid = pitem->firstkid;
    while (kid >= 0) {
        UIitem *pkid = uiItemPtr(kid);

        // if next position moved back, we assume a new line
        if (pkid->flags & UI_BREAK) {
            need_size2 += need_size;
            // newline
            need_size = 0;
        }

        // width = start margin + calculated width + end margin
        int kidsize = pkid->margins[dim] + pkid->size[dim] + pkid->margins[wdim];
        need_size = ui_max(need_size, kidsize);
        kid = uiNextSibling(kid);
    }
    pitem->size[dim] = need_size2 + need_size;
}

static void uiComputeSize(int item, int dim) {
    UIitem *pitem = uiItemPtr(item);

    // children expand the size
    int kid = pitem->firstkid;
    while (kid >= 0) {
        uiComputeSize(kid, dim);
        kid = uiNextSibling(kid);
    }

    if (pitem->size[dim])
        return;
    switch(pitem->flags & UI_ITEM_BOX_MODEL_MASK) {
    case UI_COLUMN|UI_WRAP: {
        // flex model
        if (dim) // direction
            uiComputeStackedSize(pitem, 1);
        else
            uiComputeImposedSize(pitem, 0);
    } break;
    case UI_ROW|UI_WRAP: {
        // flex model
        if (!dim) // direction
            uiComputeWrappedStackedSize(pitem, 0);
        else
            uiComputeWrappedSize(pitem, 1);
    } break;
    case UI_COLUMN:
    case UI_ROW: {
        // flex model
        if ((pitem->flags & 1) == (unsigned int)dim) // direction
            uiComputeStackedSize(pitem, dim);
        else
            uiComputeImposedSize(pitem, dim);
    } break;
    default: {
        // layout model
        uiComputeImposedSize(pitem, dim);
    } break;
    }
}

// stack all items according to their alignment
void uiArrangeStacked(UIitem *pitem, int dim, bool wrap) {
    int wdim = dim+2;

    short space = pitem->size[dim];
    float max_x2 = (float)pitem->margins[dim] + (float)space;

    int start_kid = pitem->firstkid;
    while (start_kid >= 0) {
        short used = 0;

        int count = 0; // count of fillers
        int squeezed_count = 0; // count of squeezable elements
        int total = 0;
        bool hardbreak = false;
        // first pass: count items that need to be expanded,
        // and the space that is used
        int kid = start_kid;
        int end_kid = -1;
        while (kid >= 0) {
            UIitem *pkid = uiItemPtr(kid);
            int flags = (pkid->flags & UI_ITEM_LAYOUT_MASK) >> dim;
            int fflags = (pkid->flags & UI_ITEM_FIXED_MASK) >> dim;
            short extend = used;
            if ((flags & UI_HFILL) == UI_HFILL) { // grow
                count++;
                extend += pkid->margins[dim] + pkid->margins[wdim];
            } else {
                if ((fflags & UI_ITEM_HFIXED) != UI_ITEM_HFIXED)
                    squeezed_count++;
                extend += pkid->margins[dim] + pkid->size[dim] + pkid->margins[wdim];
            }
            // wrap on end of line or manual flag
            if (wrap && (total && ((extend > space) || (pkid->flags & UI_BREAK)))) {
                end_kid = kid;
                hardbreak = ((pkid->flags & UI_BREAK) == UI_BREAK);
                // add marker for subsequent queries
                pkid->flags |= UI_BREAK;
                break;
            } else {
                used = extend;
                kid = uiNextSibling(kid);
            }
            total++;
        }

        int extra_space = space - used;
        float filler = 0.0f;
        float spacer = 0.0f;
        float extra_margin = 0.0f;
        float eater = 0.0f;

        if (extra_space > 0) {
            if (count) {
                filler = (float)extra_space / (float)count;
            } else if (total) {
                switch(pitem->flags & UI_JUSTIFY) {
                default: {
                    extra_margin = extra_space / 2.0f;
                } break;
                case UI_JUSTIFY: {
                    // justify when not wrapping or not in last line,
                    // or not manually breaking
                    if (!wrap || ((end_kid != -1) && !hardbreak))
                        spacer = (float)extra_space / (float)(total-1);
                } break;
                case UI_START: {
                } break;
                case UI_END: {
                    extra_margin = extra_space;
                } break;
                }
            }
        } else if (!wrap && (extra_space < 0)) {
           eater = (float)extra_space / (float)squeezed_count;
        }

        // distribute width among items
        float x = (float)pitem->margins[dim];
        float x1;
        // second pass: distribute and rescale
        kid = start_kid;
        while (kid != end_kid) {
            short ix0,ix1;
            UIitem *pkid = uiItemPtr(kid);
            int flags = (pkid->flags & UI_ITEM_LAYOUT_MASK) >> dim;
            int fflags = (pkid->flags & UI_ITEM_FIXED_MASK) >> dim;

            x += (float)pkid->margins[dim] + extra_margin;
            if ((flags & UI_HFILL) == UI_HFILL) { // grow
                x1 = x+filler;
            } else if ((fflags & UI_ITEM_HFIXED) == UI_ITEM_HFIXED) {
                x1 = x+(float)pkid->size[dim];
            } else {
                // squeeze
                x1 = x+ui_maxf(0.0f,(float)pkid->size[dim]+eater);
            }
            ix0 = (short)x;
            if (wrap)
                ix1 = (short)ui_minf(max_x2-(float)pkid->margins[wdim], x1);
            else
                ix1 = (short)x1;
            pkid->margins[dim] = ix0;
            pkid->size[dim] = ix1-ix0;
            x = x1 + (float)pkid->margins[wdim];

            kid = uiNextSibling(kid);
            extra_margin = spacer;
        }

        start_kid = end_kid;
    }
}

// superimpose all items according to their alignment
static void uiArrangeImposedRange(UIitem *pitem, int dim,
        int start_kid, int end_kid, short offset, short space) {
    (void)pitem; // unused
    int wdim = dim+2;

    int kid = start_kid;
    while (kid != end_kid) {
        UIitem *pkid = uiItemPtr(kid);

        int flags = (pkid->flags & UI_ITEM_LAYOUT_MASK) >> dim;

        switch(flags & UI_HFILL) {
        default: break;
        case UI_HCENTER: {
            pkid->margins[dim] += (space-pkid->size[dim])/2 - pkid->margins[wdim];
        } break;
        case UI_RIGHT: {
            pkid->margins[dim] = space-pkid->size[dim]-pkid->margins[wdim];
        } break;
        case UI_HFILL: {
            pkid->size[dim] = ui_max(0,space-pkid->margins[dim]-pkid->margins[wdim]);
        } break;
        }
        pkid->margins[dim] += offset;

        kid = uiNextSibling(kid);
    }
}

static void uiArrangeImposed(UIitem *pitem, int dim) {
    uiArrangeImposedRange(pitem, dim, pitem->firstkid, -1, pitem->margins[dim], pitem->size[dim]);
}

// superimpose all items according to their alignment,
// squeeze items that expand the available space
static void uiArrangeImposedSqueezedRange(UIitem *pitem, int dim,
        int start_kid, int end_kid, short offset, short space) {
    (void)pitem; // unused
    int wdim = dim+2;

    int kid = start_kid;
    while (kid != end_kid) {
        UIitem *pkid = uiItemPtr(kid);

        int flags = (pkid->flags & UI_ITEM_LAYOUT_MASK) >> dim;

        short min_size = ui_max(0,space-pkid->margins[dim]-pkid->margins[wdim]);
        switch(flags & UI_HFILL) {
        default: {
            pkid->size[dim] = ui_min(pkid->size[dim], min_size);
        } break;
        case UI_HCENTER: {
            pkid->size[dim] = ui_min(pkid->size[dim], min_size);
            pkid->margins[dim] += (space-pkid->size[dim])/2 - pkid->margins[wdim];
        } break;
        case UI_RIGHT: {
            pkid->size[dim] = ui_min(pkid->size[dim], min_size);
            pkid->margins[dim] = space-pkid->size[dim]-pkid->margins[wdim];
        } break;
        case UI_HFILL: {
            pkid->size[dim] = min_size;
        } break;
        }
        pkid->margins[dim] += offset;

        kid = uiNextSibling(kid);
    }
}

static void uiArrangeImposedSqueezed(UIitem *pitem, int dim) {
    uiArrangeImposedSqueezedRange(pitem, dim, pitem->firstkid, -1, pitem->margins[dim], pitem->size[dim]);
}

// superimpose all items according to their alignment
short uiArrangeWrappedImposedSqueezed(UIitem *pitem, int dim) {
    int wdim = dim+2;

    short offset = pitem->margins[dim];

    short need_size = 0;
    int kid = pitem->firstkid;
    int start_kid = kid;
    while (kid >= 0) {
        UIitem *pkid = uiItemPtr(kid);

        if (pkid->flags & UI_BREAK) {
            uiArrangeImposedSqueezedRange(pitem, dim, start_kid, kid, offset, need_size);
            offset += need_size;
            start_kid = kid;
            // newline
            need_size = 0;
        }

        // width = start margin + calculated width + end margin
        int kidsize = pkid->margins[dim] + pkid->size[dim] + pkid->margins[wdim];
        need_size = ui_max(need_size, kidsize);
        kid = uiNextSibling(kid);
    }

    uiArrangeImposedSqueezedRange(pitem, dim, start_kid, -1, offset, need_size);
    offset += need_size;
    return offset;
}

static void uiArrange(int item, int dim) {
    UIitem *pitem = uiItemPtr(item);

    switch(pitem->flags & UI_ITEM_BOX_MODEL_MASK) {
    case UI_COLUMN|UI_WRAP: {
        // flex model, wrapping
        if (dim) { // direction
            uiArrangeStacked(pitem, 1, true);
            // this retroactive resize will not effect parent widths
            short offset = uiArrangeWrappedImposedSqueezed(pitem, 0);
            pitem->size[0] = offset - pitem->margins[0];
        }
    } break;
    case UI_ROW|UI_WRAP: {
        // flex model, wrapping
        if (!dim) { // direction
            uiArrangeStacked(pitem, 0, true);
        } else {
            uiArrangeWrappedImposedSqueezed(pitem, 1);
        }
    } break;
    case UI_COLUMN:
    case UI_ROW: {
        // flex model
        if ((pitem->flags & 1) == (unsigned int)dim) // direction
            uiArrangeStacked(pitem, dim, false);
        else
            uiArrangeImposedSqueezed(pitem, dim);
    } break;
    default: {
        // layout model
        uiArrangeImposed(pitem, dim);
    } break;
    }

    int kid = uiFirstChild(item);
    while (kid >= 0) {
        uiArrange(kid, dim);
        kid = uiNextSibling(kid);
    }
}

bool uiCompareItems(UIitem *item1, UIitem *item2) {
    return ((item1->flags & UI_ITEM_COMPARE_MASK) == (item2->flags & UI_ITEM_COMPARE_MASK));

}

static bool uiMapItems(int item1, int item2) {
    UIitem *pitem1 = uiLastItemPtr(item1);
    if (item2 == -1) {
        return false;
    }

    UIitem *pitem2 = uiItemPtr(item2);
    if (!uiCompareItems(pitem1, pitem2)) {
        return false;
    }

    int count = 0;
    int failed = 0;
    int kid1 = pitem1->firstkid;
    int kid2 = pitem2->firstkid;
    while (kid1 != -1) {
        UIitem *pkid1 = uiLastItemPtr(kid1);
        count++;
        if (!uiMapItems(kid1, kid2)) {
            failed = count;
            break;
        }
        kid1 = pkid1->nextitem;
        if (kid2 != -1) {
            kid2 = uiItemPtr(kid2)->nextitem;
        }
    }

    if (count && (failed == 1)) {
        return false;
    }

    ui_context->item_map[item1] = item2;
    return true;
}

int uiRecoverItem(int olditem) {
    assert(ui_context);
    assert((olditem >= -1) && (olditem < ui_context->last_count));
    if (olditem == -1) return -1;
    return ui_context->item_map[olditem];
}

void uiRemapItem(int olditem, int newitem) {
    assert(ui_context);
    assert((olditem >= 0) && (olditem < ui_context->last_count));
    assert((newitem >= -1) && (newitem < ui_context->count));
    ui_context->item_map[olditem] = newitem;
}

void uiEndLayout() {
    assert(ui_context);
    assert(ui_context->stage == UI_STAGE_LAYOUT); // must run uiBeginLayout() first

    if (ui_context->count) {
        uiComputeSize(0,0);
        uiArrange(0,0);
        uiComputeSize(0,1);
        uiArrange(0,1);

        if (ui_context->last_count) {
            // map old item id to new item id
            uiMapItems(0,0);
        }
    }

    uiValidateStateItems();
    if (ui_context->count) {
        // drawing routines may require this to be set already
        uiUpdateHotItem();
    }

    ui_context->stage = UI_STAGE_POST_LAYOUT;
}

UIrect uiGetRect(int item) {
    UIitem *pitem = uiItemPtr(item);
    UIrect rc = {{{
            pitem->margins[0], pitem->margins[1],
            pitem->size[0], pitem->size[1]
    }}};
    return rc;
}

int uiFirstChild(int item) {
    return uiItemPtr(item)->firstkid;
}

int uiNextSibling(int item) {
    return uiItemPtr(item)->nextitem;
}

void *uiAllocHandle(int item, unsigned int size) {
    assert((size > 0) && (size < UI_MAX_DATASIZE));
    UIitem *pitem = uiItemPtr(item);
    assert(pitem->handle == NULL);
    assert((ui_context->datasize+size) <= ui_context->buffer_capacity);
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

void uiSetEvents(int item, unsigned int flags) {
    UIitem *pitem = uiItemPtr(item);
    pitem->flags &= ~UI_ITEM_EVENT_MASK;
    pitem->flags |= flags & UI_ITEM_EVENT_MASK;
}

unsigned int uiGetEvents(int item) {
    return uiItemPtr(item)->flags & UI_ITEM_EVENT_MASK;
}

void uiSetFlags(int item, unsigned int flags) {
    UIitem *pitem = uiItemPtr(item);
    pitem->flags &= ~UI_USERMASK;
    pitem->flags |= flags & UI_USERMASK;
}

unsigned int uiGetFlags(int item) {
    return uiItemPtr(item)->flags & UI_USERMASK;
}

int uiContains(int item, int x, int y) {
    UIrect rect = uiGetRect(item);
    x -= rect.x;
    y -= rect.y;
    if ((x>=0)
            && (y>=0)
            && (x<rect.w)
            && (y<rect.h)) return 1;
    return 0;
}

int uiFindItem(int item, int x, int y, unsigned int flags, unsigned int mask) {
    UIitem *pitem = uiItemPtr(item);
    if (pitem->flags & UI_ITEM_FROZEN) return -1;
    if (uiContains(item, x, y)) {
        int best_hit = -1;
        int kid = uiFirstChild(item);
        while (kid >= 0) {
            int hit = uiFindItem(kid, x, y, flags, mask);
            if (hit >= 0) {
                best_hit = hit;
            }
            kid = uiNextSibling(kid);
        }
        if (best_hit >= 0) {
            return best_hit;
        }
        if (((mask == UI_ANY) && ((flags == UI_ANY)
            || (pitem->flags & flags)))
            || ((pitem->flags & flags) == mask)) {
            return item;
        }
    }
    return -1;
}

void uiUpdateHotItem() {
    assert(ui_context);
    if (!ui_context->count) return;
    ui_context->hot_item = uiFindItem(0,
            ui_context->cursor.x, ui_context->cursor.y,
            UI_ANY_MOUSE_INPUT, UI_ANY);
}

int uiGetClicks() {
    return ui_context->clicks;
}

void uiProcess(int timestamp) {
    assert(ui_context);

    assert(ui_context->stage != UI_STAGE_LAYOUT); // must run uiBeginLayout(), uiEndLayout() first

    if (ui_context->stage == UI_STAGE_PROCESS) {
        uiUpdateHotItem();
    }
    ui_context->stage = UI_STAGE_PROCESS;

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
        int scroll_item = uiFindItem(0,
                ui_context->cursor.x, ui_context->cursor.y,
                UI_SCROLL, UI_ANY);
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
                ui_context->active_modifier = ui_context->active_button_modifier;
                uiNotifyItem(active_item, UI_BUTTON0_DOWN);
            }            
            ui_context->state = UI_STATE_CAPTURE;            
        } else if (uiGetButton(2) && !uiGetLastButton(2)) {
            hot_item = -1;
            hot = uiFindItem(0, ui_context->cursor.x, ui_context->cursor.y,
                    UI_BUTTON2_DOWN, UI_ANY);
            if (hot >= 0) {
                ui_context->active_modifier = ui_context->active_button_modifier;
                uiNotifyItem(hot, UI_BUTTON2_DOWN);
            }
        } else {
            hot_item = hot;
        }
    } break;
    case UI_STATE_CAPTURE: {
        if (!uiGetButton(0)) {
            if (active_item >= 0) {
                ui_context->active_modifier = ui_context->active_button_modifier;
                uiNotifyItem(active_item, UI_BUTTON0_UP);
                if (active_item == hot) {
                    uiNotifyItem(active_item, UI_BUTTON0_HOT_UP);
                }
            }
            active_item = -1;
            ui_context->state = UI_STATE_IDLE;
        } else {
            if (active_item >= 0) {
                ui_context->active_modifier = ui_context->active_button_modifier;
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
