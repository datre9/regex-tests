package main

import (
	"bytes"
	"fmt"
	"os"
	"regexp"
	"strconv"
	"time"
)

var toWrite bytes.Buffer

func main() {
	abc1, err := os.ReadFile("../abc1.txt")
	abc2, err := os.ReadFile("../abc2.txt")
	abc3, err := os.ReadFile("../abc3.txt")
	if err != nil {
		fmt.Println(err)
	}

	regexKMP := regexp.MustCompile("(ab)+")
	regexAC := regexp.MustCompile("ac|aca|cab|ab")
	regexSS := regexp.MustCompile("(a|b)(b|c)")
	regexWC := regexp.MustCompile("a..b..c..")
	regexNE := regexp.MustCompile("d")

	benchmark(abc1, regexKMP, "KMP1")
	benchmark(abc2, regexKMP, "KMP2")
	benchmark(abc3, regexKMP, "KMP3")

	benchmark(abc1, regexAC, "AC1")
	benchmark(abc2, regexAC, "AC2")
	benchmark(abc3, regexAC, "AC3")

	benchmark(abc1, regexSS, "SS1")
	benchmark(abc2, regexSS, "SS2")
	benchmark(abc3, regexSS, "SS3")

	benchmark(abc1, regexWC, "WC1")
	benchmark(abc2, regexWC, "WC2")
	benchmark(abc3, regexWC, "WC3")

	benchmark(abc1, regexNE, "NE1")
	benchmark(abc2, regexNE, "NE2")
	benchmark(abc3, regexNE, "NE3")

	os.WriteFile("go_results.csv", toWrite.Bytes(), 0644)
}

func benchmark(text []byte, regex *regexp.Regexp, title string) {
	toWrite.WriteString(fmt.Sprintf("%s\n", title))

	for i := 0; i < 1000; i++ {
		start := time.Now()

		regex.FindAll(text, -1)

		elapsed := time.Since(start)
		toWrite.WriteString(fmt.Sprintf("%s\n", strconv.FormatFloat((float64)(elapsed.Nanoseconds())/1000000, 'f', -1, 64)))
	}
}
