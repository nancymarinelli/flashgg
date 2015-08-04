import ROOT

#f = ROOT.TFile("outputFromNewMicroAODWithHLTCand_cut4.root")
#f = ROOT.TFile("output_full5x5R9_pt2020_rhoCorr_phoMass_fixIso_fixCut.root")
f = ROOT.TFile("output_newHoe007.root")

#canvases = []

#canvases.append(ROOT.TCanvas("c"+str(len(canvases)), ""))

effInCat=["effInCat0","effInCat1","effInCat2","effInCat3"]
hlteffInCat=["hlteffInCat0","hlteffInCat1","hlteffInCat2","hlteffInCat3"]
nMinus1_pt=["nMinus1_ptCat0","nMinus1_ptCat1","nMinus1_ptCat2","nMinus1_ptCat3"]
nMinus1_hoe=["nMinus1_hoeCat0","nMinus1_hoeCat1","nMinus1_hoeCat2","nMinus1_hoeCat3"]
nMinus1_r9=["nMinus1_r9Cat0","nMinus1_r9Cat1","nMinus1_r9Cat2","nMinus1_r9Cat3"]
nMinus1_sieie=["nMinus1_sieieCat0","nMinus1_sieieCat1","nMinus1_sieieCat2","nMinus1_sieieCat3"]
nMinus1_phoIso=["nMinus1_phoIsoCat0","nMinus1_phoIsoCat1","nMinus1_phoIsoCat2","nMinus1_phoIsoCat3"]
nMinus1_chIso=["nMinus1_chIsoCat0","nMinus1_chIsoCat1","nMinus1_chIsoCat2","nMinus1_chIsoCat3"]
nMinus1_mass=["nMinus1_massCat0","nMinus1_massCat1","nMinus1_massCat2","nMinus1_massCat3"]

YtitleSize=0.5

for i in xrange(4):
    can = ROOT.TCanvas("Plots","Plots")
    can.Divide(2,2)
    h_pt_lead_tot = f.Get("h_pt_lead_tot_cat"+str(i))
    h_pt_lead_tot.GetYaxis().SetTitle("Efficiency")
    h_pt_lead_tot.GetYaxis().SetTitleSize(YtitleSize)
    h_pt_lead_offl = f.Get("h_pt_lead_offl_cat"+str(i))
    h_pt_lead_offl.GetYaxis().SetTitle("Efficiency")
    h_pt_lead_offl.GetYaxis().SetTitleSize(YtitleSize)
    h_pt_sublead_tot = f.Get("h_pt_sublead_tot_cat"+str(i))
    h_pt_sublead_tot.GetYaxis().SetTitle("Efficiency")
    h_pt_sublead_tot.GetYaxis().SetTitleSize(YtitleSize)
    h_pt_sublead_offl = f.Get("h_pt_sublead_offl_cat"+str(i))
    h_pt_sublead_offl.GetYaxis().SetTitle("Efficiency")
    h_pt_sublead_offl.GetYaxis().SetTitleSize(YtitleSize)
    h_eta_lead_tot = f.Get("h_eta_lead_tot_cat"+str(i))
    h_eta_lead_tot.GetYaxis().SetTitle("Efficiency")
    h_eta_lead_tot.GetYaxis().SetTitleSize(YtitleSize)
    h_eta_lead_offl = f.Get("h_eta_lead_offl_cat"+str(i))
    h_eta_lead_offl.GetYaxis().SetTitle("Efficiency")
    h_eta_lead_offl.GetYaxis().SetTitleSize(YtitleSize)
    h_eta_sublead_tot = f.Get("h_eta_sublead_tot_cat"+str(i))
    h_eta_sublead_tot.GetYaxis().SetTitle("Efficiency")
    h_eta_sublead_tot.GetYaxis().SetTitleSize(YtitleSize)
    h_eta_sublead_offl = f.Get("h_eta_sublead_offl_cat"+str(i))
    h_eta_sublead_offl.GetYaxis().SetTitle("Efficiency")
    h_eta_sublead_offl.GetYaxis().SetTitleSize(YtitleSize)
    eff_pt_lead = ROOT.TEfficiency(h_pt_lead_offl,h_pt_lead_tot)
    eff_pt_sublead = ROOT.TEfficiency(h_pt_sublead_offl,h_pt_sublead_tot)
    eff_eta_lead = ROOT.TEfficiency(h_eta_lead_offl,h_eta_lead_tot)
    eff_eta_sublead = ROOT.TEfficiency(h_eta_sublead_offl,h_eta_sublead_tot)
    can.cd(1)
    eff_pt_lead.Draw()
    eff_pt_lead.SetMarkerStyle(20)
    eff_pt_lead.SetMarkerSize(0.5)
    eff_pt_lead.SetMarkerColor(ROOT.kBlue)
    eff_pt_lead.SetLineWidth(1)
    eff_pt_lead.SetLineColor(4)
    can.cd(2)
    eff_pt_sublead.Draw()
    eff_pt_sublead.SetMarkerStyle(20)
    eff_pt_sublead.SetMarkerSize(0.5)
    eff_pt_sublead.SetMarkerColor(ROOT.kBlue)
    eff_pt_sublead.SetLineWidth(1)
    eff_pt_sublead.SetLineColor(4)
    can.cd(3)
    eff_eta_lead.Draw()
    eff_eta_lead.SetMarkerStyle(20)
    eff_eta_lead.SetMarkerSize(0.5)
    eff_eta_lead.SetMarkerColor(ROOT.kBlue)
    eff_eta_lead.SetLineWidth(1)
    eff_eta_lead.SetLineColor(4)
    can.cd(4)
    eff_eta_sublead.Draw()
    eff_eta_sublead.SetMarkerStyle(20)
    eff_eta_sublead.SetMarkerSize(0.5)
    eff_eta_sublead.SetMarkerColor(ROOT.kBlue)
    eff_eta_sublead.SetLineWidth(1)
    eff_eta_sublead.SetLineColor(4)
    can.Update()
    eff_eta_lead.GetPaintedGraph().GetYaxis().SetRangeUser(0.,1.05)
    eff_eta_sublead.GetPaintedGraph().GetYaxis().SetRangeUser(0.,1.05)
    can.SaveAs("testPlots/preseleff_cat"+str(i)+".pdf")



