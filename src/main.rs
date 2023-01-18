use syntax::types::*;

fn main() {
    let type_ = Type::Fun(FunctionType {
        domain: vec![Type::I64, Type::I64, Type::Unit],
        codomain: Box::new(ComputationType {
            effect: None,
            type_: Type::I64,
        }),
    });
    println!("{}", type_to_string(type_));
}
