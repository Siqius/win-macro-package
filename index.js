const addon = require("./build/Release//mouse-controller.node");
let button;
let delay;
let move;
let x;
let y;
let params = JSON.stringify({
  "button": button,
  "delay": delay,
  "move": move,
  "x": x,
  "y": y
})
for(let i = 0; i<1; i++) {
  addon.click(params)
}
