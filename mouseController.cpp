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
  bool pos = false;
  INPUT inputs[4] = {};
  ZeroMemory(inputs, sizeof(inputs));

  inputs[0].type = INPUT_MOUSE;
  inputs[0].ki.wVk = VK_LEFT;
  inputs[0].ki.dwFlags = MOUSEEVENTF_LEFTDOWN;

  UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));

  args.GetReturnValue().Set(1);

  /*
  if (args.Length() > 3 || args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate,
                            "Wrong number of arguments").ToLocalChecked()));
    return;
  }
  if(args.Length() == 3) { 
    if (!args[1]->IsNumber() || !args[2]->IsNumber()) {
      isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
      return;
    }
    pos = true;
  }

  double value =
      args[0].As<Number>()->Value() + args[1].As<Number>()->Value();
  Local<Number> num = Number::New(isolate, value);

  args.GetReturnValue().Set(num);
  */
}


void Initialize(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "click", Click);
}

NODE_MODULE(addon, Initialize)