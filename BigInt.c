#include <stdio.h>

#define MAX_LIMBS 32 // 32 * 32 = 1024 

typedef struct {
    unsigned int limbs[MAX_LIMBS];
} BigInt;

void init(BigInt *n) {
    for (int i = 0; i < MAX_LIMBS; i++) n->limbs[i] = 0;
}

int hexCharToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

// Fixed parsing: Handles any length string and avoids limb overflow
void parseHex(BigInt *n, const char *str) {
    init(n);
    int len = 0;
    while (str[len] != '\0') len++;

    int limb_idx = 0;
    unsigned int current_val = 0;
    unsigned int multiplier = 1;
    int digit_count = 0;

    for (int i = len - 1; i >= 0; i--) {
        int val = hexCharToInt(str[i]);
        if (val == -1) continue; // Skip invalid chars like '0x' or spaces

        current_val += (unsigned int)val * multiplier;
        digit_count++;

        // Push to limb if we hit 8 hex digits OR we are at the very start of the string
        if (digit_count == 8 || i == 0) {
            if (limb_idx < MAX_LIMBS) {
                n->limbs[limb_idx++] = current_val;
            }
            current_val = 0;
            multiplier = 1;
            digit_count = 0;
        } else {
            multiplier *= 16;
        }
    }
}

// Returns 1 if A > B, -1 if A < B, 0 if A == B
int compare(BigInt a, BigInt b) {
    for (int i = MAX_LIMBS - 1; i >= 0; i--) {
        if (a.limbs[i] > b.limbs[i]) return 1;
        if (a.limbs[i] < b.limbs[i]) return -1;
    }
    return 0;
}

void printBigInt(BigInt n) {
    int started = 0;
    for (int i = MAX_LIMBS - 1; i >= 0; i--) {
        if (n.limbs[i] != 0 || started || i == 0) {
            if (started) printf("%08x", n.limbs[i]);
            else printf("%x", n.limbs[i]);
            started = 1;
        }
    }
    printf("\n");
}

BigInt add(BigInt a, BigInt b) {
    BigInt res;
    init(&res);
    unsigned long long carry = 0;
    for (int i = 0; i < MAX_LIMBS; i++) {
        unsigned long long sum = (unsigned long long)a.limbs[i] + b.limbs[i] + carry;
        res.limbs[i] = (unsigned int)sum;
        carry = sum >> 32;
    }
    return res;
}

// Subtraction: Assumes A >= B for standard positive result
BigInt sub(BigInt a, BigInt b) {
    BigInt res;
    init(&res);
    unsigned long long borrow = 0;
    for (int i = 0; i < MAX_LIMBS; i++) {
        unsigned long long sub_val = (unsigned long long)a.limbs[i] - b.limbs[i] - borrow;
        res.limbs[i] = (unsigned int)sub_val;
        borrow = (sub_val >> 32) & 1; 
    }
    return res;
}

BigInt mul(BigInt a, BigInt b) {
    BigInt res;
    init(&res);
    for (int i = 0; i < MAX_LIMBS; i++) {
        if (a.limbs[i] == 0) continue;
        unsigned long long carry = 0;
        for (int j = 0; i + j < MAX_LIMBS; j++) {
            unsigned long long prod = (unsigned long long)a.limbs[i] * b.limbs[j] + res.limbs[i+j] + carry;
            res.limbs[i+j] = (unsigned int)prod;
            carry = prod >> 32;
        }
    }
    return res;
}

int main(void) {
    char s1[512], s2[512], op;
    BigInt A, B, result;

    printf("--- 1024-bit BigInt Calculator ---\n");
    printf("Enter first hex: ");
    scanf("%511s", s1);
    printf("Enter second hex: ");
    scanf("%511s", s2);
    printf("Operation (+, -, *): ");
    scanf(" %c", &op);

    parseHex(&A, s1);
    parseHex(&B, s2);

    printf("Result: ");
    if (op == '+') {
        result = add(A, B);
        printBigInt(result);
    } else if (op == '-') {
        int cmp = compare(A, B);
        if (cmp >= 0) {
            result = sub(A, B);
            printBigInt(result);
        } else {
            // If A < B, result is -(B - A)
            printf("-");
            result = sub(B, A);
            printBigInt(result);
        }
    } else if (op == '*') {
        result = mul(A, B);
        printBigInt(result);
    } else {
        printf("Invalid operator.\n");
    }
}