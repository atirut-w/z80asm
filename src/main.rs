use clap::Parser;
use std::path::PathBuf;
use z80asm::Tokenizer;

#[derive(Parser)]
struct Args {
    /// Input file
    input: PathBuf,

    /// Output file
    #[clap(short, long)]
    output: Option<PathBuf>,
}

fn main() {
    let args = Args::parse();

    let source = match std::fs::read_to_string(args.input) {
        Ok(source) => source,
        Err(e) => {
            eprintln!("Error reading file: {}", e);
            std::process::exit(1);
        }
    };

    let mut tokenizer = Tokenizer::new();
    match tokenizer.tokenize(source) {
        Ok(_) => {
            println!("Tokens: {:?}", tokenizer.tokens);
        }
        Err(e) => {
            eprintln!("{} on {}:{}", e.message, e.line, e.column);
            std::process::exit(1);
        }
    }
}
