const addon = await import('module').then(m => m.createRequire(import.meta.url)('./build/Release/mouse-controller.node'));

setTimeout(() => {
  addon.keyPress(JSON.stringify({
    "key": "enter",
    "type": "press"
  }))
}, 1000);
setTimeout(() => {
  addon.keyPress(JSON.stringify({
    "key": "backspace",
    "type": "press"
  }))
}, 2000);