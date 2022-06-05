#ifndef LISTENKEYBOARD_H
#define LISTENKEYBOARD_H
#include <list>
#include <windows.h>
#define KEYDOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000)?1:0)
#define KEYUP(VK_NONAME) (GetKeyState(VK_NONAME)>=0)
#define ISPRESS(VK_NONAME) (LOBYTE(KeyState[VK_NONAME])?1:0)
using namespace std;
class ListenKeyboard
{
public:
    ListenKeyboard();
    ~ListenKeyboard()=default;
    list<int> UpdateDownKeys();
    const int SimpleControlKeys[33]={
        91,  //Win
        17,  //Ctrl
        18,  //Alt
        16,  //Shift
        9,  //Tab
        27,  //Esc
        46,  //Del
        45,  //Ins
        36,  //Home
        35,  //End
        33,  //PaU
        34,  //PaD
        112,113,114,115,116,117,118,119,120,121,122,123, //F1-F12
        37,  //Left
        38,  //Up
        39,  //Right
        40,  //Down
        1,  // lbutton
        2,  // rbutton
        4,  // mbutton
        20,  //CapsLock
        144  //NumLock
    };
    const int SimpleTextKeys[19]={
        192,  // ` (~)
        189,  // - (_)
        187,  // = (+)
        220,  // \ (|)
        219,  // [ ({)
        221,  // ] (})
        186,  // ; (:)
        222,  // ' (")
        188,  // , (<)
        190,  // . (>)
        191,  // / (?)
        111,  // \ ...
        106,  // *
        109,  // -
        107,  // +
        110,  // .
        8,  // <-backspace

        13,  //Enter
        32  //Space
    };
private:
    list<int> keys;
    int CapsLock,NumLock,Shift;
    bool prekey[256],sk;
    BYTE KeyState[256];
    void CheckSimpleKeys();
    void CheckSimpleTextKeys();

};

#endif // LISTENKEYBOARD_H
