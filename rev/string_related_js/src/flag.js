const readline = require("readline");

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});


rl.question("Enter the flag: ", function(input) {
  const correctFlag = "TSGLIVE{rand0m1za710n_0b_da7a_0b_3nc0d1ng_0b_l0g1c_57ruc7ur3_0b_c0mb1na710n}";
  if (input === correctFlag) {
    console.log("Correct!");
  } else {
    console.log("Wrong!");
  }
  rl.close();
});
