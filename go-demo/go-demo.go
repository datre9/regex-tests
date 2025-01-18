package main

import (
	"bytes"
	"fmt"
	"os"
	"regexp"
	"time"
)

var toWrite bytes.Buffer

func main() {
	abc1, err := os.ReadFile("../abc1.txt")
	if err != nil {
		fmt.Println(err)
	}
	abc2, err := os.ReadFile("../abc2.txt")
	if err != nil {
		fmt.Println(err)
	}
	abc3, err := os.ReadFile("../abc3.txt")
	if err != nil {
		fmt.Println(err)
	}

	regexKMP := regexp.MustCompile("(ab)+")

	benchmark(abc1, regexKMP, "KMP1")
	benchmark(abc2, regexKMP, "KMP2")
	benchmark(abc3, regexKMP, "KMP3")

	os.WriteFile("results.csv", toWrite.Bytes(), 0644)
}

func benchmark(text []byte, regex *regexp.Regexp, title string) {
	toWrite.WriteString(fmt.Sprintf("%s\n", title))

	for i := 0; i < 1000; i++ {
		start := time.Now()

		regex.FindAll(text, -1)

		elapsed := time.Since(start)
		toWrite.WriteString(fmt.Sprintf("%d\n", elapsed.Nanoseconds()))
	}
}
