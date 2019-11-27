#include <stdio.h>
#include <math.h>
#include <string.h>
#include <float.h>

#include <conio.h>
#include <graphics.h>

/*
 * Вариант 9
 * Функция f(x) = sin^2(x) + cos^3(x)
 * на [pi/2, 5pi]
 */

const int kThickness = THICK_WIDTH;
const char* kGraphDriverPath = "";
const int kFontSize = 8;

struct FloatArray {
    float* vals;
    int len;

    FloatArray(const FloatArray& fa) {
        this->len = fa.len;
        this->vals = new float[this->len];
        memcpy(this->vals, fa.vals, sizeof(float)*this->len);
    }

    FloatArray(int len) {
        this->len = len;
        vals = new float[len];
    }

    static FloatArray Range(float start, float end, float step);

    ~FloatArray() {
        delete vals;
    }
};

FloatArray FloatArray::Range(float start, float end, float step) {
    int count = (end - start) / step;
    FloatArray a = FloatArray(count);
    int k = 0;
    for (float i = start; i - end < FLT_EPSILON; i += step) {
        a.vals[k++] = i;
    }
    return a;
}

struct Size {
    int width;
    int height;

    Size() {
        this->width = 0;
        this->height = 0;
    }

    Size(int w, int h) {
        this->width = w;
        this->height = h;
    }
};

struct AxisLabel {
    char *label;
    int lbl_len;
    float rel_pos;

    AxisLabel(char *lbl, float rel_pos) {
        this->lbl_len = strlen(lbl);
        this->label = new char[this->lbl_len+1];
        strcpy(this->label, lbl);
        this->label[this->lbl_len+1] = '\0';
        this->rel_pos = rel_pos;
    }

    ~AxisLabel() {
        delete this->label;
    }
};

struct Margin {
    int left;
    int top;
    int right;
    int bottom;

    Margin(int l, int t, int r, int b) {
        this->left = l;
        this->top = t;
        this->right = r;
        this->bottom = b;
    }
};

class GraphicsWindow {
public:
    GraphicsWindow(int x_left, int y_top, int x_right, int y_bottom, int clip);

    void Focus();
    GraphicsWindow CreateInner(Margin m);
    void DrawBorders();

    viewporttype vp();
    Size size();
    int left_rel();
    int top_rel();
    int right_rel();
    int bot_rel();

private:
    viewporttype vp_;
    Size sz_;
};

GraphicsWindow::GraphicsWindow(int x_left, int y_top,
        int x_right, int y_bottom, int clip) {
    vp_.left = x_left;
    vp_.top = y_top;
    vp_.right = x_right;
    vp_.bottom = y_bottom;
    vp_.clip = clip;

    sz_ = Size(x_right - x_left, y_bottom - y_top);
}

void GraphicsWindow::Focus() {
    setviewport(vp_.left, vp_.top, vp_.right, vp_.bottom, vp_.clip);
}

GraphicsWindow GraphicsWindow::CreateInner(Margin m) {
    GraphicsWindow w = GraphicsWindow(vp_.left + m.left, vp_.top + m.top,
                                      vp_.right - m.right, vp_.bottom - m.bottom,
                                      vp_.clip);
    return w;
}

void GraphicsWindow::DrawBorders() {
    Focus();
    rectangle(0, 0, sz_.width-kThickness, sz_.height-kThickness);
}

viewporttype GraphicsWindow::vp() {
    return vp_;
}

Size GraphicsWindow::size() {
    return sz_;
}

int GraphicsWindow::left_rel() {
    return 0;
}

int GraphicsWindow::top_rel() {
    return 0;
}

int GraphicsWindow::right_rel() {
    return sz_.width;
}

int GraphicsWindow::bot_rel() {
    return sz_.height;
}

class PlotAxis {
public:
    PlotAxis(GraphicsWindow win);

    int scale();
    void set_scale(int s);

    int o_x;
    int o_y;
    int ox_start_x;
    int ox_start_y;
    int oy_start_x;
    int oy_start_y;
    int ox_end_x;
    int ox_end_y;
    int oy_end_x;
    int oy_end_y;
    int ox_len;
    int oy_len;
};

PlotAxis::PlotAxis(GraphicsWindow win) {
    int axis_pad = 20;
    o_x = 0;
    o_y = (win.bot_rel()-2*kThickness) / 2 + axis_pad;
    ox_start_x = o_x;
    ox_start_y = o_y;
    oy_start_x = 0;
    oy_start_y = win.bot_rel()-kThickness-axis_pad;
    ox_end_x = win.right_rel()-kThickness-axis_pad;
    ox_end_y = ox_start_y;
    oy_end_x = oy_start_x;
    oy_end_y = win.top_rel()+kThickness+axis_pad;

    int last_tick_arrow_pad = 20;
    ox_len = abs(ox_end_x - o_x) - last_tick_arrow_pad;
    oy_len = abs(oy_end_y - o_y) - last_tick_arrow_pad;
}

class PlotableFunction {
public:
    virtual float operator()(float x) = 0;
    virtual float max(FloatArray xs);
};

float PlotableFunction::max(FloatArray xs) {
    float m = FLT_MIN;
    for (int i = 0; i < xs.len; i++) {
        float y = (*this)(xs.vals[i]);
        if (m - y < FLT_EPSILON) {
            m = y;
        }
    }
    return m;
}

class TargetFunction : public PlotableFunction {
public:
    virtual float operator()(float x) {
        return sin(x)*sin(x) + cos(x)*cos(x)*cos(x);
    }
};

