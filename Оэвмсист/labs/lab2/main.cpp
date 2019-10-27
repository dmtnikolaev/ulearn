#include <stdio.h>

#include <dos.h>
#include <conio.h>

/*
 * Window: x1=10 y1=10 x2=70 y2=20
 * Foreground: rus (eng)
 * Symbol: number
 * Step: T=1.3, S=3
 * Direction: up
 */

const kLinePeriod = 3;
const kTimePeriod = 1300;
const kTargetWindowX1 = 10;
const kTargetWindowY1 = 10;
const kTargetWindowX2 = 70;
const kTargetWindowY2 = 20;

const int kConsoleMaxX = 80;
const int kConsoleMaxY = 25;
const int kConsoleFgFontMax = 15;
const int kConsoleBgFontMax = 15;

class TextWindow {
public:
    TextWindow(int x1, int y1, int x2, int y2);

    void Activate();

    void Print(const char* str);
    void ScrollUp(int lines_count);
    void FillLine();
    void Fill();

    void SetBackground(int color);
    void SetForeground(int color);

    void GoToLastLineBegin();

    int get_fg() {
        return fg_;
    }

    int get_bg() {
        return bg_;
    }

    static const TextWindow kRoot;

private:
    int x1_;
    int x2_;
    int y1_;
    int y2_;
    int bg_;
    int fg_;
};

const TextWindow TextWindow::kRoot =
    TextWindow(1, 1, kConsoleMaxX, kConsoleMaxY);

TextWindow::TextWindow(int x1, int y1, int x2, int y2) {
    x1_ = x1;
    y1_ = y1;
    x2_ = x2;
    y2_ = y2;
    bg_ = BLACK;
    fg_ = WHITE;
    SetForeground(fg_);
}

void TextWindow::Activate() {
    window(x1_, y1_, x2_, y2_);
}

void TextWindow::Print(const char* str) {
    cputs(str);
}

void TextWindow::ScrollUp(int lines_count) {
    union REGS r;
    r.h.al = lines_count;
    r.h.ah = 6;
    r.h.ch = y1_-1;
    r.h.cl = x1_-1;
    r.h.dh = y2_-1;
    r.h.dl = x2_-1;
    r.h.bh = bg_;
    int86(0x10, &r, &r);
}

void TextWindow::FillLine() {
    clreol();
}

void TextWindow::Fill() {
    clrscr();
}

void TextWindow::SetForeground(int color) {
    fg_ = color;
    textcolor(color);
}

void TextWindow::SetBackground(int color) {
    bg_ = color;
    textbackground(color);
}

void TextWindow::GoToLastLineBegin() {
    gotoxy(1, y2_ - y1_ + 1);
}

void ClearScreen() {
    TextWindow root = TextWindow::kRoot;
    root.Activate();
    root.SetForeground(LIGHTGRAY);
    root.SetBackground(BLACK);
    root.Fill();
}

void HideCursor() {
    union REGS i, o;
    i.h.ah = 1;
    i.h.ch = 1 << 5;
    i.h.cl = 13;
    int86(0x10, &i, &o);
}

void ShowCursor() {
    union REGS i, o;
    i.h.ah = 1;
    i.h.ch = 6;
    i.h.cl = 7;
    int86(0x10, &i, &o);
}

const char* ColorToStr(int color) {
    switch(color) {
        case BLACK:
            return "black";
        case BLUE:
            return "blue";
        case GREEN:
            return "green";
        case CYAN:
            return "cyan";
        case RED:
            return "red";
        case MAGENTA:
            return "red";
        case BROWN:
            return "brown";
        case LIGHTGRAY:
            return "light gray";
        case DARKGRAY:
            return "dark gray";
        case LIGHTBLUE:
            return "light blue";
        case LIGHTGREEN:
            return "light green";
        case LIGHTCYAN:
            return "light cyan";
        case LIGHTRED:
            return "light red";
        case LIGHTMAGENTA:
            return "light magenta";
        case YELLOW:
            return "yellow";
        case WHITE:
            return "white";
        default:
            return "<unknown>";
    }
}

const char* MakeColorInfoMessage(int fg_color_ind, int bg_color_ind) {
    static char text[48];

    const char* fg_color_str = ColorToStr(fg_color_ind);
    sprintf(text, "Font: %s, Back: %d", fg_color_str, bg_color_ind);

    return text;
}

void RunLoop() {
    TextWindow win(kTargetWindowX1, kTargetWindowY1,
                   kTargetWindowX2, kTargetWindowY2);
    win.Activate();

    const char* kDefaultMessage = "Lorem ipsum dolor sit ame";
    int cur_line = kLinePeriod-1;

    while (1) {
        for (int fg_color_ind = 0;
                 fg_color_ind < kConsoleFgFontMax;
                 fg_color_ind++) {

            win.SetForeground(fg_color_ind);

            for (int bg_color_ind = kConsoleBgFontMax;
                     bg_color_ind >= 0;
                     bg_color_ind--) {

                win.GoToLastLineBegin();
                win.SetBackground(bg_color_ind);
                win.FillLine();

                if (cur_line == kLinePeriod-1) {
                    win.Print(kDefaultMessage);
                    cur_line = 0;
                }
                else {
                    const char* text =
                        MakeColorInfoMessage(fg_color_ind, bg_color_ind);
                    win.Print(text);
                    cur_line++;
                }

                win.ScrollUp(1);

                if (kbhit()) {
                    return;
                }

                delay(kTimePeriod);
            }
        }
    }
}

int main() {
    ClearScreen();
    HideCursor();
    RunLoop();
    ShowCursor();
    ClearScreen();

    return 0;
}

