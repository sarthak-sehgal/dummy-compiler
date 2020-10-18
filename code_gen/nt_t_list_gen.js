const fs = require("fs");
const path = require("path");
let data = fs.readFileSync(path.resolve(__dirname, "../grammar.txt"), "utf8");
const file_name = `nt_t_list.txt`;

let terminalMap = {},
  nonterminalMap = {};

if (data == undefined) {
  throw new Error(`Data not found.`);
}

const grammar = data.replace(/\n/g, " ").split(" ");

for (const str of grammar) {
  if (str[0] >= "a") terminalMap[str] = true;
  else nonterminalMap[str] = true;
}

const terminals = Object.keys(terminalMap)
  .map((k) => `"${k}"`)
  .join(", ");
const nonterminals = Object.keys(nonterminalMap)
  .map((k) => `"${k}"`)
  .join(", ");

const res = terminals + "\n\n" + nonterminals;

fs.writeFile(path.resolve(__dirname, file_name), res, (err) => {
  if (err) throw err;
  console.log(`${file_name} saved.`);
});
