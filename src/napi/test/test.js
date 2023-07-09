const {
  GLPlatform,
  Background,
  Padding,
  Rounded,
} = require("../dist/elementor.js");

const platform = new GLPlatform();
const window = platform.makeWindow({ width: 400, height: 400 });
window.setTitle("Test");
window.setMinSize({ width: 300, height: 300 });
window.setRoot(
  new Background()
    .setColor("#FFAAAA")
    .setChild(
      new Padding()
        .setPaddings(32, 64)
        .setChild(
          new Background()
            .setColor("#AAFFAA")
            .setChild(
              new Padding()
                .setPaddings(32 + 64, 64)
                .setChild(
                  new Rounded()
                    .setRadius(32)
                    .setChild(new Background().setColor("#AAAAFF")),
                ),
            ),
        ),
    ),
);

platform.run();
