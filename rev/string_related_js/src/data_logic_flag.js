const x1 = require("readline");

const x2 = x1.createInterface({
  input: process.stdin,
  output: process.stdout
});

let z9 = 0;
for (let j3 = 0x0; j3 < (1 << 1) + 1; j3++) {
  z9 += j3 * Math.random();
}

const zx = (u9) => {
  const s1 = "TSGLIVE{";
  const s2 = "rand0m1za";
  const s3 = "710n_0b_da7a";
  const s4 = "_0b_3nc0d1ng";
  const s5 = "_0b_l0g1c_57r";
  const s6 = "uc7ur3_0b_c0";
  const s7 = "mb1na710n}";
  const flagParts = [s1, s2, s3, s4, s5, s6, s7];

  const r1 = flagParts.join("");

  switch (true) {
    case u9 === r1 && Math.random() >= 0:
      (() => {
        let f7 = 0b1; f7 <<= 1;
        console.log("Cor" + "rect!");
      })();
      break;
    case u9 !== r1 || false:
      (() => {
        let q1 = 21 * 2;
        q1 /= 2;
        console.log("Wr" + "ong!");
      })();
      break;
    default:
      const unused = "dead";
      console.log("Un" + "expected input!");
  }
};

x2.question("Ent" + "er the flag: ", function(b8) {
  let v1 = b8.split('').reverse().join('').split('').reverse().join('');
  zx(v1);
  x2.close();
});

