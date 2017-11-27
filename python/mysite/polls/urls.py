from django.conf.urls import url, include

from . import views
from .vi import vi_views 

app_name='polls'
urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^welcome$', views.welcome, name='welcome'),
    
    
    
    url(r'^login$', views.my_login, name='login'),
    url(r'^logout$', views.my_logout, name='logout'),
    
    #url(r'^(?P<pk>[0-9]+)/$', views.DetailView.as_view(), name='detail'),
    #url(r'^(?P<pk>[0-9]+)/results/$', views.ResultsView.as_view(), name='results'),
    #url(r'^(?P<question_id>[0-9]+)/vote/$', views.vote, name='vote'),
    #url(r'^index1/$', views.index1, name='index1'),
    
    url(r'^vi/$', vi_views.index, name='index'),
    
]