for i in xrange(4):
    can = ROOT.TCanvas("Plots","Plots")
    can.Divide(2,2)
    h_pt_lead_hlt = f.Get("h_pt_lead_hlt_cat"+str(i))
    h_pt_lead_hlt.GetYaxis().SetTitle("Efficiency")
    h_pt_lead_hlt.GetYaxis().SetTitleSize(YtitleSize)
    h_pt_lead_offl = f.Get("h_pt_lead_offl_cat"+str(i))
    h_pt_lead_offl.GetYaxis().SetTitle("Efficiency")
    h_pt_lead_offl.GetYaxis().SetTitleSize(YtitleSize)
    h_pt_sublead_hlt = f.Get("h_pt_sublead_hlt_cat"+str(i))
    h_pt_sublead_hlt.GetYaxis().SetTitle("Efficiency")
    h_pt_sublead_hlt.GetYaxis().SetTitleSize(YtitleSize)
    h_pt_sublead_offl = f.Get("h_pt_sublead_offl_cat"+str(i))
    h_pt_sublead_offl.GetYaxis().SetTitle("Efficiency")
    h_pt_sublead_offl.GetYaxis().SetTitleSize(YtitleSize)
    h_eta_lead_hlt = f.Get("h_eta_lead_hlt_cat"+str(i))
    h_eta_lead_hlt.GetYaxis().SetTitle("Efficiency")
    h_eta_lead_hlt.GetYaxis().SetTitleSize(YtitleSize)
    h_eta_lead_offl = f.Get("h_eta_lead_offl_cat"+str(i))
    h_eta_lead_offl.GetYaxis().SetTitle("Efficiency")
    h_eta_lead_offl.GetYaxis().SetTitleSize(YtitleSize)
    h_eta_sublead_hlt = f.Get("h_eta_sublead_hlt_cat"+str(i))
    h_eta_sublead_hlt.GetYaxis().SetTitle("Efficiency")
    h_eta_sublead_hlt.GetYaxis().SetTitleSize(YtitleSize)
    h_eta_sublead_offl = f.Get("h_eta_sublead_offl_cat"+str(i))
    h_eta_sublead_offl.GetYaxis().SetTitle("Efficiency")
    h_eta_sublead_offl.GetYaxis().SetTitleSize(YtitleSize)
    hlteff_pt_lead = ROOT.TEfficiency(h_pt_lead_hlt,h_pt_lead_offl)
    hlteff_pt_sublead = ROOT.TEfficiency(h_pt_sublead_hlt,h_pt_sublead_offl)
    hlteff_eta_lead = ROOT.TEfficiency(h_eta_lead_hlt,h_eta_lead_offl)
    hlteff_eta_sublead = ROOT.TEfficiency(h_eta_sublead_hlt,h_eta_sublead_offl)
    can.cd(1)
    hlteff_pt_lead.Draw()
    hlteff_pt_lead.SetMarkerStyle(20)
    hlteff_pt_lead.SetMarkerSize(0.5)
    hlteff_pt_lead.SetMarkerColor(ROOT.kBlue)
    hlteff_pt_lead.SetLineWidth(1)
    hlteff_pt_lead.SetLineColor(4)
    can.cd(2)
    hlteff_pt_sublead.Draw()
    hlteff_pt_sublead.SetMarkerStyle(20)
    hlteff_pt_sublead.SetMarkerSize(0.5)
    hlteff_pt_sublead.SetMarkerColor(ROOT.kBlue)
    hlteff_pt_sublead.SetLineWidth(1)
    hlteff_pt_sublead.SetLineColor(4)
    can.cd(3)
    hlteff_eta_lead.Draw()
    hlteff_eta_lead.SetMarkerStyle(20)
    hlteff_eta_lead.SetMarkerSize(0.5)
    hlteff_eta_lead.SetMarkerColor(ROOT.kBlue)
    hlteff_eta_lead.SetLineWidth(1)
    hlteff_eta_lead.SetLineColor(4)
    can.cd(4)
    hlteff_eta_sublead.Draw()
    hlteff_eta_sublead.SetMarkerStyle(20)
    hlteff_eta_sublead.SetMarkerSize(0.5)
    hlteff_eta_sublead.SetMarkerColor(ROOT.kBlue)
    hlteff_eta_sublead.SetLineWidth(1)
    hlteff_eta_sublead.SetLineColor(4)
    can.Update()
    hlteff_eta_lead.GetPaintedGraph().GetYaxis().SetRangeUser(0,1.03)
    hlteff_eta_sublead.GetPaintedGraph().GetYaxis().SetRangeUser(0.,1.03)
    can.SaveAs("testPlots/hlteff_cat"+str(i)+".pdf")




