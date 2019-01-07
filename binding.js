/**@type {{napiTokenize: Function}}*/
let tokenizerModule;

if (process.env.DEBUG) {
    tokenizerModule= require('./build/Debug/tokenizerModule.node')
} else {
    tokenizerModule= require('./build/Release/tokenizerModule.node')
}

module.exports = tokenizerModule;