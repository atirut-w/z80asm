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

instruction: mnemonic operandList?;

operandList
  : operand (',' operand)*
  ;

operand
  : ID
  | INT
  | HEXINT
  | '(' operand ')'
  ;

mnemonic
  : LD
  | PUSH
  | POP
  | EX
  | EXX
  | LDI
  | LDIR
  | LDD
  | LDDR
  | CPI
  | CPIR
  | CPD
  | CPDR
  | ADD
  | ADC
  | SUB
  | SBC
  | AND
  | OR
  | XOR
  | CP
  | INC
  | DEC
  | DAA
  | CPL
  | NEG
  | CCF
  | SCF
  | NOP
  | HALT
  | DI
  | EI
  | IM
  | RLCA
  | RLA
  | RRCA
  | RRA
  | RLC
  | RL
  | RRC
  | RR
  | SLA
  | SRA
  | SRL
  | RLD
  | RRD
  | BIT
  | SET
  | RES
  | JP
  | JR
  | DJNZ
  | CALL
  | RET
  | RETI
  | RETN
  | RST
  | IN
  | INI
  | INIR
  | IND
  | INDR
  | OUT
  | OUTI
  | OTIR
  | OUTD
  | OTDR
  ;

// Some basic building blocks
WHITESPACE: [ \t]+ -> skip;
EOL: '\r'? '\n'; // Keep newlines to properly parse statements
COMMENT: ';' ~[\r\n]* -> skip;

ID: [a-zA-Z_][a-zA-Z0-9_]*;
INT: [0-9]+;
HEXINT: '0x' [0-9a-fA-F]+;

// ----INSTRUCTION MNEUMONICS----
// N-bit Load Group
LD: 'ld';
PUSH: 'push';
POP: 'pop';

// Exchange, Block Transfer, and Search Group
EX: 'ex';
EXX: 'exx';
LDI: 'ldi';
LDIR: 'ldir';
LDD: 'ldd';
LDDR: 'lddr';
CPI: 'cpi';
CPIR: 'cpir';
CPD: 'cpd';
CPDR: 'cpdr';

// N-bit Arithmetic Group
ADD: 'add';
ADC: 'adc';
SUB: 'sub';
SBC: 'sbc';
AND: 'and';
OR: 'or';
XOR: 'xor';
CP: 'cp';
INC: 'inc';
DEC: 'dec';

// General-Purpose Arithmetic and CPU Control Group
DAA: 'daa';
CPL: 'cpl';
NEG: 'neg';
CCF: 'ccf';
SCF: 'scf';
NOP: 'nop';
HALT: 'halt';
DI: 'di';
EI: 'ei';
IM: 'im';

// Rotate and Shift Group
RLCA: 'rlca';
RLA: 'rla';
RRCA: 'rrca';
RRA: 'rra';
RLC: 'rlc';
RL: 'rl';
RRC: 'rrc';
RR: 'rr';
SLA: 'sla';
SRA: 'sra';
SRL: 'srl';
RLD: 'rld';
RRD: 'rrd';

// Bit Set, Reset, and Test Group
BIT: 'bit';
SET: 'set';
RES: 'res';

// Jump Group
JP: 'jp';
JR: 'jr';
DJNZ: 'djnz';

// Call and Return Group
CALL: 'call';
RET: 'ret';
RETI: 'reti';
RETN: 'retn';
RST: 'rst';

// Input and Output Group
IN: 'in';
INI: 'ini';
INIR: 'inir';
IND: 'ind';
INDR: 'indr';
OUT: 'out';
OUTI: 'outi';
OTIR: 'otir';
OUTD: 'outd';
OTDR: 'otdr';