for i in xrange(4):
    can = ROOT.TCanvas("Plots","Plots")
    h_nMin1_pt_hlt = f.Get("h_nMin1_pt_hlt_cat"+str(i))
    h_nMin1_pt_offl = f.Get("h_nMin1_pt_offl_cat"+str(i))
    h_nMin1_pt_offl.GetYaxis().SetTitle("Efficiency")
    hlteff_nMin1_pt = ROOT.TEfficiency (h_nMin1_pt_hlt, h_nMin1_pt_offl)
    hlteff_nMin1_pt.Draw()
    hlteff_nMin1_pt.SetMarkerStyle(20)
    hlteff_nMin1_pt.SetMarkerSize(0.8)
    hlteff_nMin1_pt.SetMarkerColor(ROOT.kBlue)
    hlteff_nMin1_pt.SetLineWidth(2)
    hlteff_nMin1_pt.SetLineColor(4)
    can.Update()
    can.SaveAs("testPlots/hlteff_nMin1_pt_cat"+str(i)+".pdf")


for i in xrange(4):
    can = ROOT.TCanvas("Plots","Plots")
    h_nMin1_hoe_hlt = f.Get("h_nMin1_hoe_hlt_cat"+str(i))
    h_nMin1_hoe_offl = f.Get("h_nMin1_hoe_offl_cat"+str(i))
    h_nMin1_hoe_offl.GetYaxis().SetTitle("Efficiency")
    hlteff_nMin1_hoe = ROOT.TEfficiency (h_nMin1_hoe_hlt, h_nMin1_hoe_offl)
    hlteff_nMin1_hoe.Draw()
    hlteff_nMin1_hoe.SetMarkerStyle(20)
    hlteff_nMin1_hoe.SetMarkerSize(0.8)
    hlteff_nMin1_hoe.SetMarkerColor(ROOT.kBlue)
    hlteff_nMin1_hoe.SetLineWidth(2)
    hlteff_nMin1_hoe.SetLineColor(4)
    can.Update()
    hlteff_nMin1_hoe.GetPaintedGraph().GetXaxis().SetRangeUser(0.,0.2)
    can.SaveAs("testPlots/hlteff_nMin1_hoe_cat"+str(i)+".pdf")





for i in xrange(4):
    can = ROOT.TCanvas("Plots","Plots")
    h_nMin1_r9_hlt = f.Get("h_nMin1_r9_hlt_cat"+str(i))
    h_nMin1_r9_offl = f.Get("h_nMin1_r9_offl_cat"+str(i))
    h_nMin1_r9_offl.GetYaxis().SetTitle("Efficiency")
    hlteff_nMin1_r9 = ROOT.TEfficiency (h_nMin1_r9_hlt, h_nMin1_r9_offl)
    hlteff_nMin1_r9.Draw()
    hlteff_nMin1_r9.SetMarkerStyle(20)
    hlteff_nMin1_r9.SetMarkerSize(0.8)
    hlteff_nMin1_r9.SetMarkerColor(ROOT.kBlue)
    hlteff_nMin1_r9.SetLineWidth(2)
    hlteff_nMin1_r9.SetLineColor(4)
    can.Update()
    hlteff_nMin1_r9.GetPaintedGraph().GetXaxis().SetRangeUser(0.,1.1)
    can.SaveAs("testPlots/hlteff_nMin1_r9_cat"+str(i)+".pdf")


for i in xrange(4):
    can = ROOT.TCanvas("Plots","Plots")
    h_nMin1_r9_hlt = f.Get("h_nMin1_r9_low_hlt_cat"+str(i))
    h_nMin1_r9_offl = f.Get("h_nMin1_r9_low_offl_cat"+str(i))
    h_nMin1_r9_offl.GetYaxis().SetTitle("Efficiency")
    hlteff_nMin1_r9 = ROOT.TEfficiency (h_nMin1_r9_hlt, h_nMin1_r9_offl)
    hlteff_nMin1_r9.Draw()
    hlteff_nMin1_r9.SetMarkerStyle(20)
    hlteff_nMin1_r9.SetMarkerSize(0.8)
    hlteff_nMin1_r9.SetMarkerColor(ROOT.kBlue)
    hlteff_nMin1_r9.SetLineWidth(2)
    hlteff_nMin1_r9.SetLineColor(4)
    can.Update()
    hlteff_nMin1_r9.GetPaintedGraph().GetXaxis().SetRangeUser(0.,1.1)
    can.SaveAs("testPlots/hlteff_nMin1_r9_low_cat"+str(i)+".pdf")



