import numpy as np
import paho.mqtt.client as mqtt
import json

#Thingsboard acces data
TOKEN = "ATOKEN-TESTING"
#ThingsBoard server instance.
THINGSBOARD_SERVER  = "multiaire.smartaraucania.org"
try:
    client = mqtt.Client(client_id="db792980-020b-11ed-aa0a-aff9614719fc")
    client.connect(THINGSBOARD_SERVER, 1883, 60)
    print("conexion exitosa")

except:
    print("fallo")



