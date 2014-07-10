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

#define UI_IMPLEMENTATION
#include "oui.h"

////////////////////////////////////////////////////////////////////////////////

typedef enum {
    // default
    ST_DEFAULT = 0,
    // radio button
    ST_RADIO = 1,
} SubType;

typedef struct {
    int size;
    int subtype;
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
    const UIData *data = (const UIData *)uiGetData(item);
    UIrect rect = uiGetRect(item);
    rect.x += x;
    rect.y += y;
    
    switch(uiGetKind(item)) {
        case UI_LABEL: {
            assert(data);
            bndLabel(vg,rect.x,rect.y,rect.w,rect.h,
                data->iconid,data->label);
        } break;
        case UI_BUTTON: {
            assert(data);
            switch(data->subtype) {
                default: {
                    bndToolButton(vg,rect.x,rect.y,rect.w,rect.h,
                        cornerFlags(item),(BNDwidgetState)uiGetState(item),
                        data->iconid,data->label);
                } break;
                case ST_RADIO:{
                    BNDwidgetState state = (BNDwidgetState)uiGetState(item);
                    bndRadioButton(vg,rect.x,rect.y,rect.w,rect.h,
                        cornerFlags(item),state,
                        data->iconid,data->label);
                } break;
            }
        } break;
        default: break;
    }
    
    int kid = uiFirstChild(item);
    while (kid > 0) {
        drawUI(vg, kid, rect.x, rect.y);
        kid = uiNextSibling(kid);
    }
}

int label(int parent, int iconid, const char *label) {
    UIData data = { sizeof(UIData), ST_DEFAULT, iconid, label };
    return uiItem(parent, 0, UI_LABEL, 0, BND_WIDGET_HEIGHT, &data);
}

int button(int parent, UIhandle handle, int iconid, const char *label, 
    UIhandler handler) {
    UIData data = { sizeof(UIData), ST_DEFAULT, iconid, label };
    int item = uiItem(parent, handle, UI_BUTTON, 0, BND_WIDGET_HEIGHT, &data);
    uiSetHandler(item, handler);
    return item;
}

static UIhandle radio_handle = 0;

void radiohandler(int item) {
    radio_handle = uiGetHandle(item);
    uiSetActive(item, 1);
}

int radio(int parent, UIhandle handle, int iconid, const char *label) {
    UIData data = { sizeof(UIData), ST_RADIO, iconid, label };
    int w = (label)?0:BND_TOOL_WIDTH;
    int item = uiItem(parent, handle, UI_BUTTON, w, BND_WIDGET_HEIGHT, &data);
    uiSetHandler(item, radiohandler);
    uiSetEarlyHandler(item, true);
    if (radio_handle == handle)
        uiSetActive(item, 1);    
    return item;
}

void demohandler(int item) {
    const UIData *data = (const UIData *)uiGetData(item);
    printf("clicked: %lld %s\n", uiGetHandle(item), data->label);
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
    
    // some OUI stuff
    
    uiClear();
    
    uiSetRect(0,600,10,250,400);

    int col = uiColumn(0,1);
    button(col, 1, BND_ICONID(6,3), "Item 1", demohandler);
    button(col, 2, BND_ICONID(6,3), "Item 2", demohandler);
    {
        int row = uiRow(col,-1);
        radio(row, 3, BND_ICONID(6,3), "Item 3.0");
        radio(row, 4, BND_ICONID(0,10), NULL);
        radio(row, 5, BND_ICONID(1,10), NULL);
        radio(row, 6, BND_ICONID(6,3), "Item 3.3");
    }
    
    {
        int row = uiRow(col,8);
        int coll = uiColumn(row,-2);
        label(coll, -1, "Items 4.0:");
        coll = uiColumn(coll,-2);
        button(coll, 7, BND_ICONID(6,3), "Item 4.0.0", demohandler);
        button(coll, 8, BND_ICONID(6,3), "Item 4.0.1", demohandler);
        int colr = uiColumn(row,-2);
        label(colr, -1, "Items 4.1:");
        colr = uiColumn(colr,-2);
        button(colr, 9, BND_ICONID(6,3), "Item 4.1.0", demohandler);
        button(colr,10, BND_ICONID(6,3), "Item 4.1.1", demohandler);
    }
    
    button(col, 11, BND_ICONID(6,3), "Item 5", NULL);
    
    uiProcess();
    
    
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
