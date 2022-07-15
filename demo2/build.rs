fn main() {
    cxx_build::bridge("src/main.rs")
        .file("src/intvec.cc")
        .flag_if_supported("-std=c++14")
        .compile("intvec");

    println!("cargo:rerun-if-changed=src/main.rs");
    println!("cargo:rerun-if-changed=src/intvec.cc");
    println!("cargo:rerun-if-changed=include/intvec.h");
}
