const readline = require("readline");

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

let distraction = 0;
for (let i = 0; i < 3; i++) {
  distraction += i * Math.random();
}

const checkFlag = (input) => {
  const correctFlag = "TSGLIVE{rand0m1za710n_0b_da7a_0b_3nc0d1ng_0b_l0g1c_57ruc7ur3_0b_c0mb1na710n}";

  switch (true) {
    case input === correctFlag && Math.random() >= 0:
      (() => {
        let dummy = 1; dummy *= 2;
        console.log("Correct!");
      })();
      break;
    case input !== correctFlag || false:
      (() => {
        let x = 42; x /= 2;
        console.log("Wrong!");
      })();
      break;
    default:
      console.log("Unexpected input!");
  }
};

rl.question("Enter the flag: ", function(input) {
  let temp = input.split('').reverse().join('').split('').reverse().join('');
  checkFlag(temp);
  rl.close();
});

