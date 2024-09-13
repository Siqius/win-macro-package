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

void Click(const FunctionCallbackInfo<Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  v8::String::Utf8Value str(isolate, args[0]);
  std::string cppStr(*str);
  json jsons = json::parse(cppStr);

  std::string button = jsons.value("button", "left");
  std::string movestr = jsons.value("move", "false");
  bool move;
  istringstream(movestr) >> std::boolalpha >> move;

  INPUT input;
  DWORD moveParam = MOUSEEVENTF_ABSOLUTE;
  DWORD mousedown;
  DWORD mouseup;
  input.type=INPUT_MOUSE;
  if(move) {
    input.mi.dx = (65535 / GetSystemMetrics (SM_CXSCREEN)) * stoi(jsons.value("x","200"));
    input.mi.dy = (65535 / GetSystemMetrics (SM_CXSCREEN)) * stoi(jsons.value("y","200"));
    cout << input.mi.dy << endl;
    moveParam = MOUSEEVENTF_MOVE;
  }
  if(button == "right") {
    mousedown = MOUSEEVENTF_RIGHTDOWN;
    mouseup = MOUSEEVENTF_RIGHTUP;
  }else {
    mousedown = MOUSEEVENTF_LEFTDOWN;
    mouseup = MOUSEEVENTF_LEFTUP;
  }
  input.mi.dwFlags=(MOUSEEVENTF_ABSOLUTE|moveParam|mousedown|mouseup);
  input.mi.time = 0;
  input.mi.mouseData = 0;
  input.mi.dwExtraInfo = NULL;
  SendInput(1,&input,sizeof(INPUT));
}


void Initialize(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "click", Click);
}

NODE_MODULE(addon, Initialize)