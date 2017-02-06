void run444_timediffmeantimeabs_11_12()
{
//=========Macro generated from canvas: c_5e48560_projection_100001/Canvas_1_n2
//=========  (Mon Jan 16 11:33:32 2017) by ROOT version6.06/08
   TCanvas *c_5e48560_projection_100001 = new TCanvas("c_5e48560_projection_100001", "Canvas_1_n2",218,118,700,522);
   gStyle->SetOptFit(1);
   c_5e48560_projection_100001->ToggleEventStatus();
   c_5e48560_projection_100001->Range(-12.8125,-0.6457245,12.8125,2.80122);
   c_5e48560_projection_100001->SetFillColor(0);
   c_5e48560_projection_100001->SetBorderMode(0);
   c_5e48560_projection_100001->SetBorderSize(2);
   c_5e48560_projection_100001->SetLogy();
   c_5e48560_projection_100001->SetGridx();
   c_5e48560_projection_100001->SetGridy();
   c_5e48560_projection_100001->SetFrameBorderMode(0);
   c_5e48560_projection_100001->SetFrameBorderMode(0);
   
   TH1D *slice_px_of_TimeDiffMeanTimeAbs_11_12__1 = new TH1D("slice_px_of_TimeDiffMeanTimeAbs_11_12__1","TimeDiffMeanTimeAbs ch11 - ch12",320,-80.25,79.75);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(155,5);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(156,22);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(157,19);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(158,44);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(159,70);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(160,135);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(161,151);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(162,131);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(163,121);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(164,89);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(165,63);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(166,30);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(167,20);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(168,9);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(169,2);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(170,3);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(172,1);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetBinContent(173,1);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetEntries(916);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.615,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *AText = ptstats->AddText("Entries = 916    ");
   AText = ptstats->AddText("Mean  = 0.3646");
   AText = ptstats->AddText("Std Dev   =  1.314 #pm 0.03071");
   AText = ptstats->AddText("Underflow =      0");
   AText = ptstats->AddText("Overflow  =      0");
   AText = ptstats->AddText("Integral =    916");
   ptstats->SetOptStat(1112110);
   ptstats->SetOptFit(11);
   ptstats->Draw();
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(slice_px_of_TimeDiffMeanTimeAbs_11_12__1);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetFillColor(38);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->SetLineColor(ci);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->GetXaxis()->SetTitle("ns");
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->GetXaxis()->SetRange(141,181);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->GetXaxis()->SetLabelFont(42);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->GetXaxis()->SetLabelSize(0.035);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->GetXaxis()->SetTitleSize(0.035);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->GetXaxis()->SetTitleFont(42);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->GetYaxis()->SetTitle("Number of Entries");
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->GetYaxis()->SetLabelFont(42);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->GetYaxis()->SetLabelSize(0.035);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->GetYaxis()->SetTitleSize(0.035);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->GetYaxis()->SetTitleFont(42);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->GetZaxis()->SetLabelFont(42);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->GetZaxis()->SetLabelSize(0.035);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->GetZaxis()->SetTitleSize(0.035);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->GetZaxis()->SetTitleFont(42);
   slice_px_of_TimeDiffMeanTimeAbs_11_12__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.1518911,0.9342405,0.8481089,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   AText = pt->AddText("TimeDiffMeanTimeAbs ch11 - ch12");
   pt->Draw();
   c_5e48560_projection_100001->Modified();
   c_5e48560_projection_100001->cd();
   c_5e48560_projection_100001->SetSelected(c_5e48560_projection_100001);
}
