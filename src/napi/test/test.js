const {GLPlatform, Background, Padding} = require('../dist/elementor.js')

const background1 = new Background()
background1.setColor("#FFAAAA")

const background2 = new Background()
background2.setColor("#AAFFAA")

const background3 = new Background()
background3.setColor("#AAAAFF")

const padding1 = new Padding()
padding1.setPaddings(64)

const padding2 = new Padding()
padding2.setPaddings(64)

background1.setChild(padding1)
padding1.setChild(background2)
background2.setChild(padding2)
padding2.setChild(background3)


const platform = new GLPlatform();
const window = platform.makeWindow({width: 300, height: 300})
window.setTitle("Test")
window.setMinSize({width: 200, height: 200})
window.setMaxSize({width: 400, height: 400})
window.setRoot(background1)

platform.run()
