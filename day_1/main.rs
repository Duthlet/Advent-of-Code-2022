use std::io;

fn sum() -> i32 {
    let mut my_sum:i32 = 0;
    loop {
        let mut my_string = String::new();
        io::stdin().read_line(&mut my_string).expect("read_line failed");
        if my_string.trim() == "" { break; }
        my_sum += my_string.trim().parse::<i32>().unwrap();
    }
    my_sum
}

fn main () {
    println!("Hello, world!");
    let mut max_1:i32 = 0;
    let mut max_2:i32 = 0;
    let mut max_3:i32 = 0;
    let mut cur:i32 = 0;

    loop {
        cur = sum();
        if cur == 0 { break; }
        if cur > max_1 {
            max_3 = max_2;
            max_2 = max_1;
            max_1 = cur;
        } else if cur > max_2 {
            max_3 = max_2;
            max_2 = cur;
        } else if cur > max_3 {
            max_3 = cur;
        }
    }
    println!("{}", max_1 + max_2 + max_3);
}
