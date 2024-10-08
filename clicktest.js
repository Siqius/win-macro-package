const addon = await import('module').then(m => m.createRequire(import.meta.url)('./build/Release/mouse-controller.node'));
import obj from "./jsontest.js";
import { start } from "./index.js";

start({
  "repeat": 1,
  "startDelay": "3000",
  "macro": [
    {
      "inputType": "move",
      "delay": "10",
      "duration": "2000",
      "steps": "100",
      "x": "100",
      "y": "100"
    }
  ]
});