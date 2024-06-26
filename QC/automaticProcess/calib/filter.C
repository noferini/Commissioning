#include "TFile.h"
#include "TTree.h"
#include "DataFormatsTOF/CalibTimeSlewingParamTOF.h"
#include "DataFormatsTOF/Diagnostic.h"
#include "DataFormatsTOF/CalibInfoTOF.h"


void filter(const char* filename="calib523303-part1.root",int supFactor=3){
printf("here\n");
  TFile *f = new TFile(filename);
  TTree *tree = (TTree *) f->Get("calibTOF");
printf("here\n");
  std::vector<o2::dataformats::CalibInfoTOF> mVect, *mPvect = &mVect;
  o2::tof::Diagnostic mDia, *mPdia = &mDia;
  tree->SetBranchAddress("TOFCalibInfo", &mPvect);
  tree->SetBranchAddress("TOFDiaInfo", &mPdia);

  TFile *fout = new TFile(Form("skim_%s",filename),"RECREATE");
printf("here\n");
  TTree *tout = new TTree("calibTOF","calibTOF");
  std::vector<o2::dataformats::CalibInfoTOF> mVectOut, *mPvectOut = &mVectOut;
  tout->Branch("TOFCalibInfo",&mPvectOut);
  tout->Branch("TOFDiaInfo",&mPdia);

  uint mask = 1+4+16+32+64+128;

  printf("start processing\n");

  for(int i=0; i < tree->GetEntries();i++){
    tree->GetEvent(i);
    mVectOut.clear();
    
    int n = 0;
    int nfilled = 0;
    for(auto& obj : mVect){
      if(!(n%supFactor)){
	if(!(mVect[n].getFlags() & mask)){
	  mVectOut.push_back(mVect[n]);
	  nfilled++;
	}
      }
      n++;
    }
    //    printf("%d / %d - %lld / %lld\n",nfilled,n,mVectOut.size(),mVect.size());
    tout->Fill();
  }

  tout->Write();
  fout->Close();
}
