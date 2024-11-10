#include <napi.h>
#include <windows.h>
#include <winuser.h>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <variant>
#include <thread>
#include <chrono>

#include "nlohmann/json.hpp"
using namespace nlohmann;
using namespace std;

void SmoothMoveMouse(int targetX, int targetY, int duration, int steps)
{
    POINT currentPos;
    GetCursorPos(&currentPos);
    int16_t startX = currentPos.x;
    int16_t startY = currentPos.y;
    int16_t deltaX = targetX - startX;
    int16_t deltaY = targetY - startY;
    int16_t sleepTime = duration / steps / 5;
    for (int i = 1; i <= steps; i++)
    {
        int newX = startX + (deltaX * i) / steps;
        int newY = startY + (deltaY * i) / steps;
        SetCursorPos(newX, newY);
        cout << "sleeping for " << sleepTime << " ms" <<  endl;
        cout << i << endl;
        Sleep(sleepTime);
        //https://chatgpt.com/c/66fb1265-8fe4-8007-94ff-2260b8bc0cf4
    }
    SetCursorPos(targetX, targetY);
}

int stringToScanCode(const std::string& keyName) {
  static const std::unordered_map<std::string, int> keyMap = {
    {"backspace", 0x0E},
    {"tab", 0x0F},
    {"clear", 0x0C},
    {"enter", 0x1C},
    {"shift", 0x2A},
    {"ctrl", 0x1D},
    {"alt", 0x38},
    {"pause", 0xC5},
    {"capslock", 0x3A},
    {"space", 0x39},
    {" ", 0x39},
    {"pageup", 0x49},
    {"pagedown", 0x51},
    {"end", 0x4F},
    {"home", 0x47},
    {"left", 0x4B},
    {"up", 0x48},
    {"right", 0x4D},
    {"down", 0x50},
    {"select", 0x29},
    {"print", 0x2C},
    {"execute", 0x4C},
    {"printscreen", 0x37},
    {"insert", 0x52},
    {"delete", 0x53},
    {"help", 0x2F},
    {"0", 0x0B},
    {"1", 0x02},
    {"2", 0x03},
    {"3", 0x04},
    {"4", 0x05},
    {"5", 0x06},
    {"6", 0x07},
    {"7", 0x08},
    {"8", 0x09},
    {"9", 0x0A},
    {"a", 0x1E},
    {"b", 0x30},
    {"c", 0x2E},
    {"d", 0x20},
    {"e", 0x12},
    {"f", 0x21},
    {"g", 0x22},
    {"h", 0x23},
    {"i", 0x17},
    {"j", 0x24},
    {"k", 0x25},
    {"l", 0x26},
    {"m", 0x32},
    {"n", 0x31},
    {"o", 0x18},
    {"p", 0x19},
    {"q", 0x14},
    {"r", 0x13},
    {"s", 0x1F},
    {"t", 0x14},
    {"u", 0x16},
    {"v", 0x2F},
    {"w", 0x11},
    {"x", 0x2D},
    {"y", 0x15},
    {"z", 0x2C},
    {"leftwin", 0xDB},
    {"rightwin", 0xDC},
    {"apps", 0xDD},
    {"sleep", 0x5F},
    {"numpad0", 0x52},
    {"numpad1", 0x4F},
    {"numpad2", 0x50},
    {"numpad3", 0x51},
    {"numpad4", 0x4B},
    {"numpad5", 0x4C},
    {"numpad6", 0x4D},
    {"numpad7", 0x47},
    {"numpad8", 0x48},
    {"numpad9", 0x49},
    {"multiply", 0x37},
    {"add", 0x4E},
    {"separator", 0x6C},
    {"subtract", 0x4A},
    {"decimal", 0x53},
    {"divide", 0xB5},
    {"f1", 0x3B},
    {"f2", 0x3C},
    {"f3", 0x3D},
    {"f4", 0x3E},
    {"f5", 0x3F},
    {"f6", 0x40},
    {"f7", 0x41},
    {"f8", 0x42},
    {"f9", 0x43},
    {"f10", 0x44},
    {"f11", 0x57},
    {"f12", 0x58},
    {"numlock", 0x45},
    {"scrolllock", 0x46},
    {"leftshift", 0x2A},
    {"rightshift", 0x36},
    {"leftctrl", 0x1D},
    {"rightctrl", 0x1D},
    {"leftalt", 0x38},
    {"rightalt", 0x38},
    {"volumemute", 0xE2},
    {"volumedown", 0xE0},
    {"volumeup", 0xE9},
    {"nexttrack", 0xB0},
    {"prevtrack", 0xB1},
    {"stopmedia", 0xB2},
    {"playpause", 0xB3},
    {"launchmail", 0xB4},
    {"launchmediaselect", 0xB5},
    {"launchapp1", 0xB6},
    {"launchapp2", 0xB7}
  };


  auto it = keyMap.find(keyName);
  return it->second;
}

