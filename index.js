import { Worker } from "node:worker_threads";
import path from "path";
import { fileURLToPath } from "node:url";
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);


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
  try{
    worker.terminate();
    console.log("Worker terminated.")
  }catch {}
}

export function input(obj) {
  console.log("starting");
  worker = new Worker(path.resolve(__dirname, './input-handler-worker.js'), {
    workerData: obj
  });
  worker.on("message", (message) => {
    if(message == "terminate") {
      terminateWorker();
      return;
    }
    console.log(message);
  })
  worker.on("error", (error) => {
    console.log("Error detected: ", error)
  })
  worker.on('exit', (code) => {
    if (code !== 0) {
      console.error(`Worker stopped with exit code ${code}`);
    }
  });
  console.log("Finished setting up worker");
} 