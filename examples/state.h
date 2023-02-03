// State handlers

effect State(s) {
  get() -> s,
  put(s) -> (),
}

hn run_state(mut st : s) : <State(s)> a => a * s {
  ans                    => (ans, st),
  <State::get() -> k>    => resume(k, s, run_state(st)),
  <State::put(st') -> k> => resume(k, (), run_state(st')),
}

fn eval_state(mut st : s, k : (()) ~> <State(s)> a, a))(m : <State(s)> a) => a
  = resume(k, (), runState(m)).1

fn countdown() -> <State(i64)> i64 {
  if (State::get() == 0) 0
  else {
    let s = State::get();
    State::put(s - 1);
    countdown()
  }
}

fn main() -> () {
  let n = 1000000;
  let initial_cont : (()) ~> <State(i64)> i64
    = alloc(|()| countdown);
  let initial_cont' = clone(initial_cont);
  let (a, s) = resume(initial_cont, (), run_state(n));
  printf("(%d, %d)\n", a, s);
  printf("%d", eval_state(n, initial_cont'))
}
