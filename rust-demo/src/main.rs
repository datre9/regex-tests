use std::fs;
use regex::Regex;
use std::time::Instant;

static mut TO_WRITE: String = String::new();

fn main() {
    let abc1 = fs::read_to_string("../abc1.txt").expect("error");
    let abc2 = fs::read_to_string("../abc2.txt").expect("error");
    let abc3 = fs::read_to_string("../abc3.txt").expect("error");

    let regexKMP = Regex::new("(ab)+").unwrap();
    let regexAC = Regex::new("ac|aca|cab|ab").unwrap();
    let regexSS = Regex::new("(a|b)(b|c)").unwrap();
    let regexWC = Regex::new("a..b..c..").unwrap();
    let regexNE = Regex::new("d").unwrap();
    

    benchmark(&abc1, &regexKMP, "KMP1".to_string());
    benchmark(&abc2, &regexKMP, "KMP2".to_string());
    benchmark(&abc3, &regexKMP, "KMP3".to_string());

    benchmark(&abc1, &regexAC, "AC1".to_string());
    benchmark(&abc2, &regexAC, "AC2".to_string());
    benchmark(&abc3, &regexAC, "AC3".to_string());

    benchmark(&abc1, &regexSS, "SS1".to_string());
    benchmark(&abc2, &regexSS, "SS2".to_string());
    benchmark(&abc3, &regexSS, "SS3".to_string());
    
    benchmark(&abc1, &regexWC, "WC1".to_string());
    benchmark(&abc2, &regexWC, "WC2".to_string());
    benchmark(&abc3, &regexWC, "WC3".to_string());
    
    benchmark(&abc1, &regexNE, "NE1".to_string());
    benchmark(&abc2, &regexNE, "NE2".to_string());
    benchmark(&abc3, &regexNE, "NE3".to_string());
    
    
    fs::write("rust_results.csv", unsafe { TO_WRITE.clone() }).expect("error");
}

fn benchmark(text:&str, regex:&Regex, title:String) {
    unsafe { TO_WRITE.push_str(&format!("{}\n", title)) };
    
    for _ in 0..1000 {
        let start = Instant::now();
    
        // the original version seems to have significant overhead
        // probably caused by the memory allocation of the results
        // this should be in line with the other tests which also don't save the results
        // let _matches: Vec<_> = regex.find_iter(&text).collect();
        let _ = regex.find_iter(&text).count();
    
        let duration = Instant::now().duration_since(start).as_nanos() as f64 / 1000000.0;
    
        unsafe { TO_WRITE.push_str(&format!("{}\n", duration)) };    
    }
}