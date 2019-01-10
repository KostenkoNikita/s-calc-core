const tokenizerModule = require("./binding.js");

// const value = "42! +  85!!   +523.23E-10 - sin(ln(54156e22  +  90/43cos(5)))";
const value = "42!+85!!+523.23E-10-sin(ln(54156e22+90/43cos(5)))";
const resultArray = tokenizerModule.napiTokenize(value.length, value);
console.log(resultArray);
