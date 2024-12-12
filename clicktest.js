const addon = await import('module').then(m => m.createRequire(import.meta.url)('./build/Release/mouse-controller.node'));
import obj from "./jsontest.js";
import { start } from "./index.js";

start(obj);

/*
start({
  "repeat": 1,
  "startDelay": "3000",
  "macro": [
    {
      "inputType": "move", // 
      "delay": "10", // default 100
      "duration": "2000", // default 1000
      "steps": "100", // default 100
      "x": "100", // default 200
      "y": "100" //default 200
    }
  ]
});
*/