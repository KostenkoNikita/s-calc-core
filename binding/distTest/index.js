"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var binding_1 = require("binding");
var Startup = /** @class */ (function () {
    function Startup() {
    }
    Startup.main = function () {
        console.log(binding_1);
        console.log(binding_1.napiTokenize(1, ''));
        console.log('Works.');
        return 0;
    };
    return Startup;
}());
Startup.main();
//# sourceMappingURL=index.js.map