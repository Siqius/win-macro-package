#include <node.h>
#include <windows.h>
#include <winuser.h>
#include <string>
#include <iostream>
#include <sstream>

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
/*
void keyPress(const FunctionCallbackInfo<Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  v8::String::Utf8Value str(isolate, args[0]);
  std::string cppStr(*str);
  json jsons = json::parse(cppStr);

  std::string key = jsons.value("key");
  std::int8_t duration = stoi(jsons.value("duration", "1"));

  INPUT input[];
  input.type = INPUT_KEYBOARD;
  input.mi.time = 0;
  input.mi.dwExtraInfo = NULL;
  input.mi.dwFlags=(mousedown|mouseup);

}
*/

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
}

NODE_MODULE(addon, Initialize)