for i in xrange(4):
    can = ROOT.TCanvas("Plots","Plots")
    h_nMin1_r9_hlt = f.Get("h_nMin1_r9_high_hlt_cat"+str(i))
    h_nMin1_r9_offl = f.Get("h_nMin1_r9_high_offl_cat"+str(i))
    h_nMin1_r9_offl.GetYaxis().SetTitle("Efficiency")
    hlteff_nMin1_r9 = ROOT.TEfficiency (h_nMin1_r9_hlt, h_nMin1_r9_offl)
    hlteff_nMin1_r9.Draw()
    hlteff_nMin1_r9.SetMarkerStyle(20)
    hlteff_nMin1_r9.SetMarkerSize(0.8)
    hlteff_nMin1_r9.SetMarkerColor(ROOT.kBlue)
    hlteff_nMin1_r9.SetLineWidth(2)
    hlteff_nMin1_r9.SetLineColor(4)
    can.Update()
    hlteff_nMin1_r9.GetPaintedGraph().GetXaxis().SetRangeUser(0.,1.1)
    can.SaveAs("testPlots/hlteff_nMin1_r9_high_cat"+str(i)+".pdf")





for i in xrange(4):
    can = ROOT.TCanvas("Plots","Plots")
    h_nMin1_sieie_hlt = f.Get("h_nMin1_sieie_hlt_cat"+str(i))
    h_nMin1_sieie_offl = f.Get("h_nMin1_sieie_offl_cat"+str(i))
    h_nMin1_sieie_offl.GetYaxis().SetTitle("Efficiency")
    hlteff_nMin1_sieie = ROOT.TEfficiency (h_nMin1_sieie_hlt, h_nMin1_sieie_offl)
    hlteff_nMin1_sieie.Draw()
    hlteff_nMin1_sieie.SetMarkerStyle(20)
    hlteff_nMin1_sieie.SetMarkerSize(0.8)
    hlteff_nMin1_sieie.SetMarkerColor(ROOT.kBlue)
    hlteff_nMin1_sieie.SetLineWidth(2)
    hlteff_nMin1_sieie.SetLineColor(4)
    can.Update()
    can.SaveAs("testPlots/hlteff_nMin1_sieie_cat"+str(i)+".pdf")


for i in xrange(4):
    can = ROOT.TCanvas("Plots","Plots")
    h_nMin1_phoIso_hlt = f.Get("h_nMin1_phoIso_hlt_cat"+str(i))
    h_nMin1_phoIso_offl = f.Get("h_nMin1_phoIso_offl_cat"+str(i))
    h_nMin1_phoIso_offl.GetYaxis().SetTitle("Efficiency")
    hlteff_nMin1_phoIso = ROOT.TEfficiency (h_nMin1_phoIso_hlt, h_nMin1_phoIso_offl)
    hlteff_nMin1_phoIso.Draw()
    hlteff_nMin1_phoIso.SetMarkerStyle(20)
    hlteff_nMin1_phoIso.SetMarkerSize(0.8)
    hlteff_nMin1_phoIso.SetMarkerColor(ROOT.kBlue)
    hlteff_nMin1_phoIso.SetLineWidth(2)
    hlteff_nMin1_phoIso.SetLineColor(4)
    can.Update()
    hlteff_nMin1_phoIso.GetPaintedGraph().GetXaxis().SetRangeUser(0.,10.)
    can.SaveAs("testPlots/hlteff_nMin1_phoIso_cat"+str(i)+".pdf")



for i in xrange(4):
    can = ROOT.TCanvas("Plots","Plots")
    h_nMin1_chIso_hlt = f.Get("h_nMin1_chIso_hlt_cat"+str(i))
    h_nMin1_chIso_offl = f.Get("h_nMin1_chIso_offl_cat"+str(i))
    h_nMin1_chIso_offl.GetYaxis().SetTitle("Efficiency")
    hlteff_nMin1_chIso = ROOT.TEfficiency (h_nMin1_chIso_hlt, h_nMin1_chIso_offl)
    hlteff_nMin1_chIso.Draw()
    hlteff_nMin1_chIso.SetMarkerStyle(20)
    hlteff_nMin1_chIso.SetMarkerSize(0.8)
    hlteff_nMin1_chIso.SetMarkerColor(ROOT.kBlue)
    hlteff_nMin1_chIso.SetLineWidth(2)
    hlteff_nMin1_chIso.SetLineColor(4)
    can.Update()
    hlteff_nMin1_chIso.GetPaintedGraph().GetXaxis().SetRangeUser(0.,6.)
    can.SaveAs("testPlots/hlteff_nMin1_chIso_cat"+str(i)+".pdf")




