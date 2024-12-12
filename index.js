import { Worker } from "node:worker_threads";
import path from "path";
import { fileURLToPath } from "node:url";
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

let worker;

export function stop() {
  try {
    worker.terminate();
    console.log("Worker terminated.")
  } catch { }
}

export function start(obj) {
  console.log("starting");
  worker = new Worker(path.resolve(__dirname, './input-handler-worker.js'), {
    workerData: obj
  });
  worker.on("message", (message) => {
    if (message == "terminate") {
      stop();
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

function err(prompt) {
  throw new SyntaxError(prompt);
}

export function textToJson(text) {
  text = text.replaceAll("\n", "");
  text = text.replaceAll("  ", "");
  text = text.replaceAll("; ", ";");
  let actions = text.split(";");
  actions.pop();

  let obj = {
    "repeat": actions[0],
    "startDelay": actions[1],
    "macro": [

    ]
  };

  valid_keyboard_keys = [
    "backspace",
    "tab",
    "clear",
    "enter",
    "shift",
    "ctrl",
    "alt",
    "pause",
    "capslock",
    "space",
    "pageup",
    "pagedown",
    "end",
    "home",
    "left",
    "up",
    "righ,t",
    "down",
    "select",
    "print",
    "execute",
    "printscreen",
    "insert",
    "delete",
    "help",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "a",
    "b",
    "c",
    "d",
    "e",
    "f",
    "g",
    "h",
    "i",
    "j",
    "k",
    "l",
    "m",
    "n",
    "o",
    "p",
    "q",
    "r",
    "s",
    "t",
    "u",
    "v",
    "w",
    "x",
    "y",
    "z",
    "leftwin",
    "rightwin",
    "apps",
    "sleep",
    "numpad0",
    "numpad1",
    "numpad2",
    "numpad3",
    "numpad4",
    "numpad5",
    "numpad6",
    "numpad7",
    "numpad8",
    "numpad9",
    "multiply",
    "add",
    "separator",
    "subtract",
    "decimal",
    "divide",
    "f1",
    "f2",
    "f3",
    "f4",
    "f5",
    "f6",
    "f7",
    "f8",
    "f9",
    "f10",
    "f11",
    "f12",
    "numlock",
    "scrolllock",
    "leftshift",
    "rightshift",
    "leftctrl",
    "rightctrl",
    "leftalt",
    "rightalt",
    "volumemute",
    "volumedown",
    "volumeup",
    "nexttrack",
    "prevtrack",
    "stopmedia",
    "playpause",
    "launchmail",
    "launchmediaselect",
    "launchapp1",
    "launhapp2"
  ];

  valid_mouse_keys = [
    "left",
    "right",
    "middle",
    "mouse4",
    "mouse5"
  ];

  types = [
    "press",
    "release"
  ];

  for (let i = 2; i < actions.length; i++) {
    let action = actions[i].split(" ");
    if (action[0].toLowerCase() == "click") {

      if (!(valid_mouse_keys.includes(action[1].toLowerCase()))) {
        err(`Mouse button is invalid on line ${i + 1}`);
      }

      if (!(types.includes(action[2].toLowerCase()))) {
        err(`Type is invalid on line ${i + 1}`);
      }

      try {
        parseInt(action[3]);
      } catch (error) {
        err(`Delay must be a number on line ${i + 1}`);
      } finally {
        if (parseInt(action[3]) < 15) {
          err(`Delay must be greater than 15ms`);
        }
      }

      obj.macro.push({
        "inputType": action[0],
        "button": action[1],
        "type": action[2],
        "delay": action[3]
      });
    }

    else if (action[0].toLowerCase() == "key") {

      if (!(valid_keyboard_keys.includes(action[1].toLowerCase()))) {
        err(`Mouse button is invalid on line ${i + 1}`);
      }

      if (!(types.includes(action[2].toLowerCase()))) {
        err(`Type is invalid on line ${i + 1}`);
      }

      try {
        parseInt(action[3]);
      } catch (error) {
        err(`Delay must be a number on line ${i + 1}`);
      } finally {
        if (parseInt(action[3]) < 15) {
          err(`Delay must be greater than 15ms`);
        }
      }

      obj.macro.push({
        "inputType": action[0],
        "button": action[1],
        "type": action[2],
        "delay": action[3]
      });
    }

    else if (action[0].toLowerCase() == "write") {

      try {
        parseInt(action[2]);
      } catch (error) {
        err(`Delay must be a number on line ${i + 1}`);
      } finally {
        if ((parseInt(action[2]) / action[1].length) < 15) {
          err(`Duration / message length must be greater than or equal to 15ms`);
        }
      }

      try {
        parseInt(action[3]);
      } catch (error) {
        err(`Delay must be a number on line ${i + 1}`);
      } finally {
        if (parseInt(action[3]) < 15) {
          err(`Delay must be greater than 15ms`);
        }
      }

      obj.macro.push({
        "inputType": action[0],
        "message": action[1],
        "duration": action[2],
        "delay": action[3]
      });
    }

    else if (action[0].toLowerCase() == "move") {

      try {
        parseInt(action[1]);
      } catch (error) {
        err(`X coordinate must be a number on line ${i + 1}`);
      }

      try {
        parseInt(action[2]);
      } catch (error) {
        err(`Y coordinate must be a number on line ${i + 1}`);
      }

      try {
        parseInt(action[3]);
      } catch (error) {
        err(`Duration must be a number on line ${i + 1}`);
      }

      try {
        parseInt(action[4]);
      } catch (error) {
        err(`Steps must be a number on line ${i + 1}`);
      } finally {
        if (action[3] / action[4] < 15) {
          err(`Duration / Steps must be greater than 15ms`);
        }
      }

      try {
        parseInt(action[5]);
      } catch (error) {
        err(`Delay must be a number on line ${i + 1}`);
      } finally {
        if (parseInt(action[5]) < 15) {
          err(`Delay must be greater than 15ms`);
        }
      }


      obj.macro.push({
        "inputType": action[0],
        "x": action[1],
        "y": action[2],
        "duration": action[3],
        "steps": action[4],
        "delay": action[5]
      });
    }

    else if (action[0].toLowerCase() == "moveto") {

      try {
        parseInt(action[1]);
      } catch (error) {
        err(`X coordinate must be a number on line ${i + 1}`);
      }

      try {
        parseInt(action[2]);
      } catch (error) {
        err(`Y coordinate must be a number on line ${i + 1}`);
      }

      try {
        parseInt(action[3]);
      } catch (error) {
        err(`Duration must be a number on line ${i + 1}`);
      }

      try {
        parseInt(action[4]);
      } catch (error) {
        err(`Steps must be a number on line ${i + 1}`);
      } finally {
        if (action[3] / action[4] < 15) {
          err(`Duration / Steps must be greater than 15ms`);
        }
      }

      try {
        parseInt(action[5]);
      } catch (error) {
        err(`Delay must be a number on line ${i + 1}`);
      } finally {
        if (parseInt(action[5]) < 15) {
          err(`Delay must be greater than 15ms`);
        }
      }

      obj.macro.push({
        "inputType": action[0],
        "x": action[1],
        "y": action[2],
        "duration": action[3],
        "steps": action[4],
        "delay": action[5]
      });
    }

    else {
      throw new SyntaxError(`Action type must be of type 'click', 'key', 'write', 'move' or 'moveto' on line ${i + 1}`);
    }
  }
  return obj;
}

export function jsonToText(json) {
  let text = `${json.repeat};${json.startDelay};`;
  json.macro.forEach(action => {
    let snippet = `${action.inputType} ${action.x || ""} ${action.button || ""} ${action.message || ""} ${action.y || ""} ${action.type || ""} ${action.duration || ""} ${action.steps || ""} ${action.delay};`;
    text += snippet;
  });

  text = text.replaceAll("  ", " ");
  text = text.replaceAll("  ", " ");
  return text;
}