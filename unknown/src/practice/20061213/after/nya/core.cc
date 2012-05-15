#include <iostream>
#include <string>
#include <cassert>

using namespace std;


int wrap(int addr) {
    while(addr < 0)
        addr += 8000;
    return addr % 8000;
}

enum Operation {
    DAT,
    MOV,
    ADD,
    JMP,
    JMZ,
    SLT,
    CMP,
};

enum AddressingMode {
    IMMEDIATE,
    DIRECT,
    INDIRECT,
};

struct Operand {
    AddressingMode mode;
    int value;
};

struct Block {
    Operation opcode;
    Operand operands[2];
};


Block memory[8000];


int refer(int here, int by) {
    Operand& opr = memory[here].operands[by];
    int there;
    if (opr.mode == DIRECT) {
        there = wrap(here + opr.value);
    }
    else if (opr.mode == INDIRECT) {
        there = wrap(here + opr.value);
        there = wrap(there + memory[there].operands[1].value);
    }
    else {
        assert(false);
    }
    return there;
}

int run(int pc0, int pc1, int turn) {

    for(int pcx = 0; pcx < 32000; pcx++) {

        int& pc = pc0;

        int addr = pc;
        Block cmd = memory[addr];
        Operand opa = cmd.operands[0];
        Operand opb = cmd.operands[1];
        pc = wrap(pc+1);

        switch(cmd.opcode) {

        case DAT:
            return turn^1;

        case MOV:
            if (opa.mode == IMMEDIATE) {
                memory[refer(addr, 1)].operands[1].value = opa.value;
            }
            else {
                memory[refer(addr, 1)] = memory[refer(addr, 0)];
            }
            break;

        case ADD:
            if (opa.mode == IMMEDIATE) {
                int& there = memory[refer(addr, 1)].operands[1].value;
                there = wrap(there + opa.value);
            }
            else {
                Block& x = memory[refer(addr, 0)];
                Block& y = memory[refer(addr, 1)];
                y.operands[0].value = wrap(x.operands[0].value + y.operands[0].value);
                y.operands[1].value = wrap(x.operands[1].value + y.operands[1].value);
            }
            break;

        case JMP:
            pc = refer(addr, 0);
            break;

        case JMZ:
            if (memory[refer(addr, 1)].operands[1].value == 0)
                pc = wrap(pc+1);
            break;

        case SLT:
            if (opa.mode == IMMEDIATE) {
                int va = opa.value;
                int vb = memory[refer(addr, 1)].operands[1].value;
                if (va < vb)
                    pc = wrap(pc+1);
            }
            else {
                int va = memory[refer(addr, 0)].operands[1].value;
                int vb = memory[refer(addr, 1)].operands[1].value;
                if (va < vb)
                    pc = wrap(pc+1);
            }
            break;

        case CMP:
        {
            Block& x = memory[refer(addr, 0)];
            Block& y = memory[refer(addr, 1)];
            if (x.opcode == y.opcode &&
                x.operands[0].mode == y.operands[0].mode &&
                x.operands[0].value == y.operands[0].value &&
                x.operands[1].mode == y.operands[1].mode &&
                x.operands[1].value == y.operands[1].value) {
                pc = wrap(pc+1);
            }
        }
            break;

        default:
            assert(false);

        }

        swap(pc0, pc1);
        turn ^= 1;
    }

    return -1;
}

Operand make_operand(string s) {
    char c;
    int v;
    sscanf(s.c_str(), "%c%d", &c, &v);

    Operand opr;
    switch(c) {
    case '#':
        opr.mode = IMMEDIATE;
        break;
    case '$':
        opr.mode = DIRECT;
        break;
    case '@':
        opr.mode = INDIRECT;
        break;
    default:
        assert(false);
    }
    opr.value = wrap(v);
    return opr;
}

int read_program() {
    int n, start;
    cin >> n >> start;
    int addr = start;
    for(int i = 0; i < n; i++) {
        string op, sa, sb;
        cin >> op >> sa >> sb;
        if (op == "DAT")
            memory[addr].opcode = DAT;
        else if (op == "MOV")
            memory[addr].opcode = MOV;
        else if (op == "ADD")
            memory[addr].opcode = ADD;
        else if (op == "JMP")
            memory[addr].opcode = JMP;
        else if (op == "JMZ")
            memory[addr].opcode = JMZ;
        else if (op == "SLT")
            memory[addr].opcode = SLT;
        else if (op == "CMP")
            memory[addr].opcode = CMP;
        else
            assert(false);
        memory[addr].operands[0] = make_operand(sa);
        memory[addr].operands[1] = make_operand(sb);
        addr = wrap(addr+1);
    }
    return start;
}

void solve() {
    for(int i = 0; i < 8000; i++) {
        memory[i].opcode = DAT;
        memory[i].operands[0] = memory[i].operands[1] = make_operand("#0");
    }
    int pc0 = read_program();
    int pc1 = read_program();
    int winner = run(pc0, pc1, 0) + 1;
    if (winner == 0) {
        cout << "Programs are tied." << endl;
    }
    else {
        cout << "Program #" << winner << " is the winner." << endl;
    }
}


int main() {
    int nCases;
    cin >> nCases;
    while(nCases-- > 0)
        solve();
    return 0;
}

