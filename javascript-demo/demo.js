const fs = require('fs')

let toWrite = ''

const abc1 = fs.readFileSync('../abc1.txt', 'utf-8')
const abc2 = fs.readFileSync('../abc2.txt', 'utf-8')
const abc3 = fs.readFileSync('../abc3.txt', 'utf-8')

const regexKMP = RegExp('abacab', 'g')
const regexAC = RegExp("ac|aca|cab|ab", 'g')
const regexSS = RegExp("(a|b)(b|c)", 'g')
const regexWC = RegExp("a..b..c..", 'g')


benchmark(abc1, regexKMP, 'KMP1')
benchmark(abc2, regexKMP, 'KMP2')
benchmark(abc3, regexKMP, 'KMP3')

benchmark(abc1, regexAC, "AC1")
benchmark(abc2, regexAC, "AC2")
benchmark(abc3, regexAC, "AC3")

benchmark(abc1, regexSS, "SS1")
benchmark(abc2, regexSS, "SS2")
benchmark(abc3, regexSS, "SS3")

benchmark(abc1, regexWC, "WC1")
benchmark(abc2, regexWC, "WC2")
benchmark(abc3, regexWC, "WC3")


fs.writeFileSync('js_results.csv', toWrite)



function benchmark(text, regex, title) {
    toWrite += title + '\n'

    for (let i = 0; i < 1000; i++) {
        const start = performance.now()
    
        text.match(regex)
    
        const end = performance.now()
    
        toWrite += Math.round((end - start) * 1000000) / 1000000 + '\n'
    }
}