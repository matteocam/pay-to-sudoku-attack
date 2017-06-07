# pay-to-sudoku-attack

This is an attack to the zero-knowledge contingent 
payment system [pay-to-sudoku](https://github.com/zcash/pay-to-sudoku/).

The attack allows to learn the value of a wire in the circuit generated in pay-to-sudoku. Notice that if the "attacked wire" is 0 the proving algorithm will fail (in a real world setting, a malicious verifier may deduce the wire was 0 if the prover does not send any proof).

To use, first build and install the libsnark-attack code. You will also need Rust installed. Then:

```
make
cargo run gen 2 # generate circuit for 2^2 x 2^2 puzzle and corresponding malicious key
cargo run test 2 # test the proof/malicious verification on random puzzles 
# or, as an alternative to "cargo run test 2":
cargo run serve 2 # run a server on port 25519 for buying solutions
cargo run client 2 # run a client for selling solutions
```

To change the index of the wire you want to learn change the value in file "attacked_wire".

To use debugger, first build executable:
```
make
cargo build
cargo build --release
```

To execute under gdb: 
```
cd target/release
export LD_LIBRARY_PATH=.
gdb --args ./pay-to-sudoku serve 2
```
