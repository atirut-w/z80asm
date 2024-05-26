grammar Z80Asm;
options {
  language = Cpp;
}

program: statement* EOF;

statement
  : label? instruction? EOL // TODO: Make trailing newline optional
  ;

label
  : ID ':'
  ;

instruction: ID operandList?;

operandList
  : operand (',' operand)*
  ;

operand
  : ID
  | INT
  | HEXINT
  | '(' operand ')'
  ;

// Some basic building blocks
WHITESPACE: [ \t]+ -> skip;
EOL: '\r'? '\n'; // Keep newlines to properly parse statements
COMMENT: ';' ~[\r\n]* -> skip;

ID: [a-zA-Z_][a-zA-Z0-9_]*;
INT: [0-9]+;
HEXINT: '0x' [0-9a-fA-F]+;
