#!/usr/bin/env python
'''@package docstring
Just a giant list of processes and properties
'''

from processes import * 

l = [data, BSM, SM, variations]
processes = {}
for d in l:
    processes.update(d)


if __name__=='__main__':
    import pprint
    pp = pprint.PrettyPrinter(width=160)
    for d in l:
        print 
        pp.pprint(d)
