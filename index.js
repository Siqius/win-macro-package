const addon = require("./build/Release//mouse-controller.node");
let button = "right";
let delay = "200";
let move = "true";
let x = "200";
let y = "200";
let params = JSON.stringify({
  "button": button,
  "move": move,
  "x": x,
  "y": y
})
for(let i = 0; i<1; i++) {
  addon.click(params)
}
