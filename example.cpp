//
// based on NanoVG's example code by Mikko Mononen

#include <stdio.h>
#ifdef NANOVG_GLEW
#	include <GL/glew.h>
#endif
#ifdef __APPLE__
#	define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>
#include "nanovg.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg_gl.h"

#define BLENDISH_IMPLEMENTATION
#include "blendish.h"

#include <assert.h>

////////////////////////////////////////////////////////////////////////////////

#define UI_IMPLEMENTATION
#ifndef _UI_H_
#define _UI_H_

#define UI_COLD   0x0000
#define UI_HOT    0x0001
#define UI_ACTIVE 0x0002
    
// containers
#define UI_ROOT   0x0100
#define UI_COLUMN 0x0101
#define UI_ROW    0x0102

// controls
#define UI_BUTTON 0x0203

#define UI_MAX_ITEMS 4096
#define UI_MAX_BUFFERSIZE 1048576
#define UI_MAX_DEPTH 64

typedef struct UIcontext UIcontext;
typedef unsigned long long UIhandle;

typedef struct UIrect {
    int x, y, w, h;
} UIrect;

UIcontext *uiCreateContext();
void uiMakeCurrent(UIcontext *ctx);
void uiDestroyContext(UIcontext *ctx);

void uiSetButton(int button, int enabled);
int uiGetButton(int button);

void uiSetCursor(int x, int y);
void uiGetCursor(int *x, int *y);

void uiClear();

int uiItem(int parent, UIhandle handle, int kind, 
    int w, int h, void *data, int size);
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

int uiAllocItem(int parent, UIhandle handle, int kind, void *data, int size) {
    assert(ui_context && (ui_context->count < UI_MAX_ITEMS));
    assert((size >= 0) && ((ui_context->datasize+size) <= UI_MAX_BUFFERSIZE));
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
    if (data && size) {
        item->data = ui_context->datasize;
        ui_context->datasize += size;
        memcpy(ui_context->data + item->data, data, size);
    }
    return idx;
}

int uiItem( 
        int parent, UIhandle handle, int kind, int w, int h, void *data, int size) {
    int idx = uiAllocItem(parent, handle, kind, data, size);
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
    int idx = uiItem(parent, 0, UI_COLUMN, 0, 0, NULL, 0);
    uiSetSpacing(idx, spacing);
    return idx;
}

int uiRow(int parent, int spacing) {
    int idx = uiItem(parent, 0, UI_ROW, 0, 0, NULL, 0);
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
            uiLayoutChildren(item, rect.x, rect.y);

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
                if (pitem->rect.h > rect.h)
                    rect.h = pitem->rect.h;
                if (!pitem->rect.w)
                    numdynkids++;
                else
                    w += pitem->rect.w;
                kid = uiNextSibling(kid);
            }
            uiItemPtr(item)->rect.h = rect.h;
            
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

////////////////////////////////////////////////////////////////////////////////

typedef struct UIData {
    int iconid;
    const char *label;
} UIData;

////////////////////////////////////////////////////////////////////////////////

void init(NVGcontext *vg) {
    bndSetFont(nvgCreateFont(vg, "system", "../droidsans.ttf"));
    bndSetIconImage(nvgCreateImage(vg, "../blender_icons16.png"));
}

int cornerFlags(int item) {
    int parent = uiParent(item);
    int spacing = uiGetSpacing(parent);
    if (spacing >= 0) return BND_CORNER_NONE;
    int numkids = uiGetChildCount(parent);
    int numid = uiGetChildId(item);
    if (numkids == 0) return BND_CORNER_NONE;
    switch(uiGetKind(parent)) {
        case UI_COLUMN: {
            if (!numid) return BND_CORNER_DOWN;
            else if (numid == numkids-1) return BND_CORNER_TOP;
            else return BND_CORNER_ALL;
        } break;
        case UI_ROW: {
            if (!numid) return BND_CORNER_RIGHT;
            else if (numid == numkids-1) return BND_CORNER_LEFT;
            else return BND_CORNER_ALL;
        } break;
        default: break;
    }
    return BND_CORNER_NONE;
}

