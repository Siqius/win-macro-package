#include <node.h>
#include <windows.h>
#include <winuser.h>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <variant>

#include "nlohmann/json.hpp"
using namespace nlohmann;
using namespace std;

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::String;
using v8::Local;
using v8::Number;
using v8::Exception;
using v8::Value;

int stringToVirtualKey(const std::string& keyName) {
  static const std::unordered_map<std::string, int> keyMap = {
    {"backspace", VK_BACK},
    {"tab", VK_TAB},
    {"clear", VK_CLEAR},
    {"enter", VK_RETURN},
    {"shift", VK_SHIFT},
    {"ctrl", VK_CONTROL},
    {"alt", VK_MENU},
    {"pause", VK_PAUSE},
    {"capslock", VK_CAPITAL},
    {"esc", VK_ESCAPE},
    {"space", VK_SPACE},
    {"pageup", VK_PRIOR},
    {"pagedown", VK_NEXT},
    {"end", VK_END},
    {"home", VK_HOME},
    {"left", VK_LEFT},
    {"up", VK_UP},
    {"right", VK_RIGHT},
    {"down", VK_DOWN},
    {"select", VK_SELECT},
    {"print", VK_PRINT},
    {"execute", VK_EXECUTE},
    {"printscreen", VK_SNAPSHOT},
    {"insert", VK_INSERT},
    {"delete", VK_DELETE},
    {"help", VK_HELP},
    {"0", 0x30},
    {"1", 0x31},
    {"2", 0x32},
    {"3", 0x33},
    {"4", 0x34},
    {"5", 0x35},
    {"6", 0x36},
    {"7", 0x37},
    {"8", 0x38},
    {"9", 0x39},
    {"A", 0x41},
    {"B", 0x42},
    {"C", 0x43},
    {"D", 0x44},
    {"E", 0x45},
    {"F", 0x46},
    {"G", 0x47},
    {"H", 0x48},
    {"I", 0x49},
    {"J", 0x4A},
    {"K", 0x4B},
    {"L", 0x4C},
    {"M", 0x4D},
    {"N", 0x4E},
    {"O", 0x4F},
    {"P", 0x50},
    {"Q", 0x51},
    {"R", 0x52},
    {"S", 0x53},
    {"T", 0x54},
    {"U", 0x55},
    {"V", 0x56},
    {"W", 0x57},
    {"X", 0x58},
    {"Y", 0x59},
    {"Z", 0x5A},
    {"leftwin", VK_LWIN},
    {"rightwin", VK_RWIN},
    {"apps", VK_APPS},
    {"sleep", VK_SLEEP},
    {"numpad0", VK_NUMPAD0},
    {"numpad1", VK_NUMPAD1},
    {"numpad2", VK_NUMPAD2},
    {"numpad3", VK_NUMPAD3},
    {"numpad4", VK_NUMPAD4},
    {"numpad5", VK_NUMPAD5},
    {"numpad6", VK_NUMPAD6},
    {"numpad7", VK_NUMPAD7},
    {"numpad8", VK_NUMPAD8},
    {"numpad9", VK_NUMPAD9},
    {"multiply", VK_MULTIPLY},
    {"add", VK_ADD},
    {"separator", VK_SEPARATOR},
    {"subtract", VK_SUBTRACT},
    {"decimal", VK_DECIMAL},
    {"divide", VK_DIVIDE},
    {"f1", VK_F1},
    {"f2", VK_F2},
    {"f3", VK_F3},
    {"f4", VK_F4},
    {"f5", VK_F5},
    {"f6", VK_F6},
    {"f7", VK_F7},
    {"f8", VK_F8},
    {"f9", VK_F9},
    {"f10", VK_F10},
    {"f11", VK_F11},
    {"f12", VK_F12},
    {"numlock", VK_NUMLOCK},
    {"scrolllock", VK_SCROLL},
    {"leftshift", VK_LSHIFT},
    {"rightshift", VK_RSHIFT},
    {"leftctrl", VK_LCONTROL},
    {"rightctrl", VK_RCONTROL},
    {"leftalt", VK_LMENU},
    {"rightalt", VK_RMENU},
    {"volumemute", VK_VOLUME_MUTE},
    {"volumedown", VK_VOLUME_DOWN},
    {"volumeup", VK_VOLUME_UP},
    {"nexttrack", VK_MEDIA_NEXT_TRACK},
    {"prevtrack", VK_MEDIA_PREV_TRACK},
    {"stopmedia", VK_MEDIA_STOP},
    {"playpause", VK_MEDIA_PLAY_PAUSE},
    {"launchmail", VK_LAUNCH_MAIL},
    {"launchmediaselect", VK_LAUNCH_MEDIA_SELECT},
    {"launchapp1", VK_LAUNCH_APP1},
    {"launchapp2", VK_LAUNCH_APP2}  
  };

  auto it = keyMap.find(keyName);
  return it->second;
}
void keyPress(const FunctionCallbackInfo<Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  v8::String::Utf8Value str(isolate, args[0]);
  std::string cppStr(*str);
  json jsons = json::parse(cppStr);

  std::string key = jsons.value("key", "a");
  std::string type = jsons.value("type", "press");


  INPUT input;
  input.type = INPUT_KEYBOARD;
  input.ki.dwFlags = 0;
  if (type == "release") {
    input.ki.dwFlags = KEYEVENTF_KEYUP;
  }
  input.ki.wVk = stringToVirtualKey(key);
  SendInput(1,&input,sizeof(INPUT));
}


