
#![crate_type="dylib"]

#[no_mangle] 
pub extern fn lib_hello_test() {
  println!("Hello from rust");
}