void drawUI(NVGcontext *vg, int item, int x, int y) {
    UIData *data = (UIData *)uiGetData(item);
    UIrect rect = uiGetRect(item);
    rect.x += x;
    rect.y += y;
    
    switch(uiGetKind(item)) {
        case UI_BUTTON: {
            assert(data);
            bndToolButton(vg,rect.x,rect.y,rect.w,rect.h,
                cornerFlags(item),(BNDwidgetState)uiGetState(item),
                data->iconid,data->label);
        } break;
        default: break;
    }
    
    int kid = uiFirstChild(item);
    while (kid > 0) {
        drawUI(vg, kid, rect.x, rect.y);
        kid = uiNextSibling(kid);
    }
}

void draw(NVGcontext *vg, float w, float h) {
    bndBackground(vg, 0, 0, w, h);
    
    int x = 10;
    int y = 10;
    
    bndToolButton(vg,x,y,120,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_DEFAULT,
        BND_ICONID(6,3),"Default");
    y += 25;
    bndToolButton(vg,x,y,120,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_HOVER,
        BND_ICONID(6,3),"Hovered");
    y += 25;   
    bndToolButton(vg,x,y,120,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_ACTIVE,
        BND_ICONID(6,3),"Active");
    
    y += 40;
    bndRadioButton(vg,x,y,80,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_DEFAULT,
        -1,"Default");
    y += 25;
    bndRadioButton(vg,x,y,80,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_HOVER,
        -1,"Hovered");
    y += 25;
    bndRadioButton(vg,x,y,80,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_ACTIVE,
        -1,"Active");

    y += 25;
    bndLabel(vg,x,y,120,BND_WIDGET_HEIGHT,-1,"Label:");
    y += BND_WIDGET_HEIGHT;
    bndChoiceButton(vg,x,y,80,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_DEFAULT,
        -1, "Default");
    y += 25;
    bndChoiceButton(vg,x,y,80,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_HOVER,
        -1, "Hovered");
    y += 25;
    bndChoiceButton(vg,x,y,80,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_ACTIVE,
        -1, "Active");
        
    y += 25;
    int ry = y;
    int rx = x;
    
    y = 10;
    x += 130;
    bndOptionButton(vg,x,y,120,BND_WIDGET_HEIGHT,BND_DEFAULT,"Default");
    y += 25;
    bndOptionButton(vg,x,y,120,BND_WIDGET_HEIGHT,BND_HOVER,"Hovered");
    y += 25;
    bndOptionButton(vg,x,y,120,BND_WIDGET_HEIGHT,BND_ACTIVE,"Active");

    y += 40;
    bndNumberField(vg,x,y,120,BND_WIDGET_HEIGHT,BND_CORNER_DOWN,BND_DEFAULT,
        "Top","100");
    y += BND_WIDGET_HEIGHT-2;
    bndNumberField(vg,x,y,120,BND_WIDGET_HEIGHT,BND_CORNER_ALL,BND_DEFAULT,
        "Center","100");
    y += BND_WIDGET_HEIGHT-2;
    bndNumberField(vg,x,y,120,BND_WIDGET_HEIGHT,BND_CORNER_TOP,BND_DEFAULT,
        "Bottom","100");

    int mx = x-30;
    int my = y-12;
    int mw = 120;
    bndMenuBackground(vg,mx,my,mw,120,BND_CORNER_TOP);
    bndMenuLabel(vg,mx,my,mw,BND_WIDGET_HEIGHT,-1,"Menu Title");
    my += BND_WIDGET_HEIGHT-2;
    bndMenuItem(vg,mx,my,mw,BND_WIDGET_HEIGHT,BND_DEFAULT,
        BND_ICONID(17,3),"Default");
    my += BND_WIDGET_HEIGHT-2;
    bndMenuItem(vg,mx,my,mw,BND_WIDGET_HEIGHT,BND_HOVER,
        BND_ICONID(18,3),"Hovered");
    my += BND_WIDGET_HEIGHT-2;
    bndMenuItem(vg,mx,my,mw,BND_WIDGET_HEIGHT,BND_ACTIVE,
        BND_ICONID(19,3),"Active");
    
    y = 10;
    x += 130;
    int ox = x;
    bndNumberField(vg,x,y,120,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_DEFAULT,
        "Default","100");
    y += 25;
    bndNumberField(vg,x,y,120,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_HOVER,
        "Hovered","100");
    y += 25;
    bndNumberField(vg,x,y,120,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_ACTIVE,
        "Active","100");
    
    y += 40;
    bndRadioButton(vg,x,y,60,BND_WIDGET_HEIGHT,BND_CORNER_RIGHT,BND_DEFAULT,
        -1,"One");
    x += 60-1;
    bndRadioButton(vg,x,y,60,BND_WIDGET_HEIGHT,BND_CORNER_ALL,BND_DEFAULT,
        -1,"Two");
    x += 60-1;
    bndRadioButton(vg,x,y,60,BND_WIDGET_HEIGHT,BND_CORNER_ALL,BND_DEFAULT,
        -1,"Three");
    x += 60-1;
    bndRadioButton(vg,x,y,60,BND_WIDGET_HEIGHT,BND_CORNER_LEFT,BND_ACTIVE,
        -1,"Butts");
    
    x = ox;
    y += 40;
    float progress_value = fmodf(glfwGetTime()/10.0,1.0);
    char progress_label[32];
    sprintf(progress_label, "%d%%", int(progress_value*100+0.5f));
    bndSlider(vg,x,y,240,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_DEFAULT,
        progress_value,"Default",progress_label);
    y += 25;
    bndSlider(vg,x,y,240,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_HOVER,
        progress_value,"Hovered",progress_label);
    y += 25;
    bndSlider(vg,x,y,240,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_ACTIVE,
        progress_value,"Active",progress_label);

    int rw = x+240-rx;
    float s_offset = sinf(glfwGetTime()/2.0)*0.5+0.5;
    float s_size = cosf(glfwGetTime()/3.11)*0.5+0.5;
    
    bndScrollBar(vg,rx,ry,rw,BND_SCROLLBAR_HEIGHT,BND_DEFAULT,s_offset,s_size);
    ry += 20;
    bndScrollBar(vg,rx,ry,rw,BND_SCROLLBAR_HEIGHT,BND_HOVER,s_offset,s_size);
    ry += 20;
    bndScrollBar(vg,rx,ry,rw,BND_SCROLLBAR_HEIGHT,BND_ACTIVE,s_offset,s_size);
    
    const char edit_text[] = "The quick brown fox";
    int textlen = strlen(edit_text)+1;
    int t = int(glfwGetTime()*2);
    int idx1 = (t/textlen)%textlen;
    int idx2 = idx1 + (t%(textlen-idx1));
    
    ry += 25;
    bndTextField(vg,rx,ry,240,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_DEFAULT,
        -1, edit_text, idx1, idx2);
    ry += 25;
    bndTextField(vg,rx,ry,240,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_HOVER,
        -1, edit_text, idx1, idx2);
    ry += 25;
    bndTextField(vg,rx,ry,240,BND_WIDGET_HEIGHT,BND_CORNER_NONE,BND_ACTIVE,
        -1, edit_text, idx1, idx2);
    
    rx += rw + 20;
    ry = 10;
    bndScrollBar(vg,rx,ry,BND_SCROLLBAR_WIDTH,240,BND_DEFAULT,s_offset,s_size);
    rx += 20;
    bndScrollBar(vg,rx,ry,BND_SCROLLBAR_WIDTH,240,BND_HOVER,s_offset,s_size);
    rx += 20;
    bndScrollBar(vg,rx,ry,BND_SCROLLBAR_WIDTH,240,BND_ACTIVE,s_offset,s_size);
    
    x = ox;
    y += 40;
    bndToolButton(vg,x,y,BND_TOOL_WIDTH,BND_WIDGET_HEIGHT,BND_CORNER_RIGHT,
        BND_DEFAULT,BND_ICONID(0,10),NULL);
    x += BND_TOOL_WIDTH-1;
    bndToolButton(vg,x,y,BND_TOOL_WIDTH,BND_WIDGET_HEIGHT,BND_CORNER_ALL,
        BND_DEFAULT,BND_ICONID(1,10),NULL);
    x += BND_TOOL_WIDTH-1;
    bndToolButton(vg,x,y,BND_TOOL_WIDTH,BND_WIDGET_HEIGHT,BND_CORNER_ALL,
        BND_DEFAULT,BND_ICONID(2,10),NULL);
    x += BND_TOOL_WIDTH-1;
    bndToolButton(vg,x,y,BND_TOOL_WIDTH,BND_WIDGET_HEIGHT,BND_CORNER_ALL,
        BND_DEFAULT,BND_ICONID(3,10),NULL);
    x += BND_TOOL_WIDTH-1;
    bndToolButton(vg,x,y,BND_TOOL_WIDTH,BND_WIDGET_HEIGHT,BND_CORNER_ALL,
        BND_DEFAULT,BND_ICONID(4,10),NULL);
    x += BND_TOOL_WIDTH-1;
    bndToolButton(vg,x,y,BND_TOOL_WIDTH,BND_WIDGET_HEIGHT,BND_CORNER_LEFT,
        BND_DEFAULT,BND_ICONID(5,10),NULL);
    x += BND_TOOL_WIDTH-1;
    x += 5;
    bndRadioButton(vg,x,y,BND_TOOL_WIDTH,BND_WIDGET_HEIGHT,BND_CORNER_RIGHT,
        BND_DEFAULT,BND_ICONID(0,11),NULL);
    x += BND_TOOL_WIDTH-1;
    bndRadioButton(vg,x,y,BND_TOOL_WIDTH,BND_WIDGET_HEIGHT,BND_CORNER_ALL,
        BND_DEFAULT,BND_ICONID(1,11),NULL);
    x += BND_TOOL_WIDTH-1;
    bndRadioButton(vg,x,y,BND_TOOL_WIDTH,BND_WIDGET_HEIGHT,BND_CORNER_ALL,
        BND_DEFAULT,BND_ICONID(2,11),NULL);
    x += BND_TOOL_WIDTH-1;
    bndRadioButton(vg,x,y,BND_TOOL_WIDTH,BND_WIDGET_HEIGHT,BND_CORNER_ALL,
        BND_DEFAULT,BND_ICONID(3,11),NULL);
    x += BND_TOOL_WIDTH-1;
    bndRadioButton(vg,x,y,BND_TOOL_WIDTH,BND_WIDGET_HEIGHT,BND_CORNER_ALL,
        BND_ACTIVE,BND_ICONID(4,11),NULL);
    x += BND_TOOL_WIDTH-1;
    bndRadioButton(vg,x,y,BND_TOOL_WIDTH,BND_WIDGET_HEIGHT,BND_CORNER_LEFT,
        BND_DEFAULT,BND_ICONID(5,11),NULL);
    
    uiClear();
    
    uiSetRect(0,600,10,250,400);
    
    int col = uiColumn(0,1);
    UIData data = { BND_ICONID(6,3), "Item 1" };
    uiItem(col, 1, UI_BUTTON, 0, BND_WIDGET_HEIGHT, &data, sizeof(data));
    data.label = "Item 2";
    uiItem(col, 2, UI_BUTTON, 0, BND_WIDGET_HEIGHT, &data, sizeof(data));
    { // nested row    
        int row = uiRow(col,-1);
        data.label = "Item 3.0";
        uiItem(row, 3, UI_BUTTON, 0, BND_WIDGET_HEIGHT, &data, sizeof(data));
        data.label = NULL;
        data.iconid = BND_ICONID(0,10);
        uiItem(row, 4, UI_BUTTON, BND_TOOL_WIDTH, BND_WIDGET_HEIGHT, &data, sizeof(data));
        data.label = NULL;
        data.iconid = BND_ICONID(1,10);
        uiItem(row, 5, UI_BUTTON, BND_TOOL_WIDTH, BND_WIDGET_HEIGHT, &data, sizeof(data));
        data.iconid = BND_ICONID(6,3);
        data.label = "Item 3.3";
        uiItem(row, 6, UI_BUTTON, 0, BND_WIDGET_HEIGHT, &data, sizeof(data));
    }
    
    { // nested column
        int col2 = uiColumn(col,-2);
        data.label = "Item 4.0";
        uiItem(col2, 7, UI_BUTTON, 0, BND_WIDGET_HEIGHT, &data, sizeof(data));
        data.label = "Item 4.1";
        uiItem(col2, 8, UI_BUTTON, 0, BND_WIDGET_HEIGHT, &data, sizeof(data));        
    }
    
    data.label = "Item 5";
    uiItem(col, 9, UI_BUTTON, 0, BND_WIDGET_HEIGHT, &data, sizeof(data));
    
    uiLayout();
    
    
    drawUI(vg, 0, 0, 0);
}

