from django.db import models


class LecturaTemperatura(models.Model):
    nodo = models.IntegerField()
    temperatura = models.FloatField()

    def __str__(self):
        return f"Nodo {self.nodo} - Temperatura: {self.temperatura}°C"