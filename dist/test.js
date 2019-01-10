"use strict";
// This file is required by karma.conf.js and loads recursively all the .spec and framework files
Object.defineProperty(exports, "__esModule", { value: true });
require("zone.js/dist/zone-testing");
var value = "42!+85!!+523.23E-10-sin(ln(54156e22+90/43cos(5)))";
var resultArray = tokenizer.napiTokenize(value.length, value);
// Then we find all the tests.
var context = require.context('./tests', true, /\.spec\.ts$/);
// And load the modules.
context.keys().map(context);
//# sourceMappingURL=test.js.map