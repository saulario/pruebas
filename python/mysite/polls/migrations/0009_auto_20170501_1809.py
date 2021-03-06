# -*- coding: utf-8 -*-
# Generated by Django 1.11 on 2017-05-01 18:09
from __future__ import unicode_literals

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('polls', '0008_reg_ser'),
    ]

    operations = [
        migrations.CreateModel(
            name='Cur',
            fields=[
                ('curcod', models.CharField(max_length=3, primary_key=True, serialize=False)),
                ('curinu', models.IntegerField(default=0)),
                ('curnom', models.CharField(max_length=80)),
                ('curdec', models.IntegerField(default=0)),
            ],
        ),
        migrations.CreateModel(
            name='Pai',
            fields=[
                ('paicod', models.CharField(max_length=2, primary_key=True, serialize=False)),
                ('paiia3', models.CharField(blank=True, max_length=3)),
                ('paiinu', models.IntegerField(default=0)),
                ('paifps', models.CharField(blank=True, max_length=2)),
                ('painom', models.CharField(max_length=80)),
            ],
        ),
        migrations.AddField(
            model_name='cyp',
            name='cypnif',
            field=models.CharField(default='', max_length=20),
        ),
        migrations.AlterField(
            model_name='cyp',
            name='cypnom',
            field=models.CharField(default='', max_length=80),
        ),
        migrations.AddField(
            model_name='cyp',
            name='cypcurcod',
            field=models.ForeignKey(db_column='cypcurcod', null=True, on_delete=django.db.models.deletion.PROTECT, to='polls.Cur'),
        ),
        migrations.AddField(
            model_name='cyp',
            name='cyppaicod',
            field=models.ForeignKey(db_column='cyppaicod', null=True, on_delete=django.db.models.deletion.PROTECT, to='polls.Pai'),
        ),
    ]
