#include "fft_math.h"



Complesso somma_c(Complesso a, Complesso b) {
    Complesso r;
    r.re = a.re + b.re;
    r.im = a.im + b.im;
    return r;
}

Complesso sottrazione_c(Complesso a, Complesso b){
    Complesso r;
    r.re = a.re - b.re;
    r.im = a.im - b.im;
    return r;
}

Complesso prodotto_c(Complesso a, Complesso b) {
    Complesso r;
    r.re = a.re * b.re - a.im * b.im;
    r.im = a.re * b.im + a.im * b.re;
    return r;
}

Complesso coniugato_c(Complesso a) {
    Complesso r;
    r.re = a.re;
    r.im = -a.im;
    return r;
}

float modulo_c(Complesso a) {
    return sqrtf(a.re * a.re + a.im * a.im);
}

float fase_c(Complesso a) {
    return atan2f(a.im, a.re);  // restituisce la fase in radianti
}

Complesso esponenziale_negj(int k, int N) {
    float theta = -2.0f * PI * k / (float)N;
    Complesso r = { cosf(theta), sinf(theta) };
    return r;
}
