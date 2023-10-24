from django.shortcuts import render
from django.contrib.auth.decorators import login_required
from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt
from django.http import HttpResponse
from .models import LecturaTemperatura


def index_view(request):
    return render(request, 'heat/index.html')

@login_required
def dashboard_view(request):
    return render(request, 'heat/dashboard.html')

@csrf_exempt
def en_vivo(request):
    if request.method == 'POST':
        nodo = request.POST.get('nodo')
        temperatura = request.POST.get('temperatura')
        
        # Guardar en la base de datos
        lectura = LecturaTemperatura.objects.create(nodo=nodo, temperatura=temperatura)
        
        # Imprimir mensaje en la consola del servidor Django
        print(f"Guardado en la base de datos: Nodo {nodo}, Temperatura {temperatura}")
        
        return HttpResponse("Datos guardados en la base de datos.")
    else:
        return HttpResponse("Método no permitido.")
    
def lecturas_view(request):
    if request.method == 'POST':
        if 'guardar' in request.POST:
            # Guardar una nueva lectura
            nueva_lectura = LecturaTemperatura(nodo=1, temperatura=27.75)  # Ejemplo de datos
            nueva_lectura.save()
            print(f"Guardado en la base de datos: Nodo {nueva_lectura.nodo}, Temperatura {nueva_lectura.temperatura}°C")
        elif 'detener' in request.POST:
            # Detener la lectura (puedes agregar código para detener tu lectura aquí)
            pass

    lecturas = LecturaTemperatura.objects.all()
    return render(request, 'heat/lecturas.html', {'lecturas': lecturas})