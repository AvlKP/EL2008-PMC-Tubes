#pragma once
#include "types.h"

Pasien *baca_data_pasien(char *path);
Riwayat *baca_riwayat(char *path);
void baca_biaya(char *path, int *biaya);