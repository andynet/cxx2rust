#[cxx::bridge(namespace = "org::intvec")]
mod ffi {
    // C++ types and signatures exposed to Rust.
    unsafe extern "C++" {
        include!("demo2/include/intvec.h");

        type IntVector;
        fn new_int_vector(size: u64, default_val: u64, width: u64) -> UniquePtr<IntVector>;
        fn size(&self) -> u64;
        fn width(&self) -> u8;
    }
}

fn main() {
    let size: u64 = 10;
    let width: u64 = 5;
    let mut v = ffi::new_int_vector(size, 0, width);

    // for i in 0..size {
    //     v[i] = i;
    // }

    println!("created int_vector<> containing {} {}-bit integers", v.size(), v.width());

    // for i in 0..size {
    //     println!("v[{}]={}", i, v[i]);
    // }

}