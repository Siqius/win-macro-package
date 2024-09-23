const addon = await import('module').then(m => m.createRequire(import.meta.url)('./build/Release/mouse-controller.node'));
import { workerData, parentPort } from "node:worker_threads";

await new Promise(resolve => setTimeout(resolve, 1000));
parentPort.postMessage("Worker created");
await new Promise(resolve => setTimeout(resolve, 1000));
parentPort.postMessage("Starting process");
await new Promise(resolve => setTimeout(resolve, 1000));

async function sendInput(obj) {
  parentPort.postMessage("Process started");
  const repeat = obj.repeat;
  const macro = obj.macro;
  for(let i = 0; i != repeat; i++) {
    macro.forEach(async input => {
      let clickParams = {
        "button": input.button,
        "type": input.type,
        "move": input.move,
        "x": input.x,
        "y": input.y
      }
      await new Promise(resolve => setTimeout(resolve, 1000));
      parentPort.postMessage("Initializing mouse click");
      if(input.inputType == "mouse") {
        addon.click(JSON.stringify(clickParams));
        await new Promise(resolve => setTimeout(resolve, delay));
        parentPort.postMessage("Click finished!");
      }else{
        addon.keyPress(JSON.stringify(clickParams));
      }
      await new Promise(resolve => setTimeout(resolve, delay));
    });
  }
}

sendInput(workerData);
parentPort.postMessage("Finished processing");
parentPort.postMessage("terminate");