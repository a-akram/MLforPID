#include <fstream>
using namespace std;


void rootTOcsv(){
	TH1 *histo = new TH1D("histo", "histo", 20, -2, 2);
	// output 'CSV' file
	ofstream myfile;
	myfile.open ("test.csv");
	
	// read TTree and Branches
   TFile *myFile = new TFile("signal_pid.root");
   TTree *myTree = (TTree*)myFile->Get("cbmsim");
   Int_t nentries = (Int_t)myTree->GetEntries();
   
   TClonesArray *px = new TClonesArray("PndPidCandidate");
   TClonesArray *MCpx = new TClonesArray("PndMCTrack");    //PndMCTrack //FairMCTrack
   
//   TBranch *b1 = myTree->GetBranch("PidChargedCand.fXmomentum");
//   myTree->SetMakeClass(1); // For the proper setup.
   
   myTree->GetBranch("PidChargedCand")->SetAutoDelete(kFALSE);
   
   myTree->SetBranchAddress("PidChargedCand",&px);
   myTree->SetBranchAddress("MCTrack",&MCpx);

    unsigned int is_pi = 0;
    bool flag = false;int J=0,I=0;
   //read all entries and fill the histograms
   for (int j = 0; j<myTree->GetEntries(); j++){
	   myTree->GetEntry(j);
	   
	   for (Int_t i=0; i<MCpx->GetEntries(); i++) {
		  PndMCTrack* myCand = (PndMCTrack*)MCpx->At(i);
		  //cout<<"Mother code: "<<myCand->GetMotherID()<<endl;
		  if(myCand->GetMotherID()==-1)
		  //if(abs(myCand->GetPdgCode())==-211)
		  //{++is_pi;
		  {/*cout<<"PDG code: "<<myCand->GetPdgCode()<<endl;*/++is_pi;flag=true;++I;}
		  // output file
		  //myfile<<myCand->GetMomentum().X()<<",";
		  //cout<<"value "<<i+1<<" is: "<<myCand->GetMomentum().X()<<endl;
	   }	
	      
   }
   // header of each line
   myfile<<"PidChargedCand.fXmomentum;";
   
   
   
   if(flag==true){
   //read all entries and fill the histograms
   for (int j = 0; j<myTree->GetEntries(); j++){
	   myTree->GetEntry(j);
	   
	   for (Int_t i=0; i<px->GetEntries(); i++) {
		  PndPidCandidate* myCand = (PndPidCandidate*)px->At(i);
		  // output file
		  //cout<<"MC index: "<<myCand->GetMcIndex()<<endl;
		  ++J;
		  //cout<<"value "<<i+1<<" is: "<<myCand->GetMomentum().X()<<endl;
	   }   
   } }
   cout<<"total is ----->>: "<<is_pi<<endl<<",     and flag is ====>>>"<<I<<endl;
   myfile<<"\n";
   myfile<<"MCTrack.fpx;";
   
   //read all entries and fill the histograms
   for (int j = 0; j<myTree->GetEntries(); j++){
	   myTree->GetEntry(j);
	   for (Int_t i=0; i<MCpx->GetEntries(); i++) {
		  PndMCTrack* myCand = (PndMCTrack*)MCpx->At(i);
		  
		  // output file
		  myfile<<myCand->GetMomentum().X()<<",";
		  //cout<<"value "<<i+1<<" is: "<<myCand->GetMomentum().X()<<endl;
	   }	   
   }
   
   myfile.close();
   
} // macro end here
