from django.conf.urls import patterns, include, url
from mysite.view import index

# Uncomment the next two lines to enable the admin:
# from django.contrib import admin
# admin.autodiscover()

urlpatterns = patterns('',
    (r'^search$', index),
    (r'^(?P<path>.*)','django.views.static.serve',{'document_root':''}), 
)
