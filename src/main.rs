use clap::Parser as ClapParser;
use std::path::PathBuf;

#[derive(ClapParser)]
struct Args {
    /// Input file
    input: PathBuf,

    /// Output file
    #[clap(short, long, default_value = "a.elf")]
    output: Option<PathBuf>,
}

fn main() {
    let args = Args::parse();
}
