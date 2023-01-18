// The type structure of H
#[derive(Debug)]
pub struct FunctionType {
    pub domain: Vec<Type>,
    pub codomain: Box<ComputationType>,
}

#[derive(Debug)]
pub struct HandlerType {
    pub domain: Box<ComputationType>,
    pub codomain: Box<ComputationType>,
}

#[derive(Debug)]
pub struct ParameterisedHandlerType {
    pub parameters: Vec<Type>,
    pub type_: HandlerType,
}

#[derive(Debug)]
pub struct ComputationType {
    pub effect: Option<EffectType>,
    pub type_: Type,
}

#[derive(Debug)]
pub struct EffectType {
    pub name: &'static str,
    pub operations: Vec<Operation>,
}

#[derive(Debug)]
pub struct Operation {
    pub label: &'static str,
    pub type_: OperationType,
}

#[derive(Debug)]
pub struct OperationType {
    pub domain: Vec<Type>,
    pub codomain: Type,
}

#[derive(Debug)]
pub enum Type {
    Unit,
    I64,
    Fun(FunctionType),
    Tuple(Vec<Type>),
}

pub trait ToString {
    fn to_string(&self) -> String;
}

fn to_string_vec<T: ToString>(vs: &Vec<T>) -> String {
    vs.iter().map(|v| v.to_string()).collect::<Vec<_>>().join(", ")
}


impl ToString for Type {
    fn to_string(&self) -> String {
        match self {
            Type::Unit => format!("()"),
            Type::I64 => format!("i64"),
            Type::Fun(ft) => ToString::to_string(ft),
            Type::Tuple(xs) => format!("({})", to_string_vec(xs)),
        }
    }
}

impl ToString for FunctionType {
    fn to_string(&self) -> String {
        format!("({}) -> {}", to_string_vec(&self.domain), ToString::to_string(&*self.codomain))
    }
}

impl ToString for ComputationType {
    fn to_string(&self) -> String {
        ToString::to_string(&self.type_)
    }
}

pub fn type_to_string(ty : Type) -> String {
    ToString::to_string(&ty)
}
