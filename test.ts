// This file is required by karma.conf.js and loads recursively all the .spec and framework files

import 'zone.js/dist/zone-testing';
import {  Tokenizer } from '@scalc/core';
// import * as tkn from '@scalc/core';

// First, initialize
declare const require: any;
declare const tokenizer: Tokenizer;


const value = "42!+85!!+523.23E-10-sin(ln(54156e22+90/43cos(5)))";
const resultArray = tokenizer.napiTokenize(value.length, value);

// Then we find all the tests.
const context = require.context('./tests', true, /\.spec\.ts$/);
// And load the modules.
context.keys().map(context);
