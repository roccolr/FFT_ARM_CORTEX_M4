#include "arm_fft.h"

#define MAX_N 2048  // imposta la dimensione massima FFT

static Complesso buffer_pari[MAX_N / 2];
static Complesso buffer_dispari[MAX_N / 2];

void arm_fft(Complesso* x, Complesso* y, int N){
    // vettore di input e di output devono essere allocati staticamente nel main 
    if (N==1){
        y[0] = x[0];
        return;
    }

    // divisione coefficienti pari e dispari 
    for(int i=0; i<N/2; i++){
        buffer_pari[i] = x [2*i];
        buffer_dispari[i] = x [2*i+1];
    }

    Complesso y_pari[N / 2];
    Complesso y_dispari[N / 2];

    // ricorsione
    arm_fft(buffer_pari, y_pari, N/2);
    arm_fft(buffer_dispari, y_dispari, N/2);

    // combina 
    for(int k=0; k<N/2; k++){
        Complesso W = esponenziale_negj(k, N);
        Complesso t = prodotto_c(W, y_dispari[k]);
        y[k] = somma_c(y_pari[k], t);
        y[k + N/2] = sottrazione_c(y_pari[k], t); 
    }
}

int pad_to_pow2(const Complesso* input, int N_input, Complesso* output) {
    // Calcola potenza di 2 successiva
    int N_pow2 = 1;
    while (N_pow2 < N_input) {
        N_pow2 <<= 1; // moltiplica per 2
    }

    for (int i = 0; i < N_input; i++) {
        output[i] = input[i];
    }

    for (int i = N_input; i < N_pow2; i++) {
        output[i].re = 0.0f;
        output[i].im = 0.0f;
    }

    return N_pow2; // restituisce nuova dimensione padded
}

void fft_to_spectrogram(const Complesso* X, float* magnitude_db, int N, float scaling_db){
    float max_val = 0.0f;

    // Calcola modulo 
    for (int i = 0; i < N; i++) {
        float mag = sqrtf(X[i].re * X[i].re + X[i].im * X[i].im);
        if (mag > max_val) max_val = mag;
        magnitude_db[i] = mag;
    }

    // Converti in dB (20 * log10) e applica scaling
    for (int i = 0; i < N; i++) {
        // evita log di 0 con epsilon
        float val = magnitude_db[i];
        if (val < 1e-12f) val = 1e-12f;

        float db = 20.0f * log10f(val / max_val);

        // clamp minimo e scala da 0 a 1
        if (db < scaling_db) db = scaling_db;

        magnitude_db[i] = (db - scaling_db) / (-scaling_db);
    }
}