void click(const FunctionCallbackInfo<Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  v8::String::Utf8Value str(isolate, args[0]);
  std::string cppStr(*str);
  json jsons = json::parse(cppStr);

  std::string button = jsons.value("button", "left");
  std::string type = jsons.value("type", "press");
  std::string movestr = jsons.value("move", "false");
  bool move;
  istringstream(movestr) >> std::boolalpha >> move;

  INPUT input;
  DWORD moveParam = MOUSEEVENTF_ABSOLUTE;
  DWORD mouseAction;
  DWORD xbutton;
  input.type = INPUT_MOUSE;
  if(move) {
    input.mi.dx = (65535 / GetSystemMetrics (SM_CXSCREEN)) * stoi(jsons.value("x","200"));
    input.mi.dy = (65535 / GetSystemMetrics (SM_CXSCREEN)) * stoi(jsons.value("y","200"));
    moveParam = MOUSEEVENTF_MOVE;
  }

  if (button == "left") {
    if (type == "press") {
      mouseAction = MOUSEEVENTF_LEFTDOWN;
    }
    else if (type == "release") {
      mouseAction = MOUSEEVENTF_LEFTUP;
    }
  }
  else if (button == "right") {
    if (type == "press") {
      mouseAction = MOUSEEVENTF_RIGHTDOWN;
    }
    else if (type == "release") {
      mouseAction = MOUSEEVENTF_RIGHTUP;
    }
  }
  else if (button == "middle") {
    if (type == "press") {
      mouseAction = MOUSEEVENTF_MIDDLEDOWN;
    }
    else if (type == "release") {
      mouseAction = MOUSEEVENTF_MIDDLEUP;
    }
  }
  else if (button == "mouse4" || button == "mouse5") {
    if (button == "mouse4") {
      xbutton = XBUTTON1;
    } else {
      xbutton = XBUTTON2;
    }
    if (type == "press") {
      mouseAction = MOUSEEVENTF_XDOWN;
    }
    else if (type == "release") {
      mouseAction = MOUSEEVENTF_XUP;
    }
  }
  input.mi.time = 0;
  input.mi.dwExtraInfo = NULL;
  input.mi.dwFlags=(MOUSEEVENTF_ABSOLUTE|moveParam|mouseAction);
  input.mi.mouseData = xbutton;
  SendInput(1,&input,sizeof(INPUT));
}


void Initialize(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "click", click);
  NODE_SET_METHOD(exports, "keyPress", keyPress);
}

NODE_MODULE(addon, Initialize);