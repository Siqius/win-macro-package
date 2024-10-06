const addon = await import('module').then(m => m.createRequire(import.meta.url)('./build/Release/mouse-controller.node'));
import obj from "./jsontest.js";
import { start } from "./index.js";

start(obj);