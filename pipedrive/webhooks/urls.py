from django.urls import path

from . import views

app_name = 'webhooks'

urlpatterns = [
        path('', views.dispatch, name='dispatch'),
        path('basic', views.basic, name='basic'),
]