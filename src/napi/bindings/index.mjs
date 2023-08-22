import {merge} from "../utils/index.mjs";
import platformsGl from "./platforms-gl.mjs";
import elements from "./elements.mjs";
import {defaultBindings} from "../utils/bindings-helpers.mjs";

export default merge(defaultBindings, platformsGl, elements);
