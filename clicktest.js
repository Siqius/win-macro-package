const addon = await import('module').then(m => m.createRequire(import.meta.url)('./build/Release/mouse-controller.node'));

addon.click(JSON.stringify({
  "button": "mouse5",
  "type": "press",
  "move": "false",
  "x": "0",
  "y": "0"
}))

setTimeout(() => {
  addon.click(JSON.stringify({
    "button": "mouse5",
    "type": "release",
    "move": "false",
    "x": "0",
    "y": "0"
  }))
}, 50);