use std::fs;
use regex::Regex;
use std::time::Instant;
use memory_stats::memory_stats;

fn main() {
    let string = fs::read_to_string("../adventures-of-huckleberry-finn.txt").expect("error");
    let mut to_write = String::with_capacity(1000 * 30);
    to_write.push_str("id;time(ns)\n");
    let pattern = Regex::new("Finn|Huckleberry").unwrap();
    
    for i in 0..1000 {
        let mut mem1 = 0;
        let mut mem2 = 0;

        if let Some(usage) = memory_stats() {
            mem1 = usage.physical_mem;
        }
        let start = Instant::now();

        let _matches: Vec<_> = pattern.find_iter(&string).collect();

        let duration = Instant::now().duration_since(start).as_nanos();
        if let Some(usage) = memory_stats() {
            mem2 = usage.physical_mem;
        }
        let diff = mem2 - mem1;
    
        to_write.push_str(&format!("{};{};{}\n", i, duration, diff));    
    }

    fs::write("results.csv", to_write).expect("error");
}