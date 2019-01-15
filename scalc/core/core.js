"use strict";
/**@type {{napiTokenize: Function}}*/
let tokenizerModule;

if (process.env.DEBUG) {
    tokenizerModule = require('./bin/debug/tokenizerModule.node')
} else {
    tokenizerModule = require('./bin/release/tokenizerModule.node')
}

module.exports = tokenizerModule;