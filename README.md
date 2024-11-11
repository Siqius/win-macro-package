# To use, run

```
npm install node-addon-api
npm install node-gyp
```

# Available functions

```
start(

)
stop()
```

# Object parameters

| Key        |  Type  | Description | Required |
| ---------- | :----: | :---------: | :------: |
| inputType  | string |             |   Yes    |
| delay (ms) | string |             |    No    |
| button     | string |             |    No    |

# Param inputs

Example of input

```
JSON.stringify({
"repeat": 1, //-1 for infinite, default 1 if not specified
"startDelay": "3000", //
"macro": [
  {
    "inputType": "keyboard",
    "button": "leftshift",
    "type": "press",
    "delay": "100"
  },
  {
    "inputType": "write",
    "button": "hello",
    "delay": "100"
  },
  {
    "inputType": "keyboard",
    "button": "leftshit",
    "type": "release",
    "delay": "100"
  },
  {
    "inputType": "mouse",
    "button": "left",
    "type": "press",
    "delay": "100",
    "move": "false",
    "x": "0",
    "y": "0"
  },
  {
    "inputType": "mouse",
    "button": "left",
    "type": "release",
    "delay": "100",
    "move": "false",
    "x": "0",
    "y": "0"
  }
]
})
```

Available mouse buttons

```
left
right
middle
mouse4
mouse5
```

Available keyboard buttons

```
backspace
tab
clear
enter
shift
ctrl
alt
pause
capslock
space
pageup
pagedown
end
home
left
up
right
down
select
print
execute
printscreen
insert
delete
help
0
1
2
3
4
5
6
7
8
9
a
b
c
d
e
f
g
h
i
j
k
l
m
n
o
p
q
r
s
t
u
v
w
x
y
z
leftwin
rightwin
apps
sleep
numpad0
numpad1
numpad2
numpad3
numpad4
numpad5
numpad6
numpad7
numpad8
numpad9
multiply
add
separator
subtract
decimal
divide
f1
f2
f3
f4
f5
f6
f7
f8
f9
f10
f11
f12
numlock
scrolllock
leftshift
rightshift
leftctrl
rightctrl
leftalt
rightalt
volumemute
volumedown
volumeup
nexttrack
prevtrack
stopmedia
playpause
launchmail
launchmediaselect
launchapp1
launhapp2
```
