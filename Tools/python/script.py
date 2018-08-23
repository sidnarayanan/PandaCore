import sys 
from os import environ, getenv 
from argparse import ArgumentParser
from array import array 

parser = ArgumentParser()
STORE_TRUE = {'action':'store_true'}
STORE_FALSE = {'action':'store_false'}
MANY = {'nargs':'+'}
def parse(*args):
    for a in args:
        if type(a) == tuple:
            parser.add_argument(a[0], **a[1])
        else:
            parser.add_argument(a)
    return parser.parse_args()


from PandaCore.Utils.load import * 
from PandaCore.Tools.Misc import * 

_env_vars = ['PANDA_FLATDIR', 'SUBMIT_OUTDIR', 'SUBMIT_LOGDIR',
             'SUBMIT_WORKDIR', 'SUBMIT_NAME', 'SUBMIT_USER',
             'CMSSW_BASE', 'SUBMIT_REPORT']
def validate_env(v=_env_vars):
    missing = [vv for vv in v if vv not in environ]
    if len(missing) > 0:
        logger.error('validate_env', 'missing: %s'%(repr(missing)))
        raise RuntimeError('')

flatdir = getenv('PANDA_FLATDIR')
cmssw_base = getenv('CMSSW_BASE')
