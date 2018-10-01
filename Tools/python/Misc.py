#!/usr/bin/env python
'''@package docstring
Some common python functions
'''

from re import sub
from sys import stdout,stderr
from os import getenv
from PandaCore.Utils.logging import logger

def tAND(s1,s2):
    ''' ANDs two strings '''
    if s1 and s2:
        return "(( "+s1+" ) && ( "+s2+" ))"
    if not s1:
        return s2
    if not s2:
        return s1

def tOR(s1,s2):
    ''' ORs two strings'''
    if s1 and s2:
        return "(( "+s1+" ) || ( "+s2+" ))"
    if not s1:
        return s2
    if not s2:
        return s1

def tTIMES(w,s):
    ''' MULTIPLIES two strings'''
    if w and s:
        return "( "+w+" ) * ( "+s+" )"
    if not w:
        return s
    if not s:
        return w

def tNOT(w):
    ''' NOTs two strings'''
    return '!( '+w+' )'

def removeCut(basecut,var):
    '''
    Removes the dependence on a particular variable from a formula

    @type basecut: str
    @param basecut: Input formula to modify

    @type var: str
    @param var: Variable to remove from basecut

    @rtype: string
    @return: Returns a formula with the var dependence removed
    '''
    return sub('[0-9\.]*[=<>]*%s'%(var.replace('(','\(').replace(')','\)')),
               '1==1',
                 sub('%s[=<>]+[0-9\.]+'%(var.replace('(','\(').replace(')','\)')),
                     '1==1',
                     basecut)
                 )
