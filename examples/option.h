// Catch exceptions
type Option(a) {
  None,
  Some(a),
}

fn string_of_option(f: (a) -> String, x: Option(a)) -> String {
  match x {
    None => "None",
    Some(x') => String::concat("Some", String::concat("(", String::concat(f(x'), ")")))
  }
}

effect Exn {
  abort : a. () -> a,
}

hn optionalise : <Exn> a => Option(a) {
  ans => Some(ans),
  <Exn::abort() -> k> => /* todo drop k */ None,
}

fn example() -> <Exn> i64 {
  40 + abort() + 2
}

fn main() -> () {
  let initial_cont : (()) ~> <Exn> i64 = alloc(|()|example);
  let ans = resume(initial_cont, (), optionalise);
  printf(string_of_option(Int::to_string, ans))
}
