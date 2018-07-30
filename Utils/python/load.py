#!/usr/bin/env python
'''@package docstring
Module that catalogs C++ objects known to ROOT/PandaCore.
Load libraries on-demand
'''

class Library():
    '''Simple class that defines a library'''
    def __init__(self,name,objects,deps=[]):
        self.name = name
        self.objects = objects
        self.deps = deps

_loaded = []
DEBUG = False

libraries = [
    Library(name='PandaCoreUtils', objects = ['Logger']),
    Library(name='PandaCoreTools',      objects = [ 'Functions',
                                                    'Common',
                                                    'TreeTools',
                                                    'DuplicateRemover',
                                                    'Normalizer',
                                                    'Cutter',
                                                    'BranchAdder',
                                                    'EventSyncher',
                                                    'splitPandaExpress'
                                                  ]
           ),
    Library(name='PandaCoreLearning',   objects = [ 'TMVATrainer',
                                                    'TMVABranchAdder',
                                                  ]
           ),
    Library(name='PandaCoreStatistics', objects = [ 'RooExpErf',
                                                  ]
           ),
    Library(name='PandaCoreDrawers',    objects = ['CanvasDrawer',
                                                   'GraphDrawer',
                                                   'GraphErrDrawer',
                                                   'GraphAsymmErrDrawer',
                                                   'HistogramDrawer',
                                                   'PlotUtility',
                                                   'ROCTool',
                                                  ]
           ),
    Library(name='PandaAnalysisFlat',   objects = ['PandaAnalyzer',
                                                   'PandaLeptonicAnalyzer',
                                                   'GenAnalyzer',
                                                   'LimitTreeBuilder',
                                                   'TagAnalyzer',
                                                   'SFTreeBuilder',
                                                   'BTagTreeBuilder',
                                                  ]
           ),
    Library(name='RedPandaCluster',     objects = ['Clusterer',
                                                    'Camera',
                                                    'PFAnalyzer',
                                                   ]
           ),
]

from root import root
from os import getenv
from logging import *

def load_lib(libpath):
    logger.info('PandaCore.Utils.load','Loading %s'%libpath)
    root.gSystem.Load(libpath)


def Load(request):
    '''
    Function that loads any necessary shared object files

    @type request: str
    @param request: Name of library or class
    '''

    requested_lib = None
    for l in libraries:
        if l.name==request or request in l.objects:
            requested_lib = l
            break

    if requested_lib in _loaded:
        if DEBUG:
            logger.warning('PandaCore.Utils.load','Requested %s has already been _loaded in %s'%(request, requested_lib.name))
        return

    if not requested_lib:
        logger.error('PandaCore.Utils.load','Could not load lib %s'%request)
        raise Exception('LoadError')

    for d in requested_lib.deps:
        if 'CMSSW' in d:
            load_lib(d)
        else:
            load_lib('lib'+d+'.so')

    _loaded.append(requested_lib)
    load_lib('lib'+requested_lib.name+'.so')
