const {
    GLPlatform, Background, Padding, Rounded, Flex, Width, Height, Text,
} = require("../dist/elementor.js");

const platform = new GLPlatform();
const window = platform.makeWindow({width: 960, height: 512});
window.setTitle("Test");
window.setMinSize({width: 960, height: 512});
window.setRoot(
    new Background().setColor("#FFFFFF")
        .setChild(
            new Padding().set(32, 64)
                .setChild(
                    new Rounded().set(32)
                        .setChild(
                            new Flex().setSpacing(16)
                                .appendFlexible(
                                    new Background().setColor("#FFAAAA")
                                )
                                .appendChild(
                                    new Width().setWidth(64)
                                        .setChild(
                                            new Height().setHeight(64)
                                                .setChild(new Background().setColor("#AAAAAA"))
                                        )
                                )
                                .appendFlexible(
                                    new Background().setColor("#AAFFAA")
                                )
                                .appendChild(
                                    new Background()
                                        .setColor("#AAAAAA")
                                        .setChild(
                                            new Padding().set(16)
                                                .setChild(
                                                    new Text()
                                                        .setText("Hello, world!")
                                                        .setFontColor("#FFF")
                                                )
                                        )
                                )
                                .appendFlexible(new Background().setColor("#AAAAFF"))
                        )
                )
        )
);

platform.run();