void DrawPlot(PlotAxis a, FloatArray xs,
        PlotableFunction* f, int x_scale, int y_scale) {
    int dx_1 = xs.vals[0] * x_scale;
    for (int i = 0; i < xs.len; i++) {
        int dx = xs.vals[i] * x_scale;
        int dy = (*f)(xs.vals[i]) * y_scale;
        putpixel(a.o_x + dx - dx_1, a.o_y - dy, GREEN);
    }
}

void DrawAxisX(PlotAxis a) {
    line(a.ox_start_x, a.ox_start_y, a.ox_end_x, a.ox_end_y);

    line(a.ox_end_x, a.ox_end_y, a.ox_end_x-5, a.ox_end_y-5);
    line(a.ox_end_x, a.ox_end_y, a.ox_end_x-5, a.ox_end_y+5);
}

void DrawAxisXLabels(PlotAxis a, int scale, AxisLabel* lbls, int lbls_count) {
    for (int i = 0; i < lbls_count; i++) {
        int lbl_pos_x = a.o_x + scale*lbls[i].rel_pos;
        line(lbl_pos_x, a.ox_start_y+5, lbl_pos_x, a.ox_start_y-5);

        // Do not intersect the OY
        int pad = i == 0 ? 1 : kFontSize;
        int lbl_x = lbl_pos_x - lbls[i].lbl_len/2*pad;
        outtextxy(lbl_x, a.ox_start_y+10, lbls[i].label);
    }

    outtextxy(a.ox_end_x-10, a.ox_end_y+10, "x");
}

void DrawAxisY(PlotAxis a) {
    line(a.oy_start_x, a.oy_start_y, a.oy_end_x, a.oy_end_y);

    line(a.oy_end_x, a.oy_end_y, a.oy_end_x-5, a.oy_end_y+5);
    line(a.oy_end_x, a.oy_end_y, a.oy_end_x+5, a.oy_end_y+5);
}

void DrawAxisYLabels(PlotAxis a, int scale, AxisLabel* lbls, int lbls_count) {
    for (int i = 0; i < lbls_count; i++) {
        int lbl_pos_y = a.o_y - scale*lbls[i].rel_pos;
        line(a.oy_start_x+5, lbl_pos_y, a.oy_start_x-5, lbl_pos_y);

        int lbl_y = lbl_pos_y - kFontSize/2;
        int lbl_x = a.oy_start_x-5 - lbls[i].lbl_len*kFontSize;
        outtextxy(lbl_x, lbl_y, lbls[i].label);
    }

    outtextxy(a.oy_end_x-kFontSize*2, a.oy_end_y-5*2, "f");
}

void InitializeGraphics() {
    int graph_mode;
    int driver = DETECT;
    initgraph(&driver, &graph_mode, kGraphDriverPath);
    int err_code = graphresult();
    if (err_code != grOk) {
        const char* message = grapherrormsg(err_code);
        printf("Error: %s", message);
    }
}

void FinilizeGraphics() {
    closegraph();
}

int main() {
    // Prepare.
    //
    InitializeGraphics();

    const int max_x = getmaxx(); // 640
    const int max_y = getmaxy(); // 480
    GraphicsWindow root_w = GraphicsWindow(0, 0, max_x, max_y, 0);
    GraphicsWindow plot_w = root_w.CreateInner(Margin(50, 30, 50, 80));
    GraphicsWindow draw_area_w = plot_w.CreateInner(Margin(40, 0, 0, 40));
    GraphicsWindow info_text_w =
        root_w.CreateInner(Margin(50, 30+plot_w.size().height+30, 50, 30));


    PlotAxis ax = PlotAxis(draw_area_w);

    const int x_scale = ax.ox_len / (5*M_PI - 0);
    const int y_scale = x_scale * 3;

    const int x_lbls_count = 6;
    AxisLabel x_lbls[x_lbls_count] = {
        AxisLabel(" pi/2", 0),
        AxisLabel("3pi/2", 3*M_PI/2 - M_PI/2),
        AxisLabel("5pi/2", 5*M_PI/2 - M_PI/2),
        AxisLabel("7pi/2", 7*M_PI/2 - M_PI/2),
        AxisLabel("9pi/2", 9*M_PI/2 - M_PI/2),
        AxisLabel("5pi", 5*M_PI - M_PI/2),
    };
    const int y_lbls_count = 5;
    AxisLabel y_lbls[y_lbls_count] = {
        AxisLabel("-1.0", -1.0),
        AxisLabel("-0.5", -0.5),
        AxisLabel("0", 0),
        AxisLabel("0.5", 0.5),
        AxisLabel("1.0", 1.0),
    };

    FloatArray x = FloatArray::Range(M_PI/2, 5*M_PI+0.001, (M_PI/2)/x_scale);
    PlotableFunction* f = new TargetFunction();

    // Draw everything.
    //
    setlinestyle(SOLID_LINE, 0, kThickness);
    plot_w.DrawBorders();
    draw_area_w.Focus();

    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    DrawAxisXLabels(ax, x_scale, x_lbls, x_lbls_count);
    DrawAxisYLabels(ax, y_scale, y_lbls, y_lbls_count);
    DrawPlot(ax, x, f, x_scale, y_scale);

    setlinestyle(SOLID_LINE, 0, kThickness);
    DrawAxisX(ax);
    DrawAxisY(ax);

    info_text_w.Focus();
    char text[20];
    sprintf(text, "Max value: %.1f", (*f).max(x));
    outtext(text);

    getch();

    delete f;
    FinilizeGraphics();

    return 0;
}

