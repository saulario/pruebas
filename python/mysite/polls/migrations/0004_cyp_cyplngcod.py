# -*- coding: utf-8 -*-
# Generated by Django 1.11 on 2017-04-25 21:09
from __future__ import unicode_literals

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('polls', '0003_remove_cyp_cyplngcod'),
    ]

    operations = [
        migrations.AddField(
            model_name='cyp',
            name='cyplngcod',
            field=models.ForeignKey(db_column='cyplngcod', null=True, on_delete=django.db.models.deletion.PROTECT, to='polls.Lng'),
        ),
    ]
