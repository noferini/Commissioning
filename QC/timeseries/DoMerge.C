#include "TFileMerger.h"

// macro to merge all the files in a list (they should belong to the same school)
// The header of the first file will be kept
void DoMerge(char* nomelista="listaM",char* output="filtered.root"){
//  system("ls calib/*.root  >listaM");
  FILE *f = fopen(nomelista,"r");

//  TGrid::Connect("alien://");

  TFileMerger m(kFALSE);
  m.OutputFile(output);

  Int_t i=0;
  char nome[100];
  while (fscanf(f,"%s",nome)==1) {
    m.AddFile(nome);
    i++;
  }
  if (i)
    m.Merge();
}

