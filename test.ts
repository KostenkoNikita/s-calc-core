// This file is required by karma.conf.js and loads recursively all the .spec and framework files
import {  Tokenizer } from '@scalc/core';

import 'mocha';
// import * as tkn from '@scalc/core';

// First, initialize
import * as tokenizerModule from 'binding';
declare const binding: any;


import { expect } from 'chai';


describe('Hello function', () => {
    it('should return hello world', () => {


        const value = "42!+85!!+523.23E-10-sin(ln(54156e22+90/43cos(5)))";
        const resultArray = tokenizerModule.napiTokenize(value.length, value);

        console.log(resultArray);
        const result = 'Hello World!';
        expect(result).to.equal('Hello World!');
    });
});

const value = "42!+85!!+523.23E-10-sin(ln(54156e22+90/43cos(5)))";
const resultArray = tokenizerModule.napiTokenize(value.length, value);

console.log(resultArray);
