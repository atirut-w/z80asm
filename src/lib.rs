enum TokenizerState {
    NORMAL,
    CONSUME_UNTIL,
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
    until_char: char,
    eol_ends_consume: bool,

    line: u32,
    column: u32,
}

impl Tokenizer {
    pub fn new() -> Tokenizer {
        Tokenizer {
            tokens: Vec::new(),
            current_token: String::new(),
            state: TokenizerState::NORMAL,
            until_char: '\0',
            eol_ends_consume: true,
            line: 1,
            column: 1,
        }
    }

    pub fn tokenize(&mut self, source: String) -> Result<(), TokenizerError> {
        let mut offset = 0;

        for _ in source.chars() {
            let c = match source.chars().nth(offset) {
                Some(c) => c,
                None => break,
            };
            match self.state {
                TokenizerState::NORMAL => match c {
                    '\r' => {
                        self.push_token();
                        if source.chars().nth(offset + 1) != Some('\n') {
                            offset += 1;
                        }
                    }
                    '\n' => {
                        self.push_token();
                        self.line += 1;
                        self.column = 1;
                    }
                    ';' => {
                        self.push_token();
                        self.state = TokenizerState::CONSUME_UNTIL;
                        self.until_char = '\0';
                        self.eol_ends_consume = true;
                    }
                    _ => {
                        if !c.is_whitespace() {
                            self.current_token.push(c);
                        } else {
                            self.push_token();
                        }
                        self.column += 1;
                    }
                },
                TokenizerState::CONSUME_UNTIL => match c {
                    '\r' => {
                        self.push_token();
                        if source.chars().nth(offset + 1) != Some('\n') {
                            offset += 1;
                        }
                    }
                    '\n' => {
                        if self.eol_ends_consume {
                            self.push_token();
                            self.state = TokenizerState::NORMAL;
                        }
                        self.line += 1;
                        self.column = 1;
                    }
                    _ => {}
                },
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
