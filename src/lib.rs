enum TokenizerState {
    NORMAL,
    STRING,
    COMMENT,
}

pub struct TokenizerError {
    pub message: String,
    pub line: u32,
    pub column: u32,
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

    pub fn tokenize(&mut self, source: String) -> Result<(), TokenizerError> {
        Ok(())
    }
}
