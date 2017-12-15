#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include <fstream>
#include "TCanvas.h"
#include "TDirectory.h"
#include "TH2F.h"
#include "TF1.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TPad.h"
#include "TList.h"
#include "TGraphAsymmErrors.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"

using namespace std;

int main(int argc, char* argv[])
{
	string folder = "";
	string GT = argv[2], rereco = argv[1];
	std::cout << " GT = " << GT << endl;
	string GT2 = GT;
	int ietamin = 1000, ietamax = 1000, iphimin = 1000, iphimax = 1000;
	/*int ietamin[] = {6, 26, 26, 26, 46, 6, -45, -65, -45, -5};
	int ietamax[] = {15, 35, 35, 35, 55, 15, -36, -56, -36, 0};
	int iphimin[] = {20, 100, 160, 170, 300, 310, 140, 190, 300, 20};
	int iphimax[] = {30, 110, 170, 180, 310, 320, 150, 200, 310, 30};*/
	
	/*int ietamin[] = {6, 6};
	int ietamax[] = {15, 15};
	int iphimin[] = {120, 120};
	int iphimax[] = {130, 130};
	*/
	int k = 0;
	TFile *infile[650], *infile_neg[650];
	TGraphAsymmErrors *graph[650], *neg_graph[650];
	int a_ietamin[600], a_ietamax[600], a_iphimin[600], a_iphimax[600],a_ietamin_neg[600], a_ietamax_neg[600], a_iphimin_neg[600], a_iphimax_neg[600], null_flag[86], null_flag_neg[86];;
	TH1F *h_EoPunc = new TH1F("EOPUnc", "Uncertainty on E/p; #sigma_{EoP};", 1000, 0, 6.0e-3);
	map < int, TGraphAsymmErrors* > map_eta_g;
	vector<TGraphAsymmErrors*> graph_v, neg_graph_v;
	/*TH1F *hframe;
	TPad *pad;
	TCanvas *cplot;
	TFile *framefile;
	*/
	/*for (unsigned int i = 0; i < 2; ++i)
	{
		cout << to_string(ietamin[i]) << "   " << to_string(ietamax[i]) << "    " << iphimin[i] << "    "  << iphimax[i] <<  endl;		
		if (ietamin[i] > 0 )	infile[i] = TFile::Open(("EB_Run2016BCDEFGH_WZSkim_Cal_Jan2017_ref_multifit_ietamin_"+to_string(ietamin[i])+"_ietamax_"+to_string(ietamax[i])+"_iphimin_"+to_string(iphimin[i])+"_iphimax_"+to_string(iphimax[i])+"/EB___history_vsTime.root").c_str());		
		else if (ietamin[i] < 0 )	infile[i] = TFile::Open(("EB_Run2016BCDEFGH_WZSkim_Cal_Jan2017_ref_multifit_ietamax_"+to_string(ietamax[i])+"_ietamin_"+to_string(ietamin[i])+"_iphimin_"+to_string(iphimin[i])+"_iphimax_"+to_string(iphimax[i])+"/EB___history_vsTime.root").c_str());
		cout << i << "-th name " << infile[i]->GetName() << endl;		
	}*/
	int ietamin_neg, ietamax_neg;
	
	//for (int i = 0; i  < 80; i = i + 5)
	int i = 0;
	ietamin = 0;
	ietamax = 0;
	
	//folder = "/eos/user/v/vciriolo/EoP_monitoring/harness2017/92X_dataRun2_Prompt_v9/SingleEle/";
	folder = "/eos/user/v/vciriolo/EoP_monitoring/harness2017/"+rereco+"/SingleAndDouble/"+GT+"/";
	string folder_1nw = "/eos/user/v/vciriolo/EoP_monitoring/harness2017/"+rereco+"/SingleAndDouble/"+GT+"/1nw/";
	ofstream missFiles("missingFile_SingleAndDouble"+GT+".txt", std::ofstream::out);
	
	int l = 0, l_neg = 0;
	double sigma_max = 3.0e-04;
	while ( ietamax < 85)
	{
		if ( ietamin == 0)
		{
			ietamin = i;
			ietamax = ietamin + 5;
			cout << "primo if " << endl;
		}
		if ( ietamin > 0 )
		{
			//i += 5;
			//ietamin = i+1;
			ietamin = ietamax + 1;
			ietamax += 20;
		}
		
		cout << " ietamin = " << ietamin << "  ietamax = " << ietamax << endl;

		
		ietamin_neg = -1*(ietamax);
		ietamax_neg = -1*(ietamin);
		for (unsigned int j = 0; j < 360; j = j +10)
		{
		//setprecision(1);
		
			
			if ( j == 0) iphimax = 0;
			if ( j == 0) iphimin = j;
			else if ( j > 0) iphimin = iphimax;
			//if ( i == 0 && j > 0 )	iphimin += 10;
			//iphimax = j + 10;
			if ( ietamin == 0)	iphimax += 20;
			else if ( ietamin != 0) iphimax += 10;
		
			infile[k] = TFile::Open((folder_1nw+"EB_"+GT2+"_ietamax_"+to_string(ietamax)+"_ietamin_"+to_string(ietamin)+"_iphimin_"+to_string(iphimin)+"_iphimax_"+to_string(iphimax)+"_events_10000/EB___histos.root").c_str());
			if (infile[k]==NULL)
				infile[k] = TFile::Open((folder_1nw+"EB_"+GT2+"_ietamax_"+to_string(ietamax)+"_ietamin_"+to_string(ietamin)+"_iphimin_"+to_string(iphimin)+"_iphimax_"+to_string(iphimax)+"_events_10000/EB__/EB___histos.root").c_str());
			if (infile[k]==NULL)
				infile[k] = TFile::Open((folder+"EB_"+GT2+"_ietamax_"+to_string(ietamax)+"_ietamin_"+to_string(ietamin)+"_iphimin_"+to_string(iphimin)+"_iphimax_"+to_string(iphimax)+"_events_10000/EB___histos.root").c_str());	
			if (infile[k]==NULL)	
				infile[k] = TFile::Open((folder+"EB_"+GT2+"_ietamax_"+to_string(ietamax)+"_ietamin_"+to_string(ietamin)+"_iphimin_"+to_string(iphimin)+"_iphimax_"+to_string(iphimax)+"_events_10000/EB__/EB___histos.root").c_str());
	
			infile_neg[k] = TFile::Open((folder_1nw+"EB_"+GT2+"_ietamax_"+to_string(ietamax_neg)+"_ietamin_"+to_string(ietamin_neg)+"_iphimin_"+to_string(iphimin)+"_iphimax_"+to_string(iphimax)+"_events_10000/EB___histos.root").c_str());
			if (infile_neg[k] == NULL)
				infile_neg[k] = TFile::Open((folder+"EB_"+GT2+"_ietamax_"+to_string(ietamax_neg)+"_ietamin_"+to_string(ietamin_neg)+"_iphimin_"+to_string(iphimin)+"_iphimax_"+to_string(iphimax)+"_events_10000/EB__/EB___histos.root").c_str());
			if (infile_neg[k] == NULL)	
				infile_neg[k] = TFile::Open((folder+"EB_"+GT2+"_ietamax_"+to_string(ietamax_neg)+"_ietamin_"+to_string(ietamin_neg)+"_iphimin_"+to_string(iphimin)+"_iphimax_"+to_string(iphimax)+"_events_10000/EB___histos.root").c_str());			
			if (infile_neg[k] == NULL)
				infile_neg[k] = TFile::Open((folder+"EB_"+GT2+"_ietamax_"+to_string(ietamax_neg)+"_ietamin_"+to_string(ietamin_neg)+"_iphimin_"+to_string(iphimin)+"_iphimax_"+to_string(iphimax)+"_events_10000/EB__/EB___histos.root").c_str());
		
			/*if (infile[k] != NULL)	
			{
				cout << infile[k]->GetName() << endl;
				++l;
				//getchar();
			}*/
			infile[k] == NULL ? null_flag[k] = 1 : null_flag[k] = 0;
			infile_neg[k] == NULL ? null_flag_neg[k] = 1 : null_flag_neg[k] = 0;
		
			/*if (infile[k] == NULL)
			{
				//infile[k] = infile[k-1];
				null_flag[k] = 1;
				missFiles << (folder+"EB_"+GT2+"_ietamax_"+to_string(ietamax)+"_ietamin_"+to_string(ietamin)+"_iphimin_"+to_string(iphimin)+"_iphimax_"+to_string(iphimax)+"/EB___histos.root").c_str() << endl;
			}
			if (infile_neg[k] == NULL)
			{
				//infile_neg[k] = infile_neg[k-1];
				missFiles << (folder+"EB_"+GT2+"_ietamax_"+to_string(0)+"_ietamin_"+to_string(-5)+"_iphimin_"+to_string(iphimin)+"_iphimax_"+to_string(iphimax)+"/EB___histos.root").c_str() << endl;
			}*/
			if (null_flag[k] != 1)
			{
				cout << k << "-th name " << infile[k]->GetName() << endl;
				graph_v.push_back((TGraphAsymmErrors*)infile[k]->Get("g_c_fit"));
				//if (graph_v.at(int(graph_v.size())-1) == NULL)	continue;
				graph_v.at(int(graph_v.size())-1)->SetName(("ietamin_"+to_string(ietamin)+"_ietamax_"+to_string(ietamax)+"_iphimin_"+to_string(iphimin)+"_iphimax_"+to_string(iphimax)).c_str());
				/*int totN = graph_v.at(int(graph_v.size())-1)->GetN();
				for (unsigned int nPt = 0; nPt < totN; ++nPt)
				{
					if ( graph_v.at(int(graph_v.size())-1)->GetErrorY(nPt) < sigma_max)	
					{
						graph_v.at(int(graph_v.size())-1)->RemovePoint(nPt);
						nPt -= 1;
						totN -= 1;
					}
					//if ( neg_graph[k]->GetErrorY(nPt) < 0.5e-03)	neg_graph[k]->RemovePoint(nPt);
				}*/
				++l;
			}
			else if (null_flag[k] == 1)
				{cout << (folder+"EB_"+GT2+"_ietamax_"+to_string(ietamax)+"_ietamin_"+to_string(ietamin)+"_iphimin_"+to_string(iphimin)+"_iphimax_"+to_string(iphimax)+"_events_10000"+"/EB___histos.root").c_str() << endl;
				//getchar();
				}
			if (null_flag_neg[k] != 1)
			{
				cout << k << "-th negative name " << infile_neg[k]->GetName() << endl;
				neg_graph_v.push_back((TGraphAsymmErrors*)infile_neg[k]->Get("g_c_fit"));
				if (neg_graph_v.at(int(neg_graph_v.size())-1) == NULL)	continue;				
				neg_graph_v.at(int(neg_graph_v.size()-1))->SetName(("ietamax_"+to_string(ietamax_neg)+"_ietamin_"+to_string(ietamin_neg)+"_iphimin_"+to_string(iphimin)+"_iphimax_"+to_string(iphimax)).c_str());
				
				/*int totN = neg_graph_v.at(int(neg_graph_v.size())-1)->GetN();
				for (unsigned int nPt = 0; nPt < totN; ++nPt)
				{
					if ( neg_graph_v.at(int(neg_graph_v.size())-1)->GetErrorY(nPt) < sigma_max)	
					{
						neg_graph_v.at(int(neg_graph_v.size())-1)->RemovePoint(nPt);
						nPt -= 1;
						totN -= 1;
					}
					//if ( neg_graph[k]->GetErrorY(nPt) < 0.5e-03)	neg_graph[k]->RemovePoint(nPt);
				}*/
				++l_neg;	
			}	
			else if (null_flag_neg[k] == 1)
				{cout << (folder+"EB_"+GT2+"_ietamax_"+to_string(ietamax_neg)+"_ietamin_"+to_string(ietamin_neg)+"_iphimin_"+to_string(iphimin)+"_iphimax_"+to_string(iphimax)+"_events_10000/EB___histos.root").c_str()  << endl;}// getchar();}

			a_ietamin[k] = ietamin;
			a_ietamax[k] = ietamax;
			a_iphimin[k] = iphimin;
			a_iphimax[k] = iphimax;
			a_ietamin_neg[k] = ietamin_neg;
			a_ietamax_neg[k] = ietamax_neg;
			a_iphimin_neg[k] = iphimin;
			a_iphimax_neg[k] = iphimax;
			++k;
			if (iphimax == 360)	break;
		}
		ietamin = ietamax;	
		++i;	
	
	}
	cout << "files taken" << endl;
//getchar();
missFiles.close();
/*
TCanvas *c_unc = new TCanvas();
c_unc->cd();
h_EoPunc->Draw();
c_unc->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/h_EoPunc.pdf").c_str());
c_unc->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/h_EoPunc.png").c_str());
*/
cout << " <<<  FITS  >>>  " << k << endl;
//getchar();
//infile[0] = TFile::Open("EB_Run2016BCDEFGH_WZSkim_Cal_Jan2017_ref_multifit_ietamin_26_ietamax_45_iphimin_100_iphimax_110/EB___histos.root");
//graph[0] = (TGraphAsymmErrors*)infile[0]->Get("g_c_fit");
double xi = -10., yi = -10., x2 = -10., y2 = -10.;

TF1 *fit_func[650];
TF1 *neg_fit_func[650];
TF1 *fit_func_new[650];
TFitResultPtr rp;
int fStatus = 1;
int nTrials = 0;
double chi2 = 10000.;
double xmax = -1., xmin = 1., y_xmin = -1., y_xmax = -1.;
int nPts = 0;
double p0history[650], p0history_err[650], p0history_neg[650], p0history_err_neg[650], p0history_xmin[1], dummyerr[1];

TH1F *h_chi2 = new TH1F("h_chi2", "Reduced #Chi^{2} distribution; #Chi^{2}/NDF); ", 100, 0, 22);
TH1F *h_slope = new TH1F("h_slope", "", 100, -8.0e-09, 8.0e-09);
TH1F *h_p0 = new TH1F ("h_p0", "Fit intercept distribution; P_{0}", 100, -1,3);
TH1F *h_lastOverFirst = new TH1F ("h_lastOverFirst", "Last Over First E/p value distribution; E/p_{last}/E/p_{0};", 100, 0.8 ,1.05);
TH1F *h_lastOverSecond = new TH1F ("h_lastOverSecond", "Last Over Second E/p value distribution; E/p_{last}/E/p_{1};", 100, 0.8 ,1.05);
TH1F *h_lastOverThird = new TH1F ("h_lastOverThird", "Last Over Third E/p value distribution; E/p_{last}/E/p_{2};", 100, 0.8 ,1.05);
TH1F *h_lastOverFourth = new TH1F ("h_lastOverFourth", "Last Over Fourth E/p value distribution; E/p_{last}/E/p_{3};", 100, 0.8 ,1.05);

gStyle->SetOptFit(110);
TF1 *thisfit;


xmin = 1.46319e9; //2016 
xmax = 1.47728e9; //2016
xmin = 1.49722e9; //2017
xmax = 1.50517e9; //2017
xmax = 1.51047e9; //2017 run F
xmin = 1.50788e9; //2017 run F

TH2F *map = new TH2F("map", "Fit slope map; i#phi; i#eta", 36,0,360,34,-85,85);
TH2F *m_chi2 = new TH2F("m_chi2", "Fit #chi^{2} map; i#phi; i#eta", 36,0,360,34,-85,85);
TH2F *m_p0 = new TH2F("m_p0", "Fit intercept map; i#phi; i#eta", 36,0,360,34,-85,85);
TH2F *m_lastOverFirst = new TH2F("m_lastOverFirst"," Last/First E/p scale map; i#phi; i#eta", 36,0,360,34,-85,85);
TH2F *m_lastOverSecond = new TH2F("m_lastOverSecond", "Last/Second E/p scale map; i#phi; i#eta", 36,0,360,34,-85,85);
TH2F *m_lastOverThird = new TH2F("m_lastOverThird", "Last/Third E/p scale map; i#phi; i#eta", 36,0,360,34,-85,85);
TH2F *m_lastOverFourth = new TH2F("m_lastOverFourth", "Last/Fourth E/p scale map; i#phi; i#eta", 36,0,360,34,-85,85);

TH1F *residuals01 = new TH1F("residuals","residuals",50,-5e-03,5e-03);
TH1F *residuals2 = new TH1F("residuals","residuals",50,-5e-03,5e-03);
TH1F *residuals3 = new TH1F("residuals","residuals",50,-5e-03,5e-03);
TH1F *residuals4 = new TH1F("residuals","residuals",50,-5e-03,5e-03);

TH1F *h_510 = new TH1F("","", 50, 0.5, 1.5);

float lastOverFirst[600], lastOverSecond[600], lastOverThird[600], lastOverFourth[600],lastOverFirst_neg[600], lastOverSecond_neg[600], lastOverThird_neg[600], lastOverFourth_neg[600] ;
ofstream funcs("fit_funcs.txt",std::ofstream::out);
bool npt = true;
TCanvas *c = new TCanvas();
c->cd();

TDatime min(2017,6,15,12,00,00);
TDatime max(2017,10,14,12,00,00);

cout << graph_v.size() << "    " << neg_graph_v.size() <<   endl;

double ott5 = 1507199854;
for (unsigned int i = 0; i < graph_v.size(); ++i)
{
	//cout << "check -1 " << endl;
	if (graph_v.at(i) == NULL)	{ cout << i << endl; getchar()  ;continue;}
	if (graph_v.at(i)->GetN() == 0)	continue;
	//cout << " check 1 " << endl;
	fStatus = 1;
	//nPts = graph[i]->GetN();
	//thisgraph = itr->second;
	graph_v.at(i)->GetPoint(0, xi, yi);
	graph_v.at(i)->GetPoint(graph_v.at(i)->GetN()-1, x2, y2);
	//cout << " check2 " << endl;
	fit_func[i] = new TF1(Form("fit_func_%s" , to_string(i)),"pol1",graph_v.at(i)->GetXaxis()->GetXmin(), graph_v.at(i)->GetXaxis()->GetXmax());
	//cout << "check 3 " << endl;
	thisfit = new TF1("thisfit","pol1", xi , x2 );
	thisfit->SetParameter(0, 1.);
	thisfit->SetParameter(0, 0.);
	//cout << " check 4 " << endl;
	//cout << " xmin = " << xmin << "  xmax = " << xmax << "   " << thisgraph->GetName() << endl;// graph[i]->GetXaxis()->GetXmax() << endl;

	//thisgraph->GetYaxis()->SetRangeUser(0.97, 1.02);
	graph_v.at(i)->GetYaxis()->SetRangeUser(0.97, 1.02);
	//neg_graph[i]->GetYaxis()->SetRangeUser(0.97, 1.02);	
	//cout << " prima del while " << endl;
	while( (fStatus != 0) && (nTrials < 10) )
	{
		/*rp = thisgraph -> Fit(thisfit, "RS");
		fStatus = rp;
		rp = thisgraph-> Fit(thisfit, "RS");	
		rp = thisgraph -> Fit(thisfit, "RS");		
		rp = thisgraph->  Fit(thisfit, "RS");
		rp = thisgraph->  Fit(thisfit, "RS");	
		++nTrials;
		*/
		rp = graph_v.at(i) -> Fit(thisfit, "RS");
		fStatus = rp;
		rp = graph_v.at(i) -> Fit(thisfit, "RS");	
		rp = graph_v.at(i) -> Fit(thisfit, "RS");
		fit_func[i]->SetParameter(0, thisfit->GetParameter(0));
		fit_func[i]->SetParameter(1, thisfit->GetParameter(1));			
		rp = graph_v.at(i)->  Fit(fit_func[i], "RS");
		rp = graph_v.at(i)->  Fit(fit_func[i], "RS");	
		p0history[i] = fit_func[i]->Eval(xmin);
		rp->GetConfidenceIntervals(1, 1, 1, p0history_xmin, dummyerr, 0.683, false);
		p0history_err[i] = dummyerr[0];
		//if(fStatus == 0) break;
		++nTrials;
		
	}
	
	fStatus = 1;
	nTrials = 0;
	
	if (thisfit->GetChisquare() / thisfit->GetNDF() > 1000)
	{
		while (fStatus != 0 && nTrials < 10)
		{
			/*
			//fit_func[i]->SetParameter(0,1.);
			//fit_func[i]->SetParameter(1,0.);
			thisfit->SetParameter(0,1.);
			thisfit->SetParameter(1,0.);
			//rp = graph[i]->  Fit(fit_func[i], "RS");
			//rp = graph[i]->  Fit(fit_func[i], "RS");
			rp = thisgraph->  Fit(thisfit, "RS");
			rp = thisgraph->  Fit(thisfit, "RS");		
			rp = thisgraph->  Fit(thisfit, "EX0RS");
			rp = thisgraph->  Fit(thisfit, "EX0RS");
			fStatus = rp;
			++nTrials;
			cout <<  fStatus << endl;
			*/
			
			thisfit->SetParameter(0,1.);
			thisfit->SetParameter(1,0.);
			//rp = graph[i]->  Fit(fit_func[i], "RS");
			//rp = graph[i]->  Fit(fit_func[i], "RS");
			rp = graph_v.at(i)->  Fit(thisfit, "RS");
			rp = graph_v.at(i)->  Fit(thisfit, "RS");
			fit_func[i]->SetParameter(0, thisfit->GetParameter(0));
			fit_func[i]->SetParameter(1, thisfit->GetParameter(1));			
			rp = graph_v.at(i)->  Fit(fit_func[i], "EX0RS");
			rp = graph_v.at(i)->  Fit(fit_func[i], "EX0RS");
			p0history[i] = fit_func[i]->Eval(xmin);
			rp->GetConfidenceIntervals(1, 1, 1, p0history_xmin, dummyerr, 0.683, false);
			p0history_err[i] = dummyerr[0];
			fStatus = rp;
			++nTrials;
			cout <<  fStatus << endl;
		}
	}
	
	nTrials = 0;
	
	graph_v.at(i)->GetXaxis()->SetTimeFormat("%d/%m%F1970-01-01 00:00:00");
	graph_v.at(i)->GetXaxis()->SetTimeDisplay(1);
	graph_v.at(i)->GetXaxis()->SetTitle("date (day/month)");
	graph_v.at(i)->GetYaxis()->SetTitle("Relative E/p scale"); 
	graph_v.at(i)->GetXaxis()->SetTitleOffset(0.8);
	graph_v.at(i)->GetXaxis()->SetLabelSize(0.03);

	graph_v.at(i)->Draw("AP");
	graph_v.at(i)->GetXaxis()->SetLimits(xmin - 43200, xmax + 43200);		

	string name = graph_v.at(i)->GetName();
	//if (fit_func[i]->GetChisquare() / fit_func[i]->GetNDF() < 100) 
	//{
		//c->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/fit/EBp/"+name+".pdf").c_str());
		//c->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/fit/EBp/"+name+".png").c_str());
		
	//}
	/*
	else if (fit_func[i]->GetChisquare() / fit_func[i]->GetNDF() > 100) 
	{
		c->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/etaRing/fit/EBp/highChi2/"+name+".pdf").c_str());
		c->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/etaRing/fit/EBp/highChi2/"+name+".png").c_str());
	}*/
	h_510->Fill(fit_func[i]->Eval(ott5));
	c->Clear();
	//cout << " fine for" << endl;

	double thisx = -1., thisy = -1.,lastx = -10., lasty = -10.;


	for(unsigned int biny = 0; biny < map->GetYaxis()->GetNbins() + 1 ; ++biny)
	{
		cout << "ieta min = " << a_ietamin[i] << "    ietamax = " << a_ietamax[i] << "  bin center = " <<  map->GetYaxis()->GetBinCenter(map->GetYaxis()->FindBin(a_ietamin[i] + 2.5)) << endl;
		for(unsigned int binx = 0; binx < map->GetXaxis()->GetNbins() + 1 ; ++binx)
		{
			if ( map->GetXaxis()->GetBinCenter(binx) > a_iphimin[i] && map->GetXaxis()->GetBinCenter(binx) < a_iphimax[i] && map->GetYaxis()->GetBinCenter(biny) > a_ietamin[i] && map->GetYaxis()->GetBinCenter(biny) < a_ietamax[i])
			{

				map->SetBinContent(binx, biny, fit_func[i]->GetParameter(1));
				h_slope->Fill(fit_func[i]->GetParameter(1));		
				m_chi2->SetBinContent(binx, biny, fit_func[i]->GetChisquare() / fit_func[i]->GetNDF());
				//m_p0->SetBinContent(binx, biny, fit_func[i]->GetParameter(0));
				m_p0->SetBinContent(binx, biny, p0history[i]);
				graph_v.at(i)->GetPoint(graph_v.at(i)->GetN() - 1, lastx, lasty);
				graph_v.at(i)->GetPoint(0, thisx, thisy);
				m_lastOverFirst->SetBinContent(binx, biny, lasty / thisy);
				lastOverFirst[i] = lasty / thisy;
				h_lastOverFirst->Fill(lasty / thisy);
				graph_v.at(i)->GetPoint(1, thisx, thisy);
				m_lastOverSecond->SetBinContent(binx, biny, lasty / thisy);
				lastOverSecond[i] = lasty / thisy;
				h_lastOverSecond->Fill(lasty / thisy);
				graph_v.at(i)->GetPoint(2, thisx, thisy);
				m_lastOverThird->SetBinContent(binx, biny, lasty / thisy);
				lastOverThird[i] = lasty / thisy;
				h_lastOverThird->Fill(lasty / thisy);
				graph_v.at(i)->GetPoint(3, thisx, thisy);
				m_lastOverFourth->SetBinContent(binx, biny, lasty / thisy);
				lastOverFourth[i] = lasty / thisy;
				h_lastOverFourth->Fill(lasty / thisx);	
				h_p0->Fill(fit_func[i]->GetParameter(0));
				//cout << "n points = " << graph_v.at(i)->GetN() << "  lastx = " << lastx << "   lasty = " << lasty << endl;
			}
		}
	}
}	

for (unsigned int i = 0; i < neg_graph_v.size(); ++i)
{	
	//cout << " in da for " << endl;
	fStatus = 1;
	nTrials = 0;
	neg_graph_v.at(i)->GetPoint(0, xi, yi);
	neg_graph_v.at(i)->GetPoint(neg_graph_v.at(i)->GetN()-1, x2, y2);
	thisfit = new TF1("thisfit","pol1", xi , x2 );
	thisfit->SetParameter(0, 1.);
	thisfit->SetParameter(0, 0.);
	string is = to_string(i);
	//neg_fit_func[i] = new TF1(Form("neg_fit_func_%s" , to_string(i)),"pol1",neg_graph_v.at(i)->GetXaxis()->GetXmin(), neg_graph_v.at(i)->GetXaxis()->GetXmax());
	neg_fit_func[i] = new TF1(("neg_fit_func_"+to_string(i)).c_str(),"pol1",neg_graph_v.at(i)->GetXaxis()->GetXmin(), neg_graph_v.at(i)->GetXaxis()->GetXmax());
	neg_graph_v.at(i)->GetYaxis()->SetRangeUser(0.97,1.02);
	while( (fStatus != 0) && (nTrials < 10) )
	//while ( nTrials < 10)
	{
		//cout << " in da while " <<endl;
		//rp = graph[i] -> Fit(fit_func[i]->GetName(), "RS");
		rp = neg_graph_v.at(i) -> Fit(thisfit, "RS");
		fStatus = rp;
		rp = neg_graph_v.at(i) -> Fit(thisfit, "RS");	
		rp = neg_graph_v.at(i) -> Fit(thisfit, "RS");
		neg_fit_func[i]->SetParameter(0, thisfit->GetParameter(0));
		neg_fit_func[i]->SetParameter(1, thisfit->GetParameter(1));		
		rp = neg_graph_v.at(i)->  Fit(neg_fit_func[i], "RS");
		rp = neg_graph_v.at(i)->  Fit(neg_fit_func[i], "RS");
		p0history_neg[i] = neg_fit_func[i]->Eval(xmin);
		rp->GetConfidenceIntervals(1, 1, 1, p0history_xmin, dummyerr, 0.683, false);
		p0history_err_neg[i] = dummyerr[0];
		//cout << "rp = " << rp << "  chi2 = " << thisfit->GetChisquare() / thisfit->GetNDF() << "  fStatus = " << fStatus <<  endl;	
		
		//if(fStatus == 0) break;
		++nTrials;
	}
	fStatus = 1;
	nTrials = 0;
	if (neg_fit_func[i]->GetChisquare() / neg_fit_func[i]->GetNDF() > 100)
	{
		while (fStatus != 0 && nTrials < 10)
		{
			//cout << " in da other while" << endl;
			//fit_func[i]->SetParameter(0,1.);
			//fit_func[i]->SetParameter(1,0.);
			thisfit->SetParameter(0,1.);
			thisfit->SetParameter(1,0.);
			//rp = graph[i]->  Fit(fit_func[i], "RS");
			//rp = graph[i]->  Fit(fit_func[i], "RS");
			rp = neg_graph_v.at(i)->  Fit(thisfit, "EX0RS");
			rp = neg_graph_v.at(i)->  Fit(thisfit, "EX0RS");
			neg_fit_func[i]->SetParameter(0, thisfit->GetParameter(0));
			neg_fit_func[i]->SetParameter(1, thisfit->GetParameter(1));			
			rp = neg_graph_v.at(i)->  Fit(neg_fit_func[i], "RS");
			rp = neg_graph_v.at(i)->  Fit(neg_fit_func[i], "RS");
			p0history_neg[i] = neg_fit_func[i]->Eval(xmin);
			rp->GetConfidenceIntervals(1, 1, 1, p0history_xmin, dummyerr, 0.683, false);
			p0history_err_neg[i] = dummyerr[0];
			fStatus = rp;
			++nTrials;
			cout <<  fStatus << endl;
		}
		//cout << "fuori again " << endl;
	}
	
	
	neg_graph_v.at(i)->GetXaxis()->SetTimeFormat("%d/%m%F1970-01-01 00:00:00");
	neg_graph_v.at(i)->GetXaxis()->SetTimeDisplay(1);
	neg_graph_v.at(i)->GetXaxis()->SetTitle("date (day/month)");
	neg_graph_v.at(i)->GetYaxis()->SetTitle("Relative E/p scale"); 
	neg_graph_v.at(i)->GetXaxis()->SetTitleOffset(0.8);
	neg_graph_v.at(i)->GetXaxis()->SetLabelSize(0.03);
	neg_graph_v.at(i)->Draw("AP");
	neg_graph_v.at(i)->GetXaxis()->SetLimits(xmin - 43200, xmax + 43200);		

	string name = neg_graph_v.at(i)->GetName();
	
	//if (neg_fit_func[i]->GetChisquare() / neg_fit_func[i]->GetNDF() < 100) 
	if (1 < 0){
	if (1>0)
	{
		c->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/fit/EBm/"+name+".pdf").c_str());
		c->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/fit/EBm/"+name+".png").c_str());
		
	}
	else if (neg_fit_func[i]->GetChisquare() / neg_fit_func[i]->GetNDF() > 100) 
	{
		c->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/fit/EBm/highChi2/"+name+".pdf").c_str());
		c->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/fit/EBm/highChi2/"+name+".png").c_str());
	}
	
	h_510->Fill(neg_fit_func[i]->Eval(ott5));
	c->Clear();
}
	double thisx = -1., thisy = -1.,lastx = -10., lasty = -10.;
	for(unsigned int biny = 0; biny < map->GetYaxis()->GetNbins() + 1 ; ++biny)
	{
		//cout << "ieta min = " << a_ietamin_neg[i] << "    ietamax = " << a_ietamax_neg[i] << "  bin center = " <<  map->GetYaxis()->GetBinCenter(map->GetYaxis()->FindBin(a_ietamin[i] + 2.5)) << endl;
		for(unsigned int binx = 0; binx < map->GetXaxis()->GetNbins() + 1 ; ++binx)
		{
			if ( map->GetXaxis()->GetBinCenter(binx) > a_iphimin[i] && map->GetXaxis()->GetBinCenter(binx) < a_iphimax[i] && map->GetYaxis()->GetBinCenter(biny) > a_ietamin_neg[i] && map->GetYaxis()->GetBinCenter(biny) < a_ietamax_neg[i])
			{

				map->SetBinContent(binx, biny, neg_fit_func[i]->GetParameter(1));
				h_slope->Fill(neg_fit_func[i]->GetParameter(1));		
				m_chi2->SetBinContent(binx, biny, neg_fit_func[i]->GetChisquare() / neg_fit_func[i]->GetNDF());
				//m_p0->SetBinContent(binx, biny, fit_func[i]->GetParameter(0));
				m_p0->SetBinContent(binx, biny, p0history[i]);
				neg_graph_v.at(i)->GetPoint(neg_graph_v.at(i)->GetN() - 1, lastx, lasty);
				neg_graph_v.at(i)->GetPoint(0, thisx, thisy);
				m_lastOverFirst->SetBinContent(binx, biny, lasty / thisy);
				lastOverFirst[i] = lasty / thisy;
				h_lastOverFirst->Fill(lasty / thisy);
				neg_graph_v.at(i)->GetPoint(1, thisx, thisy);
				m_lastOverSecond->SetBinContent(binx, biny, lasty / thisy);
				lastOverSecond[i] = lasty / thisy;
				h_lastOverSecond->Fill(lasty / thisy);
				neg_graph_v.at(i)->GetPoint(2, thisx, thisy);
				m_lastOverThird->SetBinContent(binx, biny, lasty / thisy);
				lastOverThird[i] = lasty / thisy;
				h_lastOverThird->Fill(lasty / thisy);
				neg_graph_v.at(i)->GetPoint(3, thisx, thisy);
				m_lastOverFourth->SetBinContent(binx, biny, lasty / thisy);
				lastOverFourth[i] = lasty / thisy;
				h_lastOverFourth->Fill(lasty / thisx);	
				h_p0->Fill(neg_fit_func[i]->GetParameter(0));
				//cout << "n points = " << neg_graph_v.at(i)->GetN() << "  lastx = " << lastx << "   lasty = " << lasty << endl;
			}
		}
	}
	
}
//cout << "fuori eh " << endl;

//TCanvas *cred = new TCanvas();
/*residuals->SetTitle("EB");
residuals->GetXaxis()->SetTitle("last E/p scale point - fit");
residuals->Draw("");
cred->Print("residuals.pdf");
cred->Print("residuals.png");
cred->Print("residuals.root");
cred->Clear();
*/
/*
residuals01->SetTitle("1-st module");
residuals01->GetXaxis()->SetTitle("last E/p scale point - fit");
residuals01->Draw("");
cred->Print("residuals01.pdf");
cred->Print("residuals01.png");
cred->Print("residuals01.root");
cred->Clear();
residuals2->SetTitle("2-nd module");
residuals2->GetXaxis()->SetTitle("last E/p scale point - fit");
residuals2->Draw("");
cred->Print("residuals2.pdf");
cred->Print("residuals2.png");
cred->Print("residuals2.root");
cred->Clear();
residuals3->SetTitle("3-rd module");
residuals3->GetXaxis()->SetTitle("last E/p scale point - fit");
residuals3->Draw("");
cred->Print("residuals3.pdf");
cred->Print("residuals3.png");
cred->Print("residuals3.root");
cred->Clear();
residuals4->SetTitle("4-th module");
residuals4->GetXaxis()->SetTitle("last E/p scale point - fit");
residuals4->Draw("");
cred->Print("residuals4.pdf");
cred->Print("residuals4.png");
cred->Print("residuals4.root");
*/
//funcs.close();
bool corr = true;
float runFbeg = 1507886942;
//int jjeta = -65;
//for (unsigned int k = 0; k < 162; ++k)
//	cout << k << "  " << a_ietamin_neg[k] << "  " << a_ietamax_neg[k] << endl;

//getchar();
if (corr)
{
//for (unsigned int idx = 0; idx < 163; ++idx)
	//cout << idx << "  " << a_ietamax_neg[idx] << "  " << a_ietamin_neg[idx] << "  " << a_iphimin[idx] << "  " << a_iphimax[idx] << endl;
//	cout << idx << "    " << neg_fit_func[idx]->GetName() << "  " << neg_fit_func[idx]->GetParameter(1) << endl;
//getchar();

	ofstream myfile("pnregions_corrections_IC_v5_v3.txt");
	int iz = 0;
	TF1 *thisfunc;
	TGraphAsymmErrors *thisgraph;
	double lastO1 = -10., lastO2 = -10., lastO3 = -10., thisp0history = -1., thisp0history_err = -1.;

	k = 0;
	for (int ieta = -85; ieta < 86; ++ieta)
	{
		if (ieta == 0 )	continue;
		//if (ieta > 0 )	thisfunc = fit_func[0];
		//else if (ieta < 0 )	thisfunc = neg_fit_func[0];
		for (int iphi = 1; iphi < 361; ++iphi)
		{
			//myfile << ieta << " "<< iphi << " "<< iz <<" "<<  thisfunc->GetParameter(1) <<" "<<  thisfunc->GetParError(1) <<" "<<  thisfunc->GetChisquare() / thisfunc->GetNDF() << '\n';
			
			if ( ieta > 0 )
			{	
				for (unsigned int k = 0; k < 162 ; ++k)
				{
					//cout << " k = " << k << "  ieta = " << ieta << "  iphi = " << iphi << " ietamin = " << a_ietamin[k] << " eitamax = " << a_ietamax[k] << "  iphimin = " << a_iphimin[k] << "  iphimax = " << a_iphimax[k] << endl;
					if ( ieta < a_ietamax[k] + 1 && (ieta > a_ietamin[k] || ieta == a_ietamin[k]) && iphi > a_iphimin[k] && iphi < a_iphimax[k])
					{
						//cout << " inif" << endl;
						thisfunc = fit_func[k];
						thisp0history = thisfunc->Eval(runFbeg);
						/*thisgraph = graph[k];
						lastO1 = lastOverFirst[k];
						lastO2 = lastOverSecond[k];
						lastO3 = lastOverThird[k];
						thisp0history = p0history[k];
						thisp0history_err = p0history_err[k];*/
						//if (ieta > 0)	thisfunc = fit_func[k];
						//else if (ieta < 0)	thisfunc = neg_fit_func[k];
						break;
					}
				}
			}
			else if ( ieta < 0 )
			{
			for (unsigned int k = 0; k < 162 ; ++k)
				{
				  if (a_ietamin_neg[k] == -85) a_ietamin_neg[k] = -86;
				
					// // //cout << " k = " << k << "  ieta = " << ieta << "  iphi = " << iphi << " ietamin = " << a_ietamin_neg[k]  << " eitamax = " << a_ietamax_neg[k] << "  iphimin = " << a_iphimin_neg[k] << "  iphimax = " << a_iphimax_neg[k] << endl;
					
					// // //if (ieta == -85 && a_ietamin_neg[k] == -85)	a_ietamin_neg[k] = -86;	
					//cout << " k = " << k << "  ieta = " << ieta << "  iphi = " << iphi << " ietamin = " << a_ietamin_neg[k]  << " eitamax = " << a_ietamax_neg[k] << "  iphimin = " << a_iphimin_neg[k] << "  iphimax = " << a_iphimax_neg[k] << endl;
					
					//if (ieta == -85 && a_ietamin_neg[k] == 85) a_ietamin_neg[k] == -86;
					//if (ieta == -65)	{cout << " k = " << k << "  ieta = " << ieta << "  iphi = " << iphi << " ietamin = " << a_ietamin[k] << " eitamax = " << a_ietamax[k] << "  iphimin = " << a_iphimin[k] << "  iphimax = " << a_iphimax[k] << "   " << neg_fit_func[k]->GetName() << endl; getchar();}
					if ( (ieta < a_ietamax_neg[k] || ieta == a_ietamax_neg[k])  && (ieta > a_ietamin_neg[k] || ieta == a_ietamin_neg[k]) && iphi > a_iphimin[k] && iphi < a_iphimax[k])
					{
					  //cout << " inif" << endl;
						thisfunc = neg_fit_func[k];
						thisp0history = thisfunc->Eval(runFbeg);
						//if (ieta == -25)	{cout << " k = " << k << "  ieta = " << ieta << "  iphi = " << iphi << " ietamin = " << a_ietamin[k] << " eitamax = " << a_ietamax[k] << "  iphimin = " << a_iphimin[k] << "  iphimax = " << a_iphimax[k] << "   " << neg_fit_func[k]->GetName() << endl; getchar();}
						/*thisgraph = neg_graph[k];
						lastO1 = lastOverFirst_neg[k];
						lastO2 = lastOverSecond_neg[k];
						lastO3 = lastOverThird_neg[k];
						thisp0history = p0history_neg[k];
						thisp0history_err = p0history_err_neg[k];*/
						//if (ieta > 0)	thisfunc = fit_func[k];
						//else if (ieta < 0)	thisfunc = neg_fit_func[k];
						break;
					}
					//a_ietamin_neg[k] = -85;
				}
			}
			
			//cout << " dopo k kfor " << endl;
			//myfile << ieta << " "<< iphi << " "<< iz <<" "<<  thisfunc->GetParameter(1) <<" "<<  thisfunc->GetParError(1) <<" "<< thisfunc->GetParameter(0) << " " << thisfunc->GetParError(0) << " " << thisfunc->GetChisquare() / thisfunc->GetNDF() << "  " << lastO1 << " " << lastO2 << " " << lastO3  << '\n';		
			myfile << ieta << " "<< iphi << " "<< iz <<" " << thisfunc->GetParameter(1) <<" "<<  thisfunc->GetParError(1) <<" "<< thisp0history << " " << thisp0history_err << " " << 10 << " " << lastO1 << " " << lastO2 << " " << lastO3  << '\n';		
			//cout << " dopo scrittura" << endl;
		}
	}
	myfile.close();		
}	

	//cout << "shdksjdsj" << endl;		getchar();
		
		/*
	TCanvas *c510 = new TCanvas();
	c510->cd();	
	h_510->Draw();
	c510->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/h510.pdf").c_str());	
	c510->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/h510.png").c_str());	
	c510->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/h510.root").c_str());	
		
	TCanvas *cslope = new TCanvas("c","c", 1400, 700);
	cslope->cd();
	gStyle->SetOptStat(0);
	gStyle->SetPalette(55);
	map->GetZaxis()->SetRangeUser(-1.0e-07,1.0e-08);
	//map->GetZaxis()->SetNdivisions();
	map->Draw("colz");
	cslope->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/slope_map.pdf").c_str());	
	cslope->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/slope_map.png").c_str());	
	cslope->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/slope_map.root").c_str());		
	
	
	map->GetZaxis()->SetRangeUser(-4.0e-09,4.0e-09);
	map->Draw("colz");
	cslope->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/slope_map_2.pdf").c_str());	
	cslope->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/slope_map_2.png").c_str());	
	cslope->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/slope_map_2.root").c_str());
	
	gStyle->SetOptStat(1111);
	TCanvas *c_slope = new TCanvas();
	c_slope->cd();
	h_slope->Draw();
	c_slope	->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/h_slope.pdf").c_str());	
	c_slope	->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/h_slope.png").c_str());	
	
	
	TCanvas *c_p0_h = new TCanvas("c_p0_h","c_p0_h", 1400, 700);
	c_p0_h->cd();
	h_p0->Draw("colz");
	c_p0_h->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/p0_h.pdf").c_str());
	c_p0_h->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/p0_h.png").c_str());
	
	
	TCanvas *c_lastOverFirst_h = new TCanvas("c_lastOverFirst_h","c_lastOverFirst_h", 1400, 700);
	c_lastOverFirst_h->cd();
	h_lastOverFirst->Draw("colz");
	c_lastOverFirst_h->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverFirst_h.pdf").c_str());
	c_lastOverFirst_h->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverFirst_h.png").c_str());
	
	TCanvas *c_lastOverSecond_h = new TCanvas("c_lastOverSecond_h","c_lastOverSecond_h", 1400, 700);
	c_lastOverSecond_h->cd();
	h_lastOverSecond->Draw("colz");
	c_lastOverSecond_h->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverSecond_h.pdf").c_str());
	c_lastOverSecond_h->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverSecond_h.png").c_str());	
		
	TCanvas *c_lastOverThird_h = new TCanvas("c_lastOverThird_h","c_lastOverThird_h", 1400, 700);
	c_lastOverThird_h->cd();
	h_lastOverThird->Draw("colz");
	c_lastOverThird_h->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverThird_h.pdf").c_str());
	c_lastOverThird_h->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverThird_h.png").c_str());	
		
	TCanvas *c_lastOverFourth_h = new TCanvas("c_lastOverFourth_h","c_lastOverFourth_h", 1400, 700);
	c_lastOverFourth_h->cd();
	h_lastOverFourth->Draw("colz");
	c_lastOverFourth_h->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverFourth_h.pdf").c_str());
	c_lastOverFourth_h->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverFourth_h.png").c_str());	
	
	
	
	
	gStyle->SetOptStat(0);
	gStyle->SetPalette(55);
	TCanvas *c_chi2 = new TCanvas("c_chi2","c_chi2", 1400, 700);
	c_chi2->cd();
	m_chi2->GetZaxis()->SetRangeUser(0,10);
	m_chi2->Draw("colz");
	c_chi2->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/chi2_map.pdf").c_str());
	c_chi2->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/chi2_map.png").c_str());
	c_chi2->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/chi2_map.root").c_str());	
	
	TCanvas *c_p0 = new TCanvas("c_p0","c_p0", 1400, 700);
	c_p0->cd();
	m_p0->GetZaxis()->SetRangeUser(0.95,1.05);
	m_p0->Draw("colz");
	c_p0->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/p0_map.pdf").c_str());
	c_p0->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/p0_map.png").c_str());
	
	
	TCanvas *c_lastOverFirst = new TCanvas("c_lastOverFirst","c_lastOverFirst", 1400, 700);
	c_lastOverFirst->cd();
	m_lastOverFirst->GetZaxis()->SetRangeUser(0.97,1.02);
	m_lastOverFirst->Draw("colz");
	c_lastOverFirst->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverFirst_map.pdf").c_str());
	c_lastOverFirst->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverFirst_map.png").c_str());
	c_lastOverFirst->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverFirst_map.root").c_str());	
	
	TCanvas *c_lastOverSecond = new TCanvas("c_lastOverSecond","c_lastOverSecond", 1400, 700);
	c_lastOverSecond->cd();
	m_lastOverSecond->GetZaxis()->SetRangeUser(0.97,1.02);
	m_lastOverSecond->Draw("colz");
	c_lastOverSecond->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverSecond_map.pdf").c_str());
	c_lastOverSecond->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverSecond_map.png").c_str());
	c_lastOverSecond->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverSecond_map.root").c_str());		
		
	TCanvas *c_lastOverThird = new TCanvas("c_lastOverThird","c_lastOverThird", 1400, 700);
	c_lastOverThird->cd();
	m_lastOverThird->GetZaxis()->SetRangeUser(0.97,1.02);
	m_lastOverThird->Draw("colz");
	c_lastOverThird->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverThird_map.pdf").c_str());
	c_lastOverThird->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverThird_map.png").c_str());
	c_lastOverThird->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverThird_map.root").c_str());		
		
	TCanvas *c_lastOverFourth = new TCanvas("c_lastOverFourth","c_lastOverFourth", 1400, 700);
	c_lastOverFourth->cd();
	m_lastOverFourth->GetZaxis()->SetRangeUser(0.97,1.02);
	m_lastOverFourth->Draw("colz");
	c_lastOverFourth->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverFourth_map.pdf").c_str());
	c_lastOverFourth->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverFourth_map.png").c_str());	
	c_lastOverFourth->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/lastOverFourth_map.root").c_str());		
	
	
	
	
	TCanvas *c_chi2_m = new TCanvas();
	c_chi2_m->cd();
	h_chi2->Draw();
	c_chi2_m->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/fit/chi2_distr.pdf").c_str());	
	c_chi2_m->Print(("~/www/EoP/PN_region/2017/"+rereco+"/"+GT+"/fit/chi2_distr.png").c_str());	

*/
}
