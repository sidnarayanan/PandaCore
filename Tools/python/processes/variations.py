import SM 

htbins = [300, 500, 700, 1000, 1500, 2000, 'Inf']
htbins = map(str, htbins)
variations = ['ISRRenorm', 'FSRRenorm', 'ISRFact', 'FSRFact', 'MPI']
_variations = ['Nominal']
_variations += [x + 'Up' for x in variations]
_variations += [x + 'Down' for x in variations]

processes = {}
for bins in zip(htbins[:-1],htbins[1:]):
    name = 'QCD_HT%sto%s'%bins 
    xsec = SM.processes[name+'_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'][-1]
    for v in _variations:
        vname = name + '_' + v
        processes[vname] = (vname, 'MC', xsec)
