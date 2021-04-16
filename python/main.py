#!/usr/bin/python
# -*- coding:utf-8 -*-

import time
import ADS1256
import DAC8532
import RPi.GPIO as GPIO
from concurrent import futures
import logging
import threading
import grpc
import motioncontroller_pb2
import motioncontroller_pb2_grpc

class Greeter (motioncontroller_pb2_grpc.DeviceService):
    def SayHello(self, request, context):
        return motioncontroller_pb2.HelloReply(message = 'Test %s!' % request.name)

def mcserver():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    motioncontroller_pb2_grpc.add_DeviceServiceServicer_to_server(Greeter(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    server.wait_for_termination()

try:
    ADC = ADS1256.ADS1256()
    DAC = DAC8532.DAC8532()
    ADC.ADS1256_init()
    serverThread = threading.Thread(target=mcserver)
    serverThread.start()
    logging.basicConfig()
    DAC.DAC8532_Out_Voltage(0x30, 3)
    DAC.DAC8532_Out_Voltage(0x34, 3)
    while(1):
        ADC_Value = ADC.ADS1256_GetAll()
        print ("0 ADC = %lf"%(ADC_Value[0]*5.0/0x7fffff))
        print ("1 ADC = %lf"%(ADC_Value[1]*5.0/0x7fffff))
        print ("2 ADC = %lf"%(ADC_Value[2]*5.0/0x7fffff))
        print ("3 ADC = %lf"%(ADC_Value[3]*5.0/0x7fffff))
        print ("4 ADC = %lf"%(ADC_Value[4]*5.0/0x7fffff))
        print ("5 ADC = %lf"%(ADC_Value[5]*5.0/0x7fffff))
        print ("6 ADC = %lf"%(ADC_Value[6]*5.0/0x7fffff))
        print ("7 ADC = %lf"%(ADC_Value[7]*5.0/0x7fffff))

        temp = (ADC_Value[0]>>7)*5.0/0xffff
        print ("DAC :",temp)
        print ("\33[10A")
        DAC.DAC8532_Out_Voltage(DAC8532.channel_A, temp / 10.0)
        DAC.DAC8532_Out_Voltage(DAC8532.channel_B, 3.3 - temp)

except :
    GPIO.cleanup()
    print ("\r\nProgram end     ")
    exit()
