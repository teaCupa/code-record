//
// Created by teagm on 2023/4/14.
//

#ifndef CPP_PRIMER_SCREEN_H
#define CPP_PRIMER_SCREEN_H

#include <iostream>
#include <string>

class Screen {
public:
    using pos = std::string::size_type;

    Screen() = default;
    Screen(pos w,pos h) : width(w),height(h),contents(w*h,' ') {}
    Screen(pos w,pos h,char c) : width(w),height(h),contents(w*h,c) {}

    char get() const { return contents[cursor]; }
    char get(pos r,pos c) const { return contents[r*width+c]; }
    inline Screen& set(char c);
    inline Screen& set(pos r,pos c,char ch);
    inline Screen& move(pos r,pos c);

    const Screen& display(std::ostream& os) const { os<<contents; return *this; }
    Screen& display(std::ostream& os) { os<<contents; return *this; }

private:
    pos cursor=0;
    pos width=0,height=0;
    std::string contents;
};

inline Screen& Screen::set(char c) {
    contents[cursor] = c;
    return *this;
}

inline Screen& Screen::set(Screen::pos r, Screen::pos c, char ch) {
    contents[r*width+c] = ch;
    return *this;
}

inline Screen& Screen::move(pos r, pos c) {
    cursor = r*width + c;
    return *this;
}


#endif //CPP_PRIMER_SCREEN_H
