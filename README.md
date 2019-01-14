# s-calc-core

Core calculator library based on postfix notation
=========

A small library executes mathematical expressions.

## Installation

  Core js: 
  `npm install scalc/core`
  Types: 
  `npm install @scalc/core`

## Usage
    JS:
    `var core = require('scalc/core');
    var formattedNum = core.napiTokenize('33+22*44');`

        JS:
    `import { napiTokenize } from 'scalc/core';
    let formattedNum = napiTokenize('33+22*44');`
  
  
  Output should be `[ '33', '+', '22', '*', '44' ]`


## Tests

  `npm test`

## Contributing

In lieu of a formal style guide, take care to maintain the existing coding style. Add unit tests for any new or changed functionality. Lint and test your code.