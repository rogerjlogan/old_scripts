DCTableOpen(TItimingHVDCTable);
DCTableNoCheck(false);
DCSetInput(TRIGGERINS,v[viltrigger1090HV],v[vihtrigger1090HV],v[vitl],v[vith]);
DCSetInput(NBIO,v[vil1090HV],v[vih1090HV],v[vitl],v[vith]);
DCSetInput(MPNMC,v[vil1090HV],v[vih1090HV],v[vitl],v[vith]);
if not PinListElement(READY,NODEVINS)then
DCSetInput(READY,v[vil1090HV],v[vih1090HV],v[vitl],v[vith]);
if not PinListElement(NHOLD,NODEVINS)then
DCSetInput(NHOLD,v[vil1090HV],v[vih1090HV],v[vitl],v[vith]);
DCSetInput(X2CLKIN,v[vilclkin1090HV],v[vihclkin1090HV],v[vitl],v[vith]);
DCSetInput(SPINS,v[vil1090HV],v[vih1090HV],v[vitl],v[vith]);
if HPIM then
DCSetInput(HPIINS,v[vil1090HV],v[vih1090HV],v[vitl],v[vith]);
DCSetInput(TRST,v[vil1090HV],v[vih1090HV],v[vitl],v[vith]);
DCSetInput(TMS,v[vil1090HV],v[vih1090HV],v[vitl],v[vith]);
DCSetInput(TCK,v[vil1090HV],v[vih1090HV],v[vitl],v[vith]);
DCSetInput(TDI,v[vil1090HV],v[vih1090HV],v[vitl],v[vith]);
if not PinListElement(NHOLDA,NODEVOUTS)then
DCSetOutput(NHOLDA,v[vohabus1090VV],v[voh1090HV],v[vload1090HV],i[iol1090HV],i[ioh1090HV]);
if not PinListElement(X1,NODEVOUTS)then
DCSetOutput(X1,v[vol1090HV],v[voh1090HV],v[vload1090HV],i[iol1090HV],i[ioh1090HV]);
DCSetOutput(ABUS,v[volabus1090HV],v[vohabus1090HV],v[vload1090HV],i[iolabus1090HV],i[iohabus1090HV]);
DCSetOutput(RNW,v[vohabus1090VV],v[vohctrl1090HV],v[vload1090HV],i[iol1090HV],i[ioh1090HV]);
DCSetOutput(NIOSTRB,v[volctrl1090HV],v[vohctrl1090HV],v[vload1090HV],i[iol1090HV],i[ioh1090HV]);
if not PinListElement(NIAQ,NODEVOUTS)then
DCSetOutput(NIAQ,v[vohabus1090VV],v[vohctrl1090HV],v[vload1090HV],i[iol1090HV],i[ioh1090HV]);
if not PinListElement(NIACK,NODEVOUTS)then
DCSetOutput(NIACK,v[vol1090HV],v[voh1090HV],v[vload1090HV],i[iol1090HV],i[ioh1090HV]);
DCSetOutput(XF,v[vol1090HV],v[voh1090HV],v[vload1090HV],i[iol1090HV],i[ioh1090HV]);
DCSetOutput(CLKOUT,v[volclkout1090HV],v[vohclkout1090HV],v[vload1090HV],i[iolclkout1090HV],i[ioh1090HV]);
DCSetOutput(NMSTRB,v[volctrl1090HV],v[vohctrl1090HV],v[vload1090HV],i[iol1090HV],i[ioh1090HV]);
if not PinListElement(NMSC,NODEVOUTS)then
DCSetOutput(NMSC,v[vol1090HV],v[voh1090HV],v[vload1090HV],i[iol1090HV],i[ioh1090HV]);
DCSetOutput(SPOUTS,v[vol1090HV],v[voh1090HV],v[vload1090HV],i[iol1090HV],i[ioh1090HV]);
if HPIM then
DCSetOutput(HPIOUTS,v[volDX1090HV],v[vohDX1090HV],v[vloadDX1090HV],i[iolDX1090HV],i[iohDX1090HV]);
DCSetOutput(TDO,v[vol1090HV],v[voh1090HV],v[vload1090HV],i[iol1090HV],i[ioh1090HV]);
if not PinListElement(TOUT,NODEVOUTS)then
DCSetOutput(TOUT,v[volrelaxHV2],v[voh1090HV],v[vload1090HV],i[iol1090HV],i[ioh1090HV]);
DCSetIO(DBUS,v[vil1090HV],v[vih1090HV],v[voldbus1090HV],v[vohdbus1090HV],v[vitl],v[vith],v[vload1090HV],i[ioldbus1090HV],i[iohdbus1090HV]);
DCSetIO(SPIOS,v[vil1090HV],v[vih1090HV],v[vol1090HV],v[voh1090HV],v[vitl],v[vith],v[vload1090HV],i[iol1090HV],i[ioh1090HV]);
if HPIM then
DCSetIO(HPIIOS,v[vil1090HV],v[vih1090HV],v[vol1090HV],v[voh1090HV],v[vitl],v[vith],v[vload1090HV],i[iol1090HV],i[ioh1090HV]);
DCSetIO(EMU1,v[vil1090HV],v[vih1090HV],v[vol1090HV],v[voh1090HV],v[vitl],v[vith],v[vload1090HV],i[iol1090HV],i[ioh1090HV]);
DCSetIO(EMU0,v[vil1090HV],v[vih1090HV],v[vol1090HV],v[voh1090HV],v[vitl],v[vith],v[vload1090HV],i[iol1090HV],i[ioh1090HV]);
DCSetInput(NODEVINS,0v,0v,0v,0v);
DCSetOutput(NODEVOUTS,0v,0v,0v,0ma,0ma);
DCSetIO(NODEVIOS,0v,0v,0v,0v,0v,0v,0v,0ma,0ma);
DCTableClose;