Napi::Value sleep(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::String arg0 = info[0].As<Napi::String>();
  std::string cppStr = arg0.Utf8Value();

  json jsons = json::parse(cppStr);
  int16_t initDelay = stoi(jsons.value("startDelay", "1000"));
  Sleep(initDelay);
  
  return env.Null();
}

Napi::Value getKey(const Napi::CallbackInfo& info) {
  
}

Napi::Value keyPress(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::String arg0 = info[0].As<Napi::String>();
  std::string cppStr = arg0.Utf8Value();

  
  json jsons = json::parse(cppStr);
  std::string key = jsons.value("button", "a");
  std::string type = jsons.value("type", "press");
  int16_t delay = stoi(jsons.value("delay", "10"));

  INPUT input;
  input.type = INPUT_KEYBOARD;
  input.ki.wScan = stringToScanCode(key);
  input.ki.dwFlags = KEYEVENTF_SCANCODE;
  
  if (type == "release") {
    input.ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_SCANCODE;
  }

  SendInput(1, &input, sizeof(INPUT));

  Sleep(delay);

  return env.Null();
}

Napi::Value write(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::String arg0 = info[0].As<Napi::String>();
  std::string cppStr = arg0.Utf8Value();

  json jsons = json::parse(cppStr);
  std::string message = jsons.value("button", "a");
  int16_t delay = stoi(jsons.value("delay", "10"));
  int16_t duration = stoi(jsons.value("duration", "1000"));

  int16_t sleepTime = duration / message.length();

  for(int16_t i = 0; i < message.length(); i++) {
    std::string key(1, message[i]);
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = stringToScanCode(key);
    input.ki.dwFlags = KEYEVENTF_SCANCODE;

    SendInput(1, &input, sizeof(INPUT));

    Sleep(5);

    INPUT inputUp;
    inputUp.type = INPUT_KEYBOARD;
    inputUp.ki.wScan = stringToScanCode(key);
    inputUp.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;

    Sleep(sleepTime);
  }

  Sleep(delay);

  return env.Null();
}

Napi::Value moveMouse(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::String arg0 = info[0].As<Napi::String>();
  std::string cppStr = arg0.Utf8Value();

  json jsons = json::parse(cppStr);
  int16_t delay = stoi(jsons.value("delay", "100"));
  int16_t duration = stoi(jsons.value("duration", "1000"));
  int16_t steps = stoi(jsons.value("steps", "100"));
  int16_t x = stoi(jsons.value("x", "200"));
  int16_t y = stoi(jsons.value("y", "200"));

  cout << duration;

  SmoothMoveMouse(x, y, duration, steps);

  Sleep(delay);

  return env.Null();
}

Napi::Value click(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::String arg0 = info[0].As<Napi::String>();
  std::string cppStr = arg0.Utf8Value();
  
  json jsons = json::parse(cppStr);
  std::string button = jsons.value("button", "left");
  std::string type = jsons.value("type", "press");
  int16_t delay = stoi(jsons.value("delay", "10"));
  int16_t duration = stoi(jsons.value("duration", "10000"));
  int16_t steps = stoi(jsons.value("steps", "100"));
  int16_t x = stoi(jsons.value("x", "200"));
  int16_t y = stoi(jsons.value("y", "200"));
  std::string movestr = jsons.value("move", "false");
  bool move;
  istringstream(movestr) >> std::boolalpha >> move;

  INPUT input;
  DWORD mouseAction = 0;
  DWORD xbutton = 0;
  
  input.type = INPUT_MOUSE;

  if (button == "left") mouseAction = (type == "press") ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP;
  else if (button == "right") mouseAction = (type == "press") ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_RIGHTUP;
  else if (button == "middle") mouseAction = (type == "press") ? MOUSEEVENTF_MIDDLEDOWN : MOUSEEVENTF_MIDDLEUP;
  else if (button == "mouse4" || button == "mouse5") {
    xbutton = (button == "mouse4") ? XBUTTON1 : XBUTTON2;
    mouseAction = (type == "press") ? MOUSEEVENTF_XDOWN : MOUSEEVENTF_XUP;
  }

  input.mi.time = 100;
  input.mi.dwExtraInfo = NULL;
  input.mi.dwFlags = (mouseAction);
  input.mi.mouseData = xbutton;

  if(move) {
    SmoothMoveMouse(x, y, duration, steps);
  }

  SendInput(1, &input, sizeof(INPUT));

  Sleep(delay);

  return env.Null();  // Return nothing
}

Napi::Object Initialize(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "click"), Napi::Function::New(env, click));
  exports.Set(Napi::String::New(env, "keyPress"), Napi::Function::New(env, keyPress));
  exports.Set(Napi::String::New(env, "write"), Napi::Function::New(env, write));
  exports.Set(Napi::String::New(env, "moveMouse"), Napi::Function::New(env, moveMouse));
  exports.Set(Napi::String::New(env, "sleep"), Napi::Function::New(env, sleep));
  return exports;
}

NODE_API_MODULE(addon, Initialize)
