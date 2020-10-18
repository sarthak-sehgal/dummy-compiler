const fs = require("fs");
const path = require("path");
let data = fs.readFileSync(path.resolve(__dirname, "../grammar.txt"), "utf8");
const file_name = `entities.txt`;

let terminalMap = {},
  nonterminalMap = {};

if (data == undefined) {
  throw new Error(`Data not found.`);
}

const grammar = data.replace(/\n/g, " ").split(" ");

for (const str of grammar) {
  if (str[0] >= "a") nonterminalMap[str] = true;
  else terminalMap[str] = true;
}

const terminals = Object.keys(terminalMap).join(", ");
const terminalCnt = Object.keys(terminalMap).length;
const nonterminals = Object.keys(nonterminalMap).join(", ");
const nonterminalCnt = Object.keys(nonterminalMap).length;

let res = `Terminal Count: ${terminalCnt}\n${terminals}`;
res += `\n\nNonterminal Count: ${nonterminalCnt}\n\n${nonterminals}`;

fs.writeFile(path.resolve(__dirname, file_name), res, (err) => {
  if (err) throw err;
  console.log(`${file_name} saved.`);
});
