const fs = require('fs')

const string = fs.readFileSync('../adventures-of-huckleberry-finn.txt', 'utf-8')
let toWrite = 'id;time(ns);memory(B)\n'
const regex = RegExp('Finn|Huckleberry', 'g')

for (let i = 0; i < 1000; i++) {
    const start = performance.now()

    string.match(regex)

    const end = performance.now()

    toWrite += i + ';' + Math.round((end - start) * 1000000) + ';0\n'
}

fs.writeFileSync('output.csv', toWrite)