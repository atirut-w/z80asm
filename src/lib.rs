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

pub struct Token {
    pub string: String,
    pub line: u32,
    pub column: u32,
}

pub struct Tokenizer {
    pub tokens: Vec<Token>,
    current_token: String,
    state: TokenizerState,

    line: u32,
    column: u32,
}

impl Tokenizer {
    pub fn new() -> Tokenizer {
        Tokenizer {
            tokens: Vec::new(),
            current_token: String::new(),
            state: TokenizerState::NORMAL,
            line: 1,
            column: 1,
        }
    }

    pub fn tokenize(&mut self, source: String) -> Result<(), TokenizerError> {
        let mut offset = 0;

        for c in source.chars() {
            match self.state {
                TokenizerState::NORMAL => {
                    match c {
                        '\r' => {
                            if source.chars().nth(offset + 1) == Some('\n') {
                                self.push_token();
                                self.line += 1;
                                self.column = 1;
                                offset += 1;
                            }
                        }
                        '\n' => {
                            self.push_token();
                            self.line += 1;
                            self.column = 1;
                        }
                        _ => {
                            if !c.is_whitespace() {
                                self.current_token.push(c);
                            } else {
                                self.push_token();
                            }
                            self.column += 1;
                        }
                    }
                }
                _ => unimplemented!("Tokenizer state not implemented"),
            };
            offset += 1;
        }

        Ok(())
    }

    fn push_token(&mut self) {
        if !self.current_token.is_empty() {
            self.tokens.push(Token {
                string: self.current_token.clone(),
                line: self.line,
                column: self.column - self.current_token.len() as u32,
            });
            self.current_token.clear();
        }
    }
}
