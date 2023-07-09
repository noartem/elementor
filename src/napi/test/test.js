const {
  GLPlatform,
  Background,
  Padding,
  Rounded,
  Flex,
  Width,
} = require("../dist/elementor.js");

const platform = new GLPlatform();
const window = platform.makeWindow({ width: 400, height: 400 });
window.setTitle("Test");
window.setMinSize({ width: 300, height: 300 });
window.setRoot(
  new Background().setColor("#FFFFFF").setChild(
    new Padding().setPaddings(32, 64).setChild(
      new Rounded().setRadius(32).setChild(
        new Flex()
          .setSpacing(16)
          .appendFlexible(new Background().setColor("#FFAAAA"))
          .appendChild(
            new Width()
              .setWidth(64)
              .setChild(new Background().setColor("#AAAAAA")),
          )
          .appendFlexible(new Background().setColor("#AAFFAA"))
          .appendFlexible(new Background().setColor("#AAAAFF")),
      ),
    ),
  ),
);

platform.run();
