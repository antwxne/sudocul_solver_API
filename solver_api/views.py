from django.http import HttpResponse, HttpRequest
from django.shortcuts import render

def solve(request: HttpRequest) -> HttpResponse:
    return HttpResponse("Hello, world. You're at the polls index.")