for i in xrange(4):
    can = ROOT.TCanvas("Plots","Plots")
    h_nMin1_mass_hlt = f.Get("h_nMin1_mass_hlt_cat"+str(i))
    h_nMin1_mass_offl = f.Get("h_nMin1_mass_offl_cat"+str(i))
    h_nMin1_mass_offl.GetYaxis().SetTitle("Efficiency")
    hlteff_nMin1_mass = ROOT.TEfficiency (h_nMin1_mass_hlt, h_nMin1_mass_offl)
    hlteff_nMin1_mass.Draw()
    hlteff_nMin1_mass.SetMarkerStyle(20)
    hlteff_nMin1_mass.SetMarkerSize(0.8)
    hlteff_nMin1_mass.SetMarkerColor(ROOT.kBlue)
    hlteff_nMin1_mass.SetLineWidth(2)
    hlteff_nMin1_mass.SetLineColor(4)
    can.Update()
    hlteff_nMin1_mass.GetPaintedGraph().GetXaxis().SetRangeUser(80.,140.)
    can.SaveAs("testPlots/hlteff_nMin1_mass_cat"+str(i)+".pdf")






all_total=0
all_pass=0
all_hlt=0
print "   "
print "   "
print " Pre-selection efficiency on the signal "
for i in xrange(4):
    h_eta_lead_tot = f.Get("h_eta_lead_tot_cat"+str(i))
    h_eta_sublead_tot = f.Get("h_eta_sublead_tot_cat"+str(i))
    h_eta_lead_offl = f.Get("h_eta_lead_offl_cat"+str(i))
    h_eta_sublead_offl = f.Get("h_eta_sublead_offl_cat"+str(i))
    all_total+=h_eta_lead_tot.GetEntries()
    all_total+=h_eta_sublead_tot.GetEntries()
    all_pass+=h_eta_lead_offl.GetEntries()
    all_pass+=h_eta_sublead_offl.GetEntries()
    effInCat[i]=(h_eta_lead_offl.GetEntries()+h_eta_sublead_offl.GetEntries())/(h_eta_lead_tot.GetEntries()+h_eta_sublead_tot.GetEntries())
    print "_Cat_"+str(i)+"_total_ = %4i"%(h_eta_lead_tot.GetEntries()+h_eta_sublead_tot.GetEntries()),"__ pass %4i"%(h_eta_lead_offl.GetEntries()+h_eta_sublead_offl.GetEntries()),"__ Presel Eff = %1.3f"%(effInCat[i])

eff=all_pass/all_total
print "Total = %4i"%(all_total)," passing = %4i"%(all_pass)," global eff = %1.3f"%(eff)

all_pass=0
print "   "
print "   "
print " Hlt efficiency w.r.t. pre-selection "
for i in xrange(4):
    h_eta_lead_offl = f.Get("h_eta_lead_offl_cat"+str(i))
    h_eta_sublead_offl = f.Get("h_eta_sublead_offl_cat"+str(i))
    h_eta_lead_hlt = f.Get("h_eta_lead_hlt_cat"+str(i))
    h_eta_sublead_hlt = f.Get("h_eta_sublead_hlt_cat"+str(i))
    all_pass+=h_eta_lead_offl.GetEntries()
    all_pass+=h_eta_sublead_offl.GetEntries()
    all_hlt+=h_eta_lead_hlt.GetEntries()
    all_hlt+=h_eta_sublead_hlt.GetEntries()
    effInCat[i]=(h_eta_lead_hlt.GetEntries()+h_eta_sublead_hlt.GetEntries())/(h_eta_lead_offl.GetEntries()+h_eta_sublead_offl.GetEntries())
    print "_Cat_"+str(i)+"_total_ = %4i"%(h_eta_lead_offl.GetEntries()+h_eta_sublead_offl.GetEntries()),"__ pass %4i"%(h_eta_lead_hlt.GetEntries()+h_eta_sublead_hlt.GetEntries()),"__ Hlt Eff = %1.3f"%(effInCat[i])

eff=all_hlt/all_pass
print "Total = %4i"%(all_pass)," passing = %4i"%(all_hlt)," avg hlt eff = %1.3f"%(eff)




#///////////////////////////////////
all_pass=0
all_tot=0
print "   "
print "   "
print "____________ Presel N-1 efficiencies: minus pt  _______________ "
for i in xrange(4):
    h_eta_lead_tot = f.Get("h_eta_lead_tot_cat"+str(i))
    h_eta_sublead_tot = f.Get("h_eta_sublead_tot_cat"+str(i))
    h_nMin1_pt_offl = f.Get("h_nMin1_pt_offl_cat"+str(i))
    all_tot+=h_eta_lead_tot.GetEntries()
    all_tot+=h_eta_sublead_tot.GetEntries()
    all_pass+=h_nMin1_pt_offl.GetEntries()
    nMinus1_pt[i]=h_nMin1_pt_offl.GetEntries()/(h_eta_lead_tot.GetEntries()+h_eta_sublead_tot.GetEntries())
    print "_Cat_"+str(i)+"_total = %4i"%(h_eta_lead_tot.GetEntries()+h_eta_sublead_tot.GetEntries()),"_passing presel minus Pt %4i"%(h_nMin1_pt_offl.GetEntries()),"__Eff = %1.3f"%(nMinus1_pt[i])  

eff=all_pass/all_tot  
print "Total = %4i"%(all_tot)," passing = %4i"%(all_pass)," avg eff = %1.3f"%(eff)

