const fs = require('fs')

let toWrite = ''

const abc1 = fs.readFileSync('../abc1.txt', 'utf-8')
const abc2 = fs.readFileSync('../abc2.txt', 'utf-8')
const abc3 = fs.readFileSync('../abc3.txt', 'utf-8')

const regexKMP = RegExp('(ab)+', 'g')


benchmark(abc1, regexKMP, 'KMP1')
benchmark(abc2, regexKMP, 'KMP2')
benchmark(abc3, regexKMP, 'KMP3')


fs.writeFileSync('output.csv', toWrite)



function benchmark(text, regex, title) {
    toWrite += title + '\n'

    for (let i = 0; i < 1000; i++) {
        const start = performance.now()
    
        text.match(regex)
    
        const end = performance.now()
    
        toWrite += Math.round((end - start) * 1000000) + '\n'
    }
}