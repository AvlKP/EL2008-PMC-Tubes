#include "types.h"
#include "files.h"

int main()
{
  Pasien *pasien = bacaDataPasien("data/Data Pasien.csv");
  Riwayat *riwayat = bacaRiwayat("data/Riwayat.csv");
  int biaya[6];
  bacaBiaya("data/Biaya.csv", biaya);

  // cetakPasien(pasien);
  // cetakRiwayat(riwayat);
  // printf("%d\n", biaya[CekGulaDarah]);

  return 0;
}