all_pass=0
print "   "
print "   "
print "____________ Presel N-1 efficiencies: minus hoe  _______________ "
for i in xrange(4):
    h_eta_lead_tot = f.Get("h_eta_lead_tot_cat"+str(i))
    h_eta_sublead_tot = f.Get("h_eta_sublead_tot_cat"+str(i))
    h_nMin1_hoe_offl = f.Get("h_nMin1_hoe_offl_cat"+str(i))
    all_pass+=h_nMin1_hoe_offl.GetEntries()
    nMinus1_hoe[i]=h_nMin1_hoe_offl.GetEntries()/(h_eta_lead_tot.GetEntries()+h_eta_sublead_tot.GetEntries())
    print "_Cat_"+str(i)+"_total = %4i"%(h_eta_lead_tot.GetEntries()+h_eta_sublead_tot.GetEntries()),"_passing presel minus Pt %4i"%(h_nMin1_hoe_offl.GetEntries()),"__Eff = %1.3f"%(nMinus1_hoe[i])    

eff=all_pass/all_tot  
print "Total = %4i"%(all_tot)," passing = %4i"%(all_pass)," avg eff = %1.3f"%(eff)

all_pass=0
print "   "
print "   "
print "____________ Presel N-1 efficiencies: minus r9  _______________ "
for i in xrange(4):
    h_eta_lead_tot = f.Get("h_eta_lead_tot_cat"+str(i))
    h_eta_sublead_tot = f.Get("h_eta_sublead_tot_cat"+str(i))
    h_nMin1_r9_offl = f.Get("h_nMin1_r9_offl_cat"+str(i))
    all_pass+=h_nMin1_r9_offl.GetEntries()
    nMinus1_r9[i]=h_nMin1_r9_offl.GetEntries()/(h_eta_lead_tot.GetEntries()+h_eta_sublead_tot.GetEntries())
    print "_Cat_"+str(i)+"_total = %4i"%(h_eta_lead_tot.GetEntries()+h_eta_sublead_tot.GetEntries()),"_passing presel minus Pt %4i"%(h_nMin1_r9_offl.GetEntries()),"__Eff = %1.3f"%(nMinus1_r9[i])    


eff=all_pass/all_tot  
print "Total = %4i"%(all_tot)," passing = %4i"%(all_pass)," avg eff = %1.3f"%(eff)



all_pass=0
print "   "
print "   "
print "____________ Presel N-1 efficiencies: minus sieie  _______________ "
for i in xrange(4):
    h_eta_lead_tot = f.Get("h_eta_lead_tot_cat"+str(i))
    h_eta_sublead_tot = f.Get("h_eta_sublead_tot_cat"+str(i))
    h_nMin1_sieie_offl = f.Get("h_nMin1_sieie_offl_cat"+str(i))
    all_pass+=h_nMin1_sieie_offl.GetEntries()
    nMinus1_sieie[i]=h_nMin1_sieie_offl.GetEntries()/(h_eta_lead_tot.GetEntries()+h_eta_sublead_tot.GetEntries())
    print "_Cat_"+str(i)+"_total = %4i"%(h_eta_lead_tot.GetEntries()+h_eta_sublead_tot.GetEntries()),"_passing presel minus Pt %4i"%(h_nMin1_sieie_offl.GetEntries()),"__Eff = %1.3f"%(nMinus1_sieie[i])    


eff=all_pass/all_tot  
print "Total = %4i"%(all_tot)," passing = %4i"%(all_pass)," avg eff = %1.3f"%(eff)



all_pass=0
print "   "
print "   "
print "____________ Presel N-1 efficiencies: minus phoIso  _______________ "
for i in xrange(4):
    h_eta_lead_tot = f.Get("h_eta_lead_tot_cat"+str(i))
    h_eta_sublead_tot = f.Get("h_eta_sublead_tot_cat"+str(i))
    h_nMin1_phoIso_offl = f.Get("h_nMin1_phoIso_offl_cat"+str(i))
    all_pass+=h_nMin1_phoIso_offl.GetEntries()
    nMinus1_phoIso[i]=h_nMin1_phoIso_offl.GetEntries()/(h_eta_lead_tot.GetEntries()+h_eta_sublead_tot.GetEntries())
    print "_Cat_"+str(i)+"_total = %4i"%(h_eta_lead_tot.GetEntries()+h_eta_sublead_tot.GetEntries()),"_passing presel minus Pt %4i"%(h_nMin1_phoIso_offl.GetEntries()),"__Eff = %1.3f"%(nMinus1_phoIso[i])   


eff=all_pass/all_tot  
print "Total = %4i"%(all_tot)," passing = %4i"%(all_pass)," avg eff = %1.3f"%(eff)

 
all_pass=0
print "   "
print "   "
print "____________ Presel N-1 efficiencies: minus chIso  _______________ "
for i in xrange(4):
    h_eta_lead_tot = f.Get("h_eta_lead_tot_cat"+str(i))
    h_eta_sublead_tot = f.Get("h_eta_sublead_tot_cat"+str(i))
    h_nMin1_chIso_offl = f.Get("h_nMin1_chIso_offl_cat"+str(i))
    all_pass+=h_nMin1_chIso_offl.GetEntries()
    nMinus1_chIso[i]=h_nMin1_chIso_offl.GetEntries()/(h_eta_lead_tot.GetEntries()+h_eta_sublead_tot.GetEntries())
    print "_Cat_"+str(i)+"_total = %4i"%(h_eta_lead_tot.GetEntries()+h_eta_sublead_tot.GetEntries()),"_passing presel minus Pt %4i"%(h_nMin1_chIso_offl.GetEntries()),"__Eff = %1.3f"%(nMinus1_chIso[i])    


