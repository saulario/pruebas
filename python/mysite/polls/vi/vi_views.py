from django.shortcuts import render
from django.contrib.auth.decorators import login_required

import logging

logger = logging.getLogger(__name__)

@login_required(login_url='/polls')
def index(request):
    logger.info("-----> Inicio", "args", extra = {"user": request.user})
    context = {}
    return render(request, 'polls/vi/index.xhtml', context)

