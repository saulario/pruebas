# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.contrib.auth import authenticate, login, logout

from django.http import HttpResponse, HttpResponseRedirect
#from django.http import Http404
from django.shortcuts import get_object_or_404
from django.shortcuts import render
from django.shortcuts import reverse
from django.views import generic

from .models import Question, Choice


def index(request):
    context = {}
    return render(request, 'polls/index.xhtml', context)

    
def login(request):
    
    for key in request.POST:
        #print key, ' => ', request.POST[key]
        print key 
    
    
    
    username = request.POST['us']
    password = request.POST['cl']
    
    user = authenticate(request, username=username, password=password)
    if user is not None:
        login(request, user)
    context = {}
    return render(request, 'polls/index.xhtml')

def logout(request):
    logout(request)
    
    context = {}
    return render(request, 'polls/index.xhtml', context)








class IndexView(generic.ListView):
    template_name = 'polls/index.html'
    context_object_name = 'latest_question_list'

    def get_queryset(self):
        return Question.objects.order_by('-pub_date')
    
class DetailView(generic.DetailView):
    model = Question
    template_name = 'polls/detail.html'    

class ResultsView(generic.DetailView):
    model = Question
    template_name = 'polls/results.html'





def index3(request):
    latest_question_list = Question.objects.order_by('-pub_date')[:5]
    context = {
        'latest_question_list': latest_question_list,
    }
    return render(request, 'polls/index.html', context)


def index1(request):
    return render(request, 'polls/index2.html')

def detail(request, question_id):
    question = get_object_or_404(Question, pk=question_id)
    return render(request, 'polls/detail.html', { 'question': question})

def results(request, question_id):
    question = get_object_or_404(Question, pk=question_id)
    return render(request, 'polls/results.html', {'question': question})

def vote(request, question_id):
    question = get_object_or_404(Question, pk=question_id)
    try:
        selected_choice = question.choice_set.get(pk=request.POST['choice'])
    except (KeyError, Choice.DoesNotExist):
        # Redisplay the question voting form.
        return render(request, 'polls/detail.html', {
            'question': question,
            'error_message': "You didn't select a choice.",
        })
    else:
        selected_choice.votes += 1
        selected_choice.save()
        # Always return an HttpResponseRedirect after successfully dealing
        # with POST data. This prevents data from being posted twice if a
        # user hits the Back button.
        return HttpResponseRedirect(reverse('polls:results', args=(question.id,)))