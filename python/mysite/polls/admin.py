# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.contrib import admin

# Register your models here.

from .models import *

admin.site.register(Choice)
admin.site.register(Question)

admin.site.register(Cur)
admin.site.register(Lng)
admin.site.register(Pai)
admin.site.register(Cyp)
admin.site.register(Reg)
admin.site.register(Ser)