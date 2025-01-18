use std::fs;
use regex::Regex;
use std::time::Instant;

static mut TO_WRITE: String = String::new();
fn main() {
    let abc1 = fs::read_to_string("../abc1.txt").expect("error");
    let abc2 = fs::read_to_string("../abc2.txt").expect("error");
    let abc3 = fs::read_to_string("../abc3.txt").expect("error");

    let regexKMP = Regex::new("(ab)+").unwrap();
    

    benchmark(&abc1, &regexKMP, "KMP1".to_string());
    benchmark(&abc2, &regexKMP, "KMP2".to_string());
    benchmark(&abc3, &regexKMP, "KMP3".to_string());

    
    fs::write("results.csv", unsafe { TO_WRITE.clone() }).expect("error");
}
fn benchmark(text:&str, regex:&Regex, title:String) {
    unsafe { TO_WRITE.push_str(&format!("{}\n", title)) };
    
    for _ in 0..1000 {
        let start = Instant::now();
    
        //the original version seems to have significant overhead
        //probably caused by the memory allocation of the results
        //this should be in line with the other tests which also don't save the results
        //let _matches: Vec<_> = regex.find_iter(&text).collect();
        let _ = regex.find_iter(&text).count();
    
        let duration = Instant::now().duration_since(start).as_nanos();
    
        unsafe { TO_WRITE.push_str(&format!("{}\n", duration)) };    
    }
}