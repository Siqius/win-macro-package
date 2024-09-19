const addon = await import('module').then(m => m.createRequire(import.meta.url)('./build/Release/mouse-controller.node'));

export async function click(obj) {
  const clickParams = {
    "button": obj.button,
    "type": obj.type,
    "move": obj.move,
    "x": obj.x,
    "y": obj.y
  }
  let repeat = obj.repeat;
  let delay = obj.delay;
  for(let i = 0; i != repeat; i++) {
      addon.click(JSON.stringify(clickParams));
      new Promise(resolve => setTimeout(resolve, delay));
  }
}