eff=all_pass/all_tot  
print "Total = %4i"%(all_tot)," passing = %4i"%(all_pass)," avg eff = %1.3f"%(eff)


all_pass=0
print "   "
print "   "
print "____________ Presel N-1 efficiencies: minus mass  _______________ "
for i in xrange(4):
    h_eta_lead_tot = f.Get("h_eta_lead_tot_cat"+str(i))
    h_eta_sublead_tot = f.Get("h_eta_sublead_tot_cat"+str(i))
    h_nMin1_mass_offl = f.Get("h_nMin1_mass_offl_cat"+str(i))
    all_pass+=h_nMin1_mass_offl.GetEntries()
#    print " entries  %4i" %h_nMin1_mass_offl.GetEntries()
    nMinus1_mass[i]=(h_nMin1_mass_offl.GetEntries()*2)/(h_eta_lead_tot.GetEntries()+h_eta_sublead_tot.GetEntries())
    print "_Cat_"+str(i)+"_total = %4i"%(h_eta_lead_tot.GetEntries()+h_eta_sublead_tot.GetEntries()),"_passing presel minus Mass %4i"%(h_nMin1_mass_offl.GetEntries()*2),"__Eff = %1.3f"%(nMinus1_mass[i])    


eff=all_pass*2/all_tot  
print "Total = %4i"%(all_tot)," passing = %4i"%(all_pass)," avg eff = %1.3f"%(eff)


#///////////////////////////////////
print "   "
print "   "
print "____________ Hlt N-1 efficiencies: minus pt  _______________ "
pt_offl=0
pt_hlt=0
for i in xrange(4):
    h_nMin1_pt_offl = f.Get("h_nMin1_pt_offl_cat"+str(i))
    h_nMin1_pt_hlt = f.Get("h_nMin1_pt_hlt_cat"+str(i))
    pt_offl+=h_nMin1_pt_offl.GetEntries()
    pt_hlt+=h_nMin1_pt_hlt.GetEntries()
    nMinus1_pt[i]=h_nMin1_pt_hlt.GetEntries()/h_nMin1_pt_offl.GetEntries()
    print "_Cat_"+str(i)+"__passing minus Pt = %4i"%(h_nMin1_pt_offl.GetEntries()),"__ plus Hlt %4i"%(h_nMin1_pt_hlt.GetEntries()),"__ hlt Eff = %1.3f"%(nMinus1_pt[i])    


print "   "
print "   "
print "____________ Hlt N-1 efficiencies: minus hoe  _______________ "
hoe_offl=0
hoe_hlt=0
for i in xrange(4):
    h_nMin1_hoe_offl = f.Get("h_nMin1_hoe_offl_cat"+str(i))
    h_nMin1_hoe_hlt = f.Get("h_nMin1_hoe_hlt_cat"+str(i))
    hoe_offl+=h_nMin1_hoe_offl.GetEntries()
    hoe_hlt+=h_nMin1_hoe_hlt.GetEntries()
    nMinus1_hoe[i]=h_nMin1_hoe_hlt.GetEntries()/h_nMin1_hoe_offl.GetEntries()
    print "_Cat_"+str(i)+"__passing minus Hoe = %4i"%(h_nMin1_hoe_offl.GetEntries()),"__ plus Hlt %4i"%(h_nMin1_hoe_hlt.GetEntries()),"__ hlt Eff = %1.3f"%(nMinus1_hoe[i])    

print "   "
print "   "
print "____________ Hlt N-1 efficiencies: minus r9  _______________ "
r9_offl=0
r9_hlt=0
for i in xrange(4):
    h_nMin1_r9_offl = f.Get("h_nMin1_r9_offl_cat"+str(i))
    h_nMin1_r9_hlt = f.Get("h_nMin1_r9_hlt_cat"+str(i))
    r9_offl+=h_nMin1_r9_offl.GetEntries()
    r9_hlt+=h_nMin1_r9_hlt.GetEntries()
    nMinus1_r9[i]=h_nMin1_r9_hlt.GetEntries()/h_nMin1_r9_offl.GetEntries()
    print "_Cat_"+str(i)+"__passing minus R9 = %4i"%(h_nMin1_r9_offl.GetEntries()),"__ plus Hlt %4i"%(h_nMin1_r9_hlt.GetEntries()),"__ hlt Eff = %1.3f"%(nMinus1_r9[i])    


