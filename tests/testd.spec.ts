import { expect } from 'chai';
import 'mocha';

import { Tokenizer } from '@scalc/core';
// import * as tkn from '@scalc/core';

// First, initialize
import * as tokenizerModule from "binding";
//declare const tokenizerModule: any;

describe('Hello function', () => {
    it('should return hello world', () => {


        const value = "42!+85!!+523.23E-10-sin(ln(54156e22+90/43cos(5)))";
        const resultArray = tokenizerModule.napiTokenize(value.length, value);

        console.log(resultArray);
        const result = 'Hello World!';
        expect(result).to.equal('Hello World!');
    });
});
