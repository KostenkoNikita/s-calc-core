import { expect } from 'chai';
import 'mocha';

// First, initialize
import * as tokenizerModule from "scalc/core";

describe('napiTokenize', () => {
    it('#1 Functional test', () => {
        const value = "42!+85!!+523.23E-10-sin(ln(54156e22+90/43cos(5)))";
        const resultArray = tokenizerModule.napiTokenize(value.length, value);
        const expected = ['42','!','+','85','!!','+','523.23E-10','-','sin','(','ln','(','54156e22','+','90','/','43','cos','(','5',')',')'];
        expect(resultArray.length, 'Length').to.equal(expected.length);
        expect(resultArray, 'Tokens').to.deep.equal(expected);
    });

    it('#2 Spaces test', () => {
        const value = "42!  + 85!!   +523.23E-10 -  sin(       ln(      54156e22 +90 /43cos(5    )))";
        const resultArray = tokenizerModule.napiTokenize(value.length, value);
        const expected = ['42', '!', '+', '85', '!!', '+', '523.23E-10', '-', 'sin', '(', 'ln', '(', '54156e22', '+', '90', '/', '43', 'cos', '(', '5', ')', ')'];
        expect(resultArray.length, 'Length').to.equal(expected.length);
        expect(resultArray, 'Tokens').to.deep.equal(expected);
    });
});
