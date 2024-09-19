import { Worker } from "node:worker_threads";
let inputType = "mouse"; // mouse / keyboard
let button = "left"; // left / middle / right
let type = "press"; // press / release
let repeat = "-1"; // amount of times to repeat
let delay = "200"; // delay between clicks (ms)
let move = "false"; // move cursor to x, y
let x = "200"; // x position
let y = "200"; // y position
let params = {
  "inputType": inputType,
  "button": button,
  "type": type,
  "repeat": repeat,
  "delay": delay,
  "move": move,
  "x": x,
  "y": y
};

let worker;

function terminateWorker() {
  worker.terminate();
}

export function input(obj) {
  terminateWorker();
  worker = new Worker("./input-handler-worker.js", {
    workerData: obj
  });
}