# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models

class Question(models.Model):
    question_text = models.CharField(max_length=200)
    pub_date = models.DateTimeField('date published')
    
    def __str__(self):
        return self.question_text


class Choice(models.Model):
    question = models.ForeignKey(Question, on_delete=models.CASCADE)
    choice_text = models.CharField(max_length=200)
    votes = models.IntegerField(default=0)
    
    def __str__(self):
        return self.choice_text
    
class Cur(models.Model):
    curcod = models.CharField(max_length=3, primary_key=True)
    curinu = models.IntegerField(default=0)
    curnom = models.CharField(max_length=80)
    curdec = models.IntegerField(default=0)
    
    def __str__(self):
        return '%s %s' % (self.curcod, self.curnom)
    

class Lng(models.Model):
    lngcod = models.CharField(max_length=2, primary_key=True)
    lngnom = models.CharField(max_length=80)    
    
    def __str__(self):
        return '%s %s' % (self.lngcod, self.lngnom)
    
class Pai(models.Model):
    paicod = models.CharField(max_length=2, primary_key=True)
    paiia3 = models.CharField(max_length=3, blank=True)
    paiinu = models.IntegerField(default=0)
    paifps = models.CharField(max_length=2, blank=True)
    painom = models.CharField(max_length=80)    
    
    def __str__(self):
        return '%s %s' % (self.paicod, self.painom)
    
class Cyp(models.Model):
    cypcod = models.BigIntegerField(primary_key=True)
    cypnom = models.CharField(max_length=80, default='')    
    cypnif = models.CharField(max_length=20, default='')
    cyplngcod = models.ForeignKey('Lng', on_delete=models.PROTECT, null=True, db_column='cyplngcod')
    cyppaicod = models.ForeignKey('Pai', on_delete=models.PROTECT, null=True, db_column='cyppaicod')
    cypcurcod = models.ForeignKey('Cur', on_delete=models.PROTECT, null=True, db_column='cypcurcod')
    cypobs = models.CharField(max_length=80, default='', blank=True)
    
    def __str__(self):
        return '%s %s %s' % (self.cypcod, self.cypnom, self.cypnif)
    
class Reg(models.Model):
    regcod = models.BigIntegerField(primary_key=True)
    regkey = models.CharField(max_length=80, unique=True)
    regtxt = models.TextField(blank=True)
    
    def __str__(self):
        return '%s %s %s' % (self.regcod, self.regkey, self.regtxt)    
    
class Ser(models.Model):
    sercod = models.CharField(max_length=10, primary_key=True)
    serval = models.BigIntegerField(default=0)
        
    

