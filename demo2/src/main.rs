#[cxx::bridge]
mod sdslrs {
    unsafe extern "C++" {
        include!("demo2/include/intvec.h");

        type IntVector;

        fn new_intvec(size: u64, defval: u64, width: u8) -> UniquePtr<IntVector>;
        fn size(&self) -> u64;
        fn width(&self) -> u8;

        fn test_ptr(v: &UniquePtr<IntVector>);
    }
}

fn main() {
    let v = sdslrs::new_intvec(20, 0, 4);
    sdslrs::test_ptr(&v);

    // for i in 0..size {
    //     v[i] = i;
    // }

    println!("created int_vector<> containing {} {}-bit integers", v.size(), v.width());

    // for i in 0..size {
    //     println!("v[{}]={}", i, v[i]);
    // }
}