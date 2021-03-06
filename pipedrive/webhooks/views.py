from django.contrib.auth import authenticate
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt

import base64
import json
import pprint

def autorizado(request):
    if not 'HTTP_AUTHORIZATION' in request.META:
        return False

    auth = request.META['HTTP_AUTHORIZATION'].split()
    if len(auth) != 2:
        return False
    
    if auth[0].lower() != 'basic':
        return False
    
    if len(auth[1]) == 0:
        return False
    
    cdn = base64.b64decode(auth[1]).decode('utf-8')
    u, p = cdn.split(':', 1)
    
    user = authenticate(request, username=u, password=p)   
    if user is None:
        return False
    
    return True

def basic(request):
    response = None
    if not autorizado(request):
        response = HttpResponse('Not authorized')
        response.status_code = 401
        response['WWW-Authenticate'] = 'Basic realm=webhooks'
    else:
        response = HttpResponse('OK')
        
    return response

@csrf_exempt
def dispatch(request):
    response = None
    if not autorizado(request):
        response = HttpResponse('Not authorized')
        response.status_code = 401
        response['WWW-Authenticate'] = 'Basic realm=webhooks'
    else:
        pprint.pprint(json.loads(request.body.decode('utf-8')))
        response = HttpResponse('OK')
        
    return response