print "   "
print "   "
print "____________ Hlt N-1 efficiencies: minus sieie  _______________ "
sieie_offl=0
sieie_hlt=0
for i in xrange(4):
    h_nMin1_sieie_offl = f.Get("h_nMin1_sieie_offl_cat"+str(i))
    h_nMin1_sieie_hlt = f.Get("h_nMin1_sieie_hlt_cat"+str(i))
    sieie_offl+=h_nMin1_sieie_offl.GetEntries()
    sieie_hlt+=h_nMin1_sieie_hlt.GetEntries()
    nMinus1_sieie[i]=h_nMin1_sieie_hlt.GetEntries()/h_nMin1_sieie_offl.GetEntries()
    print "_Cat_"+str(i)+"__passing minus SIEIE = %4i"%(h_nMin1_sieie_offl.GetEntries()),"__ plus Hlt %4i"%(h_nMin1_sieie_hlt.GetEntries()),"__ hlt Eff = %1.3f"%(nMinus1_sieie[i])  

print "   "
print "   "
print "____________ Hlt N-1 efficiencies: minus phoIso  _______________ "
phoIso_offl=0
phoIso_hlt=0
for i in xrange(4):
    h_nMin1_phoIso_offl = f.Get("h_nMin1_phoIso_offl_cat"+str(i))
    h_nMin1_phoIso_hlt = f.Get("h_nMin1_phoIso_hlt_cat"+str(i))
    phoIso_offl+=h_nMin1_phoIso_offl.GetEntries()
    phoIso_hlt+=h_nMin1_phoIso_hlt.GetEntries()
    nMinus1_phoIso[i]=h_nMin1_phoIso_hlt.GetEntries()/h_nMin1_phoIso_offl.GetEntries()
    print "_Cat_"+str(i)+"__passing minus PHOISO = %4i"%(h_nMin1_phoIso_offl.GetEntries()),"__ plus Hlt %4i"%(h_nMin1_phoIso_hlt.GetEntries()),"__ hlt Eff = %1.3f"%(nMinus1_phoIso[i])    


print "   "
print "   "
print "____________ Hlt N-1 efficiencies: minus chIso  _______________ "
chIso_offl=0
chIso_hlt=0
for i in xrange(4):
    h_nMin1_chIso_offl = f.Get("h_nMin1_chIso_offl_cat"+str(i))
    h_nMin1_chIso_hlt = f.Get("h_nMin1_chIso_hlt_cat"+str(i))
    chIso_offl+=h_nMin1_chIso_offl.GetEntries()
    chIso_hlt+=h_nMin1_chIso_hlt.GetEntries()
    nMinus1_chIso[i]=h_nMin1_chIso_hlt.GetEntries()/h_nMin1_chIso_offl.GetEntries()
    print "_Cat_"+str(i)+"__passing minus CHISO = %4i"%(h_nMin1_chIso_offl.GetEntries()),"__ plus Hlt %4i"%(h_nMin1_chIso_hlt.GetEntries()),"__ hlt Eff = %1.3f"%(nMinus1_chIso[i])  


print "   "
print "   "
print "____________ Hlt N-1 efficiencies: minus mass  _______________ "
mass_offl=0
mass_hlt=0
for i in xrange(4):
    h_nMin1_mass_offl = f.Get("h_nMin1_mass_offl_cat"+str(i))
    h_nMin1_mass_hlt = f.Get("h_nMin1_mass_hlt_cat"+str(i))
    mass_offl+=h_nMin1_mass_offl.GetEntries()
    mass_hlt+=h_nMin1_mass_hlt.GetEntries()
    nMinus1_mass[i]=h_nMin1_mass_hlt.GetEntries()/(h_nMin1_mass_offl.GetEntries())
    print "_Cat_"+str(i)+"__passing minus MASS = %4i"%(h_nMin1_mass_offl.GetEntries()),"__ plus Hlt %4i"%(h_nMin1_mass_hlt.GetEntries()),"__ hlt Eff = %1.3f"%(nMinus1_mass[i])  





can = ROOT.TCanvas("Plots","Plots")
h_nVtx_tot = f.Get("h_nVtx_tot")
h_nVtx_offl = f.Get("h_nVtx_offl")
eff_nVtx = ROOT.TEfficiency(h_nVtx_offl,h_nVtx_tot);
eff_nVtx.Draw();
eff_nVtx.SetMarkerStyle(20)
eff_nVtx.SetMarkerSize(0.5)
eff_nVtx.SetMarkerColor(ROOT.kBlue)
eff_nVtx.SetLineWidth(1)
eff_nVtx.SetLineColor(4)
can.SaveAs("testPlots/preseleff_nVtx.pdf")


can = ROOT.TCanvas("Plots","Plots")
h_nVtx_hlt = f.Get("h_nVtx_hlt")
h_nVtx_offl = f.Get("h_nVtx_offl")
h_nVtx_offl.GetYaxis().SetTitle("Efficiency")
eff_hlt_nVtx = ROOT.TEfficiency(h_nVtx_hlt,h_nVtx_offl);
eff_hlt_nVtx.Draw();
eff_hlt_nVtx.SetMarkerStyle(20)
eff_hlt_nVtx.SetMarkerSize(0.5)
eff_hlt_nVtx.SetMarkerColor(ROOT.kBlue)
eff_hlt_nVtx.SetLineWidth(1)
eff_hlt_nVtx.SetLineColor(4)
can.SaveAs("testPlots/hlteff_nVtx.pdf")







print " ------------- Efficiencies ----------- "


