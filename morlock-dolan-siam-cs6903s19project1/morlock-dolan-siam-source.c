#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef NUM
#define NUM 4
#endif

#ifndef LEN_ALPHABET
#define LEN_ALPHABET 27
#endif

#ifndef L
#define L 500
#endif

#ifndef MAX_T
#define MAX_T 24
#endif

float english_dict[] = {
    0.1918182, 0.0651738, 0.0124248, 0.0217339, 0.0349835, 0.1041442, 0.0197881,
    0.0158610, 0.0492888, 0.0558094, 0.0009033, 0.0050529, 0.0331490, 0.0202124,
    0.0564513, 0.0596302, 0.0137645, 0.0008606, 0.0497563, 0.0515760, 0.0729357,
    0.0225134, 0.0082903, 0.0171272, 0.0013692, 0.0145984, 0.0007836};

int inv_alphabet(char a) {
    if (a == ' ') {
        return 0;
    }

    return a - 'a' + 1;
}

char alphabet(int a) {
    if (a == 0) {
        return ' ';
    }

    return 'a' + a - 1;
}

float* sample(char* cipher) {
    int length = strlen(cipher);
    float* dist = malloc(sizeof(float) * LEN_ALPHABET);
    memset(dist, 0, sizeof(float) * LEN_ALPHABET);

    int i;
    for (i = 0; i < length; i++) {
        dist[inv_alphabet(cipher[i])] += 1;
    }

    return dist;
}

char** subkey(char* c, int t) {
    int i;
    int loc[t];
    memset(loc, 0, sizeof(int) * t);
    char** substrings = malloc(sizeof(char*) * t);
    for (i = 0; i < t; i++) {
        substrings[i] = malloc(sizeof(char) * L);
        memset(substrings[i], 0, sizeof(char) * L);
    }

    for (i = 0; i < strlen(c); i++) {
        substrings[i % t][loc[i % t]] = c[i];
        loc[i % t]++;
    }

    return substrings;
}

float coincidence(char* subkey) {
    float* nmbr = sample(subkey);
    float upper = 0.0f;
    int i;
    for (i = 0; i < LEN_ALPHABET; i++) {
        upper += nmbr[i] * (nmbr[i] - 1);
    }

    float lower = strlen(subkey) * (strlen(subkey) - 1);

    return upper / lower;
}

int find_key_length(char* cipher) {
    int min_i = 0;
    float min_value = 1.0f;
    int i;
    for (i = 2; i < MAX_T; i++) {
        char** subkeys = subkey(cipher, i);
        float diff = 0.0f;
        int j;
        for (j = 0; j < i; j++) {
            diff += fabs(0.0667 - coincidence(subkeys[j]));
        }
        diff /= i;
        // printf("%lf\n", diff);
        if (diff < min_value) {
            min_i = i;
            min_value = diff;
        }
    }

    return min_i;
}

char* monoalphabetic(char* m, int k) {
    int m_length = strlen(m);
    char* cipher = malloc(sizeof(char) * m_length);
    memset(cipher, 0, sizeof(char) * m_length);

    int i;
    for (i = 0; i < m_length; i++) {
        cipher[i] = alphabet((inv_alphabet(m[i]) + k) % LEN_ALPHABET);
    }

    return cipher;
}

float chi_square(float c[], float e[]) {
    float sum = 0.0f;
    int i;
    for (i = 0; i < LEN_ALPHABET; i++) {
        sum += (powf((float)(c[i] - e[i]), 2) / e[i]);
    }

    return sum;
}

void interpret(char* c, int key[], int key_length) {
    int i;
    int len = strlen(c);
    for (i = 0; i < len; i++) {
        c[i] = alphabet((inv_alphabet(c[i]) + key[i % key_length]) % 27);
    }
}

int* find_key(char* cipher, int length) {
    char** each = subkey(cipher, length);
    int exp_english[LEN_ALPHABET];
    int i;
    int j;
    for (i = 0; i < LEN_ALPHABET; i++) {
        exp_english[i] = english_dict[i] * length;
    }
    int* key = malloc(sizeof(int) * length);

    for (i = 0; i < length; i++) {
        int mmin = 100000; // some large value
        int min_idx = 0;
        for (j = 0; j < LEN_ALPHABET; j++) {
            char* shifted = monoalphabetic(each[i], j);
            float diff = chi_square(sample(shifted), english_dict);

            if (diff < mmin) {
                mmin = diff;
                min_idx = j;
            }
        }

        key[i] = min_idx;
    }

    return key;
}

int main(int argc, char const* argv[]) {
    printf("Enter a ciphertext: ");
    char* ciphertext = malloc(sizeof(char) * 500);
    memset(ciphertext, 0, sizeof(char) * 500);
    size_t buffsize = sizeof(char) * 500;
    getline(&ciphertext, &buffsize, stdin);

    int s = 0;
    while (ciphertext[s] != '\0') {
        if (ciphertext[s] == '\n') {
            ciphertext[s] = 0;
        }
        s++;
    }

    int key_length = find_key_length(ciphertext);
    int* key = find_key(ciphertext, key_length);
    interpret(ciphertext, key, key_length);
    printf("%s\n", ciphertext);
    return 0;
}
