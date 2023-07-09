const { GLPlatform, Background, Padding } = require("../dist/elementor.js");

const platform = new GLPlatform();
const window = platform.makeWindow({ width: 300, height: 300 });
window.setTitle("Test");
window.setMinSize({ width: 200, height: 200 });
window.setMaxSize({ width: 400, height: 400 });
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
                .setChild(new Background().setColor("#AAAAFF")),
            ),
        ),
    ),
);

platform.run();
