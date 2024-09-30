import { Worker } from "node:worker_threads";
import path from "path";
import { fileURLToPath } from "node:url";
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

let a = {
  "mouse": {
    "inputType": "mouse",
    "button": "left",
    "type": "press",
    "delay": "1000",
    "duration": "2000",
    "steps": "100",
    "move": "true",
    "x": "200",
    "y": "200"
  },

  "keyboard": {
    "inputType": "keyboard",
    "button": "a",
    "type": "press",
    "delay": "1000",
  },

  "write": {
    "inputType": "write",
    "button": "hellooooo",
    "delay": "1000",
    "duration": "1000"
  }
}

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