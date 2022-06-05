#include "listenkeyboard.h"

ListenKeyboard::ListenKeyboard()
{
    keys.clear();
    for(int i=0;i<256;i++){
        prekey[i]=0;
    }
    sk=0;
}

void ListenKeyboard::CheckSimpleKeys(){
    for(int i=0;i<33;++i){
        if(KEYDOWN(SimpleControlKeys[i])){
            keys.push_back(SimpleControlKeys[i]);
            if(SimpleControlKeys[i]!=16) sk=1;
        }
    }
}

void ListenKeyboard::CheckSimpleTextKeys(){
    for(int i=0;i<19;++i){
        if((sk||!prekey[SimpleTextKeys[i]]) && KEYDOWN(SimpleTextKeys[i])){
            keys.push_back(SimpleTextKeys[i]);
            prekey[SimpleTextKeys[i]]=1;
        }
        if(KEYUP(SimpleTextKeys[i])){
            prekey[SimpleTextKeys[i]]=0;
        }
    }
}

list<int> ListenKeyboard::UpdateDownKeys(){
    sk=0;
    keys.clear();
    if(GetKeyboardState(KeyState)){
        CapsLock=ISPRESS(20);
        NumLock=ISPRESS(144);
    }
    Shift=KEYDOWN(16);
    /*if(KEYDOWN(20)&&!prekey[20]){
        CapsLock=1-CapsLock;
        keys.push_back(20);
        prekey[20]=1;
    }
    if(KEYUP(20)) prekey[20]=0;
    if(KEYDOWN(144)&&!prekey[144]){
        NumLock=1-NumLock;
        keys.push_back(144);
        prekey[144]=1;
    }*/
    if(KEYUP(144)) prekey[144]=0;
    CheckSimpleKeys();
    for(int cha=0;cha<26;++cha){
        if(KEYDOWN('A'+cha)&&(!prekey['A'+cha]||sk)){
            keys.push_back('A'+(1-CapsLock^Shift)*200+cha);
            prekey['A'+cha]=1;
        }
        if(KEYUP('A'+cha)) prekey['A'+cha]=0;
    }
    for(int i=0;i<10;i++){
        if((!prekey['0'+i]||sk) && KEYDOWN('0'+i)){
            keys.push_back('0'+i);
            prekey['0'+i]=1;
        }
        if((sk||!prekey['0'+i+48]) && (KEYDOWN('0'+i+48)&&NumLock)){
            keys.push_back('0'+i+48);
            prekey['0'+i+48]=1;
        }
        if(KEYUP('0'+i)) prekey['0'+i]=0;
        if(KEYUP('0'+i+48)||!NumLock) prekey['0'+i+48]=0;
    }
    CheckSimpleTextKeys();
    return keys;
}
