const addon = await import('module').then(m => m.createRequire(import.meta.url)('./build/Release/mouse-controller.node'));

export async function sendInput(obj) {
  const repeat = obj.repeat;
  const macro = obj.macro;
  for(let i = 0; i != repeat; i++) {
    macro.forEach(input => {
      let clickParams = {
        "button": input.button,
        "type": input.type,
        "move": input.move,
        "x": input.x,
        "y": input.y
      }
      if(input.inputType == "mouse") {
        addon.click(JSON.stringify(clickParams));
      }else{
        addon.keyPress(JSON.stringify(clickParams));
      }
      new Promise(resolve => setTimeout(resolve, delay));
    });
  }
}