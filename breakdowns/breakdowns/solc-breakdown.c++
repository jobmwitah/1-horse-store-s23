// 0x6080604052348015600e575f80fd5b5060a58061001b5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea2646970667358221220eb5422d447074be5a04b169897f75fdc3b3086d0d032945e3da0287762b79c8464736f6c63430008140033

// 1. Contract Creation Code

// --> Solidity free Memory pointer!
// PUSH1 0x80
// PUSH1 0x40
// MSTORE

// --> What does chunk do?
// --> If someone calls this contract with a value, it will revert!
// --> Otherwise, jump, to continue execution >>>
// CALLVALUE    --> checks msg.value
// DUP1         --> duplicate top stack item
// ISZERO       --> returns 1 if the msg.value is 0, 0 otherwise
// PUSH1 0x0e   --> pushes 0x0e to the stack
// JUMPI        --> jumps if the top stack item is 1 to JUMPDEST 0x0e
// PUSH0
// DUP1
// REVERT

// --> Continue if msg.value is 0
// --> Stack runtime code to Chain
// JUMPDEST        --> [msg.value]
// POP             --> []
// PUSH1 0xa5      --> [0xa5]
// DUP1            --> [0xa5, 0xa5]
// PUSH2 0x001b    --> [0x001b, 0xa5, 0xa5]
// PUSH0           --> [0x0, 0x001b, 0xa5, 0xa5]
// CODECOPY        --> [0xa5]
// PUSH0           --> [0x0, 0xa5]
// RETURN          --> []
// INVALID         --> []

// 2. Runtime Code

// PUSH1 0x80
// PUSH1 0x40
// MSTORE

// CALLVALUE
// DUP1
// ISZERO
// PUSH1 0x0e
// JUMPI

// PUSH0
// DUP1
// REVERT

// JUMPDEST       --> [msg.value]
// POP            --> []
// PUSH1 0x04     --> [0x04]
// CALLDATASIZE   --> [calldata_size, 0x04]
// LT             --> [calldata_size < 0x04]
// PUSH1 0x30     --> [0x30, calldata_size <0x04]
// JUMPI          --> []

// PUSH0 0x00        --> [0x00]
// CALLDATALOAD      --> [CALLDATA_32BYTES]
// PUSH1 0xe0        --> [0xe0, CALLDATA_32BYTES]
// SHR               --> [calldata[0:4]] // function selector
// DUP1              --> [func_selector, func_selector]
// PUSH4 0xcdfead2e  --> [0xcdfead2e, func_selector, func_selector]
// EQ                --> [0xcdfead2e == func_selector, func_selector]
// PUSH1 0x34        --> [0x34, 0xcdfead2e == func_selector, func_selector]
// JUMPI             --> [func_selector]
// if func_selector == 0xcdfead2e jump to set_number_of_horses

// DUP1              --> [func_selector, func_selector]
// PUSH4 0xe026c017  --> [0xe026c017, func_selector, func_selector]
// EQ                --> [0xe026c017 == func_selector, func_selector]
// PUSH1 0x45        --> [0x45, 0xe026c017 == func_selector, func_selector]
// JUMPI             --> [func_selector]

// If a function selector isn't found during this dispatch, we can see we've returned to this revert block we used earlier:
// JUMPDEST
// PUSH0
// DUP1
// REVERT

// updateNumberOfHorses jump dest 1
// JUMPDEST     --> [func_selector]
// PUSH1 0x43   --> [0x43, func_selector]
// PUSH1 0x3f   --> [0x3f, 0x43, func_selector]
// CALLDATASIZE --> [calldata_size, 0x3f, 0x43, func_selector]
// PUSH1 0x04   --> [0x04, calldata_size, 0x3f 0x43, func_selector]
// PUSH1 0x59   --> [0x59, 0x04, calldata_size, 0x3f, 0x43, func_selector]
// JUMP         --> [0x04, calldata_size, 0x3f, 0x43, func_selector]]

// updateNumberOfHorses jump dest 4
// JUMPDEST;    --->[CALLDATA[4:], 0x43, func_selector]
// PUSH0;       --->[0x00, CALLDATA[4:], 0x43, func_selector]
// SSTORE;      --->[0x43, func_selector]     // Storage Slot 0: [CALLDATA[4:]]
// JUMP;        --->[func_selector]           // Storage Slot 0: [CALLDATA[4:]]

// JUMPDEST;    --->[func_selector]
// STOP;        --->[]

// readNumberOfHorses jump dest
// JUMPDEST   ---> [func_selector]
// PUSH0      ---> [0x00, func_selector]
// SLOAD        --> [numHorses, func_selector]
// PUSH1 0x40   --> [0x40, numHorses, func_selector]
// MLOAD        --> [0x80, numHorses, func_selector]    Memory: 0x40:0x80
// SWAP1        --> [numHorses, 0x80, func_selector]
// DUP2         --> [0x80, numHorses, 0x80, func_selector]
// MSTORE       --> [0x80, func_selector]               Memory: 0x40:0x80, 0x80:numHorses
// PUSH1 0x20      --> [0x20, 0x80, func_selector]
// ADD             --> [0xa0, func_selector]
// PUSH1 0x40      --> [0x40, 0xa0, func_selector]
// MLOAD           --> [0x80, 0xa0, func_selector]
// DUP1            --> [0x80, 0x80, 0xa0, func_selector]
// SWAP2           --> [0xa0, 0x80, 0x80, func_selector]
// SUB             --> [0xa0 - 0x80, 0x80, func_selector]
// SWAP1           --> [0x80, 0xa0 - 0x80, func_selector]
// RETURN          --> [func_selector]

// updateNumberOfHorses jump dest 2
// JUMPDEST     --> [0x04, calldata_size, 0x3f, 0x43, func_selector]
// PUSH0        --> [0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
// PUSH1 0x20   --> [0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
// DUP3         --> [0x04, 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
// DUP5         --> [calldata_size, 0x04, 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
// SUB          --> [(calldata_size - 0x04), 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
// SLT          --> [(calldata_size - 0x04) < 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
// ISZERO       --> [((calldata_size - 0x04) < 0x20) == 0, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
// PUSH1 0x68   --> [0x68, ((calldata_size - 0x04) < 0x20) == 0, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
// JUMPI        --> [0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]

// PUSH0
// DUP1
// REVERT

// updateNumberOfHorses jump dest 3
// JUMPDEST;            --->[0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
// POP;                 --->[0x04, calldata_size, 0x3f, 0x43, func_selector]
// CALLDATALOAD;        --->[CALLDATA[4:], calldata_size, 0x3f, 0x43, func_selector]
// SWAP2;               --->[0x3f, calldata_size, CALLDATA[4:], 0x43, func_selector]
// SWAP1;               --->[calldata_size, 0x3f, CALLDATA[4:], 0x43, func_selector]
// POP;                 --->[0x3f, CALLDATA[4:], 0x43, func_selector]
// JUMP;                --->[CALLDATA[4:], 0x43, func_selector]

// 3. Metadata
// INVALID
// LOG2
// PUSH5 0x6970667358
// INVALID
// SLT
// KECCAK256
// INVALID
// SLOAD
// INVALID
// INVALID
// SELFBALANCE
// SMOD
// INVALID
// INVALID
// LOG0
// INVALID
// AND
// SWAP9
// SWAP8
// INVALID
// PUSH0
// INVALID
// EXTCODESIZE
// ADDRESS
// DUP7
// INVALID
// INVALID
// ORIGIN
// SWAP5
// MCOPY
// RETURNDATASIZE
// LOG0
// INVALID
// PUSH24 0x62b79c8464736f6c63430008140033