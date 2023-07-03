const { Platform } = require("../dist/binding.js");
const assert = require("assert");

function testPlatform() {
  const platform = new Platform();

  console.log("clipboard from platform", platform.clipboard.get());
  platform.clipboard.set("SOMETHING");
  console.log("clipboard.get()", platform.clipboard.get());
}

assert.doesNotThrow(testPlatform, undefined, "testPlatform threw an expection");

console.log("Tests passed -- everything looks OK!");
