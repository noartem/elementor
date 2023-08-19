const {
    GLPlatform,
    Background,
    Padding,
    Rounded,
    Flex,
    Width,
    Height,
    Text,
    Center,
} = require("../dist/elementor.js");

const platform = new GLPlatform();
const window = platform.makeWindow({ width: 400, height: 400 });
window.setTitle("Test");
window.setMinSize({ width: 300, height: 300 });
window.setRoot(
    new Background().setColor("#FFFFFF").setChild(
        new Padding().set(32, 64).setChild(
            new Rounded().set(32).setChild(
                new Flex()
                    .setSpacing(16)
                    .appendFlexible(new Background().setColor("#FFAAAA"))
                    .appendChild(
                        new Width()
                            .setWidth(64)
                            .setChild(
                                new Height()
                                    .setHeight(64)
                                    .setChild(new Background().setColor("#AAAAAA")),
                            ),
                    )
                    .appendFlexible(
                        new Background()
                            .setColor("#AAFFAA")
                            .setChild(
                                new Center().setChild(new Text().setText("Hello, world!")),
                            ),
                    )
                    .appendFlexible(new Background().setColor("#AAAAFF")),
            ),
        ),
    ),
);

platform.run();
