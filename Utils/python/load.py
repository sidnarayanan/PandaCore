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
    return root.gSystem.Load(libpath)


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
    else:
        requested_lib = Library(request, [])

    if requested_lib in _loaded:
        if DEBUG:
            logger.warning('PandaCore.Utils.load','Requested %s has already been loaded in %s'%(request, requested_lib.name))
        return

    if not requested_lib:
        logger.error('PandaCore.Utils.load','Could not understand lib %s'%request)
        raise Exception('LoadError')

    r = 0
    for d in requested_lib.deps:
        if 'CMSSW' in d:
            r = max(r, load_lib(d))
        else:
            r = max(r, load_lib('lib'+d+'.so'))

    _loaded.append(requested_lib)
    r = max(r, load_lib('lib'+requested_lib.name+'.so'))

    if r != 0:
        logger.error('PandaCore.Utils.load', 'Could not load lib %s, error code=%i'%(requested_lib.name, r))
        raise Exception('LoadError')

load = Load 
