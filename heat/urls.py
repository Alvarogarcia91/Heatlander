from django.urls import path
from . import views
from django.contrib.auth import views as auth_views
from django.urls import path, include
from django.shortcuts import redirect

urlpatterns = [
    path('', views.index_view, name='index'),
    path('dashboard/', views.dashboard_view, name='dashboard'),
    # Otras URLs específicas de la aplicación "Heat"

    path('login/', auth_views.LoginView.as_view(), name='login'),
    path('logout/', auth_views.LogoutView.as_view(), name='logout'),
    path('en_vivo/', views.en_vivo, name='en_vivo'),
    path('lecturas/', views.lecturas_view, name='lecturas'),
    
]