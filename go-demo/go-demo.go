package main

import (
	"bytes"
	"fmt"
	"os"
	"regexp"
	"time"
)

func main() {
	s, err := os.ReadFile("../adventures-of-huckleberry-finn.txt")
	if err != nil {
		fmt.Println(err)
	}
	var toWrite bytes.Buffer
	toWrite.WriteString("id;time(ns);memory(B)\n")
	regex := regexp.MustCompile("Finn|Huckleberry")

	for i := 0; i < 1000; i++ {
		start := time.Now()

		regex.FindAll(s, -1)

		elapsed := time.Since(start)
		toWrite.WriteString(fmt.Sprintf("%d;%d;0\n", i, elapsed.Nanoseconds()))
	}

	os.WriteFile("results.csv", toWrite.Bytes(), 0644)
}
