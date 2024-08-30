#include <node.h>
#include <windows.h>
#include <winuser.h>

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::String;
using v8::Local;
using v8::Number;
using v8::Exception;
using v8::Value;

void Click(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  /*
  if (args.Length() > 3 || args.Length() < 1 || args.Length() == 2) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate,
                            "Wrong number of arguments").ToLocalChecked()));
    return;
  }
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
  input.mi.time=0;
  SendInput(1,&input,sizeof(INPUT));

  */
  args.GetReturnValue().Set(args);
  /*

  double value =
      args[0].As<Number>()->Value() + args[1].As<Number>()->Value();
  Local<Number> num = Number::New(isolate, value);

  */
}


void Initialize(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "click", Click);
}

NODE_MODULE(addon, Initialize)