////////////////////////////////////////////////////////////////////////////////

void errorcb(int error, const char* desc)
{
	printf("GLFW error %d: %s\n", error, desc);
}

static void mousebutton(GLFWwindow *window, int button, int action, int mods) {
	NVG_NOTUSED(window);
	NVG_NOTUSED(mods);
    uiSetButton(button, (action==GLFW_PRESS)?1:0);
}

static void cursorpos(GLFWwindow *window, double x, double y) {
	NVG_NOTUSED(window);
    uiSetCursor((int)x,(int)y);
}

static void key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	NVG_NOTUSED(scancode);
	NVG_NOTUSED(mods);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	GLFWwindow* window;
	struct NVGcontext* vg = NULL;
    UIcontext *uictx;
    
    uictx = uiCreateContext();
    uiMakeCurrent(uictx);

	if (!glfwInit()) {
		printf("Failed to init GLFW.");
		return -1;
	}

	glfwSetErrorCallback(errorcb);
#ifndef _WIN32 // don't require this on win32, and works with more cards
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

	window = glfwCreateWindow(1000, 600, "Blendish Demo", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, key);
    glfwSetCursorPosCallback(window, cursorpos);
    glfwSetMouseButtonCallback(window, mousebutton);

	glfwMakeContextCurrent(window);
#ifdef NANOVG_GLEW
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK) {
		printf("Could not init glew.\n");
		return -1;
	}
	// GLEW generates GL error because it calls glGetString(GL_EXTENSIONS), we'll consume it here.
	glGetError();
#endif

	vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
	if (vg == NULL) {
		printf("Could not init nanovg.\n");
		return -1;
	}
	
	init(vg);

	glfwSwapInterval(0);

	glfwSetTime(0);

	while (!glfwWindowShouldClose(window))
	{
		double mx, my;
		int winWidth, winHeight;
		int fbWidth, fbHeight;
		float pxRatio;

		glfwGetCursorPos(window, &mx, &my);
		glfwGetWindowSize(window, &winWidth, &winHeight);
		glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
		// Calculate pixel ration for hi-dpi devices.
		pxRatio = (float)fbWidth / (float)winWidth;

		// Update and render
		glViewport(0, 0, fbWidth, fbHeight);
		glClearColor(0,0,0,1);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

		nvgBeginFrame(vg, winWidth, winHeight, pxRatio);

        draw(vg, winWidth, winHeight);

		nvgEndFrame(vg);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

    uiDestroyContext(uictx);

	nvgDeleteGL3(vg);

	glfwTerminate();
	return 0;
}
