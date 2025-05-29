const crypto = require('crypto');

// 使用するキーとIV
const passphrase = "tewklwe";
const key = crypto.createHash('sha256').update(passphrase).digest();

const ivSource = ["c", "a", "t", "i", "o", "n", "b", "u", "s", "f", "o", "c", "a", "t", "e", "x"];
const ivBytes = ivSource.map(ch => ch.charCodeAt(0));
const iv = Buffer.from(ivBytes);

// AES暗号化関数
function encodeAES(text, key, iv) {
  const cipher = crypto.createCipheriv('aes-256-cbc', key, iv);
  let encrypted = cipher.update(text, 'utf8', 'base64');
  encrypted += cipher.final('base64');
  return encrypted;
}

// 暗号化対象
const original1 = "Ente";
const original2 = "r the ";

console.log("Encrypted1:", original1, " -> ", encodeAES(original1, key, iv));
console.log("Encrypted2:", original2, " -> ", encodeAES(original2, key, iv));
