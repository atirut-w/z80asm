use clap::Parser;
use std::path::PathBuf;

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
}
