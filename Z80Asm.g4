grammar Z80Asm;
options {
  language = Cpp;
}

program: statement* EOF;

statement
  : label? instruction? EOL // TODO: Make trailing newline optional
  ;

label
  : NAME ':'
  ;

instruction: mnemonic operandList?;

operandList
  : operand (',' operand)*
  ;

operand
  : NAME
  | DEC_INT
  | HEX_INT
  | reg8
  | reg16
  | '(' operand ')'
  ;

reg8
  : A
  | F
  | B
  | C
  | D
  | E
  | H
  | L
  ;

reg16
  : AF
  | BC
  | DE
  | HL
  | IX
  | IY
  | SP
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

// ----REGISTERS----
// 8-bit registers
A: 'a';
F: 'f';
B: 'b';
C: 'c';
D: 'd';
E: 'e';
H: 'h';
L: 'l';

// 16-bit registers
AF: 'af';
BC: 'bc';
DE: 'de';
HL: 'hl';
IX: 'ix';
IY: 'iy';
SP: 'sp';

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

NAME: [a-zA-Z_][a-zA-Z0-9_]*;
DEC_INT: [0-9]+;
HEX_INT: '0x' [0-9a-fA-F]+;
