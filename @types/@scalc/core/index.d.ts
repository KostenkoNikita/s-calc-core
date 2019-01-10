// Type definitions for S-Calc-Core 0.0.x
// Project: https://github.com/KostenkoNikita/s-calc-core
// Definitions by: Tsyhankov Mykyta <https://github.com/KostenkoNikita/s-calc-core/stargazers>
// TypeScript Version: 3.2.2

// export as namespace SCalcCore;

declare module '@scalc/core' {
    export class Tokenizer {
        constructor(options?: any);
        
        napiTokenize(value1: number, value2: string) : string;
        /**
        * @Method: Returns the plural form of any noun.
        * @Param {string}
        * @Return {string}
        */

    /**
    * Asynchronously reads the entire contents of a file.
    * @param path A path to a file. If a URL is provided, it must use the `file:` protocol.
    * If a file descriptor is provided, the underlying file will _not_ be closed automatically.
    * @param options An object that may contain an optional flag.
    * If a flag is not provided, it defaults to `'r'`.
    */
    }
}

  