const fs = require("fs");

const data = require("./data.json");
const dataKey = "terminals";
const text = `temp = calloc(1, sizeof(int));\n*temp = _COUNTER_;\ninsert_into_map(map, "_NAME_", temp);\n\n`;
const file_name = `${dataKey}_map_c.txt`;

let res = "";
let count = 0;

if (data[dataKey] == undefined) {
  throw new Error(`Data for ${dataKey} not found.`);
}

for (const key of data[dataKey]) {
  const str = text.replace("_COUNTER_", count).replace("_NAME_", key);
  res += str;
  count++;
}

fs.writeFile(file_name, res, (err) => {
  if (err) throw err;
  console.log(`${file_name} saved.`);
});
