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
  std::string delay = jsons.value("delay", "100");
  cout << button << endl;
  cout << delay << endl;
}
  /*
  bool pos = false;
  DWORD moveParam;
  if(args.Length() == 3) { 
    if (!args[1]->IsNumber() || !args[2]->IsNumber()) {
      isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
      return;
    }
    pos = true;
  }

  INPUT input;
  input.type=INPUT_MOUSE;
  if(pos) {
    input.mi.dx = args[1];
    input.mi.dy = args[2];
    moveParam = MOUSEEVENT_MOVE;
  }
  input.mi.dwFlags=(MOUSEEVENTF_LEFTDOWN|moveParam|MOUSEEVENTF_LEFTUP);
  input.mi.time=100;
  SendInput(1,&input,sizeof(INPUT));
  */


void Initialize(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "click", Click);
}

NODE_MODULE(addon, Initialize)