enum TokenizerState {
    NORMAL,
    STRING,
    COMMENT,
}

struct TokenizerError {
    message: String,
    line: u32,
    column: u32,
}

pub struct Tokenizer {
    pub tokens: Vec<String>,
    current_token: String,
    state: TokenizerState,
}

impl Tokenizer {
    pub fn new() -> Tokenizer {
        Tokenizer {
            tokens: Vec::new(),
            current_token: String::new(),
            state: TokenizerState::NORMAL,
        }
    }
}
