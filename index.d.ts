// Type definitions for S-Calc-Core 0.1.2
// Project: https://github.com/KostenkoNikita/s-calc-core
// Definitions by: Tsyhankov Mykyta <https://github.com/vanmxpx>
// TypeScript Version: 3.2.2


declare namespace Core {
    interface Binding {
        /**
        * @Method: Tokenize method, binded by node-gyp from C language
        * @Param {number} source string length
        * @Param {string} source string
        * @Return {string[]} 
        */
        napiTokenize(value1: number, value2: string): string[];
    }
}

declare const map: Core.Binding;

declare module '@scalc/core' {
    export = map;
}

  