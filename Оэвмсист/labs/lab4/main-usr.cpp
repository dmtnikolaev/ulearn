#include <stdio.h>

#include <dos.h>
#include <conio.h>

/*
 * Window: x1=10 y1=10 x2=70 y2=20
 * Movement: continues
 * Buttons: right, left
 * Interruption: 21h
 */

const int kTimePeriod     = 100;

const int kTargetWindowX1 = 10;
const int kTargetWindowY1 = 10;
const int kTargetWindowX2 = 70;
const int kTargetWindowY2 = 20;

const int kConsoleMaxX    = 80;
const int kConsoleMaxY    = 25;

const int kLeftCode       = 75;
const int kRightCode      = 77;

int kbhit_() {
    union REGS i, o;
    i.h.ah = 0xb;
    int86(0x21, &i, &o);
    return o.h.al;
}

void putch_(char c) {
    union REGS i, o;
    i.h.ah = 0x2;
    i.h.dl = c;
    int86(0x21, &i, &o);
}

char getch_() {
    union REGS i, o;
    i.h.ah = 0x7;
    int86(0x21, &i, &o);
    return o.h.al;
}

class TextWindow {
public:
    TextWindow();
    TextWindow(int x1, int y1, int x2, int y2);

    void Focus();

    void Fill();

    void SetBackground(int color);
    void SetForeground(int color);

    int get_fg() {
        return fg_;
    }

    int get_bg() {
        return bg_;
    }

    int width() {
        return x2_ - x1_ + 1;
    }

    int height() {
        return y2_ - y1_ + 1;
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

TextWindow::TextWindow() {
    x1_ = 0;
    y1_ = 0;
    x2_ = 0;
    y2_ = 0;
    fg_ = WHITE;
    bg_ = BLACK;
}

TextWindow::TextWindow(int x1, int y1, int x2, int y2) {
    x1_ = x1;
    y1_ = y1;
    x2_ = x2;
    y2_ = y2;
    fg_ = WHITE;
    bg_ = BLACK;
}

void TextWindow::Focus() {
    window(x1_, y1_, x2_, y2_);
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

enum MoveDirection {
    MOVE_NONE,
    MOVE_LEFT,
    MOVE_RIGHT,
};

class CharacterController {
public:
    CharacterController(TextWindow w, char sym, int x, int y);

    void Show();
    int TryMove(int dx, int dy);
    int TryStep(MoveDirection d);

private:
    TextWindow w_;
    char sym_;
    int x_;
    int y_;
};

CharacterController::CharacterController(TextWindow w, char sym, int x, int y) {
    sym_ = sym;
    x_ = x;
    y_ = y;
    w_ = w;
}

void CharacterController::Show() {
    gotoxy(x_, y_);
    putch_(sym_);
}

int CharacterController::TryMove(int dx, int dy) {
    if (dx == 0 && dy == 0) {
        return 1;
    }

    int nx = x_ + dx;
    int ny = y_ + dy;

    if (!(nx > 0 && nx <= w_.width() &&
          ny > 0 && ny <= w_.height())) {
        return 0;
    }

    delline();
    x_ = nx;
    y_ = ny;
    gotoxy(x_, y_);
    putch_(sym_);
    return 1;
}

int CharacterController::TryStep(MoveDirection d) {
    int dx;
    switch (d) {
        case MOVE_NONE:
            dx = 0;
            break;

        case MOVE_RIGHT:
            dx = 1;
            break;

        case MOVE_LEFT:
            dx = -1;
            break;
    }

    return TryMove(dx, 0);
}

void ClearScreen() {
    TextWindow root = TextWindow::kRoot;
    root.Focus();
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

enum Key {
    KEY_NONE,
    KEY_OTHER,
    KEY_ARROW_LEFT,
    KEY_ARROW_RIGHT,
};

Key ReadPressedKey() {
    if (!kbhit_()) {
        return KEY_NONE;
    }

    char c = getch_();
    if (c != 0) {
        return KEY_OTHER;
    }

    if (!kbhit_()) {
        return KEY_OTHER;
    }

    c = getch_();
    switch (c) {
        case kLeftCode:
            return KEY_ARROW_LEFT;
        case kRightCode:
            return KEY_ARROW_RIGHT;
        default:
            return KEY_OTHER;
    }

    // Unreachable.
}

MoveDirection InvertDirection(MoveDirection d) {
    switch (d) {
        case MOVE_NONE:
            return MOVE_NONE;
        case MOVE_RIGHT:
            return MOVE_LEFT;
        case MOVE_LEFT:
            return MOVE_RIGHT;
    }
    // Unreachable.
    return MOVE_NONE;
}

void RunLoop() {
    TextWindow w = TextWindow(kTargetWindowX1, kTargetWindowY1,
                              kTargetWindowX2, kTargetWindowY2);

    w.Focus();
    w.SetBackground(WHITE);
    w.SetForeground(BLUE);
    w.Fill();

    CharacterController cc = CharacterController(w, '*', w.width()/2,
                                                 w.height()/2);
    cc.Show();

    MoveDirection cur_dir = MOVE_RIGHT;
    while (1) {
        Key k = ReadPressedKey();
        switch (k) {
            case KEY_NONE:
                break;
            case KEY_ARROW_LEFT:
                cur_dir = MOVE_LEFT;
                break;
            case KEY_ARROW_RIGHT:
                cur_dir = MOVE_RIGHT;
                break;
            case KEY_OTHER:
                return;
        }

        int res = cc.TryStep(cur_dir);
        if (!res) {
            cur_dir = InvertDirection(cur_dir);
        }

        delay(kTimePeriod);
    }
}

int main() {
    ClearScreen();
    HideCursor();

    RunLoop();

    //getch_();
    ShowCursor();
    ClearScreen();
    return 0;
}

