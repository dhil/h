// UNIX style pipes

effect Sender(s) {
  send(s) -> (),
}

effect Receiver(r) {
  recv() -> r,
}

rec {
  hn hpipe(sender: () ~> <Sender(s)> a) : <Receiver(s)> a => a {
     ans => ans, // TODO add some drop primitive for `sender'.
     <recv() -> receiver> => resume(sender, (), hcopipe(receiver))
  }

  hn hcopipe(receiver: (s) ~> <Receiver(s)> a) : <Sender(s)> a => a {
     ans => ans, // TODO add some drop primitive for `receiver'.
     <send(s) -> sender> => resume(receiver, s, hpipe(sender))
  }
}

fn nats(n) -> <Sender(i64)> () {
  Sender.send(n); nats(n+1)
}

fn print_nats(n) -> <Receiver(i64)> () {
  if (n == 0) printf("0")
  else {
    let nat = Receiver.recv();
    printf("%d", nat);
    print_nats(n-1)
  }
}

fn main() -> () {
  let sender: () ~> <Sender(i64)> () = alloc(|| nats(0));
  let receiver: (i64, i64) ~> <Receiver(i64)> () = alloc(print_nats);
  resume(receiver, 32, hpipe(sender))
}
