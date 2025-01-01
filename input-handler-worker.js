const addon = await import('module').then(m => m.createRequire(import.meta.url)('./build/Release/mouse-controller.node'));
import { workerData, parentPort } from "node:worker_threads";

function sendInput(obj) {
  //gather the data from obj
  const repeat = obj.repeat;
  const macro = obj.macro;
  const startDelay = obj.startDelay;
  addon.sleep(JSON.stringify({
    "startDelay": startDelay
  }))

  //loop over the macro as many times as specified
  for (let i = 0; i != repeat; i++) {
    for (const input of macro) {
      let delay = parseInt(input.delay) >= 15 ? input.delay : "15"; //minimum of 15 delay

      //set params 
      let clickParams = {
        "type": input.type,
        "key": input.key,
        "duration": input.duration,
        "steps": input.steps,
        "x": input.x,
        "y": input.y,
        "delay": delay,
        "relative": input.inputType == "move" ? true : false,
      }
      if (input.inputType == "click") {
        addon.click(JSON.stringify(clickParams));
      } else if (input.inputType == "key") {
        addon.keyPress(JSON.stringify(clickParams));
      } else if (input.inputType == "write") {
        addon.write(JSON.stringify(clickParams));
      } else if (input.inputType.slice(0, 4) == "move") {
        addon.move(JSON.stringify(clickParams));
      }
    }
  }
  parentPort.postMessage("worker finished");
}

sendInput(workerData);
