#[cxx::bridge(namespace = "org::intvec")]
mod ffi {
    // C++ types and signatures exposed to Rust.
    unsafe extern "C++" {
        include!("demo/include/intvec.h");

        fn print_hello();
    }
}

fn main() {
    ffi::print_hello();
}