
declare module 'tokenizer' {

    if (process.env.DEBUG) {
        tokenizerModule = require('./build/Debug/tokenizerModule.node')
    } else {
        let tokenizerModule = require('./build/Release/tokenizerModule.node')
    }
    var fooLibrary: any;
    export = fooLibrary;

    /**
    * @Method: Returns the plural form of any noun.
    * @Param {string}
    * @Return {string}